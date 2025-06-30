#ifndef VIEWPORT_TELA_H
#define VIEWPORT_TELA_H

#include "matriz.h"
#include <QRect> // Para representar a área da viewport em pixels

/**
 * @brief Gerencia a transformação da viewport, que mapeia as coordenadas da cena para a tela.
 * @details Esta classe representa o estágio final do pipeline de renderização 2D. Ela
 * calcula a matriz de transformação necessária para converter as Coordenadas de Dispositivo
 * Normalizadas (NDC - Normalized Device Coordinates), que variam de -1 a 1, para as
 * coordenadas de pixel da área de desenho final na tela (a viewport).
 */
class ViewportTela {
public:
    /**
     * @brief Construtor que define a área da viewport na tela.
     * @param x A coordenada de pixel do canto superior esquerdo da viewport.
     * @param y A coordenada de pixel do canto superior esquerdo da viewport.
     * @param largura A largura da viewport em pixels.
     * @param altura A altura da viewport em pixels.
     */
    ViewportTela(int x, int y, int largura, int altura);

    /**
     * @brief Define ou atualiza todos os parâmetros da viewport.
     * @param x A nova coordenada de pixel x do canto superior esquerdo.
     * @param y A nova coordenada de pixel y do canto superior esquerdo.
     * @param largura A nova largura em pixels.
     * @param altura A nova altura em pixels.
     * @note Útil para ser chamado quando a janela da aplicação é redimensionada.
     */
    void definirParametros(int x, int y, int largura, int altura);

    // --- Getters para os parâmetros da viewport ---
    /** @brief Retorna a coordenada x (em pixels) do canto superior esquerdo da viewport. */
    int obterX() const;
    /** @brief Retorna a coordenada y (em pixels) do canto superior esquerdo da viewport. */
    int obterY() const;
    /** @brief Retorna a largura (em pixels) da viewport. */
    int obterLargura() const;
    /** @brief Retorna a altura (em pixels) da viewport. */
    int obterAltura() const;
    /** @brief Retorna um objeto QRect que representa a geometria da viewport. */
    QRect obterRect() const;

    /**
     * @brief Calcula e retorna a matriz de transformação de Viewport.
     * @details Esta matriz mapeia o espaço de Coordenadas Normalizadas de Dispositivo (NDC),
     * que vai de `[-1, 1]` em X e `[-1, 1]` em Y, para o espaço de coordenadas da tela em
     * pixels, definido pelos parâmetros desta viewport.
     * @return Uma matriz de transformação (geralmente 3x3 para 2D ou 4x4 para 3D).
     * @note A matriz gerada leva em consideração que a origem do sistema de coordenadas do Qt
     * (tela) está no canto superior esquerdo, com o eixo Y crescendo para baixo, realizando
     * a inversão necessária do eixo Y que vem do NDC.
     */
    Matriz obterMatrizTransformacaoViewport() const;

private:
    int vpX;       ///< Coordenada X do canto superior esquerdo da viewport (em pixels).
    int vpY;       ///< Coordenada Y do canto superior esquerdo da viewport (em pixels).
    int vpLargura; ///< Largura da viewport (em pixels).
    int vpAltura;  ///< Altura da viewport (em pixels).

    // Limites do NDC (Sistema de Coordenadas Normalizadas) de onde os pontos vêm.
    // O sistema Y do NDC geralmente cresce para cima.
    const double ndcXMin = -1.0;
    const double ndcYMin = -1.0;
    const double ndcXMax = 1.0;
    const double ndcYMax = 1.0;
};

#endif // VIEWPORT_TELA_H
