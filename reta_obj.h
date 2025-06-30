#ifndef RETA_OBJ_H
#define RETA_OBJ_H

#include "objeto_grafico.h"
#include <QPainter>

// Forward declarations
class BoundingBox;
class QRect;

/**
 * @brief Representa um objeto gráfico do tipo segmento de reta em um espaço 3D.
 * @details Um segmento de reta é definido por dois pontos (vértices) em suas
 * extremidades. Esta classe herda de ObjetoGrafico para se integrar ao
 * sistema de transformações e renderização.
 */
class RetaObj : public ObjetoGrafico {
public:
    /**
     * @brief Construtor para criar um novo objeto de segmento de reta.
     * @param nome O nome identificador do objeto para a interface.
     * @param p1 O Ponto3D que define o ponto inicial da reta.
     * @param p2 O Ponto3D que define o ponto final da reta.
     * @param corReta A cor para desenhar a reta.
     */
    RetaObj(const QString& nome, const Ponto3D& p1, const Ponto3D& p2, const QColor& corReta = Qt::black);

    /**
     * @brief Atualiza as coordenadas dos pontos inicial e final da reta.
     * @param p1 A nova posição do ponto inicial.
     * @param p2 A nova posição do ponto final.
     */
    void definirPontos(const Ponto3D& p1, const Ponto3D& p2);

    /**
     * @brief Retorna o ponto inicial da reta.
     * @return O Ponto3D do primeiro vértice.
     */
    Ponto3D obterPonto1() const;

    /**
     * @brief Retorna o ponto final da reta.
     * @return O Ponto3D do segundo vértice.
     */
    Ponto3D obterPonto2() const;

    // --- MÉTODOS VIRTUAIS OBRIGATÓRIOS HERDADOS ---

    /**
     * @brief Desenha o segmento de reta na tela.
     * @details Conecta os dois pontos do segmento usando as coordenadas já processadas
     * pelo pipeline de renderização (armazenadas em `pontosClip`) e mapeadas para a viewport.
     * @param painter O ponteiro para o objeto QPainter que realizará o desenho.
     * @param viewport O retângulo da tela (em pixels) para mapear as coordenadas.
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override;

    /**
     * @brief Calcula a Bounding Box (caixa delimitadora) que envolve os dois pontos da reta.
     * @return Um objeto BoundingBox contendo o segmento de reta.
     */
    BoundingBox obterBBox() const override;

    /**
     * @brief Sobrescreve o cálculo do centro geométrico para retornar o ponto médio do segmento de reta.
     * @return O Ponto3D que representa o ponto médio entre P1 e P2.
     * @note Embora o resultado seja o mesmo que a média dos vértices da classe base
     * (para um objeto de 2 pontos), esta implementação é semanticamente mais clara para uma reta.
     */
    Ponto3D calcularCentroGeometrico() const override;
};

#endif // RETA_OBJ_H
