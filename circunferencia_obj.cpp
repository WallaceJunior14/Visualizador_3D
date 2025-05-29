#include "circunferencia_obj.h"
#include <cmath> // Para M_PI, cos, sin

CircunferenciaObj::CircunferenciaObj(const QString& nome, const Ponto2D& centro, double raio, const QColor& cor)
    : ObjetoGrafico(nome, TipoObjeto::CIRCUNFERENCIA), centroOriginal_m(centro), raioOriginal_m(raio) {
    definirCor(cor);
    gerarPontosAproximacao(); // Gera os pontos para desenho e SCN
}

Ponto2D CircunferenciaObj::obterCentroOriginal() const {
    return centroOriginal_m;
}

double CircunferenciaObj::obterRaioOriginal() const {
    return raioOriginal_m;
}

void CircunferenciaObj::definirCentroOriginal(const Ponto2D& novoCentro) {
    centroOriginal_m = novoCentro;
    gerarPontosAproximacao(); // Re-gera pontos com novo centro
}

void CircunferenciaObj::definirRaioOriginal(double novoRaio) {
    if (novoRaio > 0) {
        raioOriginal_m = novoRaio;
        gerarPontosAproximacao(); // Re-gera pontos com novo raio
    }
}

// Helper para gerar pontos que serão armazenados em pontosOriginaisMundo
// Estes são os pontos no "espaço do objeto" antes de qualquer transformação acumulada.
// Para a circunferência, podemos usar pontos aproximados ou apenas o centro em pontosOriginaisMundo.
// A lógica de desenho em FrameDesenho já redesenha a circunferência ponto a ponto.
// Aqui, vamos popular pontosOriginaisMundo com pontos aproximados para consistência com outros objetos
// e para o cálculo do centro geométrico.
void CircunferenciaObj::gerarPontosAproximacao() {
    QList<Ponto2D> pontosAprox;
    int numSegmentos = 72; // Ou um valor configurável
    for (int i = 0; i < numSegmentos; ++i) {
        double angulo = 2.0 * M_PI * static_cast<double>(i) / static_cast<double>(numSegmentos);
        pontosAprox.append(Ponto2D(
            centroOriginal_m.obterX() + raioOriginal_m * std::cos(angulo),
            centroOriginal_m.obterY() + raioOriginal_m * std::sin(angulo)
            ));
    }
    // A classe base ObjetoGrafico usa pontosOriginaisMundo para recalcularPontosTransformados.
    // E calcularCentroGeometrico usa pontosOriginaisMundo.
    definirPontosOriginaisMundo(pontosAprox);
}

// O ObjetoGrafico::recalcularPontosTransformados(matrizNormalizacao)
// já pegará os pontos de `pontosOriginaisMundo` (agora atualizados por gerarPontosAproximacao)
// e aplicará `matrizTransformacaoAcumulada` e depois `matrizNormalizacao`.
