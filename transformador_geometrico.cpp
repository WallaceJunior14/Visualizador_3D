#include "transformador_geometrico.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Matriz TransformadorGeometrico::translacao(double dx, double dy) {
    return Matriz::translacao(dx, dy);
}

Matriz TransformadorGeometrico::escala(double sx, double sy, const Ponto2D& centro) {
    // Para escalar em torno de um centro C:
    // 1. Transladar C para a origem (T(-Cx, -Cy))
    // 2. Escalar (S(sx, sy))
    // 3. Transladar C de volta para sua posição original (T(Cx, Cy))
    // Matriz resultante = T(Cx, Cy) * S(sx, sy) * T(-Cx, -Cy)

    if (centro.obterX() == 0.0 && centro.obterY() == 0.0) {
        return Matriz::escala(sx, sy); // Escala em torno da origem
    }

    Matriz T_negC = Matriz::translacao(-centro.obterX(), -centro.obterY());
    Matriz S = Matriz::escala(sx, sy);
    Matriz T_posC = Matriz::translacao(centro.obterX(), centro.obterY());

    return T_posC * S * T_negC;
}

Matriz TransformadorGeometrico::rotacao(double anguloGraus, const Ponto2D& pivo) {
    // Para rotacionar em torno de um pivô P:
    // 1. Transladar P para a origem (T(-Px, -Py))
    // 2. Rotacionar (R(angulo))
    // 3. Transladar P de volta para sua posição original (T(Px, Py))
    // Matriz resultante = T(Px, Py) * R(angulo) * T(-Px, -Py)

    if (pivo.obterX() == 0.0 && pivo.obterY() == 0.0) {
        return Matriz::rotacao(anguloGraus); // Rotação em torno da origem
    }

    Matriz T_negP = Matriz::translacao(-pivo.obterX(), -pivo.obterY());
    Matriz R = Matriz::rotacao(anguloGraus);
    Matriz T_posP = Matriz::translacao(pivo.obterX(), pivo.obterY());

    return T_posP * R * T_negP;
}
