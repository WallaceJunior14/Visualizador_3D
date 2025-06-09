#include "reta_obj.h"
#include "bounding_box.h"
#include <QRect>    // <-- ADICIONADO: Inclui a definição de QRect
#include <QDebug>   // Para qWarning

RetaObj::RetaObj(const QString& nome, const Ponto3D& p1, const Ponto3D& p2, const QColor& corReta)
    : ObjetoGrafico(nome, TipoObjeto::RETA) {
    adicionarPontoOriginalMundo(p1);
    adicionarPontoOriginalMundo(p2);
    definirCor(corReta);
}


// --- IMPLEMENTAÇÃO DOS MÉTODOS VIRTUAIS ---

/**
 * @brief Implementação corrigida e robusta da função 'desenhar'.
 * Usa o QRect passado como parâmetro para mapear corretamente os pontos de NDC para a tela.
 */
void RetaObj::desenhar(QPainter* painter, const QRect& viewport) const {
    if (pontosClip.size() != 2) {
        return;
    }

    painter->setPen(obterCor());

    const Ponto3D& p1_ndc = pontosClip.at(0);
    const Ponto3D& p2_ndc = pontosClip.at(1);

    // Mapeia os pontos de NDC [-1, 1] para as coordenadas da viewport,
    // considerando o offset (x,y) da viewport.
    QPoint p1_tela(
        viewport.x() + (p1_ndc.obterX() + 1.0) * viewport.width() / 2.0,
        viewport.y() + (1.0 - p1_ndc.obterY()) * viewport.height() / 2.0 // Y invertido
        );
    QPoint p2_tela(
        viewport.x() + (p2_ndc.obterX() + 1.0) * viewport.width() / 2.0,
        viewport.y() + (1.0 - p2_ndc.obterY()) * viewport.height() / 2.0 // Y invertido
        );

    painter->drawLine(p1_tela, p2_tela);
}

/**
 * @brief Implementação da função 'obterBBox'.
 * (Nenhuma alteração necessária, já estava correta)
 */
BoundingBox RetaObj::obterBBox() const {
    if (obterPontosOriginaisMundo().size() != 2) {
        return BoundingBox();
    }

    const Matriz& matObjeto = obterMatrizTransformacao();
    Ponto3D p1_transformado = matObjeto * obterPonto1();
    Ponto3D p2_transformado = matObjeto * obterPonto2();

    return BoundingBox(p1_transformado, p2_transformado);
}

/**
 * @brief Implementação otimizada para o centro geométrico de uma reta.
 * (Nenhuma alteração necessária, já estava correta)
 */
Ponto3D RetaObj::calcularCentroGeometrico() const {
    if (obterPontosOriginaisMundo().size() == 2) {
        const Ponto3D& p1 = obterPontosOriginaisMundo().at(0);
        const Ponto3D& p2 = obterPontosOriginaisMundo().at(1);
        return (p1 + p2) / 2.0;
    }
    return Ponto3D();
}

// Métodos específicos da Reta (sem alterações)
void RetaObj::definirPontos(const Ponto3D& p1, const Ponto3D& p2) {
    pontosOriginaisMundo.clear();
    adicionarPontoOriginalMundo(p1);
    adicionarPontoOriginalMundo(p2);
}

Ponto3D RetaObj::obterPonto1() const {
    if (!obterPontosOriginaisMundo().isEmpty()) {
        return obterPontosOriginaisMundo().first();
    }
    qWarning("RetaObj::obterPonto1() chamado em uma Reta sem pontos.");
    return Ponto3D();
}

Ponto3D RetaObj::obterPonto2() const {
    if (obterPontosOriginaisMundo().size() >= 2) {
        return obterPontosOriginaisMundo().at(1);
    }
    qWarning("RetaObj::obterPonto2() chamado em uma Reta sem ponto 2.");
    return Ponto3D();
}

// <-- REMOVIDO: A implementação de RetaObj::recalcularPontos foi deletada.
// A classe agora herda e utiliza a implementação de ObjetoGrafico::recalcularPontos(const Camera&).
