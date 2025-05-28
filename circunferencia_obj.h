// circunferencia_obj.h
#ifndef CIRCUNFERENCIA_OBJ_H
#define CIRCUNFERENCIA_OBJ_H

#include "objeto_grafico.h"

class CircunferenciaObj : public ObjetoGrafico {
public:
    CircunferenciaObj(const QString& nome, const Ponto2D& centro, double raio, const QColor& cor);

    Ponto2D obterCentroOriginal() const;
    double obterRaioOriginal() const;

    void definirCentroOriginal(const Ponto2D& novoCentro);
    void definirRaioOriginal(double novoRaio);

    // Sobrescrever para gerar pontos de aproximação com base no centro/raio originais
    // void recalcularPontosTransformados(const Matriz& matrizNormalizacao) override; // Exemplo

private:
    Ponto2D centroOriginal_m; // Renomeado para evitar conflito com método herdado se houver
    double raioOriginal_m;

    void gerarPontosAproximacao(); // Helper interno para atualizar pontosOriginaisMundo
};

#endif // CIRCUNFERENCIA_OBJ_H
