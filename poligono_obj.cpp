#include "poligono_obj.h"
#include "bounding_box.h"
#include <QRect> // <-- ADICIONADO: Inclui a definição de QRect

// O construtor e os métodos específicos do Polígono permanecem os mesmos.
PoligonoObj::PoligonoObj(const QString& nome, const QList<Ponto3D>& vertices, const QColor& corPoligono)
    : ObjetoGrafico(nome, TipoObjeto::POLIGONO) {
    definirPontosOriginaisMundo(vertices);
    definirCor(corPoligono);
}

void PoligonoObj::adicionarVertice(const Ponto3D& vertice) {
    adicionarPontoOriginalMundo(vertice);
}

void PoligonoObj::definirVertices(const QList<Ponto3D>& vertices) {
    definirPontosOriginaisMundo(vertices);
}

const QList<Ponto3D>& PoligonoObj::obterVertices() const {
    return obterPontosOriginaisMundo();
}


// --- IMPLEMENTAÇÕES DOS MÉTODOS VIRTUAIS ---

/**
 * @brief Implementação corrigida da função 'desenhar'.
 * Mapeia diretamente os pontos de NDC [-1, 1] para as coordenadas do QRect da viewport.
 */
void PoligonoObj::desenhar(QPainter* painter, const QRect& viewport) const {
    if (pontosClip.size() < 2) {
        return;
    }

    painter->setPen(obterCor());

    // Função auxiliar para mapear um ponto de NDC para a tela (viewport)
    auto mapearNdcParaTela = [&](const Ponto3D& p_ndc) {
        // Converte de [-1, 1] para [0, 1]
        double x_norm = (p_ndc.obterX() + 1.0) / 2.0;
        double y_norm = (1.0 - p_ndc.obterY()) / 2.0; // Inverte Y: NDC Y cresce para cima, tela Y cresce para baixo

        // Mapeia para as dimensões da viewport
        double x_tela = viewport.x() + x_norm * viewport.width();
        double y_tela = viewport.y() + y_norm * viewport.height();

        return QPoint(static_cast<int>(x_tela), static_cast<int>(y_tela));
    };

    // Itera pelos pontos em NDC para desenhar as arestas do polígono.
    for (int i = 0; i < pontosClip.size(); ++i) {
        const Ponto3D& p1_ndc = pontosClip.at(i);
        const Ponto3D& p2_ndc = pontosClip.at((i + 1) % pontosClip.size()); // Fecha o polígono

        // Mapeia os pontos de NDC para as coordenadas da tela
        QPoint p1_tela = mapearNdcParaTela(p1_ndc);
        QPoint p2_tela = mapearNdcParaTela(p2_ndc);

        // Desenha a linha
        painter->drawLine(p1_tela, p2_tela);
    }
}

/**
 * @brief Implementação da função 'obterBBox'.
 * (Esta função não precisou de alterações, pois já estava correta)
 */
BoundingBox PoligonoObj::obterBBox() const {
    if (obterPontosOriginaisMundo().isEmpty()) {
        return BoundingBox();
    }

    const Matriz& matObjeto = obterMatrizTransformacao();
    Ponto3D primeiroPontoTransformado = matObjeto * obterPontosOriginaisMundo().first();
    BoundingBox bbox(primeiroPontoTransformado);

    for (int i = 1; i < obterPontosOriginaisMundo().size(); ++i) {
        Ponto3D pontoTransformado = matObjeto * obterPontosOriginaisMundo().at(i);
        bbox.expandir(pontoTransformado);
    }

    return bbox;
}


// <-- REMOVIDO: A implementação de PoligonoObj::recalcularPontos foi deletada.
// A classe agora herda e utiliza a implementação de ObjetoGrafico::recalcularPontos(const Camera&).
