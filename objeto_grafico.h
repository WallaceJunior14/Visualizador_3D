#ifndef OBJETO_GRAFICO_H
#define OBJETO_GRAFICO_H

#include <QString>
#include <QList>
#include <QColor> // Para cor do objeto
#include "ponto2d.h"
#include "matriz.h"
#include "tipos.h" // Para TipoObjeto

// Classe base abstrata para todos os objetos gráficos.
// Define a interface comum para manipulação e desenho de objetos.
class ObjetoGrafico {
public:
    // Construtor.
    ObjetoGrafico(const QString& nomeObjeto, TipoObjeto tipoObjeto);
    // Destrutor virtual para permitir limpeza correta em classes derivadas.
    virtual ~ObjetoGrafico() = default;


    // Getters e Setters.
    QString obterNome() const;
    void definirNome(const QString& novoNome);

    TipoObjeto obterTipo() const;

    const QList<Ponto2D>& obterPontosOriginaisMundo() const;
    const QList<Ponto2D>& obterPontosMundoTransformados() const;
    const QList<Ponto2D>& obterPontosSCN() const; // SCN = Sistema de Coordenadas Normalizadas

    const Matriz& obterMatrizTransformacaoAcumulada() const;

    // Aplica uma transformação à matriz acumulada do objeto.
    void aplicarTransformacao(const Matriz& transformacao);

    // Recalcula os pontos transformados (Mundo e SCN).
    // A matriz de normalização é necessária para calcular os pontos SCN.
    void recalcularPontosTransformados(const Matriz& matrizNormalizacao);

    // Define os pontos originais do objeto no sistema de coordenadas do mundo.
    // Esses são os pontos base antes de qualquer transformação acumulada do objeto.
    void definirPontosOriginaisMundo(const QList<Ponto2D>& pontos);

    // Adiciona um ponto à lista de pontos originais do mundo.
    void adicionarPontoOriginalMundo(const Ponto2D& ponto);

    // Calcula o centro geométrico do objeto (baseado nos pontos originais do mundo).
    // Útil para transformações como escala/rotação em torno do centro.
    virtual Ponto2D calcularCentroGeometrico() const;

    // Cor do objeto
    QColor obterCor() const;
    void definirCor(const QColor& novaCor);


protected:
    QString nome;
    TipoObjeto tipo;
    QList<Ponto2D> pontosOriginaisMundo;      // Pontos de definição no espaço do mundo
    Matriz matrizTransformacaoAcumulada;      // Matriz de transformação acumulada do objeto
    QColor cor;                               // Cor para desenhar o objeto

    // Pontos calculados para renderização
    QList<Ponto2D> pontosMundoTransformados;  // pontosOriginaisMundo * matrizTransformacaoAcumulada
    QList<Ponto2D> pontosSCN;                 // matrizNormalizacao * pontosMundoTransformados
    // Estes são os pontos que serão usados para clipping e depois viewport.
};

#endif // OBJETO_GRAFICO_H
