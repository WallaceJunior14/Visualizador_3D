#include "ponto3d.h"
#include "matriz.h"
#include <stdexcept>

// --- Construtores ---
Ponto3D::Ponto3D(double x, double y, double z, double w) : dados_m(4, 1) {
    dados_m(0, 0) = x;
    dados_m(1, 0) = y;
    dados_m(2, 0) = z;
    dados_m(3, 0) = w;
}

Ponto3D::Ponto3D(const Matriz& m) : dados_m(4, 1) {
    if (m.obterLinhas() != 4 || m.obterColunas() != 1) {
        dados_m(0, 0) = 0; dados_m(1, 0) = 0; dados_m(2, 0) = 0; dados_m(3, 0) = 1;
        return;
    }
    dados_m = m;
}

// --- Getters e Setters ---
double Ponto3D::obterX() const { return dados_m(0, 0); } // <-- NOME REVERTIDO
double Ponto3D::obterY() const { return dados_m(1, 0); } // <-- NOME REVERTIDO
double Ponto3D::obterZ() const { return dados_m(2, 0); } // <-- NOME REVERTIDO
double Ponto3D::obterW() const { return dados_m(3, 0); } // <-- NOME REVERTIDO

void Ponto3D::definirX(double x) { dados_m(0, 0) = x; }
void Ponto3D::definirY(double y) { dados_m(1, 0) = y; }
void Ponto3D::definirZ(double z) { dados_m(2, 0) = z; }
void Ponto3D::definirW(double w) { dados_m(3, 0) = w; }

const Matriz& Ponto3D::obterMatriz() const { return dados_m; }

void Ponto3D::normalizar() {
    if (obterW() != 0.0 && obterW() != 1.0) {
        dados_m(0, 0) /= obterW();
        dados_m(1, 0) /= obterW();
        dados_m(2, 0) /= obterW();
        dados_m(3, 0) = 1.0;
    }
}

Ponto3D Ponto3D::normalizarVetor() const {
    double mag = this->magnitude();
    if (mag == 0.0) {
        return Ponto3D(0, 0, 0, 0);
    }
    return Ponto3D(obterX() / mag, obterY() / mag, obterZ() / mag, 0.0);
}

double Ponto3D::magnitude() const {
    return std::sqrt(obterX() * obterX() + obterY() * obterY() + obterZ() * obterZ());
}

// --- Implementações dos Operadores ---

Ponto3D Ponto3D::operator-(const Ponto3D& outro) const {
    return Ponto3D(this->obterX() - outro.obterX(),
                   this->obterY() - outro.obterY(),
                   this->obterZ() - outro.obterZ(),
                   0.0);
}

Ponto3D Ponto3D::operator*(double escalar) const {
    return Ponto3D(this->obterX() * escalar,
                   this->obterY() * escalar,
                   this->obterZ() * escalar,
                   this->obterW());
}

Ponto3D Ponto3D::produtoVetorial(const Ponto3D& a, const Ponto3D& b) {
    double cx = a.obterY() * b.obterZ() - a.obterZ() * b.obterY();
    double cy = a.obterZ() * b.obterX() - a.obterX() * b.obterZ();
    double cz = a.obterX() * b.obterY() - a.obterY() * b.obterX();
    return Ponto3D(cx, cy, cz, 0.0);
}

Ponto3D Ponto3D::operator+(const Ponto3D& outro) const {
    return Ponto3D(this->obterX() + outro.obterX(),
                   this->obterY() + outro.obterY(),
                   this->obterZ() + outro.obterZ(),
                   this->obterW() + outro.obterW());
}

Ponto3D Ponto3D::operator/(double escalar) const {
    if (escalar == 0.0) {
        return Ponto3D(0, 0, 0, 0);
    }
    return Ponto3D(this->obterX() / escalar,
                   this->obterY() / escalar,
                   this->obterZ() / escalar,
                   this->obterW() / escalar);
}
