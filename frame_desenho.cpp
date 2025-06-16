#include "frame_desenho.h"
#include "ponto2d.h"
#include "ponto_obj.h"
#include "reta_obj.h"
#include "poligono_obj.h"
#include "circunferencia_obj.h" // A lógica de desenho será unificada com a do polígono
#include "malha_obj.h"

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
    displayFile->recalcularTodosOsPontos();

    // 2. Obtém as matrizes essenciais uma única vez
    Matriz matView = cameraAtiva->obterMatrizView();
    Matriz matProj = cameraAtiva->obterMatrizProjecao();
    Matriz matViewProj = matProj * matView; // Matriz combinada para eixos e labels
    Matriz matViewport = viewportTela->obterMatrizTransformacaoViewport();

    // 3. NOVO: Desenha os eixos de coordenadas do mundo
    desenharEixosCoordenadas(painter, matViewProj, matViewport);

    // 4. Desenha cada objeto do DisplayFile
    for (const auto& objeto : displayFile->obterObjetos()) {
        if (objeto) {
            desenharObjeto(painter, objeto, matViewport);
        }
    }

    // 5. Desenha a borda da viewport e a nova legenda
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
    } else if (tipo == TipoObjeto::MALHA) {
        auto malha = std::dynamic_pointer_cast<MalhaObj>(objeto);
        if (!malha) return;

        const auto& arestas = malha->obterArestas();
        for (const auto& aresta : arestas) {
            if (aresta.first < pontosNDC_3D.size() && aresta.second < pontosNDC_3D.size()) {
                Ponto3D p1 = pontosNDC_3D.at(aresta.first);
                Ponto3D p2 = pontosNDC_3D.at(aresta.second);

                if (clipper->cliparReta(p1, p2)) {
                    Ponto2D p1_2D(p1.obterX(), p1.obterY());
                    Ponto2D p2_2D(p2.obterX(), p2.obterY());
                    Ponto2D p1Tela(matViewport * p1_2D);
                    Ponto2D p2Tela(matViewport * p2_2D);
                    painter.drawLine(qRound(p1Tela.obterX()), qRound(p1Tela.obterY()),
                                     qRound(p2Tela.obterX()), qRound(p2Tela.obterY()));
                }
            }
        }
    }
}

// Esta função não precisa de grandes alterações, pois opera em um overlay 2D.
void FrameDesenho::desenharDetalhesDaViewport(QPainter& painter) {
    if (!viewportTela || viewportTela->obterLargura() <= 0) return;

    QRect vpRect = viewportTela->obterRect();
    painter.save(); // Salva o estado do painter

    // Desenha a borda vermelha da viewport
    QPen bordaPen(Qt::red, 1, Qt::SolidLine);
    painter.setPen(bordaPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(vpRect.adjusted(0, 0, -1, -1));

    // NOVO: Desenha a legenda "Viewport"
    QPoint legendaPos(vpRect.center().x(), vpRect.top() - 5); // 5 pixels acima do centro do topo
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    // Alinha o texto para que a posição seja o centro inferior da caixa de texto
    painter.drawText(QRect(legendaPos - QPoint(50, 20), QSize(100, 20)), Qt::AlignCenter, "Viewport");

    painter.restore(); // Restaura o estado do painter
}

void FrameDesenho::desenharEixosCoordenadas(QPainter& painter, const Matriz& matViewProj, const Matriz& matViewport)
{
    const double tamanhoEixo = 10000.0;
    const double distanciaLabel = 60.0; // Distância 3D da origem para posicionar as labels X e Y

    struct Eixo {
        Ponto3D direcao;
        QString label;
    };

    Eixo eixos[3] = {
        { {1, 0, 0}, "Eixo X" },
        { {0, 1, 0}, "Eixo Y" },
        { {0, 0, 1}, "Eixo Z" }
    };

    QPen penEixo(Qt::gray, 1, Qt::DotLine);
    painter.setFont(QFont("Arial", 9));

    for (const auto& eixo : eixos) {
        // --- 1. Projeta e desenha o eixo ---
        Ponto3D p0_mundo = eixo.direcao * -tamanhoEixo;
        Ponto3D p1_mundo = eixo.direcao * tamanhoEixo;

        Ponto3D p0_ndc = matViewProj * p0_mundo;
        Ponto3D p1_ndc = matViewProj * p1_mundo;
        p0_ndc.normalizar();
        p1_ndc.normalizar();

        if (clipper->cliparReta(p0_ndc, p1_ndc)) {
            double p0_tela_x = matViewport(0,0) * p0_ndc.obterX() + matViewport(0,2);
            double p0_tela_y = matViewport(1,1) * p0_ndc.obterY() + matViewport(1,2);
            double p1_tela_x = matViewport(0,0) * p1_ndc.obterX() + matViewport(0,2);
            double p1_tela_y = matViewport(1,1) * p1_ndc.obterY() + matViewport(1,2);

            QPoint p0_tela(qRound(p0_tela_x), qRound(p0_tela_y));
            QPoint p1_tela(qRound(p1_tela_x), qRound(p1_tela_y));

            painter.setPen(penEixo);
            painter.drawLine(p0_tela, p1_tela);

            // --- 2. Desenha a legenda ---
            painter.setPen(Qt::gray);

            // Posição da label em 3D, próximo à extremidade positiva do eixo
            Ponto3D label_mundo;

            if (eixo.label == "Eixo Z") {
                // Para o Z, calcula o ponto 3D central no eixo
                label_mundo = eixo.direcao * (tamanhoEixo * 0.5);
            } else {
                // Para X e Y, calcula uma posição mais próxima da extremidade positiva
                label_mundo = eixo.direcao * distanciaLabel;
            }

            Ponto3D label_ndc = matViewProj * label_mundo;
            label_ndc.normalizar();

            if (clipper->calcularCodigoRegiao(label_ndc) == Clipper3D::DENTRO) {
                double tela_x = matViewport(0,0) * label_ndc.obterX() + matViewport(0,2);
                double tela_y = matViewport(1,1) * label_ndc.obterY() + matViewport(1,2);

                int deslocX = 0;
                int deslocY = -8;

                if (eixo.label == "Eixo X") deslocX = 6;
                if (eixo.label == "Eixo Z") deslocY = 6;

                painter.drawText(QPointF(tela_x + deslocX, tela_y + deslocY), eixo.label);
            }
        }
    }
}
