#ifndef CLIPPER_3D_H
#define CLIPPER_3D_H

#include "ponto3d.h"

/**
 * @brief Implementa o algoritmo de recorte de linha 3D de Cohen-Sutherland.
 * @details Esta classe define um volume de recorte (geralmente o cubo canônico de -1 a 1)
 * e fornece métodos para determinar a visibilidade de pontos e recortar segmentos
 * de reta que o interceptam.
 */
class Clipper3D {
public:
    /**
     * @brief Códigos de região (bitmasks) usados pelo algoritmo Cohen-Sutherland em 3D.
     * Cada bit representa um dos 6 planos de recorte do volume. Um bit '1' significa
     * que o ponto está "fora" em relação àquele plano.
     */
    // clang-format off
    static const int DENTRO   = 0b000000; ///< 0: Ponto está dentro de todos os planos.
    static const int ESQUERDA = 0b000001; ///< Bit 0: Fora do plano esquerdo (x < xMin).
    static const int DIREITA  = 0b000010; ///< Bit 1: Fora do plano direito (x > xMax).
    static const int BAIXO    = 0b000100; ///< Bit 2: Fora do plano inferior (y < yMin).
    static const int CIMA     = 0b001000; ///< Bit 3: Fora do plano superior (y > yMax).
    static const int TRAS     = 0b010000; ///< Bit 4: Fora do plano próximo (z < zMin), "atrás" do observador.
    static const int FRENTE   = 0b100000; ///< Bit 5: Fora do plano distante (z > zMax), "na frente" do observador.
    // clang-format on

    /**
     * @brief Construtor da classe Clipper3D.
     * @param xMin Coordenada X mínima do volume de recorte.
     * @param yMin Coordenada Y mínima do volume de recorte.
     * @param zMin Coordenada Z mínima do volume de recorte.
     * @param xMax Coordenada X máxima do volume de recorte.
     * @param yMax Coordenada Y máxima do volume de recorte.
     * @param zMax Coordenada Z máxima do volume de recorte.
     * @note Por padrão, constrói um clipper para o volume de visão canônico (NDC), de -1 a 1 em todos os eixos.
     */
    Clipper3D(double xMin = -1.0, double yMin = -1.0, double zMin = -1.0,
              double xMax = 1.0,  double yMax = 1.0,  double zMax = 1.0);

    /**
     * @brief Recorta um segmento de reta 3D contra o volume de recorte definido.
     * @param p1 [in, out] O primeiro ponto do segmento de reta. Será modificado para o novo extremo se ocorrer recorte.
     * @param p2 [in, out] O segundo ponto do segmento de reta. Será modificado para o novo extremo se ocorrer recorte.
     * @return true se alguma parte do segmento de reta está visível dentro do volume (aceitação).
     * @return false se o segmento de reta está totalmente fora do volume (rejeição trivial).
     */
    bool cliparReta(Ponto3D& p1, Ponto3D& p2);

    /**
     * @brief Calcula o código de região de 6 bits para um ponto 3D.
     * @details O código identifica se um ponto está dentro do volume de recorte ou em qual
     * das 26 regiões externas ele se encontra, com base nos 6 planos de recorte.
     * @param p O ponto 3D a ser testado.
     * @return Um inteiro de 6 bits representando o código da região.
     */
    int calcularCodigoRegiao(const Ponto3D& p) const;

private:
    // Limites do volume de recorte (clipping volume).
    double xMinClip, yMinClip, zMinClip;
    double xMaxClip, yMaxClip, zMaxClip;
};

#endif // CLIPPER_3D_H
