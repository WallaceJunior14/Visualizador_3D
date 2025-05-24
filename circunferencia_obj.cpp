#include "circunferencia_obj.h"

CircunferenciaObj::CircunferenciaObj(const QString& nome, const Ponto2D& centro, double raio,
                                     const QColor& corCirc, int numSegmentos)
    : ObjetoGrafico(nome, TipoObjeto::CIRCUNFERENCIA), // Usar o novo tipo
    centroOriginal(centro), raioOriginal(raio) {
    definirCor(corCirc);
    gerarPontosAproximacao(numSegmentos);
    // A matriz de transformação acumulada é identidade por padrão.
    // recalcularPontosTransformados será chamado externamente após adição ao display file.
}

Ponto2D CircunferenciaObj::calcularCentroGeometrico() const {
    // O centro geométrico de uma circunferência é seu próprio centro.
    // Retorna o centro original, pois as transformações são aplicadas via matriz.
    return centroOriginal;
}

Ponto2D CircunferenciaObj::obterCentroOriginal() const {
    return centroOriginal;
}

double CircunferenciaObj::obterRaioOriginal() const {
    return raioOriginal;
}

void CircunferenciaObj::definirCentroRaio(const Ponto2D& novoCentro, double novoRaio, int numSegmentos) {
    centroOriginal = novoCentro;
    raioOriginal = novoRaio;
    gerarPontosAproximacao(numSegmentos);
    // Importante: após esta chamada, quem gerencia o objeto (DisplayFile/MainWindow)
    // deve chamar recalcularPontosTransformados se a janela de normalização for conhecida.
}


void CircunferenciaObj::gerarPontosAproximacao(int numSegmentos) {
    pontosOriginaisMundo.clear(); // Limpa pontos antigos
    if (numSegmentos < 3) numSegmentos = 3; // Mínimo para um polígono

    for (int i = 0; i < numSegmentos; ++i) {
        double angulo = 2.0 * M_PI * static_cast<double>(i) / static_cast<double>(numSegmentos);
        double x = centroOriginal.obterX() + raioOriginal * std::cos(angulo);
        double y = centroOriginal.obterY() + raioOriginal * std::sin(angulo);
        pontosOriginaisMundo.append(Ponto2D(x, y));
    }
}
