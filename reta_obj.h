#ifndef RETA_OBJ_H
#define RETA_OBJ_H

#include "objeto_grafico.h"
#include <QPainter>

// Forward declarations
class BoundingBox;
class QRect; // <-- ALTERADO: Usamos QRect para a viewport.
// class Janela; // <-- REMOVIDO

// Representa um objeto gráfico do tipo Reta (segmento de linha) em um espaço 3D.
class RetaObj : public ObjetoGrafico {
public:
    // Construtor: nome e coordenadas dos dois pontos 3D da reta.
    RetaObj(const QString& nome, const Ponto3D& p1, const Ponto3D& p2, const QColor& corReta = Qt::black);

    // Métodos específicos da Reta (sem alterações)
    void definirPontos(const Ponto3D& p1, const Ponto3D& p2);
    Ponto3D obterPonto1() const;
    Ponto3D obterPonto2() const;

    // --- MÉTODOS VIRTUAIS OBRIGATÓRIOS HERDADOS ---

    /**
     * @brief Desenha a reta na tela usando as coordenadas de clipping.
     * @param painter O objeto QPainter para realizar o desenho.
     * @param viewport O retângulo da tela para mapear coordenadas NDC.
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override; // <-- ALTERADO

    /**
     * @brief Calcula e retorna a Bounding Box da reta no sistema de coordenadas do mundo.
     * @return A Bounding Box do objeto.
     */
    BoundingBox obterBBox() const override;

    /**
     * @brief Sobrescreve o cálculo do centro geométrico (ponto médio da reta).
     * @return O ponto central da reta.
     */
    Ponto3D calcularCentroGeometrico() const override;

    // <-- REMOVIDO: A sobrescrita de recalcularPontos não é mais necessária.
    // A classe usará a implementação herdada de ObjetoGrafico.
};

#endif // RETA_OBJ_H
