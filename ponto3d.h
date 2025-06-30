#ifndef PONTO3D_H
#define PONTO3D_H

#include "matriz.h"
#include <cmath>

/**
 * @brief Representa um ponto ou um vetor no espaço 3D usando coordenadas homogêneas.
 * @details Utiliza uma matriz coluna 4x1 `[x, y, z, w]` para a representação interna.
 * Esta abordagem unificada permite que a mesma classe seja usada para representar
 * posições no espaço (pontos, com w=1) e direções (vetores, com w=0). A classe
 * encapsula uma Matriz, permitindo a fácil aplicação de transformações 4x4.
 */
class Ponto3D {
public:
    /**
     * @brief Construtor que cria um ponto/vetor 3D a partir de suas coordenadas.
     * @param x A coordenada x.
     * @param y A coordenada y.
     * @param z A coordenada z.
     * @param w A componente homogênea. O valor padrão é 1 (representando um ponto). Use 0 para vetores.
     */
    Ponto3D(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0);

    /**
     * @brief Construtor de conversão que cria um Ponto3D a partir de uma Matriz 4x1.
     * @param m A matriz 4x1 a ser convertida.
     * @note É `explicit` para prevenir conversões implícitas acidentais. Útil para
     * converter o resultado de uma multiplicação de matrizes de volta para um Ponto3D.
     */
    explicit Ponto3D(const Matriz& m);

    // --- Getters e Setters ---
    /** @brief Obtém a coordenada x. */
    double obterX() const;
    /** @brief Obtém a coordenada y. */
    double obterY() const;
    /** @brief Obtém a coordenada z. */
    double obterZ() const;
    /** @brief Obtém a componente homogênea w. */
    double obterW() const;

    /** @brief Define a coordenada x. @param x O novo valor de x. */
    void definirX(double x);
    /** @brief Define a coordenada y. @param y O novo valor de y. */
    void definirY(double y);
    /** @brief Define a coordenada z. @param z O novo valor de z. */
    void definirZ(double z);
    /** @brief Define a componente homogênea w. @param w O novo valor de w. */
    void definirW(double w);

    /**
     * @brief Retorna a representação interna do ponto como uma Matriz 4x1.
     * @return Uma referência constante para a matriz interna.
     */
    const Matriz& obterMatriz() const;

    // --- Métodos de Normalização ---

    /**
     * @brief Normaliza o **PONTO** para coordenadas cartesianas (divisão por w).
     * @details Transforma a representação homogênea `(x, y, z, w)` na representação
     * cartesiana `(x/w, y/w, z/w, 1)`. Modifica o objeto atual.
     * @note Essencial após uma transformação de projeção para converter de volta do espaço de recorte.
     */
    void normalizar();

    /**
     * @brief Retorna uma versão normalizada do **VETOR** (comprimento 1).
     * @details Calcula e retorna um novo vetor com a mesma direção mas com magnitude igual a 1.
     * A componente `w` do vetor resultante é mantida (geralmente 0).
     * @return Um novo objeto Ponto3D representando o vetor unitário.
     * @note Não modifica o objeto atual.
     */
    Ponto3D normalizarVetor() const;

    // --- Métodos para Operações Vetoriais ---

    /**
     * @brief Calcula o comprimento (magnitude) euclidiano do vetor.
     * @return O comprimento (magnitude) do vetor, calculado a partir das componentes x, y, e z.
     * @note Ignora a componente w.
     */
    double magnitude() const;

    // --- Sobrecarga de Operadores ---
    /** @brief Soma de dois pontos/vetores. Retorna um novo Ponto3D. */
    Ponto3D operator+(const Ponto3D& outro) const;
    /** @brief Subtração de dois pontos/vetores. Retorna um novo Ponto3D. */
    Ponto3D operator-(const Ponto3D& outro) const;
    /** @brief Multiplicação do ponto/vetor por um escalar. Retorna um novo Ponto3D. */
    Ponto3D operator*(double escalar) const;
    /** @brief Divisão do ponto/vetor por um escalar. Retorna um novo Ponto3D. */
    Ponto3D operator/(double escalar) const;

    // --- Métodos Estáticos ---
    /**
     * @brief Calcula o produto vetorial (cross product) entre dois vetores.
     * @param a O primeiro vetor (Ponto3D).
     * @param b O segundo vetor (Ponto3D).
     * @return Um novo Ponto3D representando o vetor resultante, que é perpendicular a `a` e `b`.
     */
    static Ponto3D produtoVetorial(const Ponto3D& a, const Ponto3D& b);

private:
    Matriz dados_m; ///< Armazena as coordenadas [x, y, z, w] como uma matriz coluna 4x1.
};

#endif // PONTO3D_H
