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

Matriz TransformadorGeometrico::rotacaoEixoArbitrario(const Ponto3D& eixo, double angulo)
{
    // Converte o ângulo de graus para radianos
    double rad = angulo * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    double omc = 1.0 - c; // one-minus-cosine

    // Garante que o eixo de rotação esteja normalizado
    Ponto3D u = eixo;
    u.normalizarVetor(); // Supondo que você tenha este método

    double x = u.obterX();
    double y = u.obterY();
    double z = u.obterZ();

    // Monta a matriz de rotação usando a fórmula de Rodrigues
    Matriz R; // Matriz 4x4
    R(0, 0) = c + x * x * omc;
    R(0, 1) = x * y * omc - z * s;
    R(0, 2) = x * z * omc + y * s;
    R(0, 3) = 0.0;

    R(1, 0) = y * x * omc + z * s;
    R(1, 1) = c + y * y * omc;
    R(1, 2) = y * z * omc - x * s;
    R(1, 3) = 0.0;

    R(2, 0) = z * x * omc - y * s;
    R(2, 1) = z * y * omc + x * s;
    R(2, 2) = c + z * z * omc;
    R(2, 3) = 0.0;

    R(3, 0) = 0.0;
    R(3, 1) = 0.0;
    R(3, 2) = 0.0;
    R(3, 3) = 1.0;

    return R;
}

Matriz TransformadorGeometrico::rotacaoComposta(double anguloX, double anguloY, double anguloZ, const Ponto3D& pivo)
{
    // 1. Matriz para transladar o pivô para a origem
    Matriz T = TransformadorGeometrico::translacao(-pivo.obterX(), -pivo.obterY(), -pivo.obterZ());

    // 2. Matrizes de rotação na origem
    // (A ordem pode variar dependendo do resultado desejado, mas Z-Y-X é uma convenção comum)
    Matriz Rz = TransformadorGeometrico::rotacaoZ(anguloZ);
    Matriz Ry = TransformadorGeometrico::rotacaoY(anguloY);
    Matriz Rx = TransformadorGeometrico::rotacaoX(anguloX);

    // 3. Matriz para transladar de volta da origem para a posição do pivô
    Matriz T_inversa = TransformadorGeometrico::translacao(pivo.obterX(), pivo.obterY(), pivo.obterZ());

    // A matriz de transformação final é a combinação de todas as operações.
    // Lembre-se que a ordem da multiplicação de matrizes para aplicar as transformações
    // é da direita para a esquerda (a primeira transformação a ser aplicada fica mais à direita).
    // Transformação final = (Volta para Posição) * (Rotaciona em X) * (Rotaciona em Y) * (Rotaciona em Z) * (Vai para Origem)
    Matriz matrizFinal = T_inversa * Rx * Ry * Rz * T;

    return matrizFinal;
}
