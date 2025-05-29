#ifndef RETA_OBJ_H
#define RETA_OBJ_H

#include "objeto_grafico.h"

// Representa um objeto gráfico do tipo Reta.
// Uma reta é definida por dois pontos no mundo.
class RetaObj : public ObjetoGrafico {
public:
    // Construtor: nome e coordenadas dos dois pontos da reta.
    RetaObj(const QString& nome, const Ponto2D& p1, const Ponto2D& p2, const QColor& corReta = Qt::black);

    // Sobrescreve o cálculo do centro geométrico (ponto médio da reta).
    Ponto2D calcularCentroGeometrico() const override;

    // Define os pontos da reta.
    void definirPontos(const Ponto2D& p1, const Ponto2D& p2);
    Ponto2D obterPonto1() const;
    Ponto2D obterPonto2() const;
};

#endif // RETA_OBJ_H
