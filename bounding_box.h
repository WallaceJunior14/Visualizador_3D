#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "ponto3d.h"

/**
 * @brief Representa uma caixa delimitadora alinhada aos eixos (AABB - Axis-Aligned Bounding Box).
 *
 * É definida por dois pontos: um com as coordenadas mínimas (min) e outro com as
 * coordenadas máximas (max) em todos os eixos.
 */
class BoundingBox {
public:
    // Construtor padrão: cria uma BBox "inválida" que pode ser expandida.
    BoundingBox();

    // Construtor a partir de um único ponto (BBox de volume zero).
    explicit BoundingBox(const Ponto3D& ponto);

    // Construtor a partir de dois pontos.
    BoundingBox(const Ponto3D& p1, const Ponto3D& p2);

    /**
     * @brief Expande a BBox para incluir um novo ponto.
     * @param ponto O ponto a ser incluído na BBox.
     */
    void expandir(const Ponto3D& ponto);

    /**
     * @brief Expande a BBox para incluir outra BBox.
     * @param outraBBox A outra BBox a ser unida a esta.
     */
    void expandir(const BoundingBox& outraBBox);

    // Retorna o centro geométrico da BBox.
    Ponto3D obterCentro() const;

    // Getters para os pontos min e max.
    Ponto3D obterMin() const;
    Ponto3D obterMax() const;

    // Verifica se a BBox foi inicializada (se é válida).
    bool ehValida() const;

private:
    Ponto3D m_min;
    Ponto3D m_max;
};

#endif // BOUNDING_BOX_H
