#ifndef CIRCUNFERENCIA_OBJ_H
#define CIRCUNFERENCIA_OBJ_H

#include "objeto_grafico.h"
#include <QPainter>

// Forward declarations
class BoundingBox;
class QRect;

/**
 * @brief Define um objeto gráfico do tipo circunferência em um espaço 3D.
 *
 * A classe representa uma circunferência através de um ponto central, um raio e um
 * vetor normal que define o plano no qual ela reside. Para a renderização, a
 * forma da curva é aproximada por um conjunto de segmentos de reta (um polígono),
 * que é gerado internamente. Herda toda a funcionalidade de transformação de ObjetoGrafico.
 */
class CircunferenciaObj : public ObjetoGrafico {
public:
    /**
     * @brief Construtor para criar uma nova circunferência 3D.
     * @param nome O nome identificador do objeto.
     * @param centro O ponto 3D que define o centro da circunferência.
     * @param raio O raio da circunferência.
     * @param normal O vetor normal que define a orientação do plano da circunferência.
     * @param cor A cor utilizada para desenhar o objeto.
     */
    CircunferenciaObj(const QString& nome, const Ponto3D& centro, double raio,
                      const Ponto3D& normal, const QColor& cor);

    /**
     * @brief Obtém o ponto central original da circunferência (em coordenadas de modelo).
     * @return O Ponto3D que representa o centro.
     */
    Ponto3D obterCentroOriginal() const;

    /**
     * @brief Obtém o raio original da circunferência.
     * @return O valor do raio.
     */
    double obterRaioOriginal() const;

    /**
     * @brief Obtém o vetor normal ao plano da circunferência.
     * @return O Ponto3D (usado como vetor) que representa a normal.
     */
    Ponto3D obterNormal() const;

    /**
     * @brief Define um novo ponto central para a circunferência.
     * @param novoCentro O novo ponto central do objeto.
     * @note Esta ação recalcula os vértices da aproximação poligonal.
     */
    void definirCentroOriginal(const Ponto3D& novoCentro);

    /**
     * @brief Define um novo raio para a circunferência.
     * @param novoRaio O novo valor do raio.
     * @note Esta ação recalcula os vértices da aproximação poligonal.
     */
    void definirRaioOriginal(double novoRaio);

    /**
     * @brief Define um novo vetor normal para a circunferência, reorientando seu plano.
     * @param novaNormal O novo vetor normal.
     * @note Esta ação recalcula os vértices da aproximação poligonal.
     */
    void definirNormal(const Ponto3D& novaNormal);

    /**
     * @brief Implementa o algoritmo de De Casteljau para subdividir uma curva de Bézier.
     * @param pontosControle A lista de pontos de controle que definem o segmento da curva.
     * @param pontosIntermediarios Uma lista para armazenar os pontos calculados nas etapas intermediárias.
     * @return Uma lista de pontos contendo os dois novos conjuntos de pontos de controle resultantes da subdivisão.
     * @note Este é um método auxiliar, provavelmente usado por `gerarPontosAproximacao`, para criar
     * uma aproximação suave da curva da circunferência usando curvas de Bézier.
     */
    QList<Ponto3D> casteljau(QList<Ponto3D> pontosControle, QList<Ponto3D> pontosIntermediarios);

    // --- MÉTODOS VIRTUAIS OBRIGATÓRIOS HERDADOS ---

    /**
     * @brief Desenha a aproximação poligonal da circunferência na tela.
     * @param painter O ponteiro para o objeto QPainter que fará o desenho.
     * @param viewport O retângulo que define a área de desenho da viewport na tela.
     * @note Este método é chamado pelo FrameDesenho durante o paintEvent e depende dos pontos
     * já processados pelo pipeline de renderização (armazenados em pontosClip).
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override;

    /**
     * @brief Calcula a Bounding Box (caixa delimitadora) 3D da circunferência.
     * @return Um objeto BoundingBox que envolve completamente a circunferência.
     * @note Útil para algoritmos de otimização como detecção de colisão ou frustum culling.
     */
    BoundingBox obterBBox() const override;

    /**
     * @brief Sobrescreve o cálculo do centro para retornar o centro real da circunferência.
     * @return O ponto central definido no construtor.
     * @note É uma otimização que evita o cálculo da média dos vértices da aproximação,
     * sendo mais rápido e preciso que a implementação da classe base.
     */
    Ponto3D calcularCentroGeometrico() const override;

private:
    Ponto3D centroOriginal_m;
    double raioOriginal_m;
    Ponto3D normal_m; // Vetor normal ao plano da circunferência

    /**
     * @brief Método privado para gerar os vértices que aproximam a forma da circunferência.
     * @note Os pontos gerados são armazenados na lista `pontosOriginaisMundo` da classe base.
     * Esta função é chamada no construtor e sempre que uma propriedade geométrica
     * (centro, raio, normal) é alterada.
     */
    void gerarPontosAproximacao();
};

#endif // CIRCUNFERENCIA_OBJ_H
