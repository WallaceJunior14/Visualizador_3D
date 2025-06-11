#ifndef TRANSFORMADOR_GEOMETRICO_H
#define TRANSFORMADOR_GEOMETRICO_H

#include "matriz.h"
#include "ponto3d.h"

// Classe de utilitários para criar matrizes de transformação 3D complexas.
class TransformadorGeometrico {
public:
    // Cria uma matriz de translação 3D.
    static Matriz translacao(double dx, double dy, double dz);

    // Cria uma matriz de escala 3D em torno de um ponto de pivô.
    static Matriz escala(double sx, double sy, double sz, const Ponto3D& pivo = Ponto3D(0, 0, 0));

    // Rotação em 3D ocorre em torno de um eixo. Estas funções criam matrizes
    // de rotação em torno dos eixos principais, passando por um ponto de pivô.
    // Nota: O ângulo agora é em graus, para consistência com a classe Matriz.
    static Matriz rotacaoX(double anguloGraus, const Ponto3D& pivo = Ponto3D(0, 0, 0));
    static Matriz rotacaoY(double anguloGraus, const Ponto3D& pivo = Ponto3D(0, 0, 0));
    static Matriz rotacaoZ(double anguloGraus, const Ponto3D& pivo = Ponto3D(0, 0, 0));

    static Matriz rotacaoEixoArbitrario(const Ponto3D& eixo, double angulo);
    static Matriz rotacaoComposta(double anguloX, double anguloY, double anguloZ, const Ponto3D& pivo);
};

#endif // TRANSFORMADOR_GEOMETRICO_H
