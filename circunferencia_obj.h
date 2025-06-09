#ifndef CIRCUNFERENCIA_OBJ_H
#define CIRCUNFERENCIA_OBJ_H

#include "objeto_grafico.h"
#include <QPainter>

// Forward declarations
class BoundingBox;
class QRect; // <-- ALTERADO: Usamos QRect para a viewport.
// class Janela; // <-- REMOVIDO

class CircunferenciaObj : public ObjetoGrafico {
public:
    // Construtor
    CircunferenciaObj(const QString& nome, const Ponto3D& centro, double raio,
                      const Ponto3D& normal, const QColor& cor);

    // Getters e Setters (sem alterações)
    Ponto3D obterCentroOriginal() const;
    double obterRaioOriginal() const;
    Ponto3D obterNormal() const;
    void definirCentroOriginal(const Ponto3D& novoCentro);
    void definirRaioOriginal(double novoRaio);
    void definirNormal(const Ponto3D& novaNormal);

    // --- MÉTODOS VIRTUAIS OBRIGATÓRIOS HERDADOS ---

    /**
     * @brief Desenha a aproximação da circunferência na tela.
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override; // <-- ALTERADO

    /**
     * @brief Calcula a Bounding Box da circunferência no espaço do mundo.
     */
    BoundingBox obterBBox() const override;

    /**
     * @brief Sobrescreve o cálculo do centro para retornar o centro real. É mais rápido e preciso.
     */
    Ponto3D calcularCentroGeometrico() const override; // <-- ADICIONADO (Otimização)


    // <-- REMOVIDO: A sobrescrita de recalcularPontos não é mais necessária.

private:
    Ponto3D centroOriginal_m;
    double raioOriginal_m;
    Ponto3D normal_m; // Vetor normal ao plano da circunferência

    /**
     * @brief Gera os vértices que aproximam a circunferência e os armazena na classe base.
     */
    void gerarPontosAproximacao();
};

#endif // CIRCUNFERENCIA_OBJ_H
