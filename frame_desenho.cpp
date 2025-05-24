#include "frame_desenho.h" // Nome do arquivo de cabeçalho atualizado
#include "ponto_obj.h"
#include "reta_obj.h"
#include "poligono_obj.h"
#include <QMouseEvent>
#include <QDebug>


FrameDesenho::FrameDesenho(QWidget *parent) // Construtor atualizado
    : QFrame(parent), // Chama o construtor de QFrame
    displayFile(nullptr),
    janelaMundo(std::make_shared<JanelaMundo>(-250, -250, 250, 250)), // Janela de mundo default
    viewportTela(std::make_shared<ViewportTela>(0, 0, width(), height())),
    clipper(std::make_unique<ClipperCohenSutherland>(-1.0, -1.0, 1.0, 1.0))
{
    // Configurações iniciais do widget QFrame
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white); // Fundo branco
    setPalette(pal);
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken); // Estilo do frame, pode ser ajustado

    if (width() > 0 && height() > 0) {
        viewportTela->definirParametros(0, 0, width(), height());
    }
    // Habilita o rastreamento do mouse se for usar mouseMoveEvent sem botão pressionado
    // setMouseTracking(true);
}

FrameDesenho::~FrameDesenho() {}

void FrameDesenho::definirDisplayFile(std::shared_ptr<DisplayFile> df) {
    displayFile = df;
    redesenhar();
}

void FrameDesenho::definirJanelaMundo(std::shared_ptr<JanelaMundo> janela) {
    janelaMundo = janela;
    if (displayFile && janelaMundo) {
        displayFile->recalcularTodosPontosSCN(janelaMundo->obterMatrizNormalizacao());
    }
    redesenhar();
}

std::shared_ptr<JanelaMundo> FrameDesenho::obterJanelaMundo() const {
    return janelaMundo;
}

void FrameDesenho::atualizarViewport() {
    if (viewportTela) {
        viewportTela->definirParametros(0, 0, width(), height());
        redesenhar();
    }
}

void FrameDesenho::redesenhar() {
    update();
}

void FrameDesenho::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event); // Chama o paintEvent da classe base QFrame, se necessário
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!displayFile || !janelaMundo || !viewportTela) {
        painter.drawText(rect(), Qt::AlignCenter, "Componentes não configurados.");
        return;
    }

    Matriz matViewport = viewportTela->obterMatrizTransformacaoViewport();
    // Recalcular SCN é importante se a janelaMundo mudou.
    // Idealmente, isso é feito quando janelaMundo é alterada, não em cada paintEvent.
    // displayFile->recalcularTodosPontosSCN(janelaMundo->obterMatrizNormalizacao());

    for (const auto& objeto : displayFile->obterObjetos()) {
        if (objeto) {
            desenharObjeto(painter, objeto, matViewport);
        }
    }
    desenharMolduraViewport(painter);
}

void FrameDesenho::resizeEvent(QResizeEvent *event) {
    QFrame::resizeEvent(event);
    atualizarViewport();
}

void FrameDesenho::desenharObjeto(QPainter& painter, std::shared_ptr<ObjetoGrafico> objeto, const Matriz& matViewport) {
    painter.setPen(QPen(objeto->obterCor(), 2));
    const QList<Ponto2D>& pontosSCN = objeto->obterPontosSCN();

    if (pontosSCN.isEmpty()) return;
    TipoObjeto tipo = objeto->obterTipo();

    if (tipo == TipoObjeto::PONTO) {
        Ponto2D pontoSCN = pontosSCN.first();
        // Para usar o clipper diretamente aqui, ou ter uma função pública no clipper.
        // Supondo que `calcularCodigoRegiaoPonto` foi adicionado ao FrameDesenho
        // ou que o ClipperCohenSutherland::DENTRO é acessível.
        if (clipper->calcularCodigoRegiao(pontoSCN) == ClipperCohenSutherland::DENTRO) {
            Matriz pontoTelaMat = matViewport * pontoSCN;
            Ponto2D pontoTela(pontoTelaMat);
            // painter.drawPoint(qRound(pontoTela.obterX()), qRound(pontoTela.obterY()));
            painter.fillRect(qRound(pontoTela.obterX()) - 2, qRound(pontoTela.obterY()) - 2, 5, 5, objeto->obterCor());
        }
    } else if (tipo == TipoObjeto::RETA) {
        if (pontosSCN.size() == 2) {
            Ponto2D p1_scn = pontosSCN.at(0);
            Ponto2D p2_scn = pontosSCN.at(1);
            if (clipper->cliparReta(p1_scn, p2_scn)) {
                Matriz p1TelaMat = matViewport * p1_scn;
                Matriz p2TelaMat = matViewport * p2_scn;
                Ponto2D p1Tela(p1TelaMat);
                Ponto2D p2Tela(p2TelaMat);
                painter.drawLine(qRound(p1Tela.obterX()), qRound(p1Tela.obterY()),
                                 qRound(p2Tela.obterX()), qRound(p2Tela.obterY()));
            }
        }
    } else if (tipo == TipoObjeto::POLIGONO) {
        QList<Ponto2D> pontosCorrigidos = pontosSCN;

        if (pontosSCN.size() == 2) {
            // Criar um quadrado com base em dois pontos
            Ponto2D p1 = pontosSCN.at(0);
            Ponto2D p2 = pontosSCN.at(1);

            double dx = p2.obterX() - p1.obterX();
            double dy = p2.obterY() - p1.obterY();

            // Calcula os outros dois pontos para formar um quadrado
            Ponto2D p3(p2.obterX() - dy, p2.obterY() + dx);
            Ponto2D p4(p1.obterX() - dy, p1.obterY() + dx);

            pontosCorrigidos = {p1, p2, p3, p4};
        } else if (pontosSCN.size() == 3) {
            // Já é um triângulo, não altera nada
        }

        // Desenhar como wireframe (somente as linhas)
        for (int i = 0; i < pontosCorrigidos.size(); ++i) {
            Ponto2D p1_scn = pontosCorrigidos.at(i);
            Ponto2D p2_scn = pontosCorrigidos.at((i + 1) % pontosCorrigidos.size());
            Ponto2D p1_clip = p1_scn;
            Ponto2D p2_clip = p2_scn;

            if (clipper->cliparReta(p1_clip, p2_clip)) {
                Matriz p1TelaMat = matViewport * p1_clip;
                Matriz p2TelaMat = matViewport * p2_clip;
                Ponto2D p1Tela(p1TelaMat);
                Ponto2D p2Tela(p2TelaMat);

                painter.drawLine(qRound(p1Tela.obterX()), qRound(p1Tela.obterY()),
                                 qRound(p2Tela.obterX()), qRound(p2Tela.obterY()));
            }
        }

        // Comentado o preenchimento:
        /*
    QPolygonF polygonOriginalTela;
    for (const Ponto2D& p_scn : pontosCorrigidos) {
        Matriz pTelaMat = matViewport * p_scn;
        Ponto2D pTela(pTelaMat);
        polygonOriginalTela << QPointF(pTela.obterX(), pTela.obterY());
    }
    painter.setBrush(QBrush(objeto->obterCor(), Qt::SolidPattern));
    painter.drawPolygon(polygonOriginalTela);
    */
    }
}

void FrameDesenho::desenharMolduraViewport(QPainter& painter) {
    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
    // A moldura do FrameDesenho já é visível pelo seu estilo.
    // Esta é uma moldura LÓGICA da viewport DENTRO do frame, se necessário.
    // Neste caso, a viewport lógica e o frame coincidem.
    // painter.drawRect(0, 0, width() -1, height() -1);
}

// Implementações de mouse events (descomente e adapte se necessário)
/*
void FrameDesenho::mousePressEvent(QMouseEvent *event) {
    // Exemplo: Iniciar pan ou seleção
    // lastMousePos = event->pos();
    // QFrame::mousePressEvent(event);
}

void FrameDesenho::mouseMoveEvent(QMouseEvent *event) {
    // Exemplo: Realizar pan se o botão estiver pressionado
    // if (event->buttons() & Qt::LeftButton) {
    //     QPoint delta = event->pos() - lastMousePos;
    //     lastMousePos = event->pos();
    //     if (janelaMundo) {
    //         // Converter delta em pixels para delta em coordenadas do mundo
    //         double dxMundo = static_cast<double>(delta.x()) * (janelaMundo->obterLargura() / width());
    //         double dyMundo = static_cast<double>(delta.y()) * (janelaMundo->obterAltura() / height());
    //         // Y do mouse é invertido em relação ao Y do mundo normalmente
    //         janelaMundo->deslocar(-dxMundo, dyMundo); // Ajuste o sinal conforme a direção do Y
    //         displayFile->recalcularTodosPontosSCN(janelaMundo->obterMatrizNormalizacao());
    //         redesenhar();
    //     }
    // }
    // QFrame::mouseMoveEvent(event);
}

void FrameDesenho::wheelEvent(QWheelEvent *event) {
    // Exemplo: Zoom com a roda do mouse
    // int numDegrees = event->angleDelta().y() / 8;
    // int numSteps = numDegrees / 15; // Geralmente cada "step" da roda é 15 graus

    // if (janelaMundo) {
    //     double fatorZoom = 1.0;
    //     if (numSteps > 0) {
    //         fatorZoom = std::pow(1.1, numSteps); // Zoom in
    //     } else if (numSteps < 0) {
    //         fatorZoom = std::pow(0.9, -numSteps); // Zoom out
    //     }
    //     janelaMundo->zoom(fatorZoom);
    //     displayFile->recalcularTodosPontosSCN(janelaMundo->obterMatrizNormalizacao());
    //     redesenhar();
    // }
    // event->accept();
    // // QFrame::wheelEvent(event); // Não chame o da base se você tratou o evento.
}
*/
