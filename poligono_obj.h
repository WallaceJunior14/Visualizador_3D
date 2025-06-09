#ifndef POLIGONO_OBJ_H
#define POLIGONO_OBJ_H

#include "objeto_grafico.h"
#include <QList>
#include <QPainter>

// Forward declarations
class BoundingBox;
class QRect; // <-- ALTERADO: Usamos QRect para a viewport.
// class Janela; // <-- REMOVIDO

// Representa um objeto gráfico do tipo Polígono em um espaço 3D.
class PoligonoObj : public ObjetoGrafico {
public:
    // Construtor: nome e lista de vértices 3D do polígono.
    PoligonoObj(const QString& nome, const QList<Ponto3D>& vertices, const QColor& corPoligono = Qt::black);

    // Métodos específicos do polígono (sem alterações)
    void adicionarVertice(const Ponto3D& vertice);
    void definirVertices(const QList<Ponto3D>& vertices);
    const QList<Ponto3D>& obterVertices() const;

    // --- MÉTODOS VIRTUAIS OBRIGATÓRIOS HERDADOS ---
    // A palavra-chave 'override' garante que estamos sobrescrevendo uma função da classe base.

    /**
     * @brief Desenha o polígono na tela usando as coordenadas de clipping.
     * @param painter O objeto QPainter para realizar o desenho.
     * @param viewport O retângulo da tela para mapear coordenadas NDC.
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override; // <-- ALTERADO

    /**
     * @brief Calcula e retorna a Bounding Box do polígono no sistema de coordenadas do mundo.
     * @return A Bounding Box do objeto.
     */
    BoundingBox obterBBox() const override;

    // <-- REMOVIDO: A sobrescrita de recalcularPontos não é mais necessária.
    // A classe usará a implementação da classe base ObjetoGrafico, que já é adequada.
};

#endif // POLIGONO_OBJ_H
