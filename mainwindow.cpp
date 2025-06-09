#include "mainwindow.h"
#include "ui_mainwindow.h"

// ... outros includes ...
#include "ponto_obj.h"
#include "reta_obj.h"
#include "poligono_obj.h"
#include "circunferencia_obj.h"
#include "transformador_geometrico.h"
#include "ponto3d.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QRadioButton>

#include <QMessageBox> // Adicione no topo do seu mainwindow.cpp se já não estiver lá

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    corSelecionadaParaDesenho(Qt::black)
{
    ui->setupUi(this);

    // 1. Inicializa o DisplayFile e o popula com uma cena padrão.
    displayFile = std::make_shared<DisplayFile>();
    inicializarObjetosIniciais(displayFile.get());

    // 2. Conecta o DisplayFile ao Frame de Desenho.
    if (ui->frameDesenho) {
        ui->frameDesenho->definirDisplayFile(displayFile);
    } else {
        QMessageBox::critical(this, "Erro de UI", "O frameDesenho não foi carregado corretamente da UI.");
    }

    // 3. Prepara a UI com valores e estados iniciais.
    inicializarUI();

    // 4. Conecta os sinais da UI aos slots da MainWindow.
    // Conexões de criação/modificação
    connect(ui->btnModificarForma, &QPushButton::clicked, this, &MainWindow::on_btnModificarForma_clicked);

    // Conexões de seleção
    connect(ui->cbDisplayFile, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_cbDisplayFile_currentIndexChanged);
    connect(ui->cbDFCameras, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_cbDFCamera_currentIndexChanged);

    // --- CONEXÕES DE TRANSFORMAÇÃO ATUALIZADAS PARA 3D ---
    // Translação
    connect(ui->spinTranslacaoX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::aplicarTranslacaoAtual);
    connect(ui->spinTranslacaoY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::aplicarTranslacaoAtual);
    connect(ui->spinTranslacaoZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::aplicarTranslacaoAtual); // NOVO

    // Escala
    connect(ui->spinEscalaX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::aplicarEscalaAtual);
    connect(ui->spinEscalaY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::aplicarEscalaAtual);
    connect(ui->spinEscalaZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::aplicarEscalaAtual); // NOVO

    // Rotação
    connect(ui->hsRotacaoX, &QSlider::valueChanged, this, &MainWindow::aplicarRotacaoAtual); // NOVO
    connect(ui->hsRotacaoY, &QSlider::valueChanged, this, &MainWindow::aplicarRotacaoAtual); // NOVO
    connect(ui->hsRotacaoZ, &QSlider::valueChanged, this, &MainWindow::aplicarRotacaoAtual); // Antigo hsRotacaoX

    // 5. Popula as ComboBoxes com os dados iniciais do DisplayFile.
    atualizarCbDisplayFile();
    atualizarCbDFCamera();

    // 6. Define o estado inicial da seleção.
    objetoSelecionado = nullptr;
    // A variável 'janelaSelecionada' foi removida, a câmera ativa é gerenciada pelo DisplayFile.

    // 7. Define a câmera ativa na UI, sincronizando com o estado do DisplayFile.
    // Isso dispara o slot on_cbDFCamera_currentIndexChanged, que ajusta a UI.
    if (ui->cbDFCameras->count() > 0) {
        if (displayFile && displayFile->obterCameraAtiva()) {
            // Usa a nova classe Camera
            int idx = ui->cbDFCameras->findText(displayFile->obterCameraAtiva()->obterNome());
            if (idx != -1) {
                ui->cbDFCameras->setCurrentIndex(idx);
            } else {
                ui->cbDFCameras->setCurrentIndex(0);
            }
        } else {
            ui->cbDFCameras->setCurrentIndex(0);
        }
    } else {
        // Se nenhuma câmera foi criada, garante que a UI esteja no estado correto.
        updateTransformationTargetUIState();
    }

    // 8. Dispara o primeiro desenho.
    if (ui->frameDesenho) {
        ui->frameDesenho->redesenhar();
    }
}


MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief Cria uma cena 3D padrão para popular o DisplayFile na inicialização.
 * Substitui a cena 2D anterior por um cubo, uma pirâmide e um círculo orientado.
 * @param df O DisplayFile a ser populado.
 */
void MainWindow::inicializarObjetosIniciais(DisplayFile* df) {
    // ----- CUBO 3D ARAMADO (Wireframe Cube) -----
    // O cubo será construído a partir de 6 faces (polígonos).
    // Definimos os 8 vértices do cubo, centrado na origem.
    double tam = 40.0; // Metade do tamanho do lado do cubo
    Ponto3D v0(-tam, -tam, -tam);
    Ponto3D v1( tam, -tam, -tam);
    Ponto3D v2( tam,  tam, -tam);
    Ponto3D v3(-tam,  tam, -tam);
    Ponto3D v4(-tam, -tam,  tam);
    Ponto3D v5( tam, -tam,  tam);
    Ponto3D v6( tam,  tam,  tam);
    Ponto3D v7(-tam,  tam,  tam);

    // Definir cada face como um PoligonoObj
    QList<Ponto3D> faceFrente = {v0, v1, v2, v3};
    QList<Ponto3D> faceTras   = {v5, v4, v7, v6}; // Ordem invertida para manter consistência de winding (opcional)
    QList<Ponto3D> faceBaixo  = {v1, v0, v4, v5};
    QList<Ponto3D> faceCima   = {v3, v2, v6, v7};
    QList<Ponto3D> faceEsq    = {v0, v3, v7, v4};
    QList<Ponto3D> faceDir    = {v2, v1, v5, v6};

    auto pFrente = std::make_shared<PoligonoObj>("Cubo-Frente", faceFrente, Qt::red);
    auto pTras   = std::make_shared<PoligonoObj>("Cubo-Trás", faceTras, Qt::darkRed);
    auto pBaixo  = std::make_shared<PoligonoObj>("Cubo-Baixo", faceBaixo, Qt::blue);
    auto pCima   = std::make_shared<PoligonoObj>("Cubo-Cima", faceCima, Qt::darkBlue);
    auto pEsq    = std::make_shared<PoligonoObj>("Cubo-Esquerda", faceEsq, Qt::green);
    auto pDir    = std::make_shared<PoligonoObj>("Cubo-Direita", faceDir, Qt::darkGreen);

    df->adicionarObjeto(pFrente);
    df->adicionarObjeto(pTras);
    df->adicionarObjeto(pBaixo);
    df->adicionarObjeto(pCima);
    df->adicionarObjeto(pEsq);
    df->adicionarObjeto(pDir);


    // ----- PIRÂMIDE 3D (construída com retas) -----
    // Colocada à direita do cubo
    double offsetPiramide = 150.0;
    Ponto3D p_base1(offsetPiramide - tam, -tam, -tam);
    Ponto3D p_base2(offsetPiramide + tam, -tam, -tam);
    Ponto3D p_base3(offsetPiramide + tam, -tam,  tam);
    Ponto3D p_base4(offsetPiramide - tam, -tam,  tam);
    Ponto3D p_topo (offsetPiramide,        tam,  0);

    // Base da pirâmide
    df->adicionarObjeto(std::make_shared<RetaObj>("Piramide-Base1", p_base1, p_base2, Qt::darkMagenta));
    df->adicionarObjeto(std::make_shared<RetaObj>("Piramide-Base2", p_base2, p_base3, Qt::darkMagenta));
    df->adicionarObjeto(std::make_shared<RetaObj>("Piramide-Base3", p_base3, p_base4, Qt::darkMagenta));
    df->adicionarObjeto(std::make_shared<RetaObj>("Piramide-Base4", p_base4, p_base1, Qt::darkMagenta));
    // Lados da pirâmide
    df->adicionarObjeto(std::make_shared<RetaObj>("Piramide-Lado1", p_base1, p_topo, Qt::magenta));
    df->adicionarObjeto(std::make_shared<RetaObj>("Piramide-Lado2", p_base2, p_topo, Qt::magenta));
    df->adicionarObjeto(std::make_shared<RetaObj>("Piramide-Lado3", p_base3, p_topo, Qt::magenta));
    df->adicionarObjeto(std::make_shared<RetaObj>("Piramide-Lado4", p_base4, p_topo, Qt::magenta));


    // ----- CIRCUNFERÊNCIA 3D ORIENTADA -----
    // Colocada à esquerda do cubo, em um plano diagonal.
    Ponto3D centroCirc(-150.0, 0, 0);
    double raioCirc = 50.0;
    Ponto3D normalCirc(1, 1, 0); // Normal em um plano diagonal
    auto anel = std::make_shared<CircunferenciaObj>("Anel Diagonal", centroCirc, raioCirc, normalCirc, Qt::darkCyan);
    df->adicionarObjeto(anel);
}

/**
 * @brief Prepara a UI com valores e estados iniciais para o ambiente 3D.
 */
void MainWindow::inicializarUI() {
    // 1. Popula a ComboBox com as formas, incluindo uma nova forma 3D.
    ui->comboFormas->addItem("Ponto", static_cast<int>(TipoObjeto::PONTO));
    ui->comboFormas->addItem("Reta", static_cast<int>(TipoObjeto::RETA));
    ui->comboFormas->addItem("Polígono (Triângulo)", static_cast<int>(TipoObjeto::POLIGONO));
    ui->comboFormas->addItem("Circunferência", static_cast<int>(TipoObjeto::CIRCUNFERENCIA));
    ui->comboFormas->addItem("Cubo", static_cast<int>(TipoObjeto::CUBO)); // NOVO TIPO (adicione ao seu enum TipoObjeto)

    // Dispara a chamada inicial para ajustar a visibilidade dos spinners
    on_comboFormas_currentIndexChanged(0);

    // 2. Reseta os valores iniciais dos controles de transformação 3D.
    ui->spinEscalaX->setValue(0);
    ui->spinEscalaY->setValue(0);
    ui->spinEscalaZ->setValue(0); // NOVO
    ui->hsRotacaoX->setValue(0);
    ui->hsRotacaoY->setValue(0); // NOVO
    ui->hsRotacaoZ->setValue(0); // NOVO

    // 3. Define o foco para o frame de desenho para capturar eventos de teclado, se necessário.
    if(ui->frameDesenho) {
        ui->frameDesenho->setFocusPolicy(Qt::StrongFocus);
    }

    // 4. A habilitação da aba de transformações será gerenciada pelo método
    //    updateTransformationTargetUIState(), que é chamado quando um objeto ou câmera é selecionado.
}

/**
 * @brief Mostra ou esconde os campos de entrada de coordenadas com base na forma 3D selecionada.
 */
void MainWindow::gerenciarVisibilidadeSpinners(const QString& tipoForma) {
    // Inicializa todos os flags de visibilidade como falsos
    bool mostrarPonto1 = false, mostrarPonto2 = false, mostrarPonto3 = false;
    bool mostrarRaio = false, mostrarTamanho = false, mostrarNormal = false;

    // Define quais controles são necessários para cada forma
    if (tipoForma == "Ponto") {
        mostrarPonto1 = true;
    } else if (tipoForma == "Reta") {
        mostrarPonto1 = true;
        mostrarPonto2 = true;
    } else if (tipoForma == "Polígono (Triângulo)") {
        mostrarPonto1 = true;
        mostrarPonto2 = true;
        mostrarPonto3 = true;
    } else if (tipoForma == "Circunferência") {
        // Precisa de um centro, um raio e um vetor normal para orientação
        mostrarPonto1 = true;
        mostrarRaio = true;
        mostrarNormal = true;
    } else if (tipoForma == "Cubo") {
        // Precisa de um ponto central e um tamanho de lado
        mostrarPonto1 = true;
        mostrarTamanho = true;
    }

    // --- Atualiza a visibilidade dos controles da UI ---

    // Ponto 1 (Centro para Circunferência/Cubo)
    ui->lblCoordenadaX1->setVisible(mostrarPonto1); ui->spinX1->setVisible(mostrarPonto1);
    ui->lblCoordenadaY1->setVisible(mostrarPonto1); ui->spinY1->setVisible(mostrarPonto1);
    ui->lblCoordenadaZ1->setVisible(mostrarPonto1); ui->spinZ1->setVisible(mostrarPonto1); // NOVO

    // Ponto 2
    ui->lblCoordenadaX2->setVisible(mostrarPonto2); ui->spinX2->setVisible(mostrarPonto2);
    ui->lblCoordenadaY2->setVisible(mostrarPonto2); ui->spinY2->setVisible(mostrarPonto2);
    ui->lblCoordenadaZ2->setVisible(mostrarPonto2); ui->spinZ2->setVisible(mostrarPonto2); // NOVO

    // Ponto 3
    ui->lblCoordenadaX3->setVisible(mostrarPonto3); ui->spinX3->setVisible(mostrarPonto3);
    ui->lblCoordenadaY3->setVisible(mostrarPonto3); ui->spinY3->setVisible(mostrarPonto3);
    ui->lblCoordenadaZ3->setVisible(mostrarPonto3); ui->spinZ3->setVisible(mostrarPonto3); // NOVO

    // Raio (para Circunferência)
    ui->lblRaio->setVisible(mostrarRaio);
    ui->spinRaio->setVisible(mostrarRaio);

    // Tamanho (para Cubo) - Reutilizando os controles de Raio
    ui->lblTamanho->setVisible(mostrarTamanho); // Supondo um novo QLabel "Tamanho"
    ui->spinTamanho->setVisible(mostrarTamanho); // Supondo um novo QDoubleSpinBox "spinTamanho"

    // Vetor Normal (para Circunferência)
    ui->groupBoxNormal->setVisible(mostrarNormal); // Supondo que os spins Nx, Ny, Nz estão em um GroupBox
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

/**
 * @brief Atualiza a ComboBox de câmeras com os dados do DisplayFile.
 * Este método foi atualizado para usar a classe Camera em vez de JanelaMundo.
 */
void MainWindow::atualizarCbDFCamera() {
    // 1. Salva o nome da câmera atualmente ativa para tentar re-selecioná-la depois.
    QString nomeCameraAtivaAnteriormente;
    if (displayFile && displayFile->obterCameraAtiva()) {
        nomeCameraAtivaAnteriormente = displayFile->obterCameraAtiva()->obterNome();
    }

    // 2. Limpa a ComboBox antes de repopular.
    ui->cbDFCameras->clear();

    // 3. Itera sobre a nova lista de Câmeras e as adiciona à ComboBox.
    if (displayFile) {
        // Utiliza os novos métodos e classes do pipeline 3D.
        for (const auto& cam : displayFile->obterListaCameras()) {
            if (cam) {
                ui->cbDFCameras->addItem(cam->obterNome(), QVariant::fromValue(cam->obterNome()));
            }
        }
    }

    // 4. Tenta restaurar a seleção da câmera que estava ativa.
    // A variável 'janelaSelecionada' foi removida e não é mais usada.
    if (!nomeCameraAtivaAnteriormente.isEmpty()) {
        int idx = ui->cbDFCameras->findText(nomeCameraAtivaAnteriormente);
        if (idx != -1) {
            // Nota: Chamar setCurrentIndex aqui irá disparar o slot on_cbDFCamera_currentIndexChanged,
            // que é o comportamento esperado para atualizar o resto da UI.
            ui->cbDFCameras->setCurrentIndex(idx);
        }
    }
}

/**
 * @brief Slot executado quando o usuário seleciona uma câmera diferente na ComboBox.
 * Este método define a câmera ativa para o pipeline de renderização e ajusta
 * o estado da UI para focar na transformação da câmera.
 */
void MainWindow::on_cbDFCamera_currentIndexChanged(int index) {
    if (!displayFile) return; // Checagem de segurança

    if (index < 0) {
        // Nenhuma câmera está selecionada (ex: lista limpa).
        // Ação: Define a câmera ativa como nula. A UI será desabilitada por updateTransformationTargetUIState.
        displayFile->definirCameraAtiva(std::shared_ptr<Camera>());
    } else {
        // Uma câmera foi selecionada pelo usuário.
        QString nomeCamera = ui->cbDFCameras->itemText(index);

        // 1. Busca a câmera correspondente no DisplayFile usando o novo método.
        auto cameraSelecionada = displayFile->buscarCamera(nomeCamera);

        if (cameraSelecionada) {
            // 2. Define a câmera encontrada como a ATIVA no DisplayFile.
            //    O FrameDesenho usará esta câmera na próxima vez que for redesenhado.
            displayFile->definirCameraAtiva(cameraSelecionada);

            // 3. Garante que nenhum objeto esteja selecionado para evitar ambiguidade.
            //    O foco da transformação agora é a câmera.
            if (objetoSelecionado) {
                // Bloqueia os sinais para evitar que a mudança de índice abaixo
                // dispare o slot on_cbDisplayFile_currentIndexChanged.
                ui->cbDisplayFile->blockSignals(true);
                ui->cbDisplayFile->setCurrentIndex(-1); // "Limpa" a seleção na ComboBox de objetos.
                ui->cbDisplayFile->blockSignals(false);

                // Limpa a referência interna ao objeto que estava selecionado.
                objetoSelecionado = nullptr;
            }

            // 4. Manda redesenhar a cena. O método paintEvent do FrameDesenho
            //    automaticamente usará a nova câmera ativa para recalcular tudo.
            if (ui->frameDesenho) {
                ui->frameDesenho->redesenhar();
            }

        } else {
            // Caso de erro: o nome na ComboBox não corresponde a nenhuma câmera.
            qWarning() << "Câmera não encontrada ao processar seleção:" << nomeCamera;
            displayFile->definirCameraAtiva(std::shared_ptr<Camera>());
        }
    }

    // 5. Atualiza o estado da UI (ex: habilita/desabilita a aba de transformações)
    //    com base no novo estado de seleção (agora focado na câmera).
    updateTransformationTargetUIState();
}

/**
 * @brief Slot executado quando o usuário seleciona um objeto na ComboBox.
 * Este método define o objeto ativo para transformação e ajusta a UI para
 * focar na transformação do objeto.
 */
void MainWindow::on_cbDisplayFile_currentIndexChanged(int index) {
    if (index < 0) {
        // Objeto foi "desselecionado" ou a ComboBox foi limpa.
        objetoSelecionado = nullptr;
    } else {
        if (!displayFile) { // Checagem de segurança
            objetoSelecionado = nullptr;
            updateTransformationTargetUIState();
            return;
        }

        QString nomeObjeto = ui->cbDisplayFile->itemText(index);
        auto objSelecionadoTemp = displayFile->buscarObjeto(nomeObjeto);

        if (objSelecionadoTemp) {
            // 1. Define o objeto selecionado como o alvo de transformação.
            objetoSelecionado = objSelecionadoTemp;

            // 2. Garante que a seleção na ComboBox de câmeras seja limpa para
            //    sinalizar que o foco da transformação mudou para o objeto.
            //    A câmera ativa para visualização não muda, apenas o alvo da UI.
            bool oldSignalsBlocked = ui->cbDFCameras->signalsBlocked();
            ui->cbDFCameras->blockSignals(true);
            ui->cbDFCameras->setCurrentIndex(-1);
            ui->cbDFCameras->blockSignals(oldSignalsBlocked);

            // 3. A checagem "if(janelaSelecionada != nullptr)" foi removida
            //    porque a variável 'janelaSelecionada' não existe mais. A lógica
            //    acima que limpa a seleção da ComboBox de câmeras já cumpre a função
            //    de indicar a mudança de foco na UI.

        } else {
            qWarning() << "Objeto não encontrado no cbDisplayFile_currentIndexChanged:" << nomeObjeto;
            objetoSelecionado = nullptr;
        }
    }

    // 4. Atualiza o estado da UI (ex: habilita/desabilita a aba de transformações).
    updateTransformationTargetUIState();
}
/**
 * @brief Slot executado ao clicar no botão "Desenhar". Cria um novo objeto 3D
 * com base nos dados da UI e o adiciona à cena.
 */
void MainWindow::on_btnDesenhar_clicked() {
    // 1. Checagem de pré-requisitos (usa a nova classe Camera)
    if (!displayFile || !displayFile->obterCameraAtiva()) {
        QMessageBox::critical(this, "Erro", "DisplayFile ou Câmera ativa não inicializada.");
        return;
    }

    QString tipoSelecionado = ui->comboFormas->currentText();
    std::shared_ptr<ObjetoGrafico> novaForma = nullptr;

    // REMOVIDO: A lambda local que causava o erro foi removida.
    // auto obterContagemPorTipo = [&](TipoObjeto tipo, int numVerticesEspecifico = 0) { /* ... */ };

    // --- LÓGICA DE CRIAÇÃO 3D ---
    // A principal mudança é ler a coordenada Z e usar os construtores 3D.

    if (tipoSelecionado == "Ponto") {
        Ponto3D p1(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        // CORRIGIDO: Usa o método da classe DisplayFile
        QString nomeFormaBase = QString("Ponto_%1").arg(displayFile->contarObjetosPorTipo(TipoObjeto::PONTO) + 1);
        novaForma = std::make_shared<PontoObj>(nomeFormaBase, p1, corSelecionadaParaDesenho);

    } else if (tipoSelecionado == "Reta") {
        Ponto3D p1(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        Ponto3D p2(ui->spinX2->value(), ui->spinY2->value(), ui->spinZ2->value());
        // CORRIGIDO: Usa o método da classe DisplayFile
        QString nomeFormaBase = QString("Reta_%1").arg(displayFile->contarObjetosPorTipo(TipoObjeto::RETA) + 1);
        novaForma = std::make_shared<RetaObj>(nomeFormaBase, p1, p2, corSelecionadaParaDesenho);

    } else if (tipoSelecionado == "Polígono (Triângulo)") {
        Ponto3D p1(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        Ponto3D p2(ui->spinX2->value(), ui->spinY2->value(), ui->spinZ2->value());
        Ponto3D p3(ui->spinX3->value(), ui->spinY3->value(), ui->spinZ3->value());
        // CORRIGIDO: Usa o método da classe DisplayFile, especificando 3 vértices
        QString nomeFormaBase = QString("Triangulo_%1").arg(displayFile->contarObjetosPorTipo(TipoObjeto::POLIGONO, 3) + 1);
        QList<Ponto3D> vertices = {p1, p2, p3};
        novaForma = std::make_shared<PoligonoObj>(nomeFormaBase, vertices, corSelecionadaParaDesenho);

    } else if (tipoSelecionado == "Circunferência") {
        if (ui->spinRaio->value() <= 0) { QMessageBox::warning(this, "Entrada Inválida", "O raio deve ser positivo."); return; }
        Ponto3D centro(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        double raio = ui->spinRaio->value();
        Ponto3D normal(ui->spinNx->value(), ui->spinNy->value(), ui->spinNz->value());
        if (normal.magnitude() == 0.0) {
            QMessageBox::warning(this, "Entrada Inválida", "O vetor normal não pode ser (0,0,0). Usando (0,0,1) como padrão.");
            normal.definirZ(1.0);
        }
        // CORRIGIDO: Usa o método da classe DisplayFile
        QString nomeFormaBase = QString("Circulo_%1").arg(displayFile->contarObjetosPorTipo(TipoObjeto::CIRCUNFERENCIA) + 1);
        novaForma = std::make_shared<CircunferenciaObj>(nomeFormaBase, centro, raio, normal, corSelecionadaParaDesenho);

    } else if (tipoSelecionado == "Cubo") {
        if (ui->spinTamanho->value() <= 0) { QMessageBox::warning(this, "Entrada Inválida", "O tamanho deve ser positivo."); return; }
        Ponto3D centro(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        double tam = ui->spinTamanho->value() / 2.0;

        Ponto3D v0(centro.obterX()-tam, centro.obterY()-tam, centro.obterZ()-tam);
        Ponto3D v1(centro.obterX()+tam, centro.obterY()-tam, centro.obterZ()-tam);
        Ponto3D v2(centro.obterX()+tam, centro.obterY()+tam, centro.obterZ()-tam);
        Ponto3D v3(centro.obterX()-tam, centro.obterY()+tam, centro.obterZ()-tam);
        Ponto3D v4(centro.obterX()-tam, centro.obterY()-tam, centro.obterZ()+tam);
        Ponto3D v5(centro.obterX()+tam, centro.obterY()-tam, centro.obterZ()+tam);
        Ponto3D v6(centro.obterX()+tam, centro.obterY()+tam, centro.obterZ()+tam);
        Ponto3D v7(centro.obterX()-tam, centro.obterY()+tam, centro.obterZ()+tam);

        displayFile->adicionarObjeto(std::make_shared<PoligonoObj>("Cubo-Frente", QList<Ponto3D>{v0,v1,v2,v3}, corSelecionadaParaDesenho));
        displayFile->adicionarObjeto(std::make_shared<PoligonoObj>("Cubo-Trás", QList<Ponto3D>{v5,v4,v7,v6}, corSelecionadaParaDesenho));
        displayFile->adicionarObjeto(std::make_shared<PoligonoObj>("Cubo-Baixo", QList<Ponto3D>{v1,v0,v4,v5}, corSelecionadaParaDesenho));
        displayFile->adicionarObjeto(std::make_shared<PoligonoObj>("Cubo-Cima", QList<Ponto3D>{v3,v2,v6,v7}, corSelecionadaParaDesenho));
        displayFile->adicionarObjeto(std::make_shared<PoligonoObj>("Cubo-Esquerda", QList<Ponto3D>{v0,v3,v7,v4}, corSelecionadaParaDesenho));
        displayFile->adicionarObjeto(std::make_shared<PoligonoObj>("Cubo-Direita", QList<Ponto3D>{v2,v1,v5,v6}, corSelecionadaParaDesenho));

        atualizarCbDisplayFile();
        ui->frameDesenho->redesenhar();
        return;
    }

    // --- LÓGICA DE FINALIZAÇÃO (para objetos únicos) ---
    if (novaForma) {
        QString nomeFinal = gerarNomeFormatadoParaObjeto(novaForma->obterNome(), novaForma, corSelecionadaParaDesenho);
        novaForma->definirNome(nomeFinal);
        displayFile->adicionarObjeto(novaForma);

        atualizarCbDisplayFile();
        ui->cbDisplayFile->setCurrentIndex(ui->cbDisplayFile->findText(nomeFinal));
        if (ui->frameDesenho) ui->frameDesenho->redesenhar();

    } else {
        if (!tipoSelecionado.isEmpty()) {
            QMessageBox::critical(this, "Erro Interno", "Não foi possível criar a forma selecionada.");
        }
    }
}
/**
 * @brief Converte um TipoObjeto em uma string amigável para a UI.
 * Atualizado para incluir o tipo CUBO.
 */
QString MainWindow::tipoObjetoParaStringUI(TipoObjeto tipo, int numPontos) {
    switch (tipo) {
    case TipoObjeto::PONTO: return "Ponto";
    case TipoObjeto::RETA: return "Reta";
    case TipoObjeto::POLIGONO:
        if (numPontos == 3) return "Polígono (Triângulo)";
        if (numPontos == 4) return "Polígono (Quadrado)";
        return "Polígono";
    case TipoObjeto::CIRCUNFERENCIA: return "Circunferência";
    case TipoObjeto::CUBO: return "Cubo"; // NOVO
    default: return "Desconhecido";
    }
}
#include <QMessageBox> // Adicione no topo do seu mainwindow.cpp

/**
 * @brief Atualiza a geometria e cor de um objeto com os dados atuais da UI.
 * Método atualizado para lidar com as coordenadas 3D e propriedades de objetos 3D.
 */
void MainWindow::atualizarObjetoComDadosDaUI(std::shared_ptr<ObjetoGrafico>& objeto) {
    if (!objeto) return;

    TipoObjeto tipo = objeto->obterTipo();

    // 1. Atualiza a geometria do objeto com base no tipo.
    if (tipo == TipoObjeto::PONTO) {
        Ponto3D p(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        objeto->definirPontosOriginaisMundo({p});

    } else if (tipo == TipoObjeto::RETA) {
        Ponto3D p1(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        Ponto3D p2(ui->spinX2->value(), ui->spinY2->value(), ui->spinZ2->value());
        objeto->definirPontosOriginaisMundo({p1, p2});

    } else if (tipo == TipoObjeto::POLIGONO) {
        QList<Ponto3D> novosPontos;
        // Lê os pontos da UI para criar um novo polígono 3D.
        Ponto3D p1(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        Ponto3D p2(ui->spinX2->value(), ui->spinY2->value(), ui->spinZ2->value());
        Ponto3D p3(ui->spinX3->value(), ui->spinY3->value(), ui->spinZ3->value());

        // A lógica para polígonos pode ser complexa. Aqui, simplesmente
        // atualizamos os vértices que a UI permite editar.
        if (objeto->obterPontosOriginaisMundo().size() == 3) { // Triângulo
            novosPontos << p1 << p2 << p3;
        } else { // Outros polígonos (a UI só edita os 3 primeiros vértices)
            novosPontos = objeto->obterPontosOriginaisMundo();
            if(novosPontos.size() >= 1) novosPontos[0] = p1;
            if(novosPontos.size() >= 2) novosPontos[1] = p2;
            if(novosPontos.size() >= 3) novosPontos[2] = p3;
        }
        objeto->definirPontosOriginaisMundo(novosPontos);

    } else if (tipo == TipoObjeto::CIRCUNFERENCIA) {
        auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(objeto);
        if (circulo) {
            Ponto3D novoCentro(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
            double novoRaio = ui->spinRaio->value();
            // Lê o novo vetor normal da UI.
            Ponto3D novaNormal(ui->spinNx->value(), ui->spinNy->value(), ui->spinNz->value());

            if (novoRaio <= 0 || novaNormal.magnitude() == 0.0) {
                QMessageBox::warning(this, "Entrada Inválida", "Raio deve ser positivo e vetor normal não pode ser nulo.");
                return;
            }
            // Atualiza todas as propriedades da circunferência.
            // Os setters internos chamarão a regeneração dos pontos.
            circulo->definirCentroOriginal(novoCentro);
            circulo->definirRaioOriginal(novoRaio);
            circulo->definirNormal(novaNormal);
        }
    } else if (tipo == TipoObjeto::CUBO) {
        // Modificar um objeto composto como o Cubo (que são 6 polígonos)
        // a partir da edição de um único objeto (uma de suas faces) é complexo.
        // A abordagem correta envolveria uma classe CuboObj dedicada.
        // Por simplicidade, informamos ao usuário que esta operação não é suportada.
        QMessageBox::information(this, "Operação Não Suportada",
                                 "A modificação de objetos compostos como o Cubo não é suportada nesta versão.\n"
                                 "Por favor, exclua e recrie o objeto com os novos parâmetros.");
        return; // Não prossegue com a modificação.
    }

    // 2. Atualiza a cor do objeto.
    objeto->definirCor(corSelecionadaParaDesenho);

    // 3. Atualiza o nome do objeto na ComboBox (pois a cor pode ter mudado).
    // O nome é atualizado para refletir a nova cor.
    QString nomeAntigo = objeto->obterNome();
    QString nomeBase = nomeAntigo.split(" (").first(); // Pega a parte base do nome
    QString nomeFinal = gerarNomeFormatadoParaObjeto(nomeBase, objeto, corSelecionadaParaDesenho);
    objeto->definirNome(nomeFinal);

    // Atualiza a lista na UI para mostrar o novo nome/cor.
    atualizarCbDisplayFile();
}

/**
 * @brief Slot executado ao clicar em "Modificar Forma". Aplica as mudanças
 * da UI ao objeto selecionado.
 */
void MainWindow::on_btnModificarForma_clicked() {
    // 1. Checagem de pré-requisitos (usando a nova classe Camera)
    if (!objetoSelecionado || !displayFile || !displayFile->obterCameraAtiva()) {
        QMessageBox::warning(this, "Modificar Forma", "Nenhuma forma selecionada ou sistema não inicializado.");
        return;
    }

    // Preserva o nome base do objeto para manter a identidade após a modificação da cor.
    QString nomeCompletoAtual = objetoSelecionado->obterNome();
    QString nomeBase = nomeCompletoAtual.section(" => ", 0, 0).trimmed();
    if (nomeBase.isEmpty()) {
        nomeBase = nomeCompletoAtual;
    }

    // 2. Atualiza as propriedades do objeto (geometria e cor) com os dados da UI.
    //    Esta chamada já foi atualizada para 3D em um passo anterior.
    atualizarObjetoComDadosDaUI(objetoSelecionado);

    // 3. A chamada para recalcular pontos foi REMOVIDA.
    //    objetoSelecionado->recalcularPontosTransformados(...); // <-- Linha obsoleta e removida.
    //    O recálculo agora é feito automaticamente pelo FrameDesenho antes de desenhar.

    // 4. Gera um novo nome formatado (caso a cor tenha mudado) e atualiza o objeto.
    QString nomeNovoFormatado = gerarNomeFormatadoParaObjeto(nomeBase, objetoSelecionado, corSelecionadaParaDesenho);
    objetoSelecionado->definirNome(nomeNovoFormatado);

    // 5. Atualiza a ComboBox e re-seleciona o item modificado.
    atualizarCbDisplayFile();
    int novoIndiceParaSelecionar = ui->cbDisplayFile->findText(nomeNovoFormatado);
    if (novoIndiceParaSelecionar != -1) {
        ui->cbDisplayFile->setCurrentIndex(novoIndiceParaSelecionar);
    }

    // 6. Redesenha a cena para mostrar as modificações.
    if (ui->frameDesenho) {
        ui->frameDesenho->redesenhar();
    }
}

/**
 * @brief Slot executado ao clicar em "Excluir Forma". Remove o objeto
 * selecionado da cena. Este método não precisou de alterações para o 3D.
 */
void MainWindow::on_btnExcluirForma_clicked() {
    if (!objetoSelecionado) {
        QMessageBox::information(this, "Excluir Forma", "Nenhuma forma selecionada para excluir.");
        return;
    }
    if (displayFile) {
        displayFile->removerObjeto(objetoSelecionado->obterNome());

        // Limpa e atualiza a UI, o que anula o objetoSelecionado via slots
        atualizarCbDisplayFile();
        ui->cbDisplayFile->setCurrentIndex(-1);

        if (ui->frameDesenho) ui->frameDesenho->redesenhar();
    }
}

// Slots para Transformações
/**
 * @brief Aplica a translação 3D com base nos valores dos spin boxes.
 */
void MainWindow::aplicarTranslacaoAtual() {
    // Se a aba de transformações não estiver ativa, não faz nada.
    if (!ui->tabWidget->isEnabled()) return;

    // 1. Lê os deslocamentos dos 3 eixos da UI.
    double dx = ui->spinTranslacaoX->value();
    double dy = ui->spinTranslacaoY->value();
    double dz = ui->spinTranslacaoZ->value(); // NOVO

    // 2. Determina o alvo e aplica a transformação.
    // (Assumindo que você tem radio buttons na UI para escolher o alvo)
    if (ui->rbTransformarObjeto->isChecked() && objetoSelecionado) {
        // --- Transformar OBJETO SELECIONADO ---
        Matriz T = TransformadorGeometrico::translacao(dx, dy, dz);
        objetoSelecionado->aplicarTransformacao(T);

    } else { // Transforma a câmera por padrão ou se selecionado
        // --- Transformar CÂMERA ATIVA ---
        auto camera = displayFile->obterCameraAtiva();
        if (camera) {
            // A translação da câmera (pan/dolly) é mais complexa e
            // geralmente feita em relação à sua orientação.
            // Para simplicidade, vamos mover a câmera e seu alvo juntos no espaço do mundo.
            Ponto3D posAtual = camera->obterPosicao();
            Ponto3D alvoAtual = camera->obterAlvo();

            camera->definirPosicao(Ponto3D(posAtual.obterX() + dx, posAtual.obterY() + dy, posAtual.obterZ() + dz));
            camera->definirAlvo(Ponto3D(alvoAtual.obterX() + dx, alvoAtual.obterY() + dy, alvoAtual.obterZ() + dz));
        }
    }

    // 3. Redesenha a cena para refletir a mudança.
    ui->frameDesenho->redesenhar();

    // 4. Reseta os valores dos spin boxes para permitir transformações incrementais.
    ui->spinTranslacaoX->setValue(0);
    ui->spinTranslacaoY->setValue(0);
    ui->spinTranslacaoZ->setValue(0);
}

void MainWindow::on_spinTranslacaoX_valueChanged(double /*arg1*/) {
    aplicarTranslacaoAtual();
}

void MainWindow::on_spinTranslacaoY_valueChanged(double /*arg1*/) {
    aplicarTranslacaoAtual();
}

// Novo
void MainWindow::on_spinTranslacaoZ_valueChanged(double /*arg1*/) {
    aplicarTranslacaoAtual();
}

/**
 * @brief Aplica a escala 3D com base nos valores dos spin boxes.
 */
void MainWindow::aplicarEscalaAtual() {
    if (!ui->tabWidget->isEnabled()) return;

    // 1. Lê os fatores de escala dos 3 eixos.
    double valX = ui->spinEscalaX->value();
    double valY = ui->spinEscalaY->value();
    double valZ = ui->spinEscalaZ->value(); // NOVO

    if (ui->rbTransformarObjeto->isChecked() && objetoSelecionado) {
        // --- Escalar OBJETO SELECIONADO ---
        // Converte o valor do slider/spinbox para um fator de escala.
        double sx = 1.0 + (valX / 20.0); sx = std::max(0.1, sx);
        double sy = 1.0 + (valY / 20.0); sy = std::max(0.1, sy);
        double sz = 1.0 + (valZ / 20.0); sz = std::max(0.1, sz); // NOVO

        Ponto3D centro = objetoSelecionado->calcularCentroGeometrico();
        Matriz S = TransformadorGeometrico::escala(sx, sy, sz, centro);
        objetoSelecionado->aplicarTransformacao(S);

    } else {
        // --- Escalar (Zoom/Dolly) CÂMERA ATIVA ---
        auto camera = displayFile->obterCameraAtiva();
        if (camera) {
            // Usamos o eixo Z para "dolly" (mover para frente/trás)
            // que é a forma mais comum de zoom com câmera 3D.
            Ponto3D pos = camera->obterPosicao();
            Ponto3D alvo = camera->obterAlvo();
            Ponto3D vetorDirecao = (alvo - pos).normalizarVetor();

            // Move a posição da câmera ao longo de seu vetor de direção
            double fatorDolly = valZ * 5.0; // Ajuste a sensibilidade conforme necessário
            camera->definirPosicao(pos + (vetorDirecao * fatorDolly));
        }
    }

    // 2. Redesenha a cena.
    ui->frameDesenho->redesenhar();
}

void MainWindow::on_spinEscalaX_valueChanged(double /*value*/) {
    aplicarEscalaAtual();
}

void MainWindow::on_spinEscalaY_valueChanged(double /*value*/) {
    aplicarEscalaAtual();
}

// NOVO
void MainWindow::on_spinEscalaZ_valueChanged(double /*value*/) {
    aplicarEscalaAtual();
}

/**
 * @brief Aplica a rotação 3D com base nos valores dos sliders.
 */
void MainWindow::aplicarRotacaoAtual() {
    if (!ui->tabWidget->isEnabled()) return;

    // 1. Lê os ângulos de rotação dos 3 eixos.
    double anguloX = ui->hsRotacaoX->value();
    double anguloY = ui->hsRotacaoY->value();
    double anguloZ = ui->hsRotacaoZ->value();

    if (ui->rbTransformarObjeto->isChecked() && objetoSelecionado) {
        // --- Rotacionar OBJETO SELECIONADO ---
        Ponto3D pivo = objetoSelecionado->calcularCentroGeometrico();

        // Cria uma matriz de transformação para cada eixo e as combina.
        // A ordem de multiplicação importa (Z-Y-X é uma ordem comum).
        Matriz Rx = TransformadorGeometrico::rotacaoX(anguloX, pivo);
        Matriz Ry = TransformadorGeometrico::rotacaoY(anguloY, pivo);
        Matriz Rz = TransformadorGeometrico::rotacaoZ(anguloZ, pivo);
        Matriz R_total = Rz * Ry * Rx; // Combina as rotações

        objetoSelecionado->aplicarTransformacao(R_total);

    } else {
        // --- Rotacionar (Orbitar) CÂMERA ATIVA ---
        auto camera = displayFile->obterCameraAtiva();
        if (camera) {
            // A rotação da câmera (órbita) move sua posição ao redor do alvo.
            Ponto3D alvo = camera->obterAlvo();
            Ponto3D pos_velha = camera->obterPosicao();

            // 1. Move a câmera para a origem (transladando o alvo junto).
            Ponto3D vetor_cam_alvo = pos_velha - alvo;

            // 2. Aplica as rotações no vetor que aponta do alvo para a câmera.
            //    A rotação em Y (yaw) acontece ao redor do eixo Y do mundo.
            //    A rotação em X (pitch) acontece ao redor do eixo X local da câmera.
            Matriz rotY = Matriz::rotacaoY(anguloY); // Yaw
            Ponto3D vetor_rotacionado = Ponto3D(rotY * vetor_cam_alvo);

            Ponto3D eixoXLocal = Ponto3D::produtoVetorial(camera->obterVetorUp(), (alvo - pos_velha).normalizarVetor() * -1.0);
            Matriz rotX = Matriz::rotacaoEixoArbitrario(eixoXLocal, anguloX);
            // Por simplicidade aqui, faremos a rotação pitch ao redor do eixo X do mundo.
            // rotX = Matriz::rotacaoX(anguloX);
            // vetor_rotacionado = Ponto3D(rotX * vetor_rotacionado);

            // 3. Move a câmera de volta, agora na nova posição orbital.
            Ponto3D pos_nova = alvo + vetor_rotacionado;
            camera->definirPosicao(pos_nova);
        }
    }

    // 2. Redesenha a cena.
    ui->frameDesenho->redesenhar();

    // 3. Reseta sliders para transformações incrementais
    ui->hsRotacaoX->setValue(0);
    ui->hsRotacaoY->setValue(0);
    ui->hsRotacaoZ->setValue(0);
}

void MainWindow::on_hsRotacaoX_valueChanged(int /*value*/) {
    aplicarRotacaoAtual();
}

void MainWindow::on_hsRotacaoY_valueChanged(int /*value*/) {
    aplicarRotacaoAtual();
}

void MainWindow::on_hsRotacaoZ_valueChanged(int /*value*/) {
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

/**
 * @brief Gera uma string descritiva para um objeto, incluindo suas propriedades 3D e cor.
 * Usado para popular a ComboBox de objetos na UI.
 */
QString MainWindow::gerarNomeFormatadoParaObjeto(const QString& nomeBase,
                                                 std::shared_ptr<ObjetoGrafico> objeto,
                                                 const QColor& cor) {
    if (!objeto) {
        return nomeBase;
    }

    QString coordenadasStr = "Geometria Indisponível"; // Valor padrão
    QString corStr = cor.name(QColor::HexRgb); // Formato #RRGGBB

    TipoObjeto tipo = objeto->obterTipo();
    // Obtém a lista de pontos 3D
    const QList<Ponto3D>& pontosOriginais = objeto->obterPontosOriginaisMundo();

    // --- LÓGICA DE FORMATAÇÃO ATUALIZADA PARA 3D ---

    if (tipo == TipoObjeto::PONTO) {
        if (!pontosOriginais.isEmpty()) {
            const Ponto3D& p = pontosOriginais.first();
            // Formata com 3 coordenadas (x, y, z)
            coordenadasStr = QString("(%1, %2, %3)").arg(p.obterX(), 0, 'f', 1)
                                 .arg(p.obterY(), 0, 'f', 1)
                                 .arg(p.obterZ(), 0, 'f', 1);
        }
    } else if (tipo == TipoObjeto::RETA) {
        if (pontosOriginais.size() >= 2) {
            const Ponto3D& p1 = pontosOriginais[0];
            const Ponto3D& p2 = pontosOriginais[1];
            coordenadasStr = QString("(%1,%2,%3) a (%4,%5,%6)")
                                 .arg(p1.obterX(), 0, 'f', 1).arg(p1.obterY(), 0, 'f', 1).arg(p1.obterZ(), 0, 'f', 1)
                                 .arg(p2.obterX(), 0, 'f', 1).arg(p2.obterY(), 0, 'f', 1).arg(p2.obterZ(), 0, 'f', 1);
        }
    } else if (tipo == TipoObjeto::POLIGONO) {
        // Caso especial para as faces do cubo para não poluir a UI
        if (nomeBase.startsWith("Cubo-")) {
            coordenadasStr = QString("Face de Cubo (%1 vértices)").arg(pontosOriginais.size());
        } else if (!pontosOriginais.isEmpty()) {
            coordenadasStr = QStringLiteral("%1 Vértices: ").arg(pontosOriginais.size());
            // Exibe os 2 primeiros pontos para economizar espaço
            for(int i = 0; i < qMin(pontosOriginais.size(), 2); ++i) {
                const auto& p = pontosOriginais[i];
                coordenadasStr += QString("(%1,%2,%3) ").arg(p.obterX(), 0, 'f', 1)
                                      .arg(p.obterY(), 0, 'f', 1)
                                      .arg(p.obterZ(), 0, 'f', 1);
            }
            if(pontosOriginais.size() > 2) coordenadasStr += "...";
        }
    } else if (tipo == TipoObjeto::CIRCUNFERENCIA) {
        auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(objeto);
        if (circulo) {
            Ponto3D centro = circulo->obterCentroOriginal();
            double raio = circulo->obterRaioOriginal();
            Ponto3D normal = circulo->obterNormal(); // Obtém a orientação

            // Formata a string para incluir centro 3D, raio e normal.
            coordenadasStr = QString("Centro(%1,%2,%3), Raio(%4), Normal(%5,%6,%7)")
                                 .arg(centro.obterX(), 0, 'f', 1).arg(centro.obterY(), 0, 'f', 1).arg(centro.obterZ(), 0, 'f', 1)
                                 .arg(raio, 0, 'f', 1)
                                 .arg(normal.obterX(), 0, 'f', 1).arg(normal.obterY(), 0, 'f', 1).arg(normal.obterZ(), 0, 'f', 1);
        }
    } else if (tipo == TipoObjeto::CUBO) {
        // Para um objeto Cubo dedicado, poderíamos mostrar centro e tamanho
        coordenadasStr = "Objeto Composto: Cubo";
    }

    // Monta a string final
    return QString("%1 => %2 - %3")
        .arg(nomeBase)
        .arg(coordenadasStr)
        .arg(corStr);
}

/**
 * @brief Atualiza todo o estado da UI (botões, abas, spinners) com base
 * no alvo de transformação atual (objeto selecionado ou câmera).
 */
void MainWindow::updateTransformationTargetUIState() {
    // 1. Determina o que está selecionado
    bool objectIsSelected = (objetoSelecionado != nullptr);
    // O alvo é a câmera se um item na ComboBox de câmeras estiver selecionado.
    bool cameraIsTheTarget = (ui->cbDFCameras->currentIndex() > -1);

    // 2. Define a visibilidade dos botões de CRUD
    ui->btnDesenhar->setVisible(!objectIsSelected);
    ui->btnModificarForma->setVisible(objectIsSelected);
    ui->btnExcluirForma->setVisible(objectIsSelected);

    // 3. Habilita a aba de transformações se um objeto OU a câmera for o alvo.
    ui->tabWidget->setEnabled(objectIsSelected || cameraIsTheTarget);

    if (objectIsSelected) {
        // --- CASO 1: UM OBJETO ESTÁ SELECIONADO ---
        // A UI deve mostrar os dados deste objeto.
        TipoObjeto tipo = objetoSelecionado->obterTipo();
        const QList<Ponto3D>& pontos = objetoSelecionado->obterPontosOriginaisMundo();

        gerenciarVisibilidadeSpinners(tipoObjetoParaStringUI(tipo, pontos.size()));

        // Preenche os valores dos spinners com os dados 3D do objeto
        if (tipo == TipoObjeto::PONTO && !pontos.isEmpty()) {
            ui->spinX1->setValue(pontos[0].obterX());
            ui->spinY1->setValue(pontos[0].obterY());
            ui->spinZ1->setValue(pontos[0].obterZ());
        } else if (tipo == TipoObjeto::RETA && pontos.size() >= 2) {
            ui->spinX1->setValue(pontos[0].obterX()); ui->spinY1->setValue(pontos[0].obterY()); ui->spinZ1->setValue(pontos[0].obterZ());
            ui->spinX2->setValue(pontos[1].obterX()); ui->spinY2->setValue(pontos[1].obterY()); ui->spinZ2->setValue(pontos[1].obterZ());
        } else if (tipo == TipoObjeto::POLIGONO) {
            if (pontos.size() >= 1) { ui->spinX1->setValue(pontos[0].obterX()); ui->spinY1->setValue(pontos[0].obterY()); ui->spinZ1->setValue(pontos[0].obterZ()); }
            if (pontos.size() >= 2) { ui->spinX2->setValue(pontos[1].obterX()); ui->spinY2->setValue(pontos[1].obterY()); ui->spinZ2->setValue(pontos[1].obterZ()); }
            if (pontos.size() >= 3) { ui->spinX3->setValue(pontos[2].obterX()); ui->spinY3->setValue(pontos[2].obterY()); ui->spinZ3->setValue(pontos[2].obterZ()); }
        } else if (tipo == TipoObjeto::CIRCUNFERENCIA) {
            auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(objetoSelecionado);
            if (circulo) {
                Ponto3D centro = circulo->obterCentroOriginal();
                Ponto3D normal = circulo->obterNormal();
                ui->spinX1->setValue(centro.obterX()); ui->spinY1->setValue(centro.obterY()); ui->spinZ1->setValue(centro.obterZ());
                ui->spinRaio->setValue(circulo->obterRaioOriginal());
                ui->spinNx->setValue(normal.obterX()); ui->spinNy->setValue(normal.obterY()); ui->spinNz->setValue(normal.obterZ());
            }
        }
        // Atualiza a cor selecionada para a cor do objeto
        corSelecionadaParaDesenho = objetoSelecionado->obterCor();
        // Atualiza a amostra de cor na UI (assumindo um QLabel chamado lblCorPreview)
        //ui->lblCorPreview->setStyleSheet(QString("background-color: %1").arg(corSelecionadaParaDesenho.name()));

    } else {
        // --- CASO 2: NENHUM OBJETO SELECIONADO (a câmera pode ser o alvo ou não) ---
        // A UI deve mostrar os campos para criar uma NOVA forma.
        gerenciarVisibilidadeSpinners(ui->comboFormas->currentText());

        // Limpa todos os campos de entrada de geometria.
        ui->spinX1->setValue(0); ui->spinY1->setValue(0); ui->spinZ1->setValue(0);
        ui->spinX2->setValue(0); ui->spinY2->setValue(0); ui->spinZ2->setValue(0);
        ui->spinX3->setValue(0); ui->spinY3->setValue(0); ui->spinZ3->setValue(0);
        ui->spinRaio->setValue(50);
        ui->spinTamanho->setValue(100);
        ui->spinNx->setValue(0); ui->spinNy->setValue(0); ui->spinNz->setValue(1); // Padrão: normal Z (plano XY)
    }

    // 5. Reseta os controles de transformação (T,S,R) para 0, pois eles são incrementais.
    ui->spinTranslacaoX->setValue(0); ui->spinTranslacaoY->setValue(0); ui->spinTranslacaoZ->setValue(0);
    ui->spinEscalaX->setValue(0); ui->spinEscalaY->setValue(0); ui->spinEscalaZ->setValue(0);
    ui->hsRotacaoX->setValue(0); ui->hsRotacaoY->setValue(0); ui->hsRotacaoZ->setValue(0);
}

void MainWindow::on_btnLimparSelecao_clicked(){
    ui->cbDisplayFile->setCurrentIndex(-1);
}

void MainWindow::on_btnCarregarOBJ_clicked() {
    QMessageBox::information(this, "Carregar", "Funcionalidade de carregar arquivo ainda não implementada completamente.");
}

