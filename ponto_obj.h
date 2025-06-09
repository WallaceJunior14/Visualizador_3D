#ifndef PONTO_OBJ_H
#define PONTO_OBJ_H

#include "objeto_grafico.h"
#include <QPainter>

// Forward declarations
class BoundingBox;
class QRect; // <-- ALTERADO: Usamos QRect para a viewport.

// Representa um objeto gráfico do tipo Ponto em um espaço 3D.
class PontoObj : public ObjetoGrafico {
public:
    // Construtor: nome e coordenada 3D do ponto.
    PontoObj(const QString& nome, const Ponto3D& coordenada, const QColor& corPonto = Qt::black);

    // Métodos específicos do Ponto (sem alterações)
    void definirCoordenada(const Ponto3D& coordenada);
    Ponto3D obterCoordenada() const;

    // --- MÉTODOS VIRTUAIS OBRIGATÓRIOS HERDADOS ---

    /**
     * @brief Desenha o ponto na tela.
     * @param painter O objeto QPainter para realizar o desenho.
     * @param viewport O retângulo da tela para mapear coordenadas NDC.
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override; // <-- ALTERADO

    /**
     * @brief Calcula a Bounding Box do ponto (que é ele mesmo).
     */
    BoundingBox obterBBox() const override;

    /**
     * @brief Sobrescreve o cálculo do centro geométrico (é o próprio ponto).
     */
    Ponto3D calcularCentroGeometrico() const override;

    // <-- REMOVIDO: A sobrescrita de recalcularPontos não é mais necessária.
};

#endif // PONTO_OBJ_H
