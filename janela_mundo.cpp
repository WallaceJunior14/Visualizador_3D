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
    double xw_min = minW.obterX();
    double yw_min = minW.obterY();
    double xw_max = maxW.obterX();
    double yw_max = maxW.obterY();

    if (xw_max == xw_min || yw_max == yw_min) {
        qWarning("JanelaMundo: Largura ou altura da janela é zero. Retornando matriz identidade.");
        return Matriz::identidade(3);
    }

    double sx = (ndcXMax - ndcXMin) / (xw_max - xw_min);
    double sy = (ndcYMax - ndcYMin) / (yw_max - yw_min);
    double tx = ndcXMin - xw_min * sx;
    double ty = ndcYMin - yw_min * sy;

    Matriz escalaTranslacao = Matriz::identidade(3);
    escalaTranslacao(0,0) = sx; escalaTranslacao(0,2) = tx;
    escalaTranslacao(1,1) = sy; escalaTranslacao(1,2) = ty;

    double cx = (xw_min + xw_max) / 2.0;
    double cy = (yw_min + yw_max) / 2.0;
    double theta = -anguloRotacao * M_PI / 180.0;

    Matriz T1 = Matriz::translacao(-cx, -cy);
    Matriz R = Matriz::rotacao(theta);
    Matriz T2 = Matriz::translacao(cx, cy);
    Matriz rotacaoCentro = T2 * R * T1;

    Matriz normalizacao = escalaTranslacao * rotacaoCentro;
    return normalizacao;
}

