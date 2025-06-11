#include "malha_obj.h"
#include "ponto2d.h" // Precisamos para projeção e viewport
#include "clipper.h" // Assumindo que o clipper está acessível

#include <QPainter>
#include <QRect>

// Implementação simples de um clipper para o exemplo.
// No seu código, você já tem uma instância no FrameDesenho.
// Esta implementação é apenas para garantir que o código compile de forma isolada.
Clipper3D clipper(-1.0, -1.0, -1.0, 1.0, 1.0, 1.0);

MalhaObj::MalhaObj(const QString& nome, const QList<Ponto3D>& vertices, const QList<QPair<int, int>>& arestas)
    : ObjetoGrafico(nome, TipoObjeto::MALHA), arestas(arestas) {
    definirPontosOriginaisMundo(vertices);
}

void MalhaObj::desenhar(QPainter* painter, const QRect& viewport) const {
    // Propositalmente vazio.
    (void)painter; // Evita warning de variável não utilizada
    (void)viewport; // Evita warning de variável não utilizada
}

BoundingBox MalhaObj::obterBBox() const {
    const auto& pontos = obterPontosOriginaisMundo();
    if (pontos.isEmpty()) {
        return BoundingBox(); // Retorna uma BBox vazia/inválida
    }

    const Matriz& matObjeto = obterMatrizTransformacao();

    // Inicia a BBox com o primeiro ponto transformado
    Ponto3D primeiroPontoTransformado = matObjeto * pontos.first();
    BoundingBox bbox(primeiroPontoTransformado);

    // Expande a BBox para incluir todos os outros pontos transformados
    for (int i = 1; i < pontos.size(); ++i) {
        Ponto3D pontoTransformado = matObjeto * pontos.at(i);
        bbox.expandir(pontoTransformado);
    }

    return bbox;
}
