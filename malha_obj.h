#ifndef MALHA_OBJ_H
#define MALHA_OBJ_H

#include "objeto_grafico.h"
#include "bounding_box.h"
#include <QPair>

/**
 * @brief Representa um objeto de malha de arame (wireframe mesh) em 3D.
 * @details Esta classe é usada para representar objetos 3D complexos definidos por
 * um conjunto de vértices e uma lista de arestas que conectam esses vértices.
 * É ideal para carregar modelos de arquivos (como .obj) ou para criar formas
 * geométricas que não são primitivas simples. Herda de ObjetoGrafico.
 */
class MalhaObj : public ObjetoGrafico {
public:
    /**
     * @brief Construtor para criar um novo objeto de malha de arame.
     * @param nome O nome identificador do objeto.
     * @param vertices A lista de todos os vértices (Ponto3D) que compõem a malha.
     * @param arestas A lista de pares de inteiros (QPair<int, int>) que definem as
     * arestas, conectando os vértices da lista `vertices` por seus índices.
     */
    MalhaObj(const QString& nome,
             const QList<Ponto3D>& vertices,
             const QList<QPair<int, int>>& arestas);

    /**
     * @brief Retorna a lista de arestas que definem a conectividade da malha.
     * @return Uma referência constante para a QList de pares de índices que representam as arestas.
     * @note Esta informação é usada pelo `FrameDesenho` para saber quais vértices
     * devem ser conectados por linhas ao desenhar o objeto.
     */
    const QList<QPair<int, int>>& obterArestas() const { return arestas; }

    // --- Implementação da Interface Abstrata ---

    /**
     * @brief Implementa a lógica de desenho específica para uma malha de arame.
     * @details Itera sobre a lista de arestas, busca os vértices correspondentes (já
     * transformados e clipados pela classe base) e desenha uma linha para cada aresta.
     * @param painter O ponteiro para o objeto QPainter que fará o desenho.
     * @param viewport O retângulo que define a área de desenho da viewport na tela.
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override;

    /**
     * @brief Calcula a Bounding Box (caixa delimitadora) 3D que envolve todos os vértices da malha.
     * @return Um objeto BoundingBox contendo a malha.
     * @note A implementação normalmente itera sobre todos os vértices da malha para
     * encontrar as coordenadas mínimas и máximas em cada eixo.
     */
    BoundingBox obterBBox() const override;

private:
    /**
     * @brief Lista de arestas da malha.
     * Cada QPair contém os índices (base 0) de dois vértices na lista de pontos
     * da classe base, indicando que uma linha deve ser desenhada entre eles.
     */
    QList<QPair<int, int>> arestas;
};

#endif // MALHA_OBJ_H
