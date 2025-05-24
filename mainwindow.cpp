#include "mainwindow.h"
#include "ui_mainwindow.h" // Importante: gerado pelo UIC a partir do mainwindow.ui

#include "frame_desenho.h" // Nosso widget de desenho
#include "display_file.h"
#include "janela_mundo.h" // Para interagir com a janela do frameDesenho
#include "ponto_obj.h"
#include "reta_obj.h"
#include "poligono_obj.h"
#include "transformador_geometrico.h"
#include "ponto2d.h" // Incluir Ponto2D

#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog> // Para btnCarregarOBJ
#include <QDebug>      // Para mensagens de depuração

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), // Inicializa o ui
    corSelecionadaParaDesenho(Qt::black)
{
    ui->setupUi(this); // Configura a UI a partir do arquivo .ui
    // Neste ponto, ui->frameDesenho já é um frameDesenho* (devido à promoção)

    // 1. Inicializar o DisplayFile
    displayFile = std::make_shared<DisplayFile>();

    // 2. Configurar o frameDesenho (que foi promovido a partir do QFrame no .ui)
    // O frameDesenho é ui->frameDesenho
    if (ui->frameDesenho) { // Verifica se a promoção funcionou
        ui->frameDesenho->definirDisplayFile(displayFile);
    } else {
        QMessageBox::critical(this, "Erro de UI", "O frameDesenho não foi carregado corretamente da UI.");
        // Tratar o erro, talvez fechar a aplicação ou usar um renderizador padrão
    }

    // 3. Configurações iniciais da UI
    inicializarUI();

    // 4. Conectar sinais e slots (Muitos já podem ser conectados pelo nome usando on_NOMEOBJETO_SINAL)
    // Conexões explícitas se o nome não seguir o padrão Qt Auto-Connection
    connect(ui->spinTranslacaoX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_spinTranslacaoX_valueChanged);
    connect(ui->spinTranslacaoY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_spinTranslacaoY_valueChanged);

    connect(ui->hsEscalaX, &QSlider::valueChanged, this, &MainWindow::on_hsEscalaX_valueChanged);
    connect(ui->hsEscalaY, &QSlider::valueChanged, this, &MainWindow::on_hsEscalaY_valueChanged);

    connect(ui->hsRotacaoX, &QSlider::valueChanged, this, &MainWindow::on_hsRotacaoX_valueChanged);
    // Se for usar os outros sliders de rotação para algo (ex: rotação 3D no futuro)
    // connect(ui->hsRotacaoY, &QSlider::valueChanged, this, ...);
    // connect(ui->hsRotacaoZ, &QSlider::valueChanged, this, ...);


    if (ui->frameDesenho) {
        ui->frameDesenho->redesenhar();
    }
    atualizarCbDisplayFile();
    if (ui->cbDisplayFile->count() > 0) {
        ui->cbDisplayFile->setCurrentIndex(0); // Seleciona o primeiro objeto por padrão
        on_cbDisplayFile_currentIndexChanged(0); // Dispara a lógica de seleção
    }
}

MainWindow::~MainWindow() {
    delete ui; // ui é um ponteiro gerenciado, precisa ser deletado
}

void MainWindow::inicializarUI() {
    // Popular ComboBox de formas
    ui->comboFormas->addItem("Ponto", static_cast<int>(TipoObjeto::PONTO));
    ui->comboFormas->addItem("Reta", static_cast<int>(TipoObjeto::RETA));
    ui->comboFormas->addItem("Polígono (Triângulo)", static_cast<int>(TipoObjeto::POLIGONO)); // Exemplo para polígono
    ui->comboFormas->addItem("Polígono (Quadrado)", static_cast<int>(TipoObjeto::POLIGONO)); // Exemplo para polígono
    // Adicionar mais tipos de polígonos se necessário ou um modo genérico.

    // Configurar estado inicial dos spinners de coordenadas
    on_comboFormas_currentIndexChanged(0); // Chama para configurar visibilidade inicial

    // Definir ranges e valores iniciais para sliders de transformação se necessário
    // Escala: Sliders de -10 a 10. Interpretar 0 como fator 1.0.
    // Valor V do slider -> Fator de escala = 1.0 + (V / 10.0) (se V=0 => 1x, V=10 => 2x, V=-10 => 0x - CUIDADO!)
    // Melhor: Fator = pow(BASE_ESCALA, V). Ex: BASE_ESCALA = 1.1.
    // Ou usar QDoubleSpinBox para fatores de escala diretos.
    // Para este exemplo, vamos tratar o valor do slider como um delta aplicado.
    ui->hsEscalaX->setValue(0); // Representa escala 1.0x (sem mudança)
    ui->hsEscalaY->setValue(0);

    // Rotação: Sliders de -180 a 180 (graus)
    ui->hsRotacaoX->setValue(0);
    ui->hsRotacaoY->setValue(0);
    ui->hsRotacaoZ->setValue(0);

    // Definir o frame de desenho para ter foco para eventos de teclado (se necessário para pan/zoom por teclado)
    if(ui->frameDesenho) {
        ui->frameDesenho->setFocusPolicy(Qt::StrongFocus);
    }

    // Desabilitar controles de transformação se nenhum objeto estiver selecionado.
    ui->tabWidget->setEnabled(objetoSelecionado != nullptr);
}

void MainWindow::gerenciarVisibilidadeSpinners(const QString& tipoForma) {
    bool mostrarX1Y1 = true;
    bool mostrarX2Y2 = false;
    bool mostrarX3Y3 = false;
    bool mostrarRaio = false;

    if (tipoForma == "Ponto") {
        // Apenas X1, Y1
    } else if (tipoForma == "Reta") {
        mostrarX2Y2 = true;
    } else if (tipoForma == "Polígono (Triângulo)") {
        mostrarX2Y2 = true;
        mostrarX3Y3 = true;
    } else if (tipoForma == "Polígono (Quadrado)") {
        mostrarX2Y2 = true;
        // Para um quadrado, X3/Y3 e X4/Y4 podem ser derivados ou entrados de outra forma.
        // Por simplicidade, o usuário pode entrar 3 e o 4º é calculado, ou entra os 4.
        // Para este exemplo, vamos pedir 2 pontos (canto opostos) ou 4 pontos.
        // O código atual para polígono aceita uma lista de pontos.
        // Para a UI simplificada, talvez pedir lado e ponto inicial para um quadrado.
        // Vou manter X3/Y3 visível e o usuário pode adicionar mais pontos depois se a lógica permitir.
        //mostrarX3Y3 = true; // E implicitamente X4Y4...
        // A UI só tem até X3Y3. Para mais pontos, a UI teria que ser dinâmica ou usar QInputDialog.
    }
    // "Raio" não é usado para Ponto, Reta, Polígono 2D como definido.
    // Poderia ser para Círculo, que não está na lista.

    ui->lblCoordenadaX1->setVisible(mostrarX1Y1); ui->spinX1->setVisible(mostrarX1Y1);
    ui->lblCoordenadaY1->setVisible(mostrarX1Y1); ui->spinY1->setVisible(mostrarX1Y1);

    ui->lblCoordenadaX2->setVisible(mostrarX2Y2); ui->spinX2->setVisible(mostrarX2Y2);
    ui->lblCoordenadaY2->setVisible(mostrarX2Y2); ui->spinY2->setVisible(mostrarX2Y2);

    ui->lblCoordenadaX3->setVisible(mostrarX3Y3); ui->spinX3->setVisible(mostrarX3Y3);
    ui->lblCoordenadaY3->setVisible(mostrarX3Y3); ui->spinY3->setVisible(mostrarX3Y3);

    ui->lblRaio->setVisible(mostrarRaio); ui->spinRaio->setVisible(mostrarRaio);
}

void MainWindow::atualizarCbDisplayFile() {
    ui->cbDisplayFile->clear();
    if (displayFile) {
        for (const auto& obj : displayFile->obterObjetos()) {
            if (obj) {
                ui->cbDisplayFile->addItem(obj->obterNome(), QVariant::fromValue(obj->obterNome()));
            }
        }
    }
    // Habilitar/desabilitar controles de transformação
    ui->tabWidget->setEnabled(objetoSelecionado != nullptr && ui->cbDisplayFile->count() > 0);
}


// --- Slots da UI ---

void MainWindow::on_comboFormas_currentIndexChanged(int index) {
    if (index < 0) return;
    QString tipoSelecionado = ui->comboFormas->currentText();
    gerenciarVisibilidadeSpinners(tipoSelecionado);
}

void MainWindow::on_btnCor_clicked() {
    QColor cor = QColorDialog::getColor(corSelecionadaParaDesenho, this, "Selecionar Cor da Forma");
    if (cor.isValid()) {
        corSelecionadaParaDesenho = cor;
        // Poderia ter um preview da cor em um QLabel, por exemplo.
        // ui->lblPreviewCor->setStyleSheet(QString("background-color: %1").arg(cor.name()));
    }
}

void MainWindow::on_btnDesenhar_clicked() {
    QString nomeFormaBase = "Forma";
    int count = displayFile ? displayFile->obterObjetos().size() + 1 : 1;
    QString nomeForma = QString("%1_%2").arg(ui->comboFormas->currentText().left(3)).arg(count); // Nome simples

    QString tipoSelecionado = ui->comboFormas->currentText();
    std::shared_ptr<ObjetoGrafico> novaForma = nullptr;

    Ponto2D p1(ui->spinX1->value(), ui->spinY1->value());

    if (tipoSelecionado == "Ponto") {
        novaForma = std::make_shared<PontoObj>(nomeForma, p1, corSelecionadaParaDesenho);
    } else if (tipoSelecionado == "Reta") {
        Ponto2D p2(ui->spinX2->value(), ui->spinY2->value());
        novaForma = std::make_shared<RetaObj>(nomeForma, p1, p2, corSelecionadaParaDesenho);
    } else if (tipoSelecionado == "Polígono (Triângulo)") {
        Ponto2D p2(ui->spinX2->value(), ui->spinY2->value());
        Ponto2D p3(ui->spinX3->value(), ui->spinY3->value());
        QList<Ponto2D> vertices = {p1, p2, p3};
        novaForma = std::make_shared<PoligonoObj>(nomeForma, vertices, corSelecionadaParaDesenho);
    } else if (tipoSelecionado == "Polígono (Quadrado)") {
        // Para um quadrado a partir de X1,Y1 e X2,Y2 (pontos opostos)
        // Ponto2D p2(ui->spinX2->value(), ui->spinY2->value());
        // Ponto2D p3(p1.obterX(), p2.obterY());
        // Ponto2D p4(p2.obterX(), p1.obterY());
        // QList<Ponto2D> vertices = {p1, p3, p2, p4}; // Ordem importa para desenho
        // Ou, se X1Y1, X2Y2, X3Y3 são 3 vértices e o 4o é para fechar um retângulo
        Ponto2D p1(ui->spinX1->value(), ui->spinY1->value());
        Ponto2D p2(ui->spinX2->value(), ui->spinY2->value());
        // Supondo que X3, Y3 são para o terceiro ponto e o usuário quer um polígono com mais pontos.
        // Um quadrado pode ser feito com 4 pontos. Para a UI com apenas 3,
        // pode ser um polígono genérico com 3 pontos, ou o usuário adiciona mais depois.
        // Para este exemplo, faremos um polígono com os pontos fornecidos (até 3 da UI).
        QList<Ponto2D> vertices;
        vertices.append(p1);
        vertices.append(p2);


        novaForma = std::make_shared<PoligonoObj>(nomeForma, vertices, corSelecionadaParaDesenho);
    }


    if (novaForma && displayFile && ui->frameDesenho && ui->frameDesenho->obterJanelaMundo()) {
        // Recalcular pontos SCN para o novo objeto antes de adicionar.
        novaForma->recalcularPontosTransformados(ui->frameDesenho->obterJanelaMundo()->obterMatrizNormalizacao());
        displayFile->adicionarObjeto(novaForma);
        atualizarCbDisplayFile();
        ui->frameDesenho->redesenhar();
        ui->cbDisplayFile->setCurrentText(novaForma->obterNome()); // Seleciona o objeto recém-adicionado
    } else {
        if(!ui->frameDesenho || !ui->frameDesenho->obterJanelaMundo()){
            QMessageBox::critical(this, "Erro", "Frame de desenho ou Janela Mundo não inicializada.");
        }
    }
}

void MainWindow::on_btnExcluirForma_clicked() {
    if (!objetoSelecionado) {
        QMessageBox::information(this, "Excluir Forma", "Nenhuma forma selecionada para excluir.");
        return;
    }
    if (displayFile) {
        displayFile->removerObjeto(objetoSelecionado->obterNome());
        objetoSelecionado = nullptr; // Desseleciona
        atualizarCbDisplayFile();
        if (ui->frameDesenho) {
            ui->frameDesenho->redesenhar();
        }
        ui->tabWidget->setEnabled(false); // Desabilita abas de transformação
    }
}

void MainWindow::on_btnCarregarOBJ_clicked() {
    // Placeholder: Carregamento de arquivos .obj é tipicamente para 3D.
    // Para 2D, poderia ser um formato de texto simples:
    // TIPO NOME X1 Y1 [X2 Y2 X3 Y3 ...] [R G B]
    QString caminhoArquivo = QFileDialog::getOpenFileName(this, "Carregar Descrição de Cena 2D", "", "Arquivos de Texto (*.txt);;Todos os Arquivos (*)");
    if (caminhoArquivo.isEmpty()) {
        return;
    }
    QFile arquivo(caminhoArquivo);
    if (!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erro ao Carregar", "Não foi possível abrir o arquivo: " + arquivo.errorString());
        return;
    }
    QTextStream in(&arquivo);
    // TODO: Lógica para parsear o arquivo e criar objetos.
    // Exemplo de linha: PONTO P1 10 20 255 0 0
    //                 RETA R1 0 0 50 50 0 255 0
    //                 POLIGONO PG1 0 0 10 0 5 10 0 0 255 (3 vértices)
    arquivo.close();
    atualizarCbDisplayFile();
    if(ui->frameDesenho) ui->frameDesenho->redesenhar();
    QMessageBox::information(this, "Carregar", "Funcionalidade de carregar arquivo ainda não implementada completamente.");
}

void MainWindow::on_cbDisplayFile_currentIndexChanged(int index) {
    if (index < 0 || !displayFile) {
        objetoSelecionado = nullptr;
        ui->tabWidget->setEnabled(false);
        return;
    }
    QString nomeObjeto = ui->cbDisplayFile->itemText(index);
    objetoSelecionado = displayFile->buscarObjeto(nomeObjeto);
    ui->tabWidget->setEnabled(objetoSelecionado != nullptr);

    // Resetar controles de transformação para o estado do objeto selecionado (ou para default)
    // Por ora, vamos resetar para valores neutros.
    // Se quiser que os controles reflitam o estado do objeto, é mais complexo.
    if (objetoSelecionado) {
        ui->spinTranslacaoX->setValue(0); // Idealmente, o acumulado do objeto
        ui->spinTranslacaoY->setValue(0);
        ui->hsEscalaX->setValue(0); // 0 no slider = fator 1x
        ui->hsEscalaY->setValue(0);
        ui->hsRotacaoX->setValue(0);
    }
}


// --- Slots para Transformações ---

void MainWindow::aplicarTranslacaoAtual() {
    if (!objetoSelecionado || !ui->frameDesenho || !ui->frameDesenho->obterJanelaMundo()) return;

    double dx = ui->spinTranslacaoX->value();
    double dy = ui->spinTranslacaoY->value();

    // A translação aqui é absoluta a partir da última posição do objeto
    // Se for para ser incremental a cada mudança no spinbox:
    // 1. Guardar a última matriz de transformação do objeto antes desta operação.
    // 2. Calcular a matriz de translação com dx, dy.
    // 3. Aplicar T * M_ultima_guardada.
    // Por simplicidade, vamos assumir que spinTranslacaoX/Y definem uma NOVA translação
    // que é combinada com a matriz de transformação atual do objeto.
    // Para um comportamento de "arrastar", os valores de dx, dy deveriam ser incrementais.
    // A UI com spinbox sugere valores diretos.
    // Se os spinboxes fossem para definir a POSIÇÃO final, seria diferente.
    // Como está, cada mudança aplica uma translação ADICIONAL com os valores atuais.
    // Isso pode ser confuso.
    // Uma abordagem melhor: ter um botão "Aplicar Translação" ou
    // os spin boxes representam a translação *total* a ser aplicada a partir de um estado "resetado".

    // Solução mais simples para agora: aplicar a translação (dx, dy) à matriz atual.
    // Se o usuário mudar o valor novamente, aplicará outra translação.
    // Para evitar acumulação excessiva a cada valueChanged,
    // pode-se aplicar a transformação apenas quando o usuário para de editar (editingFinished).
    // Ou, a cada mudança, resetar a transformação específica (translação) do objeto e aplicar a nova total.

    // Para este exemplo, cada mudança no spinbox aplica uma nova translação (dx, dy)
    // à matriz de transformação acumulada do objeto.
    Matriz T = TransformadorGeometrico::translacao(dx, dy);
    objetoSelecionado->aplicarTransformacao(T);
    objetoSelecionado->recalcularPontosTransformados(ui->frameDesenho->obterJanelaMundo()->obterMatrizNormalizacao());
    ui->frameDesenho->redesenhar();

    // Para que os spinboxes não acumulem indefinidamente ao aplicar:
    // Poderia resetá-los para 0 APÓS aplicar, indicando que a translação (dx,dy) foi "consumida".
    // ui->spinTranslacaoX->setValue(0);
    // ui->spinTranslacaoY->setValue(0);
    // Mas isso impede o usuário de ajustar finamente.
    // A melhor forma é ter um botão "Aplicar" ou os spinboxes representarem o estado final desejado.
}

void MainWindow::on_spinTranslacaoX_valueChanged(double arg1) {
    Q_UNUSED(arg1);
    aplicarTranslacaoAtual(); // Ou conectar ao signal editingFinished()
}

void MainWindow::on_spinTranslacaoY_valueChanged(double arg1) {
    Q_UNUSED(arg1);
    aplicarTranslacaoAtual(); // Ou conectar ao signal editingFinished()
}


void MainWindow::aplicarEscalaAtual() {
    if (!objetoSelecionado || !ui->frameDesenho || !ui->frameDesenho->obterJanelaMundo()) return;

    // Mapear valor do slider (-10 a 10) para fator de escala.
    // Slider = 0  -> fator 1.0 (sem escala)
    // Slider > 0 -> fator > 1.0 (aumentar)
    // Slider < 0 -> fator < 1.0 (diminuir)
    double valX = ui->hsEscalaX->value();
    double valY = ui->hsEscalaY->value();

    double sx = 1.0 + (valX / 20.0); // Ex: -10 -> 0.5x; 0 -> 1x; 10 -> 1.5x. Ajustar faixa conforme desejado.
    double sy = 1.0 + (valY / 20.0); // Se valX/Y for -20, sx/y seria 0, o que colapsa o objeto.
    // Garantir que sx, sy > 0.
    sx = std::max(0.1, sx); // Mínimo de 0.1x
    sy = std::max(0.1, sy);

    // A escala é em torno do centro geométrico do objeto.
    Ponto2D centro = objetoSelecionado->calcularCentroGeometrico();
    Matriz S = TransformadorGeometrico::escala(sx, sy, centro);

    // IMPORTANTE: Como aplicar? Se aplicarmos S diretamente à matriz acumulada,
    // a escala será relativa ao estado JÁ escalado.
    // Se quisermos que os sliders definam a escala TOTAL em relação ao original:
    // 1. Obter a matriz de transformação do objeto SEM a última escala.
    // 2. Aplicar a nova escala.
    // Isto é complexo de gerenciar.

    // Abordagem mais simples (e comum para sliders):
    // Os sliders controlam uma escala *adicional* ou *total* relativa a um estado.
    // Para este exemplo, vamos aplicar a escala S à matriz acumulada.
    // O usuário deve estar ciente que é acumulativo.
    // Para um controle mais fino, seria melhor ter um botão "Aplicar Escala" e
    // os sliders/spinboxes definem a escala para *essa* operação.

    // Solução: Armazenar a matriz de transformação "base" do objeto (antes de T,S,R desta UI)
    // e reconstruir a matriz total: M_total = M_trans_ui * M_escala_ui * M_rot_ui * M_base.
    // Isso é mais robusto mas requer mais gerenciamento de estado.

    // Por ora, vamos aplicar incrementalmente, mas isso é menos intuitivo para sliders.
    // ALTERNATIVA: Resetar a escala do objeto para 1,1 antes de aplicar a nova.
    // Isso requer decompor a matriz do objeto, o que não é trivial.

    // Vamos tentar uma abordagem onde os sliders definem a escala *total* do objeto.
    // Isso significa que precisamos de uma forma de "resetar" a escala anterior do objeto
    // e aplicar a nova.
    // Uma forma simplificada (mas não perfeita):
    // Se o objeto tem uma matriz de escala S_antiga e queremos aplicar uma nova S_nova (dos sliders)
    // de forma que a escala final seja S_nova, precisamos aplicar S_nova * Inversa(S_antiga).
    // Isso é complexo.

    // Mais simples: cada mudança no slider aplica uma PEQUENA escala incremental.
    // Isso é mais para botões "+/-" do que para sliders que definem um estado.

    // Ação para agora: os sliders definem uma escala que é aplicada.
    // Para que isso funcione como "estado final", a matriz de transformação do objeto
    // precisaria ser reconstruída a partir dos valores dos sliders + translação + rotação.
    // Esta é a abordagem MVC mais correta.

    // Reconstruir a matriz de transformação do objeto a partir dos valores atuais dos controles de UI:
    // (Assumindo que os valores de translação e rotação também são mantidos de forma similar)
    // Matriz M_obj_nova = Matriz_Translacao_UI * Matriz_Escala_UI * Matriz_Rotacao_UI;
    // objetoSelecionado->setMatrizTransformacao(M_obj_nova); // Precisaria de um setter.

    // Para o comportamento mais direto com o código atual:
    // O slider aplica uma escala. Se o usuário move de 0 para 1 e depois para 2,
    // ele aplica Escala(f(1)) e depois Escala(f(2)) sobre o resultado anterior.
    // Isso não é o ideal para sliders que representam um estado.

    // Ação: Aplicar a escala (sx, sy) em relação ao estado atual.
    // Isso é o que o código `aplicarTransformacao` já faz (multiplica pela matriz atual).
    // O usuário precisará resetar o slider para 0 para voltar à escala "anterior" antes desta operação.
    objetoSelecionado->aplicarTransformacao(S);
    objetoSelecionado->recalcularPontosTransformados(ui->frameDesenho->obterJanelaMundo()->obterMatrizNormalizacao());
    ui->frameDesenho->redesenhar();
}


void MainWindow::on_hsEscalaX_valueChanged(int value) {
    Q_UNUSED(value);
    // Para sliders, é comum aplicar a transformação quando o slider é liberado (sliderReleased)
    // ou ter um botão "Aplicar". Aplicar em valueChanged pode ser pesado e levar a múltiplas transformações.
    // Para este exemplo, vamos aplicar em valueChanged.
    aplicarEscalaAtual();
}

void MainWindow::on_hsEscalaY_valueChanged(int value) {
    Q_UNUSED(value);
    aplicarEscalaAtual();
}

void MainWindow::aplicarRotacaoAtual() {
    if (!objetoSelecionado || !ui->frameDesenho || !ui->frameDesenho->obterJanelaMundo()) return;

    double angulo = ui->hsRotacaoX->value(); // Usando hsRotacaoX para rotação 2D.

    // Rotação em torno do centro geométrico do objeto.
    Ponto2D centro = objetoSelecionado->calcularCentroGeometrico();
    Matriz R = TransformadorGeometrico::rotacao(angulo, centro);

    // Similar à Escala, a forma como a rotação é aplicada (acumulativa vs. estado final) é importante.
    // Por consistência com a aplicação de escala acima, será acumulativa.
    objetoSelecionado->aplicarTransformacao(R);
    objetoSelecionado->recalcularPontosTransformados(ui->frameDesenho->obterJanelaMundo()->obterMatrizNormalizacao());
    ui->frameDesenho->redesenhar();
}

void MainWindow::on_hsRotacaoX_valueChanged(int value) {
    Q_UNUSED(value);
    // Considerar usar sliderReleased para rotação também.
    aplicarRotacaoAtual();
}
