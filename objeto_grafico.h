#ifndef OBJETO_GRAFICO_H
#define OBJETO_GRAFICO_H

#include <QString>
#include <QList>
#include <QColor>
#include "ponto3d.h"
#include "matriz.h"
#include "tipos.h"

// Forward declarations para acelerar a compilação e evitar dependências circulares.
class QPainter;
class BoundingBox;
class Camera;
class QRect;

/**
 * @brief Classe base abstrata para todos os objetos gráficos renderizáveis em uma cena 3D.
 * @details Define uma interface comum e armazena dados essenciais para qualquer objeto, como
 * nome, cor, vértices e matriz de transformação. Utiliza funções virtuais puras para forçar
 * as classes derivadas a implementar comportamentos essenciais (como desenhar) e funções
 * virtuais com implementação padrão para fornecer lógica reutilizável.
 */
class ObjetoGrafico {
public:
    /**
     * @brief Construtor da classe base ObjetoGrafico.
     * @param nomeObjeto O nome que identificará o objeto na interface.
     * @param tipoObjeto O enum que define o tipo do objeto (ex: PONTO, RETA).
     */
    ObjetoGrafico(const QString& nomeObjeto, TipoObjeto tipoObjeto);

    /**
     * @brief Destrutor virtual padrão.
     * @note É crucial que o destrutor de uma classe base com funções virtuais seja virtual
     * para garantir a destruição correta de objetos de classes derivadas.
     */
    virtual ~ObjetoGrafico() = default;

    // --- MÉTODOS DE CONTRATO (INTERFACE VIRTUAL PURA) ---
    // Toda classe filha CONCRETA é OBRIGADA a implementar estes métodos.

    /**
     * @brief Método virtual puro para desenhar o objeto na tela.
     * @param painter O ponteiro para o objeto QPainter que será usado para o desenho.
     * @param viewport O retângulo da tela (em pixels) onde o desenho deve ocorrer.
     * @note Toda classe derivada deve implementar este método com sua lógica de desenho específica.
     */
    virtual void desenhar(QPainter* painter, const QRect& viewport) const = 0;

    /**
     * @brief Método virtual puro para calcular e retornar a Bounding Box do objeto.
     * @return Um objeto BoundingBox que envolve completamente o objeto em suas coordenadas de mundo.
     * @note Toda classe derivada deve implementar este método.
     */
    virtual BoundingBox obterBBox() const = 0;


    // --- MÉTODOS COM IMPLEMENTAÇÃO PADRÃO (PODEM SER SOBRESCRITOS) ---

    /**
     * @brief Calcula os pontos do objeto no espaço de recorte normalizado (NDC - Normalized Device Coordinates).
     * @details Esta implementação padrão aplica a matriz Model-View-Projection (MVP) a cada vértice
     * em `pontosOriginaisMundo` e armazena o resultado em `pontosClip` para uso posterior.
     * @param camera A câmera ativa que fornece as matrizes View e Projection.
     * @note Geralmente não precisa ser sobrescrita, pois a lógica do pipeline é universal.
     */
    virtual void recalcularPontos(const Camera& camera);

    /**
     * @brief Calcula o centro geométrico do objeto como a média aritmética de seus vértices originais.
     * @return O Ponto3D que representa o centro geométrico do objeto em coordenadas de modelo.
     * @note Pode ser sobrescrita por classes filhas (como CircunferenciaObj) para uma
     * implementação mais eficiente e precisa, se disponível.
     */
    virtual Ponto3D calcularCentroGeometrico() const;


    // --- MÉTODOS COMUNS (NÃO VIRTUAIS) ---
    // Fornecem a funcionalidade principal que não deve ser alterada pelas classes filhas.

    /** @brief Retorna o nome do objeto. */
    QString obterNome() const;
    /** @brief Define um novo nome para o objeto. @param novoNome O novo nome. */
    void definirNome(const QString& novoNome);
    /** @brief Retorna o tipo do objeto (PONTO, RETA, etc.). */
    TipoObjeto obterTipo() const;
    /** @brief Retorna a lista de vértices originais do objeto em coordenadas de modelo/mundo. */
    const QList<Ponto3D>& obterPontosOriginaisMundo() const;
    /** @brief Retorna a lista de vértices já processados pelo pipeline MVP e normalizados (em NDC). */
    const QList<Ponto3D>& obterPontosClip() const;
    /** @brief Retorna a matriz de transformação (Model) acumulada do objeto. */
    const Matriz& obterMatrizTransformacao() const;
    /** @brief Retorna a cor do objeto. */
    QColor obterCor() const;
    /** @brief Define uma nova cor para o objeto. @param novaCor A nova cor. */
    void definirCor(const QColor& novaCor);

    /**
     * @brief Acumula uma nova transformação na matriz de transformação existente do objeto.
     * @param transformacao A matriz de transformação (ex: translação, rotação) a ser pré-multiplicada.
     * @note A fórmula `matrizTransformacao = T_nova * T_antiga` aplica a nova transformação no
     * sistema de coordenadas do mundo.
     */
    void aplicarTransformacao(const Matriz& transformacao);

    /** @brief Define a lista de vértices originais do objeto. @param pontos A nova lista de pontos. */
    void definirPontosOriginaisMundo(const QList<Ponto3D>& pontos);
    /** @brief Adiciona um único ponto à lista de vértices originais do objeto. @param ponto O ponto a ser adicionado. */
    void adicionarPontoOriginalMundo(const Ponto3D& ponto);


protected:
    QString nome;                           ///< Nome identificador do objeto.
    TipoObjeto tipo;                        ///< Enum que identifica o tipo do objeto (PONTO, RETA, etc.).
    QList<Ponto3D> pontosOriginaisMundo;    ///< Os vértices do objeto em seu estado original, em coordenadas de modelo.
    Matriz matrizTransformacao;             ///< A matriz Modelo (Model) que acumula todas as transformações aplicadas.
    QColor cor;                             ///< A cor do objeto.
    QList<Ponto3D> pontosClip;              ///< Cache dos vértices após a aplicação da matriz MVP, em NDC.
};

#endif // OBJETO_GRAFICO_H
