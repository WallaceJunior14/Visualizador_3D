#include "circunferencia_obj.h"
#include "bounding_box.h"
#include <cmath>
#include <QRect> // <-- ADICIONADO
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Construtor e Setters/Getters não precisam de alteração.
// A lógica de chamar gerarPontosAproximacao() está correta.
CircunferenciaObj::CircunferenciaObj(const QString& nome, const Ponto3D& centro, double raio,
                                     const Ponto3D& normal, const QColor& cor)
    : ObjetoGrafico(nome, TipoObjeto::CIRCUNFERENCIA),
    centroOriginal_m(centro),
    raioOriginal_m(raio),
    normal_m(normal.normalizarVetor()) {
    definirCor(cor);
    gerarPontosAproximacao();
}

Ponto3D CircunferenciaObj::obterCentroOriginal() const { return centroOriginal_m; }
double CircunferenciaObj::obterRaioOriginal() const { return raioOriginal_m; }
Ponto3D CircunferenciaObj::obterNormal() const { return normal_m; }

void CircunferenciaObj::definirCentroOriginal(const Ponto3D& novoCentro) {
    centroOriginal_m = novoCentro;
    gerarPontosAproximacao();
}

void CircunferenciaObj::definirRaioOriginal(double novoRaio) {
    if (novoRaio > 0) {
        raioOriginal_m = novoRaio;
        gerarPontosAproximacao();
    }
}

void CircunferenciaObj::definirNormal(const Ponto3D& novaNormal) {
    normal_m = novaNormal.normalizarVetor();
    gerarPontosAproximacao();
}

/*Ponto3D casteljau(QList<Ponto3D> pontosControle, double i){
    QList<Ponto3D> pontosAtuais = pontosControle;
    int n = pontosAtuais.size() - 1;

    for (int j = 1; j <= n; ++j) {
        for (int k = 0; k <= (n - j); ++k) {
            //pontosAtuais[k] = pontosAtuais[k] * (1.0 - i) + pontosAtuais[k+1] * i;
            pontosAtuais[k] = (pontosAtuais[k] + pontosAtuais[k+1]) / 2;
        }
    }
    return pontosAtuais[0];
}*/

QList<Ponto3D> CircunferenciaObj::casteljau(QList<Ponto3D> controlPoints, QList<Ponto3D> allMidpoints) {
    Ponto3D vetorCentroPonto;

    // Adiciona os pontos do nível atual (exceto o último nível que será o ponto final)
    if (controlPoints.size() > 1) {
        for (const Ponto3D& pt : controlPoints) {
            allMidpoints.push_back(pt);
        }
    }

    // Caso base: Se houver apenas um ponto de controle, ele é o ponto final da recursão.
    if (controlPoints.size() == 1) {
        allMidpoints.push_back(controlPoints.first()); // Adiciona o ponto final também
        return allMidpoints; // Retorna o ponto final da recursão
    }

    // Passo recursivo: Crie um novo conjunto de pontos interpolados usando o ponto médio
    QList<Ponto3D> newPoints;
    for (int i = 0; i < (controlPoints.size()-1); i++) {
        Ponto3D p1 = controlPoints[i];
            Ponto3D p2 = controlPoints[i+1];
            Ponto3D interpolatedPoint = (p1 + p2) / 2.0; // Interpolação fixa em t=0.5
            newPoints.push_back(interpolatedPoint);
            i = controlPoints.size()-1;
    }

    // Chame a função recursivamente com o novo conjunto de pontos
    return casteljau(newPoints, allMidpoints);
}

// --- IMPLEMENTAÇÃO DOS MÉTODOS VIRTUAIS ---

/**
 * @brief Implementação corrigida da função 'desenhar'.
 * A lógica é idêntica à de um Polígono, desenhando as linhas entre os pontos da aproximação.
 */
void CircunferenciaObj::desenhar(QPainter* painter, const QRect& viewport) const {
    if (pontosClip.size() < 2) {
        return;
    }
    painter->setPen(obterCor());

    // Função auxiliar para mapear NDC para a tela
    auto mapearNdcParaTela = [&](const Ponto3D& p_ndc) {
        double x_norm = (p_ndc.obterX() + 1.0) / 2.0;
        double y_norm = (1.0 - p_ndc.obterY()) / 2.0; // Inverte Y
        double x_tela = viewport.x() + x_norm * viewport.width();
        double y_tela = viewport.y() + y_norm * viewport.height();
        return QPoint(static_cast<int>(x_tela), static_cast<int>(y_tela));
    };

    for (int i = 0; i < pontosClip.size(); ++i) {
        const Ponto3D& p1_ndc = pontosClip.at(i);
        const Ponto3D& p2_ndc = pontosClip.at((i + 1) % pontosClip.size()); // Fecha o ciclo
        QPoint p1_tela = mapearNdcParaTela(p1_ndc);
        QPoint p2_tela = mapearNdcParaTela(p2_ndc);
        painter->drawLine(p1_tela, p2_tela);
    }
}

/**
 * @brief Implementação de 'obterBBox'.
 * (Nenhuma alteração necessária, já estava correta)
 */
BoundingBox CircunferenciaObj::obterBBox() const {
    if (obterPontosOriginaisMundo().isEmpty()) {
        return BoundingBox();
    }
    const Matriz& matObjeto = obterMatrizTransformacao();
    BoundingBox bbox(matObjeto * obterPontosOriginaisMundo().first());
    for (int i = 1; i < obterPontosOriginaisMundo().size(); ++i) {
        bbox.expandir(matObjeto * obterPontosOriginaisMundo().at(i));
    }
    return bbox;
}

/**
 * @brief Implementação otimizada de 'calcularCentroGeometrico'.
 */
Ponto3D CircunferenciaObj::calcularCentroGeometrico() const {
    // Retornar o centro real é mais preciso e muito mais rápido
    // do que calcular a média dos pontos da aproximação.
    return obterCentroOriginal();
}


// <-- REMOVIDO: A implementação de CircunferenciaObj::recalcularPontos foi deletada.


/**
 * @brief Geração dos pontos de aproximação.
 * (Nenhuma alteração necessária, a lógica é interna e está correta)
 */
void CircunferenciaObj::gerarPontosAproximacao() {
    Ponto3D n = normal_m;

    Ponto3D u;
    if (std::abs(n.obterY()) < 0.99) {
        u = Ponto3D::produtoVetorial(Ponto3D(0, 1, 0), n).normalizarVetor();
    } else {
        u = Ponto3D::produtoVetorial(n, Ponto3D(1, 0, 0)).normalizarVetor();
    }
    Ponto3D v = Ponto3D::produtoVetorial(n, u);

    QList<Ponto3D> pontosAprox;
    int numSegmentos = 72;
    for (int i = 0; i < numSegmentos; ++i) {
        double angulo = 2.0 * M_PI * static_cast<double>(i) / numSegmentos;
        double cosA = std::cos(angulo);
        double sinA = std::sin(angulo);
        Ponto3D ponto = centroOriginal_m + (u * (raioOriginal_m * cosA)) + (v * (raioOriginal_m * sinA));
        pontosAprox.append(ponto);
    }

    QList<Ponto3D> vetor;
    QList<Ponto3D> novosPontos = casteljau(pontosAprox, vetor);

    //definirPontosOriginaisMundo(pontosAprox);
    definirPontosOriginaisMundo(novosPontos);

    int i = 0;
    for (i;i<pontosAprox.size()-1;i++){
        printf("\nComparando %f com %f", pontosAprox[i].obterX(), pontosAprox[pontosAprox.size()-1-i].obterX());
    }
}
