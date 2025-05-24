#ifndef JANELA_MUNDO_H
#define JANELA_MUNDO_H

#include "ponto2d.h"
#include "matriz.h"

// Define a "janela" de visualização no sistema de coordenadas do mundo. [cite: 10]
// Esta janela é mapeada para o sistema de coordenadas normalizadas (NDC).
// Por padrão, NDC é [-1, 1] para X e Y.
class JanelaMundo {
public:
    // Construtor define a janela inicial. Ex: xwmin, ywmin, xwmax, ywmax.
    JanelaMundo(double xMin, double yMin, double xMax, double yMax);

    // Altera os parâmetros da janela (zoom, deslocamento). [cite: 11]
    void zoom(double fator); // Fator > 1 para zoom in, < 1 para zoom out
    void deslocar(double dx, double dy); // Pan

    // Define os limites da janela diretamente.
    void definirLimites(double xMin, double yMin, double xMax, double yMax);

    // Getters para os limites da janela.
    Ponto2D obterMin() const;
    Ponto2D obterMax() const;
    double obterLargura() const;
    double obterAltura() const;

    // Calcula e retorna a matriz de transformação de Normalização.
    // Mapeia coordenadas do mundo (dentro desta janela) para Coordenadas Normalizadas de Dispositivo (NDC).
    // NDC é tipicamente [-1, 1] para X e Y.
    Matriz obterMatrizNormalizacao() const;

private:
    Ponto2D minW; // Canto inferior esquerdo da janela no mundo
    Ponto2D maxW; // Canto superior direito da janela no mundo

    // Coordenadas do NDC para o qual a janela do mundo será mapeada
    // Por padrão, assumimos que o SCN vai de (-1, -1) no canto inferior esquerdo
    // até (1, 1) no canto superior direito. Se o Qt usar Y invertido para tela,
    // isso será tratado na transformação de Viewport.
    // Para esta matriz de normalização, vamos mapear Y do mundo para Y do SCN
    // de forma que yMinMundo -> -1 e yMaxMundo -> 1 (ou o oposto, dependendo da convenção)
    // Vamos usar yMinMundo -> -1 (baixo) e yMaxMundo -> 1 (cima) para SCN.
    // Se a viewport do Qt tem y para baixo, a matriz da viewport fará a inversão.
    const double ndcXMin = -1.0;
    const double ndcYMin = -1.0;
    const double ndcXMax = 1.0;
    const double ndcYMax = 1.0;
};

#endif // JANELA_MUNDO_H
