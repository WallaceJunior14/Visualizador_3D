#ifndef FRAME_DESENHO_H
#define FRAME_DESENHO_H

#include <QFrame> // Alterado de QWidget para QFrame
#include <QPainter>
#include <memory> // Para std::shared_ptr
#include "display_file.h"
#include "janela_mundo.h"
#include "viewport_tela.h"
#include "clipper.h"

// Widget responsável por renderizar os objetos gráficos do DisplayFile.
// Herda de QFrame para ser promovido no Qt Designer.
// Este widget representa a "View" no padrão MVC.
class FrameDesenho : public QFrame { // Alterado de QWidget para QFrame
    Q_OBJECT

public:
    // O construtor agora aceita QWidget* como pai, típico para widgets promovidos
    explicit FrameDesenho(QWidget *parent = nullptr);
    ~FrameDesenho();

    // Define o DisplayFile a ser renderizado.
    void definirDisplayFile(std::shared_ptr<DisplayFile> df);

    // Define a Janela do Mundo (world window).
    void definirJanelaMundo(std::shared_ptr<JanelaMundo> janela);
    std::shared_ptr<JanelaMundo> obterJanelaMundo() const;


    // Atualiza a viewport com base no tamanho atual do widget.
    void atualizarViewport();

    // Solicita um redesenho do widget.
    void redesenhar();

protected:
    // Evento de pintura, onde o desenho realmente acontece.
    void paintEvent(QPaintEvent *event) override;
    // Evento de redimensionamento, para ajustar a viewport.
    void resizeEvent(QResizeEvent *event) override;

    // Adicionado para interações com mouse (ex: zoom/pan se desejado no futuro)
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void wheelEvent(QWheelEvent *event) override;

private:
    std::shared_ptr<DisplayFile> displayFile;
    std::shared_ptr<JanelaMundo> janelaMundo;    // A "window" com coordenadas normalizadas (ou do mundo)
    std::shared_ptr<ViewportTela> viewportTela;  // A área da tela (em pixels) onde os objetos são desenhados
    std::unique_ptr<ClipperCohenSutherland> clipper;

    // Desenha um único objeto gráfico.
    void desenharObjeto(QPainter& painter, std::shared_ptr<ObjetoGrafico> objeto, const Matriz& matViewport);

    // Desenha a moldura da viewport
    void desenharMolduraViewport(QPainter& painter);

    // Para tornar público se necessário, ou usar friend class
public:
    int calcularCodigoRegiaoPonto(const Ponto2D& p) const { // Wrapper para o método do clipper
        if(clipper) return clipper->calcularCodigoRegiao(p);
        return -1; // ou algum valor de erro
    }
    static const int CODIGO_REGIAO_DENTRO = 0; // Expondo o valor DENTRO do clipper

};

#endif // FRAME_DESENHO_H
