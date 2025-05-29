#include "janela_mundo.h"
#include <algorithm> // Para std::min, std::max
#include <cmath>     // Para M_PI, cos, sin em rotação
#include <QDebug>    // Para qWarning

JanelaMundo::JanelaMundo(const QString& nomeJanela, double xMin, double yMin, double xMax, double yMax)
    : nome(nomeJanela), minW(xMin, yMin), maxW(xMax, yMax), anguloRotacao(0.0) {
    if (xMin >= xMax || yMin >= yMax) {
        qWarning("JanelaMundo: Coordenadas mínimas devem ser menores que as máximas. Ajustando para default.");
        minW.definirX(-1.0); minW.definirY(-1.0);
        maxW.definirX(1.0);  maxW.definirY(1.0);
    }
}

QString JanelaMundo::obterNome() const {
    return nome;
}

void JanelaMundo::definirNome(const QString& novoNome) {
    nome = novoNome;
}

void JanelaMundo::zoom(double fator) {
    if (fator <= 0.01) fator = 0.01; // Evitar zoom zero ou negativo

    double centroX = (minW.obterX() + maxW.obterX()) / 2.0;
    double centroY = (minW.obterY() + maxW.obterY()) / 2.0;
    double larguraAtual = obterLargura();
    double alturaAtual = obterAltura();

    double novaLargura = larguraAtual / fator;
    double novaAltura = alturaAtual / fator;

    minW.definirX(centroX - novaLargura / 2.0);
    maxW.definirX(centroX + novaLargura / 2.0);
    minW.definirY(centroY - novaAltura / 2.0);
    maxW.definirY(centroY + novaAltura / 2.0);
}

void JanelaMundo::deslocar(double dx, double dy) {
    minW.definirX(minW.obterX() + dx);
    maxW.definirX(maxW.obterX() + dx);
    minW.definirY(minW.obterY() + dy);
    maxW.definirY(maxW.obterY() + dy);
}

// Método para rotação (simplificado, apenas armazena o ângulo)
void JanelaMundo::rotacionar(double deltaAnguloGraus) {
    anguloRotacao += deltaAnguloGraus;
    // A normalização precisaria usar this->anguloRotacao
    qDebug() << "JanelaMundo '" << nome << "' rotacionada para " << anguloRotacao << " graus (lógica de matriz de normalização pendente).";
}

void JanelaMundo::definirLimites(double xMin, double yMin, double xMax, double yMax) {
    if (xMin >= xMax || yMin >= yMax) {
        qWarning("JanelaMundo::definirLimites: Coordenadas mínimas devem ser menores que as máximas.");
        return;
    }
    minW.definirX(xMin);
    minW.definirY(yMin);
    maxW.definirX(xMax);
    maxW.definirY(yMax);
}

Ponto2D JanelaMundo::obterMin() const {
    return minW;
}

Ponto2D JanelaMundo::obterMax() const {
    return maxW;
}

double JanelaMundo::obterLargura() const {
    return maxW.obterX() - minW.obterX();
}

double JanelaMundo::obterAltura() const {
    return maxW.obterY() - minW.obterY();
}

Matriz JanelaMundo::obterMatrizNormalizacao() const {
    Matriz norm = Matriz::identidade(3);
    double xw_min = minW.obterX();
    double yw_min = minW.obterY();
    double xw_max = maxW.obterX();
    double yw_max = maxW.obterY();

    if (xw_max == xw_min || yw_max == yw_min) {
        qWarning("JanelaMundo: Largura ou altura da janela é zero. Retornando matriz identidade.");
        return Matriz::identidade(3);
    }

    // Se anguloRotacao != 0, a matriz de normalização precisaria incluir
    // uma rotação inversa em torno do centro da JanelaMundo ANTES da translação/escala.
    // Exemplo conceitual: M_norm = M_escala_para_NDC * M_trans_para_origem_NDC * R(-anguloRotacao, centro_janela_mundo) * T(-centro_janela_mundo)
    // Isso é uma simplificação e a implementação correta é mais envolvida.
    // Por agora, a rotação não afetará a matriz.

    double sx = (ndcXMax - ndcXMin) / (xw_max - xw_min);
    double sy = (ndcYMax - ndcYMin) / (yw_max - yw_min);

    double tx = ndcXMin - xw_min * sx;
    double ty = ndcYMin - yw_min * sy;

    norm(0,0) = sx; norm(0,2) = tx;
    norm(1,1) = sy; norm(1,2) = ty;

    return norm;
}
