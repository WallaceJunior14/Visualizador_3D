// matriz.cpp

#include "matriz.h"
#include "ponto3d.h" // Necessário para as operações que envolvem Ponto3D
#include <vector>
#include <stdexcept>
#include <cmath>
#include <QDebug>

// Define o valor de PI caso não seja fornecido por <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- CONSTRUTORES E OPERADORES ---

Matriz::Matriz(int linhas, int colunas) : numLinhas(linhas), numColunas(colunas) {
    if (linhas <= 0 || colunas <= 0) {
        throw std::invalid_argument("As dimensões da matriz devem ser positivas.");
    }
    // Inicializa a matriz com zeros
    dados.resize(numLinhas, std::vector<double>(numColunas, 0.0));
}

Matriz::Matriz(const Matriz& outra)
    : dados(outra.dados), numLinhas(outra.numLinhas), numColunas(outra.numColunas) {}

Matriz& Matriz::operator=(const Matriz& outra) {
    // Proteção contra auto-atribuição
    if (this == &outra) {
        return *this;
    }
    numLinhas = outra.numLinhas;
    numColunas = outra.numColunas;
    dados = outra.dados;
    return *this;
}

// --- ACESSO E OPERAÇÕES ---

double& Matriz::operator()(int linha, int coluna) {
    if (linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) {
        throw std::out_of_range("Acesso fora dos limites da matriz.");
    }
    return dados[linha][coluna];
}

const double& Matriz::operator()(int linha, int coluna) const {
    if (linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) {
        throw std::out_of_range("Acesso fora dos limites da matriz.");
    }
    return dados[linha][coluna];
}

Matriz Matriz::operator*(const Matriz& outra) const {
    if (numColunas != outra.numLinhas) {
        throw std::invalid_argument("Dimensões de matriz inválidas para multiplicação.");
    }

    Matriz resultado(numLinhas, outra.numColunas);
    for (int i = 0; i < numLinhas; ++i) {
        for (int j = 0; j < outra.numColunas; ++j) {
            for (int k = 0; k < numColunas; ++k) {
                resultado(i, j) += dados[i][k] * outra(k, j);
            }
        }
    }
    return resultado;
}

Ponto3D Matriz::operator*(const Ponto3D& ponto) const {
    if (numLinhas != 4 || numColunas != 4) {
        qWarning("Multiplicação Matriz*Ponto requer uma matriz 4x4.");
        return Ponto3D(0, 0, 0); // Retorna um ponto nulo em caso de erro
    }

    double x = ponto.obterX();
    double y = ponto.obterY();
    double z = ponto.obterZ();
    double w = ponto.obterW();

    double resX = dados[0][0] * x + dados[0][1] * y + dados[0][2] * z + dados[0][3] * w;
    double resY = dados[1][0] * x + dados[1][1] * y + dados[1][2] * z + dados[1][3] * w;
    double resZ = dados[2][0] * x + dados[2][1] * y + dados[2][2] * z + dados[2][3] * w;
    double resW = dados[3][0] * x + dados[3][1] * y + dados[3][2] * z + dados[3][3] * w;

    return Ponto3D(resX, resY, resZ, resW);
}

// --- GETTERS ---

int Matriz::obterLinhas() const {
    return numLinhas;
}

int Matriz::obterColunas() const {
    return numColunas;
}

// --- FUNÇÕES ESTÁTICAS DE TRANSFORMAÇÃO ---

Matriz Matriz::identidade(int tamanho) {
    Matriz id(tamanho, tamanho);
    for (int i = 0; i < tamanho; ++i) {
        id(i, i) = 1.0;
    }
    return id;
}

Matriz Matriz::translacao(double dx, double dy, double dz) {
    Matriz t = identidade(4);
    t(0, 3) = dx;
    t(1, 3) = dy;
    t(2, 3) = dz;
    return t;
}

Matriz Matriz::escala(double sx, double sy, double sz) {
    Matriz s = identidade(4);
    s(0, 0) = sx;
    s(1, 1) = sy;
    s(2, 2) = sz;
    return s;
}

Matriz Matriz::rotacaoX(double anguloGraus) {
    double rad = anguloGraus * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    Matriz r = identidade(4);
    r(1, 1) = c;
    r(1, 2) = -s;
    r(2, 1) = s;
    r(2, 2) = c;
    return r;
}

Matriz Matriz::rotacaoY(double anguloGraus) {
    double rad = anguloGraus * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    Matriz r = identidade(4);
    r(0, 0) = c;
    r(0, 2) = s;
    r(2, 0) = -s;
    r(2, 2) = c;
    return r;
}

Matriz Matriz::rotacaoZ(double anguloGraus) {
    double rad = anguloGraus * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    Matriz r = identidade(4);
    r(0, 0) = c;
    r(0, 1) = -s;
    r(1, 0) = s;
    r(1, 1) = c;
    return r;
}

Matriz Matriz::rotacaoEixoArbitrario(const Ponto3D& eixo, double anguloGraus) {
    Ponto3D u = eixo.normalizarVetor();
    double x = u.obterX();
    double y = u.obterY();
    double z = u.obterZ();

    double rad = anguloGraus * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);
    double one_minus_c = 1.0 - c;

    Matriz r = identidade(4);
    r(0, 0) = c + x * x * one_minus_c;
    r(0, 1) = x * y * one_minus_c - z * s;
    r(0, 2) = x * z * one_minus_c + y * s;

    r(1, 0) = y * x * one_minus_c + z * s;
    r(1, 1) = c + y * y * one_minus_c;
    r(1, 2) = y * z * one_minus_c - x * s;

    r(2, 0) = z * x * one_minus_c - y * s;
    r(2, 1) = z * y * one_minus_c + x * s;
    r(2, 2) = c + z * z * one_minus_c;

    return r;
}


// --- FUNÇÕES ESTÁTICAS DE CÂMERA ---

Matriz Matriz::lookAt(const Ponto3D& pos, const Ponto3D& alvo, const Ponto3D& up) {
    Ponto3D z_cam = (pos - alvo).normalizarVetor();
    Ponto3D x_cam = Ponto3D::produtoVetorial(up, z_cam).normalizarVetor();
    Ponto3D y_cam = Ponto3D::produtoVetorial(z_cam, x_cam);

    Matriz orientacao = identidade(4);
    orientacao(0, 0) = x_cam.obterX(); orientacao(0, 1) = x_cam.obterY(); orientacao(0, 2) = x_cam.obterZ();
    orientacao(1, 0) = y_cam.obterX(); orientacao(1, 1) = y_cam.obterY(); orientacao(1, 2) = y_cam.obterZ();
    orientacao(2, 0) = z_cam.obterX(); orientacao(2, 1) = z_cam.obterY(); orientacao(2, 2) = z_cam.obterZ();

    Matriz translacaoMat = identidade(4);
    translacaoMat(0, 3) = -pos.obterX();
    translacaoMat(1, 3) = -pos.obterY();
    translacaoMat(2, 3) = -pos.obterZ();

    return orientacao * translacaoMat;
}

Matriz Matriz::perspectiva(double fovYGraus, double aspecto, double near, double far) {
    Matriz p(4, 4);
    double fovRad = fovYGraus * M_PI / 180.0;
    double tanHalfFov = tan(fovRad / 2.0);

    p(0, 0) = 1.0 / (aspecto * tanHalfFov);
    p(1, 1) = 1.0 / (tanHalfFov);
    p(2, 2) = -(far + near) / (far - near);
    p(2, 3) = -(2.0 * far * near) / (far - near);
    p(3, 2) = -1.0;

    return p;
}

Matriz Matriz::ortografica(double left, double right, double bottom, double top, double near, double far) {
    Matriz p = identidade(4);
    p(0, 0) = 2.0 / (right - left);
    p(1, 1) = 2.0 / (top - bottom);
    p(2, 2) = -2.0 / (far - near);
    p(0, 3) = -(right + left) / (right - left);
    p(1, 3) = -(top + bottom) / (top - bottom);
    p(2, 3) = -(far + near) / (far - near);
    return p;
}

// --- MÉTODOS DE DEPURAÇÃO ---

void Matriz::imprimir(QString nome) const {
    qDebug().noquote() << "---" << nome << "---";
    QString linhaStr;
    for (int i = 0; i < numLinhas; ++i) {
        linhaStr.clear();
        for (int j = 0; j < numColunas; ++j) {
            linhaStr += QString::number(dados[i][j], 'f', 2) + "\t";
        }
        qDebug().noquote() << linhaStr;
    }
    qDebug().noquote() << "---------------";
}
