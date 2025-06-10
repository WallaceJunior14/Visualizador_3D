#ifndef FRAME_DESENHO_H
#define FRAME_DESENHO_H

#include <QFrame>
#include <QPainter>
#include <memory>
#include "display_file.h"
#include "camera.h"           // Alterado
#include "viewport_tela.h"
#include "clipper.h"        // Alterado
#include <cmath>

class FrameDesenho : public QFrame {
    Q_OBJECT

public:
    explicit FrameDesenho(QWidget *parent = nullptr);
    ~FrameDesenho();

    void definirDisplayFile(std::shared_ptr<DisplayFile> df);
    std::shared_ptr<Camera> obterCameraAtiva() const; // Alterado

    void atualizarViewport();
    void redesenhar();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    std::shared_ptr<DisplayFile> displayFile;
    std::shared_ptr<ViewportTela> viewportTela;
    std::unique_ptr<Clipper3D> clipper; // Alterado

    void desenharObjeto(QPainter& painter, std::shared_ptr<ObjetoGrafico> objeto, const Matriz& matViewport);
    void desenharDetalhesDaViewport(QPainter& painter);
    void desenharEixosCoordenadas(QPainter& painter, const Matriz& matViewProj, const Matriz& matViewport);

};

#endif // FRAME_DESENHO_H
