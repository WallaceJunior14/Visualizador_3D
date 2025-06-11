#ifndef MALHA_OBJ_H
#define MALHA_OBJ_H

#include "objeto_grafico.h"
#include "bounding_box.h"
#include <QPair>

class MalhaObj : public ObjetoGrafico {
public:
    MalhaObj(const QString& nome,
             const QList<Ponto3D>& vertices,
             const QList<QPair<int, int>>& arestas);

    // Getter público para as arestas, necessário para o FrameDesenho
    const QList<QPair<int, int>>& obterArestas() const { return arestas; }

    // --- Implementação da Interface Abstrata ---
    // Sobrescreve as funções virtuais puras da classe ObjetoGrafico.
    void desenhar(QPainter* painter, const QRect& viewport) const override;
    BoundingBox obterBBox() const override;

private:
    QList<QPair<int, int>> arestas;
};

#endif // MALHA_OBJ_H
