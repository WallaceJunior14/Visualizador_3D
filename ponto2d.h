#ifndef PONTO2D_H
#define PONTO2D_H

#include "matriz.h"
#include <QString> // Para o construtor que pode receber nome

// Classe Ponto2D representa um ponto no espaço 2D usando coordenadas homogêneas.
// Herda de Matriz, sendo um Ponto2D uma matriz coluna 3x1: [x, y, w]^T.
// A coordenada w é tipicamente 1 para pontos.
class Ponto2D : public Matriz {
public:
    // Construtor padrão: ponto na origem (0,0,1).
    Ponto2D(double x = 0.0, double y = 0.0, double w = 1.0);

    // Construtor de cópia a partir de Matriz (para resultados de transformações)
    explicit Ponto2D(const Matriz& m);

    // Getters para as coordenadas.
    // Retornam as coordenadas cartesianas (x/w, y/w) se w não for 0 ou 1.
    double obterX() const;
    double obterY() const;
    double obterW() const;

    // Setters para as coordenadas.
    void definirX(double x);
    void definirY(double y);
    void definirW(double w); // Geralmente w é 1.

    // Normaliza o ponto (divide x e y por w) se w não for 0 nem 1.
    // Isso é útil após transformações projetivas, mas para transformações afins (2D), w geralmente permanece 1.
    void normalizar();
};

#endif // PONTO2D_H
