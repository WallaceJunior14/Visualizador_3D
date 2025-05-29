#include "transformador_geometrico.h"
#include <cmath>

Matriz TransformadorGeometrico::rotacao(double anguloRad, const Ponto2D& pivo) {
    Matriz r = Matriz::identidade(3);
    double cosTheta = cos(anguloRad);
    double sinTheta = sin(anguloRad);
    double px = pivo.obterX();
    double py = pivo.obterY();

    r(0, 0) = cosTheta;
    r(0, 1) = -sinTheta;
    r(1, 0) = sinTheta;
    r(1, 1) = cosTheta;

    // Correction for rotation around a pivot point
    r(0, 2) = px * (1 - cosTheta) + py * sinTheta;
    r(1, 2) = py * (1 - cosTheta) - px * sinTheta;

    return r;
}

Matriz TransformadorGeometrico::translacao(double dx, double dy) {
    Matriz t = Matriz::identidade(3);
    t(0, 2) = dx;
    t(1, 2) = dy;
    return t;
}

Matriz TransformadorGeometrico::escala(double sx, double sy, const Ponto2D& pivo) {
    Matriz s = Matriz::identidade(3);
    double px = pivo.obterX();
    double py = pivo.obterY();

    s(0, 0) = sx;
    s(1, 1) = sy;

    // Correction for scaling around a pivot point
    s(0, 2) = px * (1 - sx);
    s(1, 2) = py * (1 - sy);

    return s;
}
