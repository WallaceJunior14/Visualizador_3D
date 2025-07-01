#ifndef FRAME_DESENHO_H
#define FRAME_DESENHO_H

#include <QFrame>
#include <QPainter>
#include <memory>
#include <cmath>
#include "display_file.h"
#include "camera.h"
#include "viewport_tela.h"
#include "clipper.h" // Renomeado de clipper.h para consistência

/**
 * @brief Um widget customizado do Qt que serve como a tela de desenho principal para a cena 3D.
 * @details Esta classe é responsável por todo o processo de renderização. Ela gerencia o
 * paintEvent para desenhar os objetos do DisplayFile, lida com o redimensionamento da janela
 * para ajustar a viewport e a câmera, e orquestra a aplicação do pipeline de renderização 3D.
 */
class FrameDesenho : public QFrame {
    Q_OBJECT

public:
    /**
     * @brief Construtor da classe FrameDesenho.
     * @param parent O widget pai, como de praxe no Qt.
     */
    explicit FrameDesenho(QWidget *parent = nullptr);

    /**
     * @brief Destrutor da classe FrameDesenho.
     */
    ~FrameDesenho();

    /**
     * @brief Associa um DisplayFile (a cena 3D) a esta tela de desenho.
     * @param df Um std::shared_ptr para o DisplayFile que contém os objetos e câmeras a serem renderizados.
     */
    void definirDisplayFile(std::shared_ptr<DisplayFile> df);

    /**
     * @brief Obtém um ponteiro para a câmera ativa atualmente em uso na cena.
     * @return Um std::shared_ptr para a Camera ativa, ou `nullptr` se não houver uma.
     */
    std::shared_ptr<Camera> obterCameraAtiva() const;

    /**
     * @brief Recalcula as dimensões da viewport com base no tamanho atual do widget.
     * @note Também atualiza a matriz de projeção da câmera para manter a proporção
     * correta da imagem (aspect ratio) e evitar distorções visuais.
     */
    void atualizarViewport();

    /**
     * @brief Força um redesenho completo do widget.
     * @note É uma chamada de conveniência para o método `update()` do Qt, que agenda
     * uma chamada futura ao `paintEvent`.
     */
    void redesenhar();

protected:
    /**
     * @brief O principal evento de desenho, chamado pelo Qt sempre que o widget precisa ser redesenhado.
     * @param event Ponteiro para o objeto de evento de pintura (QPaintEvent).
     * @note É dentro deste método que todo o pipeline de renderização 3D é executado a cada frame.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Evento chamado pelo Qt sempre que o tamanho do widget é alterado.
     * @param event Ponteiro para o objeto de evento de redimensionamento (QResizeEvent).
     * @note É usado para chamar `atualizarViewport()` e garantir que a cena se adapte ao novo tamanho.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    std::shared_ptr<DisplayFile> displayFile;   ///< A cena 3D contendo todos os objetos e câmeras.
    std::shared_ptr<ViewportTela> viewportTela; ///< Objeto que gerencia o mapeamento de NDC para coordenadas de tela.
    std::unique_ptr<Clipper3D> clipper;         ///< Objeto responsável pelo recorte de primitivas 3D contra o volume de visão.

    /**
     * @brief Método auxiliar para desenhar um único objeto gráfico na tela.
     * @param painter A referência para o QPainter ativo.
     * @param objeto O objeto gráfico a ser desenhado.
     * @param matViewport A matriz de transformação da viewport.
     */
    void desenharObjeto(QPainter& painter, std::shared_ptr<ObjetoGrafico> objeto, const Matriz& matViewport);

    /**
     * @brief Método auxiliar para desenhar elementos de UI sobre a cena, como a borda da viewport.
     * @param painter A referência para o QPainter ativo.
     */
    void desenharDetalhesDaViewport(QPainter& painter);

    /**
     * @brief Método auxiliar para desenhar os eixos X, Y e Z do sistema de coordenadas do mundo.
     * @param painter A referência para o QPainter ativo.
     * @param matViewProj A matriz combinada de View-Projeção para transformar os eixos.
     * @param matViewport A matriz da viewport para mapear os eixos para a tela.
     */
    //void desenharEixosCoordenadas(QPainter& painter, const Matriz& matViewProj, const Matriz& matViewport);

    /**
     * @brief Desenha um indicador de eixos fixo em um canto da tela (HUD).
     * Este indicador rotaciona para mostrar a orientação atual do mundo, mas
     * sua posição na tela é fixa.
     */
    void desenharIndicadorDeEixos(QPainter& painter);
};

#endif // FRAME_DESENHO_H
