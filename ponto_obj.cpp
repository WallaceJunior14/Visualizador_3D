#include "ponto_obj.h"
#include "bounding_box.h"
#include <QRect>    // <-- ADICIONADO: Inclui a definição de QRect
#include <QDebug>   // Para qWarning

PontoObj::PontoObj(const QString& nome, const Ponto3D& coordenada, const QColor& corPonto)
    : ObjetoGrafico(nome, TipoObjeto::PONTO) {
    adicionarPontoOriginalMundo(coordenada);
    definirCor(corPonto);
}


// --- IMPLEMENTAÇÃO DOS MÉTODOS VIRTUAIS ---

/**
 * @brief Implementação corrigida da função 'desenhar'.
 * Mapeia a coordenada NDC do ponto para a viewport e desenha um ponto.
 */
void PontoObj::desenhar(QPainter* painter, const QRect& viewport) const {
    if (pontosClip.isEmpty()) {
        return;
    }

    painter->setPen(obterCor());

    const Ponto3D& p_ndc = pontosClip.first();

    // Mapeia o ponto de NDC [-1, 1] para as coordenadas da viewport
    QPoint ponto_tela(
        viewport.x() + (p_ndc.obterX() + 1.0) * viewport.width() / 2.0,
        viewport.y() + (1.0 - p_ndc.obterY()) * viewport.height() / 2.0 // Y invertido
        );

    // Desenha um único pixel na tela
    painter->drawPoint(ponto_tela);
}

/**
 * @brief Implementação otimizada da Bounding Box para um ponto.
 * (Nenhuma alteração necessária)
 */
BoundingBox PontoObj::obterBBox() const {
    if (obterPontosOriginaisMundo().isEmpty()) {
        return BoundingBox(); // BBox inválida
    }
    const Matriz& matObjeto = obterMatrizTransformacao();
    Ponto3D pontoTransformado = matObjeto * obterCoordenada();
    return BoundingBox(pontoTransformado);
}

/**
 * @brief Implementação otimizada do centro geométrico para um ponto.
 * (Nenhuma alteração necessária)
 */
Ponto3D PontoObj::calcularCentroGeometrico() const {
    // O centro geométrico de um ponto é o próprio ponto.
    return obterCoordenada();
}


// <-- REMOVIDO: A implementação de PontoObj::recalcularPontos foi deletada.
// A classe agora herda e utiliza a implementação de ObjetoGrafico::recalcularPontos(const Camera&).


// Métodos específicos do Ponto (sem alterações)
void PontoObj::definirCoordenada(const Ponto3D& coordenada) {
    // Limpa a lista para garantir que há apenas um ponto
    pontosOriginaisMundo.clear();
    adicionarPontoOriginalMundo(coordenada);
}

Ponto3D PontoObj::obterCoordenada() const {
    if (!obterPontosOriginaisMundo().isEmpty()) {
        return obterPontosOriginaisMundo().first();
    }
    qWarning("PontoObj::obterCoordenada() chamado em um Ponto sem coordenada definida.");
    return Ponto3D();
}
