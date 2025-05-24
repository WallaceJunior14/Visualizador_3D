// (Conteúdo anterior de objeto_grafico.cpp...)
#include "objeto_grafico.h"
#include <numeric> // Para std::accumulate (se necessário para centroide mais complexo)

ObjetoGrafico::ObjetoGrafico(const QString& nomeObjeto, TipoObjeto tipoObjeto)
    : nome(nomeObjeto), tipo(tipoObjeto), matrizTransformacaoAcumulada(Matriz::identidade(3)), cor(Qt::black) {}

QString ObjetoGrafico::obterNome() const {
    return nome;
}

void ObjetoGrafico::definirNome(const QString& novoNome) {
    nome = novoNome;
}

TipoObjeto ObjetoGrafico::obterTipo() const {
    return tipo;
}

const QList<Ponto2D>& ObjetoGrafico::obterPontosOriginaisMundo() const {
    return pontosOriginaisMundo;
}

const QList<Ponto2D>& ObjetoGrafico::obterPontosMundoTransformados() const {
    return pontosMundoTransformados;
}

const QList<Ponto2D>& ObjetoGrafico::obterPontosSCN() const {
    return pontosSCN;
}

const Matriz& ObjetoGrafico::obterMatrizTransformacaoAcumulada() const {
    return matrizTransformacaoAcumulada;
}

void ObjetoGrafico::aplicarTransformacao(const Matriz& transformacao) {
    matrizTransformacaoAcumulada = transformacao * matrizTransformacaoAcumulada;
    // AVISO: Após aplicar a transformação, é crucial chamar recalcularPontosTransformados
    // passando a matriz de normalização atual para que os pontos SCN sejam atualizados.
    // Ex: objeto->aplicarTransformacao(T);
    //     objeto->recalcularPontosTransformados(janelaMundo->obterMatrizNormalizacao());
}

void ObjetoGrafico::recalcularPontosTransformados(const Matriz& matrizNormalizacao) {
    pontosMundoTransformados.clear();
    for (const Ponto2D& pOrig : pontosOriginaisMundo) {
        Matriz pMat = matrizTransformacaoAcumulada * pOrig; // pOrig já é uma Matriz 3x1
        pontosMundoTransformados.append(Ponto2D(pMat));
    }

    pontosSCN.clear();
    for (const Ponto2D& pMundoTransf : pontosMundoTransformados) {
        Matriz pMatSCN = matrizNormalizacao * pMundoTransf;
        Ponto2D pontoSCN_temp(pMatSCN);
        pontoSCN_temp.normalizar(); // Garante que w=1 se não for ponto no infinito
        pontosSCN.append(pontoSCN_temp);
    }
}

void ObjetoGrafico::definirPontosOriginaisMundo(const QList<Ponto2D>& pontos) {
    pontosOriginaisMundo = pontos;
    // Após definir novos pontos, a matriz de transformação acumulada não é resetada,
    // mas os pontos transformados precisam ser recalculados.
}

void ObjetoGrafico::adicionarPontoOriginalMundo(const Ponto2D& ponto) {
    pontosOriginaisMundo.append(ponto);
}

Ponto2D ObjetoGrafico::calcularCentroGeometrico() const {
    if (pontosOriginaisMundo.isEmpty()) {
        return Ponto2D(0, 0); // Ou lançar exceção
    }

    double somaX = 0.0;
    double somaY = 0.0;
    for (const Ponto2D& p : pontosOriginaisMundo) {
        somaX += p.obterX(); // Usa obterX() que considera a normalização por W, embora para pontos originais W seja 1.
        somaY += p.obterY();
    }
    int numPontos = pontosOriginaisMundo.size();
    return Ponto2D(somaX / numPontos, somaY / numPontos);
}

QColor ObjetoGrafico::obterCor() const {
    return cor;
}

void ObjetoGrafico::definirCor(const QColor& novaCor) {
    cor = novaCor;
}
