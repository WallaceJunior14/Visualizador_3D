#ifndef POLIGONO_OBJ_H
#define POLIGONO_OBJ_H

#include "objeto_grafico.h"
#include <QList>

// Representa um objeto gráfico do tipo Polígono
// Um polígono é definido por uma lista de vértices no mundo
class PoligonoObj : public ObjetoGrafico {
public:
    // Construtor: nome e lista de vértices do polígono.
    PoligonoObj(const QString& nome, const QList<Ponto2D>& vertices, const QColor& corPoligono = Qt::black);

    // Adiciona um vértice ao polígono.
    void adicionarVertice(const Ponto2D& vertice);

    // Define todos os vértices do polígono.
    void definirVertices(const QList<Ponto2D>& vertices);
    const QList<Ponto2D>& obterVertices() const; // Retorna os pontosOriginaisMundo

};

#endif // POLIGONO_OBJ_H
