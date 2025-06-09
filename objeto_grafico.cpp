#include "objeto_grafico.h"
#include "bounding_box.h" // Incluído para implementação padrão de BBox
#include "camera.h"

// Construtor inicializa com uma matriz de transformação identidade 4x4.
ObjetoGrafico::ObjetoGrafico(const QString& nomeObjeto, TipoObjeto tipoObjeto)
    : nome(nomeObjeto),
    tipo(tipoObjeto),
    matrizTransformacao(Matriz::identidade(4)), // Nome da matriz atualizado
    cor(Qt::black) {}

// --- MÉTODOS COMUNS ---

QString ObjetoGrafico::obterNome() const { return nome; }
void ObjetoGrafico::definirNome(const QString& novoNome) { nome = novoNome; }
TipoObjeto ObjetoGrafico::obterTipo() const { return tipo; } // Não precisa ser virtual
const QList<Ponto3D>& ObjetoGrafico::obterPontosOriginaisMundo() const { return pontosOriginaisMundo; }
const QList<Ponto3D>& ObjetoGrafico::obterPontosClip() const { return pontosClip; }
const Matriz& ObjetoGrafico::obterMatrizTransformacao() const { return matrizTransformacao; } // Nome do método atualizado
QColor ObjetoGrafico::obterCor() const { return cor; }
void ObjetoGrafico::definirCor(const QColor& novaCor) { cor = novaCor; }
void ObjetoGrafico::definirPontosOriginaisMundo(const QList<Ponto3D>& pontos) { pontosOriginaisMundo = pontos; }
void ObjetoGrafico::adicionarPontoOriginalMundo(const Ponto3D& ponto) { pontosOriginaisMundo.append(ponto); }

// Aplica uma nova transformação à matriz de modelo existente.
void ObjetoGrafico::aplicarTransformacao(const Matriz& transformacao) {
    // A ordem T_nova * T_antiga aplica a 'transformacao' em relação ao sistema de coordenadas do mundo.
    matrizTransformacao = transformacao * matrizTransformacao;
}


// --- MÉTODOS VIRTUAIS COM IMPLEMENTAÇÃO PADRÃO ---

/**
 * @brief Implementação padrão para recalcular pontos.
 * Esta função é tão genérica que TODAS as suas classes filhas podem usá-la
 * sem precisar de uma implementação própria.
 */
void ObjetoGrafico::recalcularPontos(const Camera& camera) { // <-- ALTERADO: Assinatura da função
    pontosClip.clear();

    // Obtém as matrizes diretamente do objeto Camera
    Matriz matView = camera.obterMatrizView();
    Matriz matProj = camera.obterMatrizProjecao();

    // Pré-calcula a matriz Model-View-Projection (MVP)
    // A lógica interna permanece a mesma
    Matriz matMVP = matProj * matView * matrizTransformacao;

    for (const Ponto3D& pOrig : pontosOriginaisMundo) {
        // Aplica a transformação completa
        Ponto3D pontoEmClip = matMVP * pOrig;
        // Normaliza (divisão por W) para ir de Coordenadas Homogêneas para NDC
        pontoEmClip.normalizar();
        pontosClip.append(pontoEmClip);
    }
}

/**
 * @brief Implementação padrão para calcular o centro geométrico.
 * Funciona bem para polígonos e nuvens de pontos.
 */
Ponto3D ObjetoGrafico::calcularCentroGeometrico() const {
    if (pontosOriginaisMundo.isEmpty()) {
        return Ponto3D(0, 0, 0);
    }
    Ponto3D soma; // Inicializa com (0,0,0)
    for (const Ponto3D& p : pontosOriginaisMundo) {
        soma = soma + p;
    }
    return soma / pontosOriginaisMundo.size();
}
