#include "reta_obj.h"

RetaObj::RetaObj(const QString& nome, const Ponto2D& p1, const Ponto2D& p2, const QColor& corReta)
    : ObjetoGrafico(nome, TipoObjeto::RETA) {
    adicionarPontoOriginalMundo(p1);
    adicionarPontoOriginalMundo(p2);
    definirCor(corReta);
}

Ponto2D RetaObj::calcularCentroGeometrico() const {
    if (pontosOriginaisMundo.size() == 2) {
        const Ponto2D& p1 = pontosOriginaisMundo.at(0);
        const Ponto2D& p2 = pontosOriginaisMundo.at(1);
        return Ponto2D((p1.obterX() + p2.obterX()) / 2.0,
                       (p1.obterY() + p2.obterY()) / 2.0);
    }
    return Ponto2D(0,0); // Caso de erro ou reta não definida corretamente
}

void RetaObj::definirPontos(const Ponto2D& p1, const Ponto2D& p2) {
    pontosOriginaisMundo.clear();
    adicionarPontoOriginalMundo(p1);
    adicionarPontoOriginalMundo(p2);
    // Recalcular pontos transformados após alteração
}

Ponto2D RetaObj::obterPonto1() const {
    if (pontosOriginaisMundo.size() >= 1) {
        return pontosOriginaisMundo.at(0);
    }
    qWarning("RetaObj::obterPonto1() chamado em uma Reta sem ponto 1 definido.");
    return Ponto2D();
}

Ponto2D RetaObj::obterPonto2() const {
    if (pontosOriginaisMundo.size() >= 2) {
        return pontosOriginaisMundo.at(1);
    }
    qWarning("RetaObj::obterPonto2() chamado em uma Reta sem ponto 2 definido.");
    return Ponto2D();
}
