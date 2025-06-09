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
class Camera; // <-- ALTERADO: Substituído Janela por Camera.
class QRect;  // <-- ADICIONADO: Para definir a área de desenho (viewport).

// Classe base para objetos gráficos em um ambiente 3D.
// Define a interface comum para manipulação e desenho de objetos.
class ObjetoGrafico {
public:
    // Construtor e Destrutor.
    ObjetoGrafico(const QString& nomeObjeto, TipoObjeto tipoObjeto);
    virtual ~ObjetoGrafico() = default;

    // --- MÉTODOS DE CONTRATO (INTERFACE VIRTUAL PURA) ---
    // Toda classe filha CONCRETA é OBRIGADA a implementar estes métodos.

    /**
     * @brief Desenha o objeto na tela dentro de uma viewport específica.
     * @param painter O QPainter para desenhar.
     * @param viewport O retângulo da tela onde o desenho ocorrerá.
     */
    virtual void desenhar(QPainter* painter, const QRect& viewport) const = 0; // <-- ALTERADO

    /**
     * @brief Retorna a caixa delimitadora (Bounding Box) do objeto.
     */
    virtual BoundingBox obterBBox() const = 0;


    // --- MÉTODOS COM IMPLEMENTAÇÃO PADRÃO (PODEM SER SOBRESCRITOS) ---

    /**
     * @brief Atualiza os pontos de clipping (NDC) a partir da câmera.
     * @param camera A câmera que define as matrizes de View e Projection.
     */
    virtual void recalcularPontos(const Camera& camera);

    /**
     * @brief Calcula o centro geométrico do objeto 3D.
     */
    virtual Ponto3D calcularCentroGeometrico() const;


    // --- MÉTODOS COMUNS (NÃO VIRTUAIS) ---
    // (Nenhuma alteração nesta seção)
    QString obterNome() const;
    void definirNome(const QString& novoNome);
    TipoObjeto obterTipo() const;
    const QList<Ponto3D>& obterPontosOriginaisMundo() const;
    const QList<Ponto3D>& obterPontosClip() const;
    const Matriz& obterMatrizTransformacao() const;
    void aplicarTransformacao(const Matriz& transformacao);
    void definirPontosOriginaisMundo(const QList<Ponto3D>& pontos);
    void adicionarPontoOriginalMundo(const Ponto3D& ponto);
    QColor obterCor() const;
    void definirCor(const QColor& novaCor);

protected:
    // (Nenhuma alteração nesta seção)
    QString nome;
    TipoObjeto tipo;
    QColor cor;
    QList<Ponto3D> pontosOriginaisMundo;
    Matriz matrizTransformacao;
    QList<Ponto3D> pontosClip;
};

#endif // OBJETO_GRAFICO_H
