#ifndef PONTO_OBJ_H
#define PONTO_OBJ_H

#include "objeto_grafico.h"
#include <QPainter>

// Forward declarations
class BoundingBox;
class QRect;

/**
 * @brief Representa um objeto gráfico do tipo Ponto em um espaço 3D.
 * @details É a primitiva geométrica mais simples, definida por uma única coordenada 3D.
 * Herda de ObjetoGrafico para se integrar ao sistema de transformações,
 * renderização e gerenciamento de cena.
 */
class PontoObj : public ObjetoGrafico {
public:
    /**
     * @brief Construtor para criar um novo objeto Ponto.
     * @param nome O nome identificador do objeto para a interface.
     * @param coordenada O Ponto3D que define a posição do ponto no espaço.
     * @param corPonto A cor com que o ponto será desenhado.
     */
    PontoObj(const QString& nome, const Ponto3D& coordenada, const QColor& corPonto = Qt::black);

    /**
     * @brief Atualiza a coordenada do ponto.
     * @param coordenada A nova posição 3D do ponto.
     */
    void definirCoordenada(const Ponto3D& coordenada);

    /**
     * @brief Retorna a coordenada atual do ponto.
     * @return O Ponto3D que representa a posição do ponto.
     */
    Ponto3D obterCoordenada() const;

    // --- MÉTODOS VIRTUAIS OBRIGATÓRIOS HERDADOS ---

    /**
     * @brief Desenha o ponto na tela como um pequeno quadrado ou círculo.
     * @details A implementação utiliza a coordenada já processada pelo pipeline de renderização
     * (armazenada em `pontosClip`) e a mapeia para a viewport antes de desenhar.
     * @param painter O ponteiro para o objeto QPainter que realizará o desenho.
     * @param viewport O retângulo da tela (em pixels) para mapear as coordenadas.
     */
    void desenhar(QPainter* painter, const QRect& viewport) const override;

    /**
     * @brief Calcula a Bounding Box de um ponto.
     * @return Um objeto BoundingBox degenerado, onde as coordenadas mínimas e máximas
     * são iguais à coordenada do próprio ponto.
     */
    BoundingBox obterBBox() const override;

    /**
     * @brief Sobrescreve o cálculo do centro geométrico.
     * @return A própria coordenada do ponto.
     * @note Esta é uma otimização, pois o centro geométrico de um único ponto é ele mesmo.
     */
    Ponto3D calcularCentroGeometrico() const override;
};

#endif // PONTO_OBJ_H
