#include "transformador_geometrico.h"

// A translação é direta, chamando a função estática da classe Matriz.
Matriz TransformadorGeometrico::translacao(double dx, double dy, double dz) {
    return Matriz::translacao(dx, dy, dz);
}

// Cria uma matriz de escala em torno de um pivô.
// Implementado como T(p) * S(sx,sy,sz) * T(-p)
Matriz TransformadorGeometrico::escala(double sx, double sy, double sz, const Ponto3D& pivo) {
    double px = pivo.obterX();
    double py = pivo.obterY();
    double pz = pivo.obterZ();

    // 1. Matriz para mover o pivô para a origem.
    Matriz T_inv = Matriz::translacao(-px, -py, -pz);

    // 2. Matriz de escala na origem.
    Matriz S = Matriz::escala(sx, sy, sz);

    // 3. Matriz para mover o pivô de volta à sua posição.
    Matriz T = Matriz::translacao(px, py, pz);

    // 4. Combina as matrizes na ordem correta.
    return T * S * T_inv;
}

// Cria uma matriz de rotação em torno do eixo X que passa por um pivô.
// Implementado como T(p) * Rx(angulo) * T(-p)
Matriz TransformadorGeometrico::rotacaoX(double anguloGraus, const Ponto3D& pivo) {
    double px = pivo.obterX();
    double py = pivo.obterY();
    double pz = pivo.obterZ();

    Matriz T_inv = Matriz::translacao(-px, -py, -pz);
    Matriz R = Matriz::rotacaoX(anguloGraus);
    Matriz T = Matriz::translacao(px, py, pz);

    return T * R * T_inv;
}

// Cria uma matriz de rotação em torno do eixo Y que passa por um pivô.
// Implementado como T(p) * Ry(angulo) * T(-p)
Matriz TransformadorGeometrico::rotacaoY(double anguloGraus, const Ponto3D& pivo) {
    double px = pivo.obterX();
    double py = pivo.obterY();
    double pz = pivo.obterZ();

    Matriz T_inv = Matriz::translacao(-px, -py, -pz);
    Matriz R = Matriz::rotacaoY(anguloGraus);
    Matriz T = Matriz::translacao(px, py, pz);

    return T * R * T_inv;
}

// Cria uma matriz de rotação em torno do eixo Z que passa por um pivô.
// Implementado como T(p) * Rz(angulo) * T(-p)
Matriz TransformadorGeometrico::rotacaoZ(double anguloGraus, const Ponto3D& pivo) {
    double px = pivo.obterX();
    double py = pivo.obterY();
    double pz = pivo.obterZ();

    Matriz T_inv = Matriz::translacao(-px, -py, -pz);
    Matriz R = Matriz::rotacaoZ(anguloGraus);
    Matriz T = Matriz::translacao(px, py, pz);

    return T * R * T_inv;
}
