#ifndef TRANSFORMADOR_GEOMETRICO_H
#define TRANSFORMADOR_GEOMETRICO_H

#include "matriz.h"
#include "ponto2d.h"

// Classe utilitária para gerar matrizes de transformação geométrica 2D.
// As transformações são implementadas usando multiplicação de matrizes homogêneas. [cite: 9]
class TransformadorGeometrico {
public:
    // Cria uma matriz de translação. [cite: 8]
    static Matriz translacao(double dx, double dy);

    // Cria uma matriz de escala em torno de um ponto (centro). [cite: 8]
    // Se o centro não for fornecido, a escala é em torno da origem (0,0).
    static Matriz escala(double sx, double sy, const Ponto2D& centro = Ponto2D(0,0));

    // Cria uma matriz de rotação em torno de um ponto (pivo). [cite: 8]
    // O ângulo é em graus. Se o pivô não for fornecido, a rotação é em torno da origem.
    static Matriz rotacao(double anguloGraus, const Ponto2D& pivo = Ponto2D(0,0));
};

#endif // TRANSFORMADOR_GEOMETRICO_H
