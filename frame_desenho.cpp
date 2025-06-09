#include "frame_desenho.h"
#include "ponto2d.h"
#include "ponto_obj.h"
#include "reta_obj.h"
#include "poligono_obj.h"
#include "circunferencia_obj.h" // A lógica de desenho será unificada com a do polígono
#include <QMouseEvent>
#include <QDebug>

FrameDesenho::FrameDesenho(QWidget *parent)
    : QFrame(parent),
    displayFile(nullptr),
    clipper(std::make_unique<Clipper3D>(-1.0, -1.0, -1.0, 1.0, 1.0, 1.0)) // Clipper 3D
{
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    // Inicializa a viewport (lógica inalterada)
    if (width() > 0 && height() > 0) {
        atualizarViewport();
    } else {
        viewportTela = std::make_shared<ViewportTela>(0, 0, 0, 0);
    }
}

FrameDesenho::~FrameDesenho() {}

void FrameDesenho::definirDisplayFile(std::shared_ptr<DisplayFile> df) {
    displayFile = df;
    redesenhar();
}

std::shared_ptr<Camera> FrameDesenho::obterCameraAtiva() const {
    if (displayFile) {
        return displayFile->obterCameraAtiva();
    }
    return nullptr;
}

void FrameDesenho::atualizarViewport() {
    if (!viewportTela) {
        viewportTela = std::make_shared<ViewportTela>(0,0,0,0);
    }
    int padding = 10;
    int vpWidth = std::max(0, width() - 2 * padding);
    int vpHeight = std::max(0, height() - 2 * padding);

    viewportTela->definirParametros(padding, padding, vpWidth, vpHeight);

    // Atualiza o aspect ratio da câmera ativa
    auto cam = obterCameraAtiva();
    if (cam && vpHeight > 0) {
        cam->definirProjecaoPerspectiva(45.0, static_cast<double>(vpWidth) / vpHeight, 0.1, 1000.0);
    }

    redesenhar();
}

void FrameDesenho::redesenhar() {
    update();
}

void FrameDesenho::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    auto cameraAtiva = obterCameraAtiva();
    if (!displayFile || !cameraAtiva || !viewportTela || viewportTela->obterLargura() <= 0) {
        painter.drawText(rect(), Qt::AlignCenter, "Sistema 3D não configurado.");
        return;
    }

    // --- CORAÇÃO DO PIPELINE 3D ---
    // 1. Recalcula todos os pontos, aplicando o pipeline MVP (Model-View-Projection)
    //    Isso popula a lista `pontosClip` de cada objeto com coordenadas 3D em NDC.
    displayFile->recalcularTodosOsPontos();

    // 2. Obtém a matriz de transformação da Viewport (NDC -> Tela)
    Matriz matViewport = viewportTela->obterMatrizTransformacaoViewport();

    // 3. Desenha cada objeto
    for (const auto& objeto : displayFile->obterObjetos()) {
        if (objeto) {
            desenharObjeto(painter, objeto, matViewport);
        }
    }

    // 4. Desenha a borda da viewport e outros detalhes (overlay 2D)
    desenharDetalhesDaViewport(painter);
}

void FrameDesenho::resizeEvent(QResizeEvent *event) {
    QFrame::resizeEvent(event);
    atualizarViewport();
}

void FrameDesenho::desenharObjeto(QPainter& painter, std::shared_ptr<ObjetoGrafico> objeto, const Matriz& matViewport) {
    painter.setPen(QPen(objeto->obterCor(), 2));

    // Obtém os pontos em Coordenadas de Recorte Normalizadas (3D NDC)
    const QList<Ponto3D>& pontosNDC_3D = objeto->obterPontosClip();

    if (pontosNDC_3D.isEmpty()) return;
    TipoObjeto tipo = objeto->obterTipo();

    if (tipo == TipoObjeto::PONTO) {
        Ponto3D ponto3D = pontosNDC_3D.first();
        // Um ponto só é visível se estiver totalmente dentro do volume 3D
        if (clipper->calcularCodigoRegiao(ponto3D) == Clipper3D::DENTRO) {
            // Projeta para 2D (ignora Z) e transforma para a tela
            Ponto2D ponto2D(ponto3D.obterX(), ponto3D.obterY());
            Ponto2D pontoTela(matViewport * ponto2D);
            painter.fillRect(qRound(pontoTela.obterX()) - 2, qRound(pontoTela.obterY()) - 2, 5, 5, objeto->obterCor());
        }
    } else if (tipo == TipoObjeto::RETA) {
        if (pontosNDC_3D.size() == 2) {
            Ponto3D p1 = pontosNDC_3D.at(0);
            Ponto3D p2 = pontosNDC_3D.at(1);
            // Recorta a linha em 3D
            if (clipper->cliparReta(p1, p2)) {
                // Projeta para 2D (ignora Z) e transforma para a tela
                Ponto2D p1_2D(p1.obterX(), p1.obterY());
                Ponto2D p2_2D(p2.obterX(), p2.obterY());
                Ponto2D p1Tela(matViewport * p1_2D);
                Ponto2D p2Tela(matViewport * p2_2D);
                painter.drawLine(qRound(p1Tela.obterX()), qRound(p1Tela.obterY()),
                                 qRound(p2Tela.obterX()), qRound(p2Tela.obterY()));
            }
        }
    } else if (tipo == TipoObjeto::POLIGONO || tipo == TipoObjeto::CIRCUNFERENCIA) {
        // Trata a circunferência como um polígono, desenhando suas arestas
        for (int i = 0; i < pontosNDC_3D.size(); ++i) {
            Ponto3D p1_3D = pontosNDC_3D.at(i);
            Ponto3D p2_3D = pontosNDC_3D.at((i + 1) % pontosNDC_3D.size());

            // Recorta cada aresta do polígono em 3D
            if (clipper->cliparReta(p1_3D, p2_3D)) {
                // Projeta para 2D (ignora Z) e transforma para a tela
                Ponto2D p1_2D(p1_3D.obterX(), p1_3D.obterY());
                Ponto2D p2_2D(p2_3D.obterX(), p2_3D.obterY());
                Ponto2D p1Tela(matViewport * p1_2D);
                Ponto2D p2Tela(matViewport * p2_2D);
                painter.drawLine(qRound(p1Tela.obterX()), qRound(p1Tela.obterY()),
                                 qRound(p2Tela.obterX()), qRound(p2Tela.obterY()));
            }
        }
    }
}

// Esta função não precisa de grandes alterações, pois opera em um overlay 2D.
void FrameDesenho::desenharDetalhesDaViewport(QPainter& painter) {
    if (!viewportTela || viewportTela->obterLargura() <= 0) return;
    QRect vpRect = viewportTela->obterRect();
    painter.save();
    QPen bordaPen(Qt::red, 1, Qt::SolidLine);
    painter.setPen(bordaPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(vpRect.adjusted(0, 0, -1, -1));
    painter.restore();
}

/*
Com a modificação da classe FrameDesenho, você completou a migração de todo o seu pipeline de renderização para 3D.

Resumo do Novo Pipeline 3D:

FrameDesenho::paintEvent é chamado.
Ele obtém a Camera ativa do DisplayFile.
Ele chama displayFile->recalcularTodosOsPontos().
Dentro disso, para cada ObjetoGrafico:
O método objeto->recalcularPontos(view, projection) é executado.
Isso calcula MVP * PontoOriginal e armazena o resultado 3D normalizado (após divisão por W) na lista pontosClip.
De volta ao paintEvent, ele obtém a matViewport.
Ele itera sobre cada objeto e chama desenharObjeto.
desenharObjeto:
Pega os pontosClip (que são Ponto3D).
Usa o Clipper3D para recortar as primitivas (pontos, arestas) contra o volume canônico 3D.
Descarta a coordenada Z dos pontos recortados, projetando-os em um plano 2D.
Usa a matViewport para transformar esses pontos 2D para as coordenadas da tela.
Usa o QPainter para desenhar os pixels finais.
Seu sistema agora é um renderizador 3D de wireframe completo. Os próximos passos poderiam envolver a implementação de um Z-buffer para renderização de superfícies preenchidas, iluminação, ou controles de câmera mais complexos.
*/
