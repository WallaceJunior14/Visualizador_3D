#include "matriz.h"
#include <cmath> // Para std::cos, std::sin, M_PI (pode precisar definir _USE_MATH_DEFINES no Windows)

#ifndef M_PI // Definir M_PI se não estiver disponível (comum em MSVC)
#define M_PI 3.14159265358979323846
#endif

Matriz::Matriz(int linhas, int colunas) : numLinhas(linhas), numColunas(colunas) {
    if (linhas <= 0 || colunas <= 0) {
        throw std::invalid_argument("Dimensões da matriz devem ser positivas.");
    }
    dados.resize(numLinhas, std::vector<double>(numColunas, 0.0));
}

Matriz::Matriz(const Matriz& outra) : numLinhas(outra.numLinhas), numColunas(outra.numColunas), dados(outra.dados) {}

Matriz& Matriz::operator=(const Matriz& outra) {
    if (this == &outra) {
        return *this;
    }
    numLinhas = outra.numLinhas;
    numColunas = outra.numColunas;
    dados = outra.dados;
    return *this;
}

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
        throw std::invalid_argument("Número de colunas da primeira matriz deve ser igual ao número de linhas da segunda para multiplicação.");
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

int Matriz::obterLinhas() const {
    return numLinhas;
}

int Matriz::obterColunas() const {
    return numColunas;
}

Matriz Matriz::identidade(int tamanho) {
    Matriz id(tamanho, tamanho);
    for (int i = 0; i < tamanho; ++i) {
        id(i, i) = 1.0;
    }
    return id;
}

Matriz Matriz::translacao(double dx, double dy) {
    Matriz t = identidade(3);
    t(0, 2) = dx;
    t(1, 2) = dy;
    return t;
}

Matriz Matriz::escala(double sx, double sy) {
    Matriz s = identidade(3);
    s(0, 0) = sx;
    s(1, 1) = sy;
    return s;
}

Matriz Matriz::rotacao(double anguloGraus) {
    double radianos = anguloGraus * M_PI / 180.0;
    double cosAngulo = std::cos(radianos);
    double sinAngulo = std::sin(radianos);

    Matriz r = identidade(3);
    r(0, 0) = cosAngulo;
    r(0, 1) = -sinAngulo;
    r(1, 0) = sinAngulo;
    r(1, 1) = cosAngulo;
    return r;
}

void Matriz::imprimir(QString nome) const {
    qDebug().noquote() << nome << ":" << numLinhas << "x" << numColunas;
    QString linhaStr;
    for (int i = 0; i < numLinhas; ++i) {
        linhaStr.clear();
        for (int j = 0; j < numColunas; ++j) {
            linhaStr += QString::number(dados[i][j], 'f', 2) + "\t";
        }
        qDebug().noquote() << linhaStr;
    }
}
