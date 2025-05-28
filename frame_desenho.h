#ifndef FRAME_DESENHO_H
#define FRAME_DESENHO_H

#include <QFrame> // Alterado de QWidget para QFrame
#include <QPainter>
#include <memory> // Para std::shared_ptr
#include "display_file.h"
#include "janela_mundo.h"
#include "viewport_tela.h"
#include "clipper.h"

class FrameDesenho : public QFrame {
    Q_OBJECT

public:
    explicit FrameDesenho(QWidget *parent = nullptr);
    ~FrameDesenho();

    void definirDisplayFile(std::shared_ptr<DisplayFile> df);
    std::shared_ptr<JanelaMundo> obterJanelaMundo() const;
    std::shared_ptr<JanelaMundo> obterJanelaMundoAtiva() const;

    void atualizarViewport();
    void redesenhar();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    std::shared_ptr<DisplayFile> displayFile;
    std::shared_ptr<ViewportTela> viewportTela; // A viewport com as coordenadas de tela
    std::unique_ptr<ClipperCohenSutherland> clipper;

    void desenharObjeto(QPainter& painter, std::shared_ptr<ObjetoGrafico> objeto, const Matriz& matViewport);

    // Modificado para incluir todos os detalhes da viewport (borda, label, eixos)
    void desenharDetalhesDaViewport(QPainter& painter);

public:
    int calcularCodigoRegiaoPonto(const Ponto2D& p) const {
        if(clipper) return clipper->calcularCodigoRegiao(p);
        return -1;
    }
    static const int CODIGO_REGIAO_DENTRO = 0;
};

#endif // FRAME_DESENHO_H
