#ifndef TRANSFORMADOR_GEOMETRICO_H
#define TRANSFORMADOR_GEOMETRICO_H

#include "matriz.h"
#include "ponto2d.h"

class TransformadorGeometrico {
public:
    static Matriz rotacao(double anguloRad, const Ponto2D& pivo = Ponto2D(0, 0));
    static Matriz translacao(double dx, double dy);
    static Matriz escala(double sx, double sy, const Ponto2D& pivo = Ponto2D(0, 0));
};

#endif // TRANSFORMADOR_GEOMETRICO_H

