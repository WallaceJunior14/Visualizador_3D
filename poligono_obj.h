#ifndef POLIGONO_OBJ_H
#define POLIGONO_OBJ_H

#include "objeto_grafico.h"
#include <QList>

// Representa um objeto gráfico do tipo Polígono. [cite: 1]
// Um polígono é definido por uma lista de vértices no mundo. [cite: 5]
class PoligonoObj : public ObjetoGrafico {
public:
    // Construtor: nome e lista de vértices do polígono.
    PoligonoObj(const QString& nome, const QList<Ponto2D>& vertices, const QColor& corPoligono = Qt::black);

    // Adiciona um vértice ao polígono.
    void adicionarVertice(const Ponto2D& vertice);

    // Define todos os vértices do polígono.
    void definirVertices(const QList<Ponto2D>& vertices);
    const QList<Ponto2D>& obterVertices() const; // Retorna os pontosOriginaisMundo

    // O cálculo do centro geométrico herdado de ObjetoGrafico (média dos vértices)
    // geralmente é suficiente para polígonos convexos. Para polígonos complexos,
    // o centroide pode ser mais apropriado, mas a média é um bom começo.
};

#endif // POLIGONO_OBJ_H
