#include "mainwindow.h"
#include "ui_mainwindow.h"

// ... outros includes ...
#include "ponto_obj.h"
#include "reta_obj.h"
#include "poligono_obj.h"
#include "circunferencia_obj.h"
#include "transformador_geometrico.h"
#include "ponto2d.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    corSelecionadaParaDesenho(Qt::black)
{
    ui->setupUi(this);

    displayFile = std::make_shared<DisplayFile>();
    inicializarObjetosIniciais(displayFile.get());

    if (ui->frameDesenho) {
        ui->frameDesenho->definirDisplayFile(displayFile);
    } else {
        QMessageBox::critical(this, "Erro de UI", "O frameDesenho não foi carregado corretamente da UI.");
        // Considere não continuar se o frameDesenho for essencial
    }

    inicializarUI(); // Chama on_comboFormas_currentIndexChanged(0) -> gerenciarVisibilidadeSpinners

    // Conexões
    connect(ui->spinTranslacaoX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_spinTranslacaoX_valueChanged);
    connect(ui->spinTranslacaoY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_spinTranslacaoY_valueChanged);
    connect(ui->spinEscalaX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_spinEscalaX_valueChanged);
    connect(ui->spinEscalaY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_spinEscalaY_valueChanged);
    connect(ui->hsRotacaoX, &QSlider::valueChanged, this, &MainWindow::on_hsRotacaoX_valueChanged);

    connect(ui->cbDisplayFile, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_cbDisplayFile_currentIndexChanged); // Certifique-se que esta conexão existe
    connect(ui->cbDFCameras, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_cbDFCamera_currentIndexChanged);
    connect(ui->btnModificarForma, &QPushButton::clicked, this, &MainWindow::on_btnModificarForma_clicked);

    atualizarCbDisplayFile(); // Popula ComboBox de objetos
    atualizarCbDFCamera();    // Popula ComboBox de câmeras

    objetoSelecionado = nullptr;
    janelaSelecionada = nullptr;

    // Se cbDFCameras tiver itens, seleciona o ativo do displayFile ou o primeiro.
    // Isso DISPARARÁ on_cbDFCamera_currentIndexChanged, que por sua vez chamará updateTransformationTargetUIState.
    if (ui->cbDFCameras->count() > 0) {
        if (displayFile && displayFile->obterJanelaMundoAtiva()) {
            int idx = ui->cbDFCameras->findText(displayFile->obterJanelaMundoAtiva()->obterNome());
            if (idx != -1) {
                ui->cbDFCameras->setCurrentIndex(idx); // Dispara o slot
            } else if (ui->cbDFCameras->count() > 0) {
                ui->cbDFCameras->setCurrentIndex(0); // Dispara o slot
            }
        } else if (ui->cbDFCameras->count() > 0) {
            ui->cbDFCameras->setCurrentIndex(0); // Dispara o slot
        }
    } else {
        // Se não houver câmeras, e nenhum objeto selecionado (que é o padrão aqui),
        // a UI deve estar no estado "pronto para adicionar".
        // Chamada explícita para garantir, caso os setCurrentIndex acima não disparem.
        updateTransformationTargetUIState();
    }
    // A lógica acima para selecionar a câmera ativa já deve ter chamado updateTransformationTargetUIState
    // através do slot on_cbDFCamera_currentIndexChanged. Se nenhuma câmera for selecionada,
    // updateTransformationTargetUIState ainda precisa ser chamado uma vez para o estado inicial.
    // Se on_cbDFCamera_currentIndexChanged não foi chamado (nenhuma câmera), chamamos manualmente.
    if(ui->cbDFCameras->currentIndex() == -1 && ui->cbDisplayFile->currentIndex() == -1) {
        updateTransformationTargetUIState();
    }


    if (ui->frameDesenho) {
        ui->frameDesenho->redesenhar();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::inicializarObjetosIniciais(DisplayFile* df) {
    // ----- CASINHA -----
    QList<Ponto2D> verticesCasa;
    verticesCasa << Ponto2D(0, 0) << Ponto2D(0, 50)
                 << Ponto2D(50, 50) << Ponto2D(50, 0)
                 << Ponto2D(0, 50) << Ponto2D(25, 80) << Ponto2D(50, 50);
    auto casa = std::make_shared<PoligonoObj>("Casinha", verticesCasa, Qt::darkBlue);
    df->adicionarObjeto(casa);

    // ----- ÁRVORE -----
    QList<Ponto2D> verticesArvore;
    // Tronco (retângulo)
    verticesArvore << Ponto2D(100, 0) << Ponto2D(100, 30)
                   << Ponto2D(115, 30) << Ponto2D(115, 0);
    // Copa (triângulo ou círculo simples com 3 vértices)
    verticesArvore << Ponto2D(90, 30) << Ponto2D(107.5, 60) << Ponto2D(125, 30);
    auto arvore = std::make_shared<PoligonoObj>("Árvore", verticesArvore, Qt::darkGreen);
    df->adicionarObjeto(arvore);

    // ----- CARRO -----
    QList<Ponto2D> verticesCarro;
    // Corpo principal (retângulo)
    verticesCarro << Ponto2D(160, 0) << Ponto2D(160, 20)
                  << Ponto2D(220, 20) << Ponto2D(220, 0);
    // Parte superior (parabrisas)
    verticesCarro << Ponto2D(175, 20) << Ponto2D(190, 35)
                  << Ponto2D(205, 35) << Ponto2D(215, 20);
    auto carro = std::make_shared<PoligonoObj>("Carro", verticesCarro, Qt::red);
    df->adicionarObjeto(carro);

    // ----- SOL -----
    QList<Ponto2D> verticesSol;
    // Simulando um "sol" com uma estrela simples (octógono pontudo, estilizado com 8 raios)
    verticesSol << Ponto2D(300, 50) << Ponto2D(310, 70)
                << Ponto2D(330, 70) << Ponto2D(320, 90)
                << Ponto2D(330, 110) << Ponto2D(310, 110)
                << Ponto2D(300, 130) << Ponto2D(290, 110)
                << Ponto2D(270, 110) << Ponto2D(280, 90)
                << Ponto2D(270, 70) << Ponto2D(290, 70);
    auto sol = std::make_shared<PoligonoObj>("Sol", verticesSol, Qt::yellow);
    df->adicionarObjeto(sol);
}

void MainWindow::inicializarUI() {
    ui->comboFormas->addItem("Ponto", static_cast<int>(TipoObjeto::PONTO));
    ui->comboFormas->addItem("Reta", static_cast<int>(TipoObjeto::RETA));
    ui->comboFormas->addItem("Polígono (Triângulo)", static_cast<int>(TipoObjeto::POLIGONO));
    ui->comboFormas->addItem("Polígono (Quadrado)", static_cast<int>(TipoObjeto::POLIGONO));
    ui->comboFormas->addItem("Circunferência", static_cast<int>(TipoObjeto::CIRCUNFERENCIA));

    on_comboFormas_currentIndexChanged(0);

    ui->spinEscalaX->setValue(0);
    ui->spinEscalaY->setValue(0);
    ui->hsRotacaoX->setValue(0);

    if(ui->frameDesenho) {
        ui->frameDesenho->setFocusPolicy(Qt::StrongFocus);
    }
    // A habilitação do tabWidget agora depende de objetoSelecionado OU janelaSelecionada
    ui->tabWidget->setEnabled(objetoSelecionado != nullptr || janelaSelecionada != nullptr);
}

void MainWindow::gerenciarVisibilidadeSpinners(const QString& tipoForma) {
    bool mostrarX1Y1 = true;
    bool mostrarX2Y2 = false;
    bool mostrarX3Y3 = false;
    bool mostrarRaio = false;

    if (tipoForma == "Ponto") { /* ... */ }
    else if (tipoForma == "Reta") { mostrarX2Y2 = true; }
    else if (tipoForma == "Polígono (Triângulo)") { mostrarX2Y2 = true; mostrarX3Y3 = true; }
    else if (tipoForma == "Polígono (Quadrado)") { mostrarX2Y2 = true; }
    else if (tipoForma == "Circunferência") { mostrarRaio = true; }

    ui->lblCoordenadaX1->setVisible(mostrarX1Y1); ui->spinX1->setVisible(mostrarX1Y1);
    ui->lblCoordenadaY1->setVisible(mostrarX1Y1); ui->spinY1->setVisible(mostrarX1Y1);
    ui->lblCoordenadaX2->setVisible(mostrarX2Y2); ui->spinX2->setVisible(mostrarX2Y2);
    ui->lblCoordenadaY2->setVisible(mostrarX2Y2); ui->spinY2->setVisible(mostrarX2Y2);
    ui->lblCoordenadaX3->setVisible(mostrarX3Y3); ui->spinX3->setVisible(mostrarX3Y3);
    ui->lblCoordenadaY3->setVisible(mostrarX3Y3); ui->spinY3->setVisible(mostrarX3Y3);
    ui->lblRaio->setVisible(mostrarRaio); ui->spinRaio->setVisible(mostrarRaio);
}

void MainWindow::atualizarCbDisplayFile() {
    QString nomeObjetoSelecionadoAnteriormente = objetoSelecionado ? objetoSelecionado->obterNome() : "";
    ui->cbDisplayFile->clear();
    if (displayFile) {
        for (const auto& obj : displayFile->obterObjetos()) {
            if (obj) {
                ui->cbDisplayFile->addItem(obj->obterNome(), QVariant::fromValue(obj->obterNome()));
            }
        }
    }
    if (!nomeObjetoSelecionadoAnteriormente.isEmpty()) {
        int idx = ui->cbDisplayFile->findText(nomeObjetoSelecionadoAnteriormente);
        if (idx != -1) {
            ui->cbDisplayFile->setCurrentIndex(idx);
            // Não chamar on_cbDisplayFile_currentIndexChanged aqui para evitar loop se chamado de dentro dele
        } else {
            objetoSelecionado = nullptr; // Objeto não existe mais
        }
    }
    // A habilitação do tabWidget é tratada em on_cbDisplayFile_currentIndexChanged e on_cbDFCamera_currentIndexChanged
}

void MainWindow::atualizarCbDFCamera() {
    QString nomeJanelaSelecionadaAnteriormente = janelaSelecionada ? janelaSelecionada->obterNome() : (displayFile && displayFile->obterJanelaMundoAtiva() ? displayFile->obterJanelaMundoAtiva()->obterNome() : "");

    ui->cbDFCameras->clear();
    if (displayFile) {
        for (const auto& jm : displayFile->obterListaJanelasMundo()) {
            if (jm) {
                ui->cbDFCameras->addItem(jm->obterNome(), QVariant::fromValue(jm->obterNome()));
            }
        }
    }
    if (!nomeJanelaSelecionadaAnteriormente.isEmpty()) {
        int idx = ui->cbDFCameras->findText(nomeJanelaSelecionadaAnteriormente);
        if (idx != -1) {
            ui->cbDFCameras->setCurrentIndex(idx);
            // Não chamar on_cbDFCamera_currentIndexChanged aqui para evitar loop
        } else {
            janelaSelecionada = nullptr; // Janela não existe mais
        }
    }
}

void MainWindow::on_cbDFCamera_currentIndexChanged(int index) {
    if (index < 0) { // Câmera foi "desselecionada" ou ComboBox limpo
        janelaSelecionada = nullptr;
    } else { // Uma câmera foi selecionada
        if (!displayFile) { // Checagem de segurança
            janelaSelecionada = nullptr;
            updateTransformationTargetUIState();
            return;
        }
        QString nomeJanela = ui->cbDFCameras->itemText(index);
        std::shared_ptr<JanelaMundo> jmSelecionadaTemp = displayFile->buscarJanelaMundo(nomeJanela);

        if (jmSelecionadaTemp) {
            janelaSelecionada = jmSelecionadaTemp;
            displayFile->definirJanelaMundoAtiva(janelaSelecionada);

            // Garante que nenhum objeto esteja selecionado para transformação
            // Bloqueia sinais para evitar chamada recursiva de on_cbDisplayFile_currentIndexChanged
            bool oldSignalsBlocked = ui->cbDisplayFile->signalsBlocked();
            ui->cbDisplayFile->blockSignals(true);
            ui->cbDisplayFile->setCurrentIndex(-1);
            ui->cbDisplayFile->blockSignals(oldSignalsBlocked);

            // Se um objeto estava selecionado, limpamos a referência interna
            if(objetoSelecionado != nullptr){
                objetoSelecionado = nullptr;
            }

            if (displayFile) displayFile->recalcularTodosPontosSCN(); // Recalcula para a nova câmera ativa
            if (ui->frameDesenho) ui->frameDesenho->redesenhar();
        } else {
            // Câmera não encontrada, trata como desseleção
            qWarning() << "Câmera não encontrada no cbDFCameras_currentIndexChanged:" << nomeJanela;
            janelaSelecionada = nullptr;
        }
    }
    updateTransformationTargetUIState(); // Atualiza a UI com base no novo estado de seleção
}

void MainWindow::on_cbDisplayFile_currentIndexChanged(int index) {
    if (index < 0) { // Objeto foi "desselecionado" ou ComboBox limpo
        objetoSelecionado = nullptr;
    } else { // Um objeto foi selecionado
        if (!displayFile) { // Checagem de segurança
            objetoSelecionado = nullptr;
            updateTransformationTargetUIState();
            return;
        }
        QString nomeObjeto = ui->cbDisplayFile->itemText(index);
        std::shared_ptr<ObjetoGrafico> objSelecionadoTemp = displayFile->buscarObjeto(nomeObjeto);

        if (objSelecionadoTemp) {
            objetoSelecionado = objSelecionadoTemp;

            // Garante que nenhuma câmera esteja selecionada para transformação
            bool oldSignalsBlocked = ui->cbDFCameras->signalsBlocked();
            ui->cbDFCameras->blockSignals(true);
            ui->cbDFCameras->setCurrentIndex(-1);
            ui->cbDFCameras->blockSignals(oldSignalsBlocked);

            // Se uma câmera estava selecionada, limpamos a referência interna
            if(janelaSelecionada != nullptr){
                janelaSelecionada = nullptr;
            }
        } else {
            qWarning() << "Objeto não encontrado no cbDisplayFile_currentIndexChanged:" << nomeObjeto;
            objetoSelecionado = nullptr; // Não encontrou o objeto, trata como desseleção
        }
    }
    updateTransformationTargetUIState(); // Atualiza a UI com base no novo estado de seleção
}

// Slots de Desenho e Exclusão
void MainWindow::on_btnDesenhar_clicked() {
    if (!displayFile || !displayFile->obterJanelaMundoAtiva()) {
        QMessageBox::critical(this, "Erro", "DisplayFile ou Janela Mundo ativa não inicializada.");
        return;
    }

    QString tipoSelecionado = ui->comboFormas->currentText();
    std::shared_ptr<ObjetoGrafico> novaForma = nullptr;
    Ponto2D p1(ui->spinX1->value(), ui->spinY1->value()); // Ponto base

    QString nomeFormaBase; // Será definido dentro de cada case

    // Helper lambda para contar objetos de um tipo específico (mesmo de antes)
    auto obterContagemPorTipo = [&](TipoObjeto tipo, int numVerticesEspecifico = 0) {
        if (!displayFile) return 0;
        int contagem = 0;
        for (const auto& obj : displayFile->obterObjetos()) {
            if (obj && obj->obterTipo() == tipo) {
                if (tipo == TipoObjeto::POLIGONO && numVerticesEspecifico > 0) {
                    if (obj->obterPontosOriginaisMundo().size() == numVerticesEspecifico) {
                        contagem++;
                    }
                } else {
                    contagem++;
                }
            }
        }
        return contagem;
    };

    // Criação do objeto com o nomeFormaBase
    if (tipoSelecionado == "Ponto") {
        nomeFormaBase = QString("Ponto_%1").arg(obterContagemPorTipo(TipoObjeto::PONTO) + 1);
        novaForma = std::make_shared<PontoObj>(nomeFormaBase, p1, corSelecionadaParaDesenho);
    } else if (tipoSelecionado == "Reta") {
        if (!ui->spinX2->isVisible()) { /* ... validação ... */ return; }
        Ponto2D p2(ui->spinX2->value(), ui->spinY2->value());
        nomeFormaBase = QString("Reta_%1").arg(obterContagemPorTipo(TipoObjeto::RETA) + 1);
        novaForma = std::make_shared<RetaObj>(nomeFormaBase, p1, p2, corSelecionadaParaDesenho);
    } else if (tipoSelecionado == "Polígono (Triângulo)") {
        if (!ui->spinX2->isVisible() || !ui->spinX3->isVisible()) { /* ... validação ... */ return; }
        Ponto2D p2(ui->spinX2->value(), ui->spinY2->value());
        Ponto2D p3(ui->spinX3->value(), ui->spinY3->value());
        nomeFormaBase = QString("Triangulo_%1").arg(obterContagemPorTipo(TipoObjeto::POLIGONO, 3) + 1);
        QList<Ponto2D> vertices = {p1, p2, p3};
        novaForma = std::make_shared<PoligonoObj>(nomeFormaBase, vertices, corSelecionadaParaDesenho);
    } else if (tipoSelecionado == "Polígono (Quadrado)") {
        if (!ui->spinX2->isVisible()) { /* ... validação ... */ return; }
        Ponto2D p2_diag(ui->spinX2->value(), ui->spinY2->value());
        nomeFormaBase = QString("Quadrado_%1").arg(obterContagemPorTipo(TipoObjeto::POLIGONO, 4) + 1);
        Ponto2D v1 = p1; Ponto2D v2(p2_diag.obterX(), p1.obterY());
        Ponto2D v3 = p2_diag; Ponto2D v4(p1.obterX(), p2_diag.obterY());
        QList<Ponto2D> vertices = {v1, v2, v3, v4};
        novaForma = std::make_shared<PoligonoObj>(nomeFormaBase, vertices, corSelecionadaParaDesenho);
    } else if (tipoSelecionado == "Circunferência") {
        if (!ui->spinRaio->isVisible() || ui->spinRaio->value() <= 0) { /* ... validação ... */ return; }
        double raio = ui->spinRaio->value();
        nomeFormaBase = QString("Circulo_%1").arg(obterContagemPorTipo(TipoObjeto::CIRCUNFERENCIA) + 1);
        novaForma = std::make_shared<CircunferenciaObj>(nomeFormaBase, p1, raio, corSelecionadaParaDesenho);
    }

    if (novaForma) {
        // Usa a nova função para gerar o nome completo e definir no objeto
        QString nomeFinal = gerarNomeFormatadoParaObjeto(nomeFormaBase, novaForma, corSelecionadaParaDesenho);
        novaForma->definirNome(nomeFinal);

        novaForma->recalcularPontosTransformados(displayFile->obterJanelaMundoAtiva()->obterMatrizNormalizacao());
        displayFile->adicionarObjeto(novaForma);

        atualizarCbDisplayFile();

        ui->cbDisplayFile->setCurrentIndex(-1);

        if (ui->frameDesenho) ui->frameDesenho->redesenhar();

    } else {
        if (tipoSelecionado.isEmpty()){
            QMessageBox::warning(this, "Seleção Inválida", "Nenhuma forma selecionada para desenhar.");
        } else {
            QMessageBox::critical(this, "Erro Interno", "Não foi possível criar a forma selecionada.");
        }
    }
}

QString MainWindow::tipoObjetoParaStringUI(TipoObjeto tipo, int numPontos) {
    switch (tipo) {
    case TipoObjeto::PONTO: return "Ponto";
    case TipoObjeto::RETA: return "Reta";
    case TipoObjeto::POLIGONO:
        if (numPontos == 3) return "Polígono (Triângulo)";
        if (numPontos == 4) return "Polígono (Quadrado)";
        // Adicione mais casos se tiver outros tipos de polígonos específicos na UI
        return "Polígono"; // Fallback para outros polígonos
    case TipoObjeto::CIRCUNFERENCIA: return "Circunferência";
    default: return "";
    }
}

void MainWindow::atualizarObjetoComDadosDaUI(std::shared_ptr<ObjetoGrafico>& objeto) {
    if (!objeto) return;

    TipoObjeto tipo = objeto->obterTipo(); // O tipo é do objeto que está sendo modificado/criado

    // 1. Obter novas coordenadas/raio dos campos da UI e definir no objeto
    if (tipo == TipoObjeto::PONTO) {
        Ponto2D p(ui->spinX1->value(), ui->spinY1->value());
        objeto->definirPontosOriginaisMundo({p}); // Define a lista de pontos
    } else if (tipo == TipoObjeto::RETA) {
        Ponto2D p1(ui->spinX1->value(), ui->spinY1->value());
        Ponto2D p2(ui->spinX2->value(), ui->spinY2->value());
        objeto->definirPontosOriginaisMundo({p1, p2});
    } else if (tipo == TipoObjeto::POLIGONO) {
        QList<Ponto2D> novosPontos;
        if (tipoObjetoParaStringUI(tipo, objeto->obterPontosOriginaisMundo().size()) == "Polígono (Triângulo)") {
            novosPontos << Ponto2D(ui->spinX1->value(), ui->spinY1->value())
            << Ponto2D(ui->spinX2->value(), ui->spinY2->value())
            << Ponto2D(ui->spinX3->value(), ui->spinY3->value());
        }
        // Se for um quadrado e X1/Y1 (canto1) e X2/Y2 (canto oposto) estão visíveis:
        else if (tipoObjetoParaStringUI(tipo, objeto->obterPontosOriginaisMundo().size()) == "Polígono (Quadrado)") {
            Ponto2D c1(ui->spinX1->value(), ui->spinY1->value());
            Ponto2D c3_oposto(ui->spinX2->value(), ui->spinY2->value());
            novosPontos << c1 << Ponto2D(c3_oposto.obterX(), c1.obterY())
                        << c3_oposto << Ponto2D(c1.obterX(), c3_oposto.obterY());
        } else { // Fallback ou outros polígonos (a UI precisa suportar)
            // Se a UI só tem X1-Y3, só podemos atualizar os 3 primeiros pontos.
            // Isso é uma simplificação; uma edição de polígono real é mais complexa.
            QList<Ponto2D> pontosAtuais = objeto->obterPontosOriginaisMundo();
            novosPontos = pontosAtuais; // Começa com os pontos existentes
            if (novosPontos.size() >= 1 && ui->spinX1->isVisible()) { novosPontos[0].definirX(ui->spinX1->value()); novosPontos[0].definirY(ui->spinY1->value());}
            if (novosPontos.size() >= 2 && ui->spinX2->isVisible()) { novosPontos[1].definirX(ui->spinX2->value()); novosPontos[1].definirY(ui->spinY2->value());}
            if (novosPontos.size() >= 3 && ui->spinX3->isVisible()) { novosPontos[2].definirX(ui->spinX3->value()); novosPontos[2].definirY(ui->spinY3->value());}
        }
        objeto->definirPontosOriginaisMundo(novosPontos);
    } else if (tipo == TipoObjeto::CIRCUNFERENCIA) {
        auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(objeto);
        if (circulo) {
            Ponto2D novoCentro(ui->spinX1->value(), ui->spinY1->value());
            double novoRaio = ui->spinRaio->value();
            if (novoRaio <= 0) {
                QMessageBox::warning(this, "Raio Inválido", "O raio da circunferência deve ser positivo. Alteração não aplicada.");
                return;
            }
            circulo->definirCentroOriginal(novoCentro); // Atualiza o centro
            circulo->definirRaioOriginal(novoRaio);   // Atualiza o raio (isso deve chamar gerarPontosAproximacao)
        }
    }

    // 2. Atualizar cor do objeto
    objeto->definirCor(corSelecionadaParaDesenho); // corSelecionadaParaDesenho é membro de MainWindow
}

void MainWindow::on_btnModificarForma_clicked() {
    if (!objetoSelecionado || !displayFile || !displayFile->obterJanelaMundoAtiva()) {
        QMessageBox::warning(this, "Modificar Forma", "Nenhuma forma selecionada ou sistema não inicializado.");
        return;
    }

    // 1. Preservar o nome base original do objeto
    QString nomeCompletoAtual = objetoSelecionado->obterNome();
    QString nomeBase = nomeCompletoAtual.section(" => ", 0, 0);
    if (nomeBase.isEmpty() || !nomeCompletoAtual.contains(" => ")) {
        // Fallback se o nome não estiver no formato esperado
        // Você pode querer uma lógica mais robusta aqui para extrair/manter o identificador único
        nomeBase = tipoObjetoParaStringUI(objetoSelecionado->obterTipo(), objetoSelecionado->obterPontosOriginaisMundo().size()) + "_modificado";
        qWarning() << "Não foi possível extrair nome base de: " << nomeCompletoAtual << ". Usando fallback: " << nomeBase;
    }

    // 2. Atualizar as propriedades do objeto (geométricas e cor) com os dados da UI
    atualizarObjetoComDadosDaUI(objetoSelecionado);

    // 3. Recalcular pontos SCN do objeto modificado
    objetoSelecionado->recalcularPontosTransformados(displayFile->obterJanelaMundoAtiva()->obterMatrizNormalizacao());

    // 4. Gerar e definir o novo nome formatado
    QString nomeNovoFormatado = gerarNomeFormatadoParaObjeto(nomeBase, objetoSelecionado, corSelecionadaParaDesenho);
    objetoSelecionado->definirNome(nomeNovoFormatado);

    // 5. Atualizar o ComboBox e redesenhar a cena
    // int indiceSelecionadoOriginal = ui->cbDisplayFile->currentIndex(); // Não é mais necessário com a busca pelo nome

    atualizarCbDisplayFile(); // Limpa e recarrega o ComboBox

    // Tenta encontrar e re-selecionar o item (agora possivelmente com novo nome)
    int novoIndiceParaSelecionar = ui->cbDisplayFile->findText(nomeNovoFormatado);
    ui->cbDisplayFile->setCurrentIndex(novoIndiceParaSelecionar);
    // Se não encontrar (novoIndiceParaSelecionar == -1), a seleção será removida,
    // o que é o comportamento correto e acionará on_cbDisplayFile_currentIndexChanged(-1).

    if (ui->frameDesenho) {
        ui->frameDesenho->redesenhar();
    }
    // QMessageBox::information(this, "Modificar Forma", "Forma modificada."); // Opcional
}

void MainWindow::on_btnExcluirForma_clicked() {
    if (!objetoSelecionado) {
        QMessageBox::information(this, "Excluir Forma", "Nenhuma forma selecionada para excluir.");
        return;
    }
    if (displayFile) {
        displayFile->removerObjeto(objetoSelecionado->obterNome());
        // objetoSelecionado será definido como nullptr por on_cbDisplayFile_currentIndexChanged

        atualizarCbDisplayFile(); // Atualiza a lista no ComboBox

        // Garante que nada esteja selecionado após a exclusão
        ui->cbDisplayFile->setCurrentIndex(-1);
        // Isso irá disparar on_cbDisplayFile_currentIndexChanged(-1) para atualizar os botões

        if (ui->frameDesenho) ui->frameDesenho->redesenhar();
    }
}

// Slots para Transformações
void MainWindow::aplicarTranslacaoAtual() {
    if (!ui->tabWidget->isEnabled()) return; // Se as transformações não estiverem habilitadas, não faz nada

    double dx = ui->spinTranslacaoX->value();
    double dy = ui->spinTranslacaoY->value();

    if (objetoSelecionado && displayFile && displayFile->obterJanelaMundoAtiva()) {
        // Transformar OBJETO SELECIONADO
        Matriz T = TransformadorGeometrico::translacao(dx, dy);
        objetoSelecionado->aplicarTransformacao(T);
        objetoSelecionado->recalcularPontosTransformados(displayFile->obterJanelaMundoAtiva()->obterMatrizNormalizacao());
        // O nome do objeto não muda com transformações geométricas, apenas com edição de coordenadas/cor
    } else if (janelaSelecionada && displayFile) {
        // Transformar CÂMERA SELECIONADA
        janelaSelecionada->deslocar(dx, dy);
        displayFile->recalcularTodosPontosSCN(); // Recalcula SCN de todos os objetos para a nova câmera
    } else {
        return; // Nenhum alvo válido para transformação
    }

    if (ui->frameDesenho) ui->frameDesenho->redesenhar();

    // Opcional: resetar os valores de dx, dy nos spinboxes se forem incrementais
    ui->spinTranslacaoX->setValue(0);
    ui->spinTranslacaoY->setValue(0);
}

void MainWindow::on_spinTranslacaoX_valueChanged(double /*arg1*/) {
    aplicarTranslacaoAtual();
}

void MainWindow::on_spinTranslacaoY_valueChanged(double /*arg1*/) {
    aplicarTranslacaoAtual();
}

void MainWindow::aplicarEscalaAtual() {
    if (!ui->tabWidget->isEnabled()) return;

    double valX = ui->spinEscalaX->value();
    double valY = ui->spinEscalaY->value(); // Usado para objeto, para câmera podemos usar só X

    if (objetoSelecionado && displayFile && displayFile->obterJanelaMundoAtiva()) {
        // Escalar OBJETO SELECIONADO
        double sx = 1.0 + (valX / 20.0); sx = std::max(0.1, sx);
        double sy = 1.0 + (valY / 20.0); sy = std::max(0.1, sy);
        Ponto2D centro = objetoSelecionado->calcularCentroGeometrico();
        Matriz S = TransformadorGeometrico::escala(sx, sy, centro);
        objetoSelecionado->aplicarTransformacao(S);
        objetoSelecionado->recalcularPontosTransformados(displayFile->obterJanelaMundoAtiva()->obterMatrizNormalizacao());
    } else if (janelaSelecionada && displayFile) {
        // Escalar (Zoom) CÂMERA SELECIONADA
        double fatorZoom = 1.0 + (valX / 10.0); // Exemplo: slider X controla zoom
        fatorZoom = std::max(0.1, fatorZoom);
        janelaSelecionada->zoom(fatorZoom);
        displayFile->recalcularTodosPontosSCN();
    } else {
        return; // Nenhum alvo válido
    }

    if (ui->frameDesenho) ui->frameDesenho->redesenhar();
}

void MainWindow::on_spinEscalaX_valueChanged(double /*value*/) {
    aplicarEscalaAtual();
}

void MainWindow::on_spinEscalaY_valueChanged(double /*value*/) {
    aplicarEscalaAtual();
}

void MainWindow::aplicarRotacaoAtual() {
    if (!ui->tabWidget->isEnabled()) return;

    double anguloGraus = ui->hsRotacaoX->value();

    if (objetoSelecionado && displayFile && displayFile->obterJanelaMundoAtiva()) {
        // Rotacionar OBJETO SELECIONADO
        Ponto2D pivo = objetoSelecionado->calcularCentroGeometrico();
        Matriz R = TransformadorGeometrico::rotacao(anguloGraus, pivo); // Se esperar radianos: qDegreesToRadians(anguloGraus)
        objetoSelecionado->aplicarTransformacao(R);
        objetoSelecionado->recalcularPontosTransformados(displayFile->obterJanelaMundoAtiva()->obterMatrizNormalizacao());
    } else if (janelaSelecionada && displayFile) {
        // Rotacionar CÂMERA SELECIONADA
        janelaSelecionada->rotacionar(anguloGraus);
        displayFile->recalcularTodosPontosSCN();
        qDebug() << "Tentativa de rotacionar câmera: " << janelaSelecionada->obterNome() << " por " << anguloGraus << " graus.";
    } else {
        return; // Nenhum alvo válido
    }

    if (ui->frameDesenho) ui->frameDesenho->redesenhar();
}

void MainWindow::on_hsRotacaoX_valueChanged(int /*value*/) {
    aplicarRotacaoAtual();
}

void MainWindow::on_btnCor_clicked() {
    QColor cor = QColorDialog::getColor(corSelecionadaParaDesenho, this, "Selecionar Cor da Forma");
    if (cor.isValid()) {
        corSelecionadaParaDesenho = cor;
        // Se um objeto estiver selecionado, poderia aplicar a cor a ele diretamente
        if (objetoSelecionado) {
            objetoSelecionado->definirCor(corSelecionadaParaDesenho);
            if (ui->frameDesenho) ui->frameDesenho->redesenhar();
        }
    }
}

void MainWindow::on_comboFormas_currentIndexChanged(int index) {
    if (index < 0) return; // Proteção contra índice inválido
    QString tipoSelecionado = ui->comboFormas->currentText();
    gerenciarVisibilidadeSpinners(tipoSelecionado);
}

QString MainWindow::gerarNomeFormatadoParaObjeto(const QString& nomeBase,
                                                 std::shared_ptr<ObjetoGrafico> objeto,
                                                 const QColor& cor) {
    if (!objeto) {
        return nomeBase; // Retorna o nome base se o objeto for inválido por algum motivo
    }

    QString coordenadasStr = "Coordenadas Indisponíveis"; // Valor padrão
    QString corStr = cor.name(QColor::HexRgb); // Formato ex: #RRGGBB

    TipoObjeto tipo = objeto->obterTipo();
    const QList<Ponto2D>& pontosOriginais = objeto->obterPontosOriginaisMundo();

    if (tipo == TipoObjeto::PONTO) {
        if (!pontosOriginais.isEmpty()) {
            const Ponto2D& p = pontosOriginais.first();
            coordenadasStr = QString("(%1, %2)").arg(p.obterX()).arg(p.obterY());
        }
    } else if (tipo == TipoObjeto::RETA) {
        if (pontosOriginais.size() >= 2) {
            const Ponto2D& p1 = pontosOriginais[0];
            const Ponto2D& p2 = pontosOriginais[1];
            coordenadasStr = QString("(%1, %2) a (%3, %4)")
                                 .arg(p1.obterX()).arg(p1.obterY())
                                 .arg(p2.obterX()).arg(p2.obterY());
        }
    } else if (tipo == TipoObjeto::POLIGONO) {
        if (pontosOriginais.size() == 3) { // Triângulo
            coordenadasStr = QString("(%1,%2), (%3,%4), (%5,%6)")
                                 .arg(pontosOriginais[0].obterX()).arg(pontosOriginais[0].obterY())
                                 .arg(pontosOriginais[1].obterX()).arg(pontosOriginais[1].obterY())
                                 .arg(pontosOriginais[2].obterX()).arg(pontosOriginais[2].obterY());
        } else if (pontosOriginais.size() == 4) { // Quadrado/Retângulo
            // Assume que os pontos já estão na ordem correta no objeto
            coordenadasStr = QString("(%1,%2), (%3,%4), (%5,%6), (%7,%8)")
                                 .arg(pontosOriginais[0].obterX()).arg(pontosOriginais[0].obterY())
                                 .arg(pontosOriginais[1].obterX()).arg(pontosOriginais[1].obterY())
                                 .arg(pontosOriginais[2].obterX()).arg(pontosOriginais[2].obterY())
                                 .arg(pontosOriginais[3].obterX()).arg(pontosOriginais[3].obterY());
        } else if (!pontosOriginais.isEmpty()){ // Outros polígonos
            coordenadasStr = QStringLiteral("%1 Vértices: ").arg(pontosOriginais.size());
            for(int i = 0; i < qMin(pontosOriginais.size(), 2); ++i) { // Exibe os 2 primeiros pontos
                coordenadasStr += QString("(%1,%2) ").arg(pontosOriginais[i].obterX()).arg(pontosOriginais[i].obterY());
            }
            if(pontosOriginais.size() > 2) coordenadasStr += "...";
        }
    } else if (tipo == TipoObjeto::CIRCUNFERENCIA) {
        // Para obter o centro e raio originais, precisamos fazer um cast
        // e assumir que CircunferenciaObj armazena esses dados.
        auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(objeto);
        if (circulo) {
            if (!pontosOriginais.isEmpty()) { // O centro pode estar aqui
                Ponto2D centro = circulo->obterCentroOriginal(); // NECESSÁRIO: Adicionar este método a CircunferenciaObj
                double raio = circulo->obterRaioOriginal();   // NECESSÁRIO: Adicionar este método a CircunferenciaObj
                coordenadasStr = QString("Centro(%1, %2), Raio(%3)")
                                     .arg(centro.obterX()).arg(centro.obterY()).arg(raio);
            } else {
                coordenadasStr = "Dados da Circunferência Incompletos";
            }
        }
    }

    return QString("%1 => %2 - %3")
        .arg(nomeBase)
        .arg(coordenadasStr)
        .arg(corStr);
}

void MainWindow::updateTransformationTargetUIState() {
    bool objectIsSelected = (objetoSelecionado != nullptr);
    bool cameraIsSelected = (janelaSelecionada != nullptr);

    // Definir qual é o alvo ativo para as transformações (T,S,R)
    // Se um objeto está selecionado, ele é o alvo. Senão, se uma câmera está selecionada, ela é o alvo.
    bool transformTargetIsObject = objectIsSelected;
    bool transformTargetIsCamera = !objectIsSelected && cameraIsSelected;

    // Visibilidade dos botões Adicionar/Modificar/Excluir (ligada à seleção de OBJETOS)
    ui->btnDesenhar->setVisible(!objectIsSelected);
    ui->btnModificarForma->setVisible(objectIsSelected);
    ui->btnExcluirForma->setVisible(objectIsSelected);

    // Habilitar/Desabilitar abas de transformação (T,S,R)
    ui->tabWidget->setEnabled(transformTargetIsObject || transformTargetIsCamera);

    if (transformTargetIsObject) {
        // Objeto é o alvo: popular campos de edição com dados do objeto
        TipoObjeto tipo = objetoSelecionado->obterTipo();
        const QList<Ponto2D>& pontos = objetoSelecionado->obterPontosOriginaisMundo();

        // Atualiza visibilidade dos spinners (X1, Raio, etc.)
        gerenciarVisibilidadeSpinners(tipoObjetoParaStringUI(tipo, pontos.size()));

        // Preenche os valores dos spinners
        if (tipo == TipoObjeto::PONTO && !pontos.isEmpty()) {
            ui->spinX1->setValue(pontos[0].obterX()); ui->spinY1->setValue(pontos[0].obterY());
        } else if (tipo == TipoObjeto::RETA && pontos.size() >= 2) {
            ui->spinX1->setValue(pontos[0].obterX()); ui->spinY1->setValue(pontos[0].obterY());
            ui->spinX2->setValue(pontos[1].obterX()); ui->spinY2->setValue(pontos[1].obterY());
        } else if (tipo == TipoObjeto::POLIGONO) {
            // Preenche os spinners visíveis com os dados dos pontos do polígono
            if (pontos.size() >= 1 && ui->spinX1->isVisible()) { ui->spinX1->setValue(pontos[0].obterX()); ui->spinY1->setValue(pontos[0].obterY()); } else { ui->spinX1->setValue(0); ui->spinY1->setValue(0); }
            if (pontos.size() >= 2 && ui->spinX2->isVisible()) { ui->spinX2->setValue(pontos[1].obterX()); ui->spinY2->setValue(pontos[1].obterY()); } else { ui->spinX2->setValue(0); ui->spinY2->setValue(0); }
            if (pontos.size() >= 3 && ui->spinX3->isVisible()) { ui->spinX3->setValue(pontos[2].obterX()); ui->spinY3->setValue(pontos[2].obterY()); } else { ui->spinX3->setValue(0); ui->spinY3->setValue(0); }
        } else if (tipo == TipoObjeto::CIRCUNFERENCIA) {
            auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(objetoSelecionado);
            if (circulo) {
                ui->spinX1->setValue(circulo->obterCentroOriginal().obterX());
                ui->spinY1->setValue(circulo->obterCentroOriginal().obterY());
                ui->spinRaio->setValue(circulo->obterRaioOriginal());
            } else { /* Fallback: limpar spinners */ ui->spinX1->setValue(0); ui->spinY1->setValue(0); ui->spinRaio->setValue(0); }
        }
        corSelecionadaParaDesenho = objetoSelecionado->obterCor();
        // Ex: ui->lblPreviewCor->setStyleSheet(QString("background-color: %1").arg(corSelecionadaParaDesenho.name()));
    } else if (transformTargetIsCamera) {
        // Câmera é o alvo: os spinners de geometria (X1, Raio) não se aplicam diretamente à câmera
        // Mantém a visibilidade dos spinners para adicionar NOVAS formas.
        gerenciarVisibilidadeSpinners(ui->comboFormas->currentText());
    } else { // Nenhum alvo de transformação selecionado
        // Mantém a visibilidade dos spinners para adicionar NOVAS formas.
        gerenciarVisibilidadeSpinners(ui->comboFormas->currentText());
        // Limpar campos de entrada de coordenadas se não houver seleção de objeto
        ui->spinX1->setValue(0); ui->spinY1->setValue(0);
        ui->spinX2->setValue(0); ui->spinY2->setValue(0);
        ui->spinX3->setValue(0); ui->spinY3->setValue(0);
        ui->spinRaio->setValue(0);
    }

    // Resetar controles de Translação, Escala, Rotação (T,S,R)
    // pois eles geralmente representam uma ação a ser aplicada, não um estado fixo do objeto/câmera
    ui->spinTranslacaoX->setValue(0);
    ui->spinTranslacaoY->setValue(0);
    ui->spinEscalaX->setValue(0);
    ui->spinEscalaY->setValue(0);
    ui->hsRotacaoX->setValue(0);
}

void MainWindow::on_btnLimparSelecao_clicked(){
    ui->cbDisplayFile->setCurrentIndex(-1);
}

void MainWindow::on_btnCarregarOBJ_clicked() {
    QMessageBox::information(this, "Carregar", "Funcionalidade de carregar arquivo ainda não implementada completamente.");
}


// Botão para criar nova câmera/janela:
/*
void MainWindow::on_btnNovaCamera_clicked() {
    // Exemplo: Criar uma nova janela com nome e dimensões padrão ou pedidas ao usuário
    QString nomeNovaCamera = QString("Câmera %1").arg(displayFile->obterListaJanelasMundo().size() + 1);
    auto novaJanela = std::make_shared<JanelaMundo>(nomeNovaCamera, -100, -100, 100, 100); // Exemplo de dimensões
    displayFile->adicionarJanelaMundo(novaJanela);
    atualizarCbDFCamera();
    ui->cbDFCameras->setCurrentText(novaJanela->obterNome()); // Seleciona a nova câmera
}
*/
