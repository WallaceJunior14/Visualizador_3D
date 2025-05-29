#ifndef VIEWPORT_TELA_H
#define VIEWPORT_TELA_H

#include "matriz.h"
#include <QRect> // Para representar a área da viewport em pixels

// Define a "viewport" na tela, uma área em coordenadas de dispositivo (pixels)
// onde os objetos normalizados (NDC) serão desenhados.
class ViewportTela {
public:
    // Construtor: x, y do canto superior esquerdo, largura e altura em pixels.
    ViewportTela(int x, int y, int largura, int altura);

    // Define os parâmetros da viewport.
    void definirParametros(int x, int y, int largura, int altura);

    // Getters.
    int obterX() const;
    int obterY() const;
    int obterLargura() const;
    int obterAltura() const;
    QRect obterRect() const;

    // Calcula e retorna a matriz de transformação de Viewport.
    // Mapeia coordenadas Normalizadas de Dispositivo (NDC) [-1,1]x[-1,1]
    // para coordenadas da viewport na tela (pixels).
    // Considera que o Y do Qt (tela) cresce para baixo.
    Matriz obterMatrizTransformacaoViewport() const;

private:
    int vpX;       // Coordenada X do canto superior esquerdo da viewport (pixels)
    int vpY;       // Coordenada Y do canto superior esquerdo da viewport (pixels)
    int vpLargura; // Largura da viewport (pixels)
    int vpAltura;  // Altura da viewport (pixels)

    // Limites do NDC (Sistema de Coordenadas Normalizadas) de onde os pontos vêm
    const double ndcXMin = -1.0;
    const double ndcYMin = -1.0; // Assumindo que o NDC tem Y crescendo para cima
    const double ndcXMax = 1.0;
    const double ndcYMax = 1.0;
};

#endif // VIEWPORT_TELA_H
