#ifndef CAMERA_H
#define CAMERA_H

#include <QString>
#include "ponto3d.h"
#include "matriz.h"

/**
 * @brief Define os tipos de projeção que a câmera pode utilizar.
 */
enum class TipoProjecao {
    PERSPECTIVA,    ///< Projeção que simula a visão humana, com profundidade.
    ORTOGRAFICA     ///< Projeção sem perspectiva, onde o tamanho dos objetos não muda com a distância.
};

/**
 * @brief Representa uma câmera virtual em uma cena 3D.
 *
 * Esta classe é responsável por gerenciar a posição e orientação da câmera no mundo,
 * bem como a forma como a cena 3D é projetada em um plano 2D. Ela calcula as
 * matrizes de Visualização (View) e Projeção, que são fundamentais no pipeline
 * de renderização gráfica.
 */
class Camera {
public:
    /**
     * @brief Construtor da classe Camera.
     * @param pos Posição inicial da câmera no espaço do mundo.
     * @param target Ponto no espaço para o qual a câmera está olhando.
     * @param nome Um nome identificador para a câmera (ex: "Câmera Principal").
     */
    Camera(const Ponto3D& pos, const Ponto3D& target, const QString& nome = "Câmera");

    // --- MÉTODOS DE CONFIGURAÇÃO DA VISUALIZAÇÃO (VIEW) ---

    /**
     * @brief Define um novo nome para a câmera.
     * @param novoNome O novo nome a ser atribuído.
     */
    void definirNome(const QString& novoNome);

    /**
     * @brief Define uma nova posição para a câmera no espaço.
     * @param pos A nova coordenada 3D da câmera.
     */
    void definirPosicao(const Ponto3D& pos);

    /**
     * @brief Define um novo ponto de alvo para a câmera.
     * @param alvo A nova coordenada 3D para a qual a câmera irá apontar.
     */
    void definirAlvo(const Ponto3D& alvo);

    /**
     * @brief Define o vetor "para cima" da câmera, que orienta sua rotação.
     * @param up O novo vetor 'up' (geralmente (0, 1, 0) para o eixo Y do mundo).
     */
    void definirVetorUp(const Ponto3D& up);

    /**
     * @brief Obtém a posição atual da câmera.
     * @return A coordenada 3D da posição da câmera.
     */
    Ponto3D obterPosicao() const;

    /**
     * @brief Obtém o ponto de alvo atual da câmera.
     * @return A coordenada 3D do alvo.
     */
    Ponto3D obterAlvo() const;

    /**
     * @brief Obtém o vetor "para cima" atual da câmera.
     * @return O vetor 'up'.
     */
    Ponto3D obterVetorUp() const;

    // --- MÉTODOS DE CONFIGURAÇÃO DA PROJEÇÃO ---

    /**
     * @brief Define o tipo de projeção a ser utilizado (Perspectiva ou Ortográfica).
     * @param tipo O novo tipo de projeção.
     */
    void definirTipoProjecao(TipoProjecao tipo);

    /**
     * @brief Obtém o tipo de projeção atual.
     * @return O enum correspondente ao tipo de projeção.
     */
    TipoProjecao obterTipoProjecao() const;

    /**
     * @brief Configura a câmera para usar uma projeção perspectiva.
     * @param fovY Campo de visão vertical (Field of View), em graus.
     * @param aspectRatio A proporção da tela (largura / altura).
     * @param near A distância para o plano de corte próximo (near plane).
     * @param far A distância para o plano de corte distante (far plane).
     */
    void definirProjecaoPerspectiva(double fovY, double aspectRatio, double near, double far);

    /**
     * @brief Configura a câmera para usar uma projeção ortográfica.
     * @param left Coordenada esquerda do volume de visualização.
     * @param right Coordenada direita do volume de visualização.
     * @param bottom Coordenada inferior do volume de visualização.
     * @param top Coordenada superior do volume de visualização.
     * @param near A distância para o plano de corte próximo.
     * @param far A distância para o plano de corte distante.
     */
    void definirProjecaoOrtografica(double left, double right, double bottom, double top, double near, double far);

    // --- OBTENÇÃO DAS MATRIZES FINAIS ---

    /**
     * @brief Calcula e retorna a matriz de visualização (View) 4x4.
     * A matriz é calculada com base na posição, alvo e vetor 'up' atuais.
     * @return A matriz de visualização (View) calculada.
     */
    Matriz obterMatrizView() const;

    /**
     * @brief Calcula e retorna a matriz de projeção 4x4.
     * A matriz é calculada com base no tipo de projeção e seus parâmetros atuais.
     * @return A matriz de projeção calculada.
     */
    Matriz obterMatrizProjecao() const;

    /**
     * @brief Obtém o nome da câmera.
     * @return O nome da câmera como QString.
     */
    QString obterNome() const;

    // --- MÉTODOS DE MOVIMENTAÇÃO DA CÂMERA ---

    /**
     * @brief Move a câmera e seu alvo juntos no espaço (pan/strafe).
     * @param dx Deslocamento no eixo X.
     * @param dy Deslocamento no eixo Y.
     * @param dz Deslocamento no eixo Z.
     */
    void transladar(double dx, double dy, double dz);

    /**
     * @brief Move a câmera para frente ou para trás ao longo de sua linha de visão.
     * @param fator A quantidade de movimento (positivo aproxima, negativo afasta).
     */
    void dolly(double fator);

    /**
     * @brief Rotaciona a posição da câmera em torno do ponto de alvo e sua orientação.
     * @param deltaYaw Rotação horizontal (em torno do eixo Y), em graus.
     * @param deltaPitch Rotação vertical (em torno do eixo X da câmera), em graus.
     * @param deltaRoll Rotação de inclinação (em torno do eixo Z da câmera), em graus.
     */
    void orbitar(double deltaYaw, double deltaPitch, double deltaRoll);


private:
    QString nome;

    // Parâmetros da Matriz View (LookAt)
    Ponto3D posicao;
    Ponto3D alvo;
    Ponto3D vetorUp;

    // Parâmetros da Matriz de Projeção
    TipoProjecao tipoProjecao;
    // Perspectiva
    double fovY;        // Campo de visão vertical em graus
    double aspectRatio;   // Proporção da tela (largura / altura)
    // Ortográfica
    double left, right, bottom, top;
    // Comum a ambas
    double nearPlane, farPlane;
};

#endif // CAMERA_H
