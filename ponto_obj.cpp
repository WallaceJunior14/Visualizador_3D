#include "ponto_obj.h"

PontoObj::PontoObj(const QString& nome, const Ponto2D& coordenada, const QColor& corPonto)
    : ObjetoGrafico(nome, TipoObjeto::PONTO) {
    adicionarPontoOriginalMundo(coordenada);
    definirCor(corPonto);
}

Ponto2D PontoObj::calcularCentroGeometrico() const {
    if (!pontosOriginaisMundo.isEmpty()) {
        return pontosOriginaisMundo.first();
    }
    return Ponto2D(0,0); // Caso de erro ou ponto não definido
}

void PontoObj::definirCoordenada(const Ponto2D& coordenada) {
    pontosOriginaisMundo.clear();
    adicionarPontoOriginalMundo(coordenada);
    // Após alterar a geometria base, os pontos transformados precisam ser recalculados.
    // Ex: pontoObj->definirCoordenada(novaCoord);
    //     pontoObj->recalcularPontosTransformados(janelaMundo->obterMatrizNormalizacao());
}

Ponto2D PontoObj::obterCoordenada() const {
    if (!pontosOriginaisMundo.isEmpty()) {
        return pontosOriginaisMundo.first();
    }
    // Retornar um Ponto2D padrão ou lançar exceção se for mais apropriado
    qWarning("PontoObj::obterCoordenada() chamado em um objeto Ponto sem coordenadas definidas.");
    return Ponto2D(); // Ponto na origem por padrão
}
