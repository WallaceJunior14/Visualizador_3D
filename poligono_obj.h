#ifndef POLIGONO_OBJ_H
#define POLIGONO_OBJ_H

#include "objeto_grafico.h"
#include <QList>
#include <QPainter>

// Forward declarations
class BoundingBox;
class QRect;

/**
 * @brief Representa um objeto gráfico do tipo Polígono em um espaço 3D.
 * @details Um polígono é definido por uma lista ordenada de vértices que formam
 * uma forma fechada. Esta classe herda de ObjetoGrafico e fornece a lógica
 * específica para desenhar e calcular as propriedades de um polígono.
 */
class PoligonoObj : public ObjetoGrafico {
public:
    /**
     * @brief Construtor para criar um novo objeto Polígono.
     * @param nome O nome identificador do objeto para a interface.
     * @param vertices A lista de vértices (Ponto3D) que definem o polígono, em ordem sequencial.
     * @param corPoligono A cor para desenhar as arestas do polígono.
     */
    PoligonoObj(const QString& nome, const QList<Ponto3D>& vertices, const QColor& corPoligono = Qt::black);

    // --- Métodos específicos do polígono ---

    /**
     * @brief Adiciona um novo vértice à lista de vértices do polígono.
     * @param vertice O Ponto3D a ser adicionado ao final da lista.
     */
    void adicionarVertice(const Ponto3D& vertice);

    /**
     * @brief Substitui a lista de vértices existente do polígono por uma nova lista.
     * @param vertices A nova lista de vértices para o polígono.
     */
    void definirVertices(const QList<Ponto3D>& vertices);

    /**
     * @brief Retorna a lista de vértices que definem o polígono.
     * @return Uma referência constante para a QList de Ponto3D.
     * @note Este método geralmente retorna a lista `pontosOriginaisMundo` herdada da classe base.
     */
    const QList<Ponto3D>& obterVertices() const;

    // --- MÉTODOS VIRTUAIS OBRIGATÓRIOS HERDADOS ---
    // A palavra-chave 'override' garante que estamos sobrescrevendo corretamente uma função da classe base.

    /**
     * @brief Desenha as arestas do polígono na tela.
     * @details Conecta os vértices do polígono em sequência, usando os pontos já
     * processados pelo pipeline de renderização (armazenados em `pontosClip`).
     * Inclui a aresta de fechamento, que conecta o último ao primeiro vértice.
     * @param painter O ponteiro para o objeto QPainter que realizará o desenho.
     * @param viewport O retângulo da tela (em pixels) para mapear as coordenadas.
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override;

    /**
     * @brief Calcula e retorna a Bounding Box (caixa delimitadora) que envolve todos os vértices do polígono.
     * @return Um objeto BoundingBox contendo o polígono.
     */
    BoundingBox obterBBox() const override;
};

#endif // POLIGONO_OBJ_H
