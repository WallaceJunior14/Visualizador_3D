#ifndef TRANSFORMADOR_GEOMETRICO_H
#define TRANSFORMADOR_GEOMETRICO_H

#include "matriz.h"
#include "ponto3d.h"

/**
 * @brief Uma classe de utilitários estática para criar matrizes de transformação 3D.
 * @details Esta classe não deve ser instanciada. Ela fornece um conjunto de métodos
 * estáticos (fábrica) que encapsulam a lógica para gerar matrizes de transformação
 * compostas, como rotação ou escala em torno de um ponto de pivô arbitrário,
 * simplificando as operações em outras partes do código.
 */
class TransformadorGeometrico {
public:
    /**
     * @brief Cria uma matriz de translação 3D.
     * @param dx O deslocamento a ser aplicado no eixo X.
     * @param dy O deslocamento a ser aplicado no eixo Y.
     * @param dz O deslocamento a ser aplicado no eixo Z.
     * @return Uma matriz de translação 4x4.
     */
    static Matriz translacao(double dx, double dy, double dz);

    /**
     * @brief Cria uma matriz de escala 3D em torno de um ponto de pivô arbitrário.
     * @param sx O fator de escala a ser aplicado no eixo X.
     * @param sy O fator de escala a ser aplicado no eixo Y.
     * @param sz O fator de escala a ser aplicado no eixo Z.
     * @param pivo O ponto no espaço que permanecerá fixo durante a escala. Se omitido, a escala ocorre em relação à origem (0,0,0).
     * @return Uma matriz de escala composta 4x4.
     * @note A operação é implementada internamente como uma sequência: Translação(-pivô) * Escala * Translação(pivô).
     */
    static Matriz escala(double sx, double sy, double sz, const Ponto3D& pivo = Ponto3D(0, 0, 0));

    /**
     * @brief Cria uma matriz de rotação em torno do eixo X, passando por um ponto de pivô arbitrário.
     * @param anguloGraus O ângulo da rotação, em graus.
     * @param pivo O ponto que serve como centro da rotação. Se omitido, a rotação ocorre em torno do eixo X na origem.
     * @return A matriz de rotação composta 4x4.
     */
    static Matriz rotacaoX(double anguloGraus, const Ponto3D& pivo = Ponto3D(0, 0, 0));

    /**
     * @brief Cria uma matriz de rotação em torno do eixo Y, passando por um ponto de pivô arbitrário.
     * @param anguloGraus O ângulo da rotação, em graus.
     * @param pivo O ponto que serve como centro da rotação. Se omitido, a rotação ocorre em torno do eixo Y na origem.
     * @return A matriz de rotação composta 4x4.
     */
    static Matriz rotacaoY(double anguloGraus, const Ponto3D& pivo = Ponto3D(0, 0, 0));

    /**
     * @brief Cria uma matriz de rotação em torno do eixo Z, passando por um ponto de pivô arbitrário.
     * @param anguloGraus O ângulo da rotação, em graus.
     * @param pivo O ponto que serve como centro da rotação. Se omitido, a rotação ocorre em torno do eixo Z na origem.
     * @return A matriz de rotação composta 4x4.
     */
    static Matriz rotacaoZ(double anguloGraus, const Ponto3D& pivo = Ponto3D(0, 0, 0));

    /**
     * @brief Cria uma matriz de rotação 4x4 em torno de um eixo arbitrário que passa pela origem.
     * @param eixo O vetor (Ponto3D) que define o eixo de rotação. Idealmente, deve ser um vetor unitário.
     * @param angulo O ângulo da rotação, em graus.
     * @return A matriz de rotação 4x4.
     */
    static Matriz rotacaoEixoArbitrario(const Ponto3D& eixo, double angulo);

    /**
     * @brief Cria uma matriz que combina rotações nos eixos X, Y e Z em torno de um ponto de pivô.
     * @param anguloX O ângulo de rotação em graus para o eixo X.
     * @param anguloY O ângulo de rotação em graus para o eixo Y.
     * @param anguloZ O ângulo de rotação em graus para o eixo Z.
     * @param pivo O ponto no espaço que serve como centro para todas as rotações.
     * @return A matriz de transformação composta 4x4.
     * @note A ordem de aplicação das rotações (geralmente Z, depois Y, depois X) é encapsulada nesta função.
     */
    static Matriz rotacaoComposta(double anguloX, double anguloY, double anguloZ, const Ponto3D& pivo);
};

#endif // TRANSFORMADOR_GEOMETRICO_H
