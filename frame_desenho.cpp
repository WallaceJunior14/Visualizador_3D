#include "frame_desenho.h" // Nome do arquivo de cabeçalho atualizado
#include "ponto_obj.h"
#include "reta_obj.h"
#include "poligono_obj.h"
#include "circunferencia_obj.h"
#include <QMouseEvent>
#include <QDebug>


FrameDesenho::FrameDesenho(QWidget *parent)
    : QFrame(parent),
    displayFile(nullptr),
    clipper(std::make_unique<ClipperCohenSutherland>(-1.0, -1.0, 1.0, 1.0))
{
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    // Inicializa viewportTela com padding se as dimensões já estiverem disponíveis
    if (width() > 0 && height() > 0) {
        int padding = 10;
        // Garante que a largura e altura não sejam negativas após o padding
        int vpWidth = std::max(0, width() - 2 * padding);
        int vpHeight = std::max(0, height() - 2 * padding);
        viewportTela = std::make_shared<ViewportTela>(padding, padding, vpWidth, vpHeight);
    } else {
        // Caso contrário, inicializa com tamanho zero e será ajustado no primeiro resizeEvent
        viewportTela = std::make_shared<ViewportTela>(0, 0, 0, 0);
    }
}

FrameDesenho::~FrameDesenho() {}

void FrameDesenho::definirDisplayFile(std::shared_ptr<DisplayFile> df) {
    displayFile = df;
    if (displayFile) {
        // Garante que os objetos no displayFile estejam com SCNs corretos
        // de acordo com a janela interna do displayFile.
        displayFile->recalcularTodosPontosSCN();
    }
    redesenhar(); // Redesenha com o novo display file
}

// void FrameDesenho::definirJanelaMundo(std::shared_ptr<JanelaMundo> janela) {
//     janelaMundo = janela;
//     if (displayFile && janelaMundo) {
//         displayFile->recalcularTodosPontosSCN(janelaMundo->obterMatrizNormalizacao());
//     }
//     redesenhar();
// }

std::shared_ptr<JanelaMundo> FrameDesenho::obterJanelaMundoAtiva() const {
    if (displayFile) {
        return displayFile->obterJanelaMundoAtiva(); // Modificado
    }
    qWarning("FrameDesenho::obterJanelaMundoAtiva() chamada, mas DisplayFile não está definido ou não tem janela ativa.");
    return nullptr;
}

void FrameDesenho::atualizarViewport() {
    if (viewportTela) {
        int padding = 10;
        // Garante que a largura e altura não sejam negativas
        int vpWidth = std::max(0, width() - 2 * padding);
        int vpHeight = std::max(0, height() - 2 * padding);

        viewportTela->definirParametros(padding, padding, vpWidth, vpHeight);
        redesenhar();
    }
}

void FrameDesenho::redesenhar() {
    update();
}

void FrameDesenho::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    std::shared_ptr<JanelaMundo> janelaAtiva = obterJanelaMundoAtiva();
    if (!displayFile || !janelaAtiva || !viewportTela || viewportTela->obterLargura() <= 0 || viewportTela->obterAltura() <= 0) {
        // Não desenha se a viewport não estiver pronta ou tiver tamanho inválido
        if (viewportTela && (viewportTela->obterLargura() <= 0 || viewportTela->obterAltura() <= 0)) {
            painter.drawText(rect(), Qt::AlignCenter, "Viewport com tamanho inválido.");
        } else {
            painter.drawText(rect(), Qt::AlignCenter, "Componentes não configurados.");
        }
        return;
    }

    Matriz matNorm = janelaAtiva->obterMatrizNormalizacao();
    Matriz matViewport = viewportTela->obterMatrizTransformacaoViewport(); // Matriz da viewport do frame

    // Desenhar objetos
    for (const auto& objeto : displayFile->obterObjetos()) {
        if (objeto) {
            desenharObjeto(painter, objeto, matViewport);
        }
    }

    // Desenhar os detalhes da viewport (borda, label, eixos)
    desenharDetalhesDaViewport(painter);
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
    } else if (tipo == TipoObjeto::CIRCUNFERENCIA) {
        auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(objeto);
        if (!circulo) return;

        // Usar a cor definida no objeto para a caneta.
        // A espessura 1 é boa para uma linha de circunferência suave.
        painter.setPen(QPen(circulo->obterCor(), 1));

        Ponto2D centroOriginal = circulo->obterCentroOriginal();
        double raioOriginal = circulo->obterRaioOriginal();
        int numPontosAprox = 1000; // Número de segmentos para aproximar a circunferência

        // Matrizes de transformação
        Matriz matObj = circulo->obterMatrizTransformacaoAcumulada();
        std::shared_ptr<JanelaMundo> janelaAtiva = displayFile->obterJanelaMundoAtiva(); // Certifique-se que displayFile é válido
        if (!janelaAtiva) return; // Adiciona uma verificação para janelaAtiva
        Matriz matNorm = janelaAtiva->obterMatrizNormalizacao();
        // matViewport já é um argumento da função desenharObjeto

        Matriz matTransformacaoOriginalParaSCN = matNorm * matObj;

        Ponto2D p1_original, p2_original; // Pontos no espaço original do objeto
        Ponto2D p1_scn, p2_scn;           // Pontos em SCN

        for (int i = 0; i < numPontosAprox; ++i) {
            // Calcula o ângulo para o ponto atual (i) e o próximo ponto (i+1)
            double angulo1 = 2.0 * M_PI * static_cast<double>(i) / static_cast<double>(numPontosAprox);
            // O operador % numPontosAprox garante que o último ponto conecte-se ao primeiro
            double angulo2 = 2.0 * M_PI * static_cast<double>((i + 1) % numPontosAprox) / static_cast<double>(numPontosAprox);

            // Ponto 1 do segmento (atual) no espaço original do objeto
            p1_original = Ponto2D(
                centroOriginal.obterX() + raioOriginal * std::cos(angulo1),
                centroOriginal.obterY() + raioOriginal * std::sin(angulo1)
                );

            // Ponto 2 do segmento (próximo) no espaço original do objeto
            p2_original = Ponto2D(
                centroOriginal.obterX() + raioOriginal * std::cos(angulo2),
                centroOriginal.obterY() + raioOriginal * std::sin(angulo2)
                );

            // Transforma os pontos originais para SCN
            p1_scn = Ponto2D(matTransformacaoOriginalParaSCN * p1_original);
            p1_scn.normalizar(); // Garante w=1

            p2_scn = Ponto2D(matTransformacaoOriginalParaSCN * p2_original);
            p2_scn.normalizar(); // Garante w=1

            // Cria cópias para o clipper, pois ele pode modificar os pontos
            Ponto2D p1_scn_para_clipping = p1_scn;
            Ponto2D p2_scn_para_clipping = p2_scn;

            // Aplica o clipping de reta ao segmento (p1_scn_clippable, p2_scn_clippable)
            // A função cliparReta deve modificar p1_scn_clippable e p2_scn_clippable se necessário
            if (clipper->cliparReta(p1_scn_para_clipping, p2_scn_para_clipping)) {
                // Se o segmento (ou parte dele) é visível após o clipping:

                // Transforma os pontos SCN (agora clipados) para coordenadas de Tela
                // A matriz matViewport transforma de SCN para Tela.
                Matriz p1_tela_mat = matViewport * p1_scn_para_clipping;
                Matriz p2_tela_mat = matViewport * p2_scn_para_clipping;

                Ponto2D p1_tela(p1_tela_mat); // Construtor Ponto2D(Matriz) deve normalizar W se aplicável
                Ponto2D p2_tela(p2_tela_mat);

                // Desenha o segmento de reta na tela
                painter.drawLine(qRound(p1_tela.obterX()), qRound(p1_tela.obterY()),
                                 qRound(p2_tela.obterX()), qRound(p2_tela.obterY()));
            }
        }
    }
}

void FrameDesenho::desenharDetalhesDaViewport(QPainter& painter) {
    if (!viewportTela || viewportTela->obterLargura() <= 0 || viewportTela->obterAltura() <= 0) {
        return; // Não desenha se a viewport não for válida
    }

    // Obter o retângulo da viewport em coordenadas de tela (pixels)
    QRect vpRect = viewportTela->obterRect();

    // --- 1. Borda Vermelha da Viewport ---
    painter.save(); // Salva o estado atual do painter
    QPen bordaPen(Qt::red, 1, Qt::SolidLine); // Caneta vermelha, 1 pixel de espessura
    painter.setPen(bordaPen);
    painter.setBrush(Qt::NoBrush); // Sem preenchimento para o retângulo da borda
    painter.drawRect(vpRect.adjusted(0, 0, -1, -1)); // -1 para desenhar dentro dos limites exatos
    painter.restore(); // Restaura o estado do painter

    // --- 2. Label "Viewport" ---
    painter.save();
    painter.setPen(Qt::black); // Cor do texto
    QString textoLabelViewport = "Viewport";
    QFontMetrics fm = painter.fontMetrics();
    int larguraTexto = fm.horizontalAdvance(textoLabelViewport);
    int alturaTexto = fm.height();
    // Posiciona acima da borda da viewport, centralizado
    int xLabel = vpRect.x() + (vpRect.width() - larguraTexto) / 2;
    int yLabel = vpRect.y() - alturaTexto / 2 - 2; // 2 pixels de espaço acima da borda
    if (yLabel < fm.ascent()) yLabel = fm.ascent(); // Garante que não saia do topo do frame
    painter.drawText(xLabel, yLabel, textoLabelViewport);
    painter.restore();

    // --- 3. Eixos X e Y dentro da Viewport ---
    painter.save();
    // Matriz para transformar de NDC para coordenadas da viewport (tela)
    Matriz matTransformacaoVP = viewportTela->obterMatrizTransformacaoViewport();

    // Definir pontos dos eixos em NDC
    Ponto2D eixoY_ndc_inicio(0.0, -1.0); // Y de -1 a 1 em X=0
    Ponto2D eixoY_ndc_fim(0.0, 1.0);
    Ponto2D eixoX_ndc_inicio(-1.0, 0.0); // X de -1 a 1 em Y=0
    Ponto2D eixoX_ndc_fim(1.0, 0.0);

    // Transformar para coordenadas da viewport
    Ponto2D eixoY_tela_inicio(matTransformacaoVP * eixoY_ndc_inicio);
    Ponto2D eixoY_tela_fim(matTransformacaoVP * eixoY_ndc_fim);
    Ponto2D eixoX_tela_inicio(matTransformacaoVP * eixoX_ndc_inicio);
    Ponto2D eixoX_tela_fim(matTransformacaoVP * eixoX_ndc_fim);

    // Cor e estilo dos eixos
    QPen eixoPen(Qt::darkGray, 1, Qt::DashLine); // Cinza escuro, tracejado
    painter.setPen(eixoPen);

    // Desenhar os eixos
    // É importante clipar as linhas para que fiquem DENTRO da vpRect,
    // pois a transformação pode resultar em pontos fora se a janela mundo for maior que NDC.
    // QPainter já clipa para a área do widget, mas para ser explícito com a viewport:
    painter.setClipRect(vpRect); // Clipar o desenho à área da viewport

    painter.drawLine(QPointF(eixoX_tela_inicio.obterX(), eixoX_tela_inicio.obterY()),
                     QPointF(eixoX_tela_fim.obterX(), eixoX_tela_fim.obterY())); // Eixo X
    painter.drawLine(QPointF(eixoY_tela_inicio.obterX(), eixoY_tela_inicio.obterY()),
                     QPointF(eixoY_tela_fim.obterX(), eixoY_tela_fim.obterY())); // Eixo Y


    // Labels para os eixos
    painter.setPen(Qt::black); // Cor para os rótulos dos eixos
    QFont eixoLabelFont = painter.font();
    eixoLabelFont.setPointSize(std::max(6, eixoLabelFont.pointSize() - 2)); // Fonte um pouco menor
    painter.setFont(eixoLabelFont);
    QFontMetrics fmEixo = painter.fontMetrics();

    // Label "Eixo X"
    QString labelX = "Eixo X";
    int larguraLabelX = fmEixo.horizontalAdvance(labelX);
    // Posicionar próximo ao final do eixo X (direita), dentro da viewport
    double posXLabelX = eixoX_tela_fim.obterX() - larguraLabelX - 5; // 5 pixels de margem
    double posYLabelX = eixoX_tela_fim.obterY() - fmEixo.descent() - 2; // Um pouco acima do eixo
    // Ajustar para não sair da viewport
    if (posXLabelX + larguraLabelX > vpRect.right()) posXLabelX = vpRect.right() - larguraLabelX;
    if (posXLabelX < vpRect.left()) posXLabelX = vpRect.left();
    if (posYLabelX + fmEixo.height() > vpRect.bottom()) posYLabelX = vpRect.bottom() - fmEixo.descent();
    if (posYLabelX - fmEixo.ascent() < vpRect.top()) posYLabelX = vpRect.top() + fmEixo.ascent();
    painter.drawText(qRound(posXLabelX), qRound(posYLabelX), labelX);

    // Label "Eixo Y"
    QString labelY = "Eixo Y";
    int larguraLabelY = fmEixo.horizontalAdvance(labelY);
    // Posicionar próximo ao final do eixo Y (topo, pois Y na tela cresce para baixo), dentro da viewport
    double posXLabelY = eixoY_tela_fim.obterX() + 5; // 5 pixels à direita do eixo Y
    double posYLabelY = eixoY_tela_fim.obterY() + fmEixo.ascent() + 5; // 5 pixels abaixo do topo do eixo
    // Ajustar para não sair da viewport
    if (posXLabelY + larguraLabelY > vpRect.right()) posXLabelY = vpRect.right() - larguraLabelY;
    if (posXLabelY < vpRect.left()) posXLabelY = vpRect.left();
    if (posYLabelY > vpRect.bottom()) posYLabelY = vpRect.bottom() - fmEixo.descent();
    if (posYLabelY - fmEixo.ascent() < vpRect.top()) posYLabelY = vpRect.top() + fmEixo.ascent();
    painter.drawText(qRound(posXLabelY), qRound(posYLabelY), labelY);

    painter.setClipping(false); // Remove o clipping específico da viewport
    painter.restore(); // Restaura o estado do painter
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
