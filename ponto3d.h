#ifndef PONTO3D_H
#define PONTO3D_H

#include "matriz.h" // <-- CORREÇÃO: Inclui a definição completa da Matriz.
#include <cmath>

// A declaração antecipada foi removida pois agora usamos o #include.

class Ponto3D {
public:
    // Construtor padrão: ponto na origem (0,0,0,1).
    Ponto3D(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0);

    // Construtor de cópia a partir de Matriz (para resultados de transformações)
    explicit Ponto3D(const Matriz& m);

    // Getters para as coordenadas.
    double obterX() const;
    double obterY() const;
    double obterZ() const;
    double obterW() const;

    // Setters para as coordenadas.
    void definirX(double x);
    void definirY(double y);
    void definirZ(double z);
    void definirW(double w);

    // Retorna a representação interna como uma Matriz 4x1
    const Matriz& obterMatriz() const;

    // Normaliza o PONTO (divide x, y, e z por w). Modifica o objeto atual.
    void normalizar();

    // --- MÉTODOS PARA OPERAÇÕES VETORIAIS ---

    // Retorna o comprimento (magnitude) do vetor (ignora w).
    double magnitude() const;

    // Retorna uma versão normalizada do VETOR (comprimento 1), com w=0.
    Ponto3D normalizarVetor() const;

    // --- SOBRECARGA DE OPERADORES ---
    Ponto3D operator+(const Ponto3D& outro) const;
    Ponto3D operator-(const Ponto3D& outro) const;
    Ponto3D operator*(double escalar) const;
    Ponto3D operator/(double escalar) const;

    // --- MÉTODOS ESTÁTICOS ---
    static Ponto3D produtoVetorial(const Ponto3D& a, const Ponto3D& b);

private:
    Matriz dados_m; // Agora o compilador sabe o que é uma Matriz e qual seu tamanho.
};

#endif // PONTO3D_H
