#include "poligono_obj.h"

PoligonoObj::PoligonoObj(const QString& nome, const QList<Ponto2D>& vertices, const QColor& corPoligono)
    : ObjetoGrafico(nome, TipoObjeto::POLIGONO) {
    for (const Ponto2D& vertice : vertices) {
        adicionarPontoOriginalMundo(vertice);
    }
    definirCor(corPoligono);
}

void PoligonoObj::adicionarVertice(const Ponto2D& vertice) {
    adicionarPontoOriginalMundo(vertice);
    // Recalcular pontos transformados após alteração
}

void PoligonoObj::definirVertices(const QList<Ponto2D>& vertices) {
    pontosOriginaisMundo.clear();
    for (const Ponto2D& vertice : vertices) {
        adicionarPontoOriginalMundo(vertice);
    }
    // Recalcular pontos transformados após alteração
}

const QList<Ponto2D>& PoligonoObj::obterVertices() const {
    return obterPontosOriginaisMundo();
}
