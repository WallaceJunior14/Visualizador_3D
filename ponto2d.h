#ifndef PONTO2D_H
#define PONTO2D_H

#include "matriz.h"
#include <QString>

/**
 * @brief Representa um ponto no espaço 2D utilizando coordenadas homogêneas.
 * @details Esta classe herda de `Matriz` e modela um ponto 2D como uma matriz
 * coluna 3x1 no formato `[x, y, w]^T`. A herança permite que transformações
 * 2D (usando matrizes 3x3) sejam aplicadas diretamente ao ponto através da
 * multiplicação de matrizes. A coordenada `w` (componente homogênea) é usada
 * para facilitar transformações como a translação de forma matricial.
 */
class Ponto2D : public Matriz {
public:
    /**
     * @brief Construtor padrão que cria um ponto 2D.
     * @param x A coordenada x do ponto. O padrão é 0.
     * @param y A coordenada y do ponto. O padrão é 0.
     * @param w A componente homogênea. O padrão é 1, que é o valor correto para um ponto.
     */
    Ponto2D(double x = 0.0, double y = 0.0, double w = 1.0);

    /**
     * @brief Construtor de conversão que cria um Ponto2D a partir de uma Matriz 3x1.
     * @param m A matriz 3x1 a ser convertida em ponto.
     * @note É `explicit` para prevenir conversões implícitas acidentais. Usado principalmente
     * para converter o resultado de uma multiplicação de matrizes de volta para um Ponto2D.
     */
    explicit Ponto2D(const Matriz& m);

    /**
     * @brief Obtém a coordenada x cartesiana do ponto.
     * @return O valor da coordenada x.
     * @note Se a componente w não for 1, o valor retornado geralmente deve ser o
     * resultado de x/w. A implementação do método deve garantir isso.
     */
    double obterX() const;

    /**
     * @brief Obtém a coordenada y cartesiana do ponto.
     * @return O valor da coordenada y.
     */
    double obterY() const;

    /**
     * @brief Obtém a componente homogênea `w` do ponto.
     * @return O valor de w.
     */
    double obterW() const;

    /**
     * @brief Define a coordenada x do ponto.
     * @param x O novo valor para a coordenada x.
     */
    void definirX(double x);

    /**
     * @brief Define a coordenada y do ponto.
     * @param y O novo valor para a coordenada y.
     */
    void definirY(double y);

    /**
     * @brief Define a componente homogênea `w` do ponto.
     * @param w O novo valor para a componente w.
     */
    void definirW(double w);

    /**
     * @brief Normaliza o ponto dividindo suas coordenadas por `w`.
     * @details Transforma o ponto de coordenadas homogêneas `(x, y, w)` para
     * coordenadas cartesianas `(x/w, y/w, 1)`. Esta operação é essencial após a
     * aplicação de uma matriz de projeção, mas não é sempre necessária para
     * transformações afins 2D (como translação, rotação, escala) onde `w`
     * geralmente permanece 1.
     */
    void normalizar();
};

#endif // PONTO2D_H
