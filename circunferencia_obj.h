#ifndef CIRCUNFERENCIA_OBJ_H
#define CIRCUNFERENCIA_OBJ_H

#include "objeto_grafico.h"
#include <cmath> // Para M_PI, cos, sin

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class CircunferenciaObj : public ObjetoGrafico {
public:
    CircunferenciaObj(const QString& nome, const Ponto2D& centro, double raio,
                      const QColor& corCirc = Qt::black, int numSegmentos = 36);

    Ponto2D calcularCentroGeometrico() const override;

    Ponto2D obterCentroOriginal() const;
    double obterRaioOriginal() const;

    void definirCentroRaio(const Ponto2D& novoCentro, double novoRaio, int numSegmentos = 36);

private:
    void gerarPontosAproximacao(int numSegmentos);

    Ponto2D centroOriginal; // Armazena o centro original para referência
    double raioOriginal;    // Armazena o raio original
};

#endif // CIRCUNFERENCIA_OBJ_H
