#include "gerenciadorobjetosdialog.h"
#include "ui_gerenciadorobjetosdialog.h"

// Includes completos para usar as classes
#include "display_file.h"
#include "ponto_obj.h"
#include "reta_obj.h"
#include "poligono_obj.h"
#include "circunferencia_obj.h"
#include "tipos.h"

#include <QColorDialog>
#include <QMessageBox>

// --- Construtores ---

// Construtor para MODO CRIAÇÃO
GerenciadorObjetosDialog::GerenciadorObjetosDialog(std::shared_ptr<DisplayFile> displayFile, QWidget *parent) :
    QDialog(parent), ui(new Ui::GerenciadorObjetosDialog), m_displayFile(displayFile), m_corSelecionada(Qt::black), m_modoEdicao(false)
{
    ui->setupUi(this); setup(); limparCampos();
    ui->btnModificarForma->setVisible(false); ui->btnExcluirForma->setVisible(false);
}

GerenciadorObjetosDialog::GerenciadorObjetosDialog(std::shared_ptr<ObjetoGrafico> objetoParaEditar, QWidget *parent) :
    QDialog(parent), ui(new Ui::GerenciadorObjetosDialog), m_objetoResultante(objetoParaEditar), m_corSelecionada(objetoParaEditar->obterCor()), m_modoEdicao(true)
{
    ui->setupUi(this); setup(); preencherCampos(m_objetoResultante);
    ui->btnDesenhar->setVisible(false); ui->comboFormas->setEnabled(false);
}


GerenciadorObjetosDialog::~GerenciadorObjetosDialog()
{
    delete ui;
}

// --- Configuração Inicial ---

void GerenciadorObjetosDialog::setup() {
    conectarSinais();
    ui->comboFormas->addItem("Ponto");
    ui->comboFormas->addItem("Reta");
    ui->comboFormas->addItem("Polígono");
    ui->comboFormas->addItem("Circunferência");
    ui->comboFormas->addItem("Cubo");
}

void GerenciadorObjetosDialog::conectarSinais() {
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &GerenciadorObjetosDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &GerenciadorObjetosDialog::reject);
    connect(ui->btnCor, &QPushButton::clicked, this, &GerenciadorObjetosDialog::on_btnCor_clicked);
    connect(ui->comboFormas, &QComboBox::currentTextChanged, this, &GerenciadorObjetosDialog::on_comboFormas_currentTextChanged);
    // Os botões Adicionar/Modificar/Excluir do seu .ui não precisam de connect se
    // eles seguirem o padrão de nomenclatura "on_<objectName>_<signalName>()"
    // Mas conectar explicitamente é mais seguro.
    connect(ui->btnDesenhar, &QPushButton::clicked, this, &GerenciadorObjetosDialog::accept);
    connect(ui->btnModificarForma, &QPushButton::clicked, this, &GerenciadorObjetosDialog::accept);
}

// --- Lógica Principal ---

void GerenciadorObjetosDialog::accept()
{
    // Tenta construir ou atualizar o objeto com os dados da UI.
    if (construirOuAtualizarObjeto()) {
        // Se a operação for bem-sucedida, chama o accept() da classe base para fechar o diálogo.
        QDialog::accept();
    }
    // Se falhar (dados inválidos), a função retorna e o diálogo permanece aberto.
}


bool GerenciadorObjetosDialog::construirOuAtualizarObjeto()
{
    const QString tipoStr = ui->comboFormas->currentText();

    // Para o modo de criação, precisamos do DisplayFile para gerar nomes únicos.
    if (!m_modoEdicao && !m_displayFile) {
        QMessageBox::critical(this, "Erro Crítico", "DisplayFile não está disponível para criar um novo objeto.");
        return false;
    }


    if (tipoStr == "Ponto") {
        Ponto3D p(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        if (m_modoEdicao) {
            m_objetoResultante->definirPontosOriginaisMundo({p});
        } else {
            QString nome = QString("Ponto_%1").arg(m_displayFile->contarObjetosPorTipo(TipoObjeto::PONTO) + 1);
            m_objetoResultante = std::make_shared<PontoObj>(nome, p);
        }

    } else if (tipoStr == "Reta") {
        Ponto3D p1(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        Ponto3D p2(ui->spinX2->value(), ui->spinY2->value(), ui->spinZ2->value());
        if (m_modoEdicao) {
            m_objetoResultante->definirPontosOriginaisMundo({p1, p2});
        } else {
            QString nome = QString("Reta_%1").arg(m_displayFile->contarObjetosPorTipo(TipoObjeto::RETA) + 1);
            m_objetoResultante = std::make_shared<RetaObj>(nome, p1, p2);
        }

    } else if (tipoStr == "Polígono") {
        // A UI atual só suporta 3 vértices (triângulo)
        Ponto3D p1(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        Ponto3D p2(ui->spinX2->value(), ui->spinY2->value(), ui->spinZ2->value());
        Ponto3D p3(ui->spinX3->value(), ui->spinY3->value(), ui->spinZ3->value());
        if (m_modoEdicao) {
            // Apenas atualiza polígonos que são triângulos, para consistência com a UI.
            if (m_objetoResultante->obterPontosOriginaisMundo().size() == 3) {
                m_objetoResultante->definirPontosOriginaisMundo({p1, p2, p3});
            } else {
                QMessageBox::information(this, "Aviso", "A UI atual só permite a edição de triângulos.");
                return false;
            }
        } else {
            QString nome = QString("Triangulo_%1").arg(m_displayFile->contarObjetosPorTipo(TipoObjeto::POLIGONO, 3) + 1);
            m_objetoResultante = std::make_shared<PoligonoObj>(nome, QList<Ponto3D>{p1, p2, p3}, m_corSelecionada);
        }

    } else if (tipoStr == "Circunferência") {
        if (ui->spinRaio->value() <= 0) {
            QMessageBox::warning(this, "Entrada Inválida", "O raio da circunferência deve ser um valor positivo.");
            return false;
        }
        Ponto3D centro(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        double raio = ui->spinRaio->value();
        // (A UI não tem campos para a normal, então usamos um padrão ou mantemos a original)
        if (m_modoEdicao) {
            auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(m_objetoResultante);
            if(circulo) {
                circulo->definirCentroOriginal(centro);
                circulo->definirRaioOriginal(raio);
            }
        } else {
            QString nome = QString("Circulo_%1").arg(m_displayFile->contarObjetosPorTipo(TipoObjeto::CIRCUNFERENCIA) + 1);
            m_objetoResultante = std::make_shared<CircunferenciaObj>(nome, centro, raio, Ponto3D(0,0,1), m_corSelecionada);
        }

    } else if (tipoStr == "Cubo") {
        // O cubo é um caso especial, pois é composto por múltiplos objetos.
        // A modificação dele é complexa e foi desabilitada. Apenas a criação é implementada.
        if (m_modoEdicao) {
            QMessageBox::information(this, "Operação Não Suportada", "A modificação de um Cubo não é permitida. Por favor, exclua e crie um novo.");
            return false;
        }
        if (ui->spinTamanho->value() <= 0) {
            QMessageBox::warning(this, "Entrada Inválida", "O tamanho do cubo deve ser um valor positivo.");
            return false;
        }
        Ponto3D centro(ui->spinX1->value(), ui->spinY1->value(), ui->spinZ1->value());
        double tam = ui->spinTamanho->value() / 2.0;
        int N = (m_displayFile->contarObjetosPorTipo(TipoObjeto::POLIGONO) / 6) + 1; // Aproxima um ID de cubo

        Ponto3D v[8];
        v[0] = centro + Ponto3D(-tam, -tam, -tam); v[1] = centro + Ponto3D( tam, -tam, -tam);
        v[2] = centro + Ponto3D( tam,  tam, -tam); v[3] = centro + Ponto3D(-tam,  tam, -tam);
        v[4] = centro + Ponto3D(-tam, -tam,  tam); v[5] = centro + Ponto3D( tam, -tam,  tam);
        v[6] = centro + Ponto3D( tam,  tam,  tam); v[7] = centro + Ponto3D(-tam,  tam,  tam);

        // Como o cubo é composto, não podemos retornar um único objeto.
        // Adicionamos as faces diretamente ao DisplayFile e retornamos sucesso.
        m_displayFile->adicionarObjeto(std::make_shared<PoligonoObj>(QString("Cubo%1-Frente").arg(N), QList<Ponto3D>{v[0], v[1], v[2], v[3]}, m_corSelecionada));
        m_displayFile->adicionarObjeto(std::make_shared<PoligonoObj>(QString("Cubo%1-Tras").arg(N),   QList<Ponto3D>{v[5], v[4], v[7], v[6]}, m_corSelecionada));
        m_displayFile->adicionarObjeto(std::make_shared<PoligonoObj>(QString("Cubo%1-Baixo").arg(N),  QList<Ponto3D>{v[1], v[0], v[4], v[5]}, m_corSelecionada));
        m_displayFile->adicionarObjeto(std::make_shared<PoligonoObj>(QString("Cubo%1-Cima").arg(N),   QList<Ponto3D>{v[3], v[2], v[6], v[7]}, m_corSelecionada));
        m_displayFile->adicionarObjeto(std::make_shared<PoligonoObj>(QString("Cubo%1-Esq").arg(N),    QList<Ponto3D>{v[0], v[3], v[7], v[4]}, m_corSelecionada));
        m_displayFile->adicionarObjeto(std::make_shared<PoligonoObj>(QString("Cubo%1-Dir").arg(N),    QList<Ponto3D>{v[2], v[1], v[5], v[6]}, m_corSelecionada));

        // Define o ponteiro de resultado como nulo, pois não há um único objeto a ser retornado.
        m_objetoResultante = nullptr;
        return true; // Sucesso na criação do cubo.
    } else {
        QMessageBox::warning(this, "Erro", "Tipo de forma desconhecido.");
        return false;
    }

    if (!m_objetoResultante) {
        QMessageBox::critical(this, "Erro Crítico", "Falha ao criar ou encontrar o objeto para modificação.");
        return false;
    }

    // Aplica a cor selecionada ao objeto resultante
    m_objetoResultante->definirCor(m_corSelecionada);
    return true; // Sucesso na operação
}

std::shared_ptr<ObjetoGrafico> GerenciadorObjetosDialog::obterObjetoResultante() const
{
    return m_objetoResultante;
}

// --- Implementação dos Slots e Helpers ---

void GerenciadorObjetosDialog::on_btnCor_clicked()
{
    QColor cor = QColorDialog::getColor(m_corSelecionada, this, "Selecionar Cor");
    if (cor.isValid()) {
        m_corSelecionada = cor;
        // Aqui você pode atualizar uma amostra de cor na UI, se tiver uma.
    }
}

void GerenciadorObjetosDialog::on_comboFormas_currentTextChanged(const QString &text)
{
    gerenciarVisibilidadeInputs(text);
}

void GerenciadorObjetosDialog::limparCampos()
{
    ui->spinX1->setValue(0.0); ui->spinY1->setValue(0.0); ui->spinZ1->setValue(0.0);
    ui->spinX2->setValue(0.0); ui->spinY2->setValue(0.0); ui->spinZ2->setValue(0.0);
    ui->spinX3->setValue(0.0); ui->spinY3->setValue(0.0); ui->spinZ3->setValue(0.0);
    ui->spinRaio->setValue(50.0);
    ui->spinTamanho->setValue(100.0);
    m_corSelecionada = Qt::black;
    on_comboFormas_currentTextChanged(ui->comboFormas->currentText());
}

void GerenciadorObjetosDialog::preencherCampos(std::shared_ptr<ObjetoGrafico> obj)
{
    if (!obj) {
        limparCampos();
        return;
    }
    limparCampos(); // Limpa primeiro para garantir um estado consistente

    ui->comboFormas->setCurrentText(tipoObjetoParaString(obj->obterTipo()));
    m_corSelecionada = obj->obterCor();

    const auto& pontos = obj->obterPontosOriginaisMundo();
    if(pontos.size() >= 1) { ui->spinX1->setValue(pontos[0].obterX()); ui->spinY1->setValue(pontos[0].obterY()); ui->spinZ1->setValue(pontos[0].obterZ()); }
    if(pontos.size() >= 2) { ui->spinX2->setValue(pontos[1].obterX()); ui->spinY2->setValue(pontos[1].obterY()); ui->spinZ2->setValue(pontos[1].obterZ()); }
    if(pontos.size() >= 3) { ui->spinX3->setValue(pontos[2].obterX()); ui->spinY3->setValue(pontos[2].obterY()); ui->spinZ3->setValue(pontos[2].obterZ()); }

    if (obj->obterTipo() == TipoObjeto::CIRCUNFERENCIA) {
        auto circulo = std::dynamic_pointer_cast<CircunferenciaObj>(obj);
        if (circulo) ui->spinRaio->setValue(circulo->obterRaioOriginal());
    }
}

void GerenciadorObjetosDialog::gerenciarVisibilidadeInputs(const QString &tipoForma)
{
    // Lógica para mostrar/esconder os campos de entrada (igual à da sua MainWindow)
    bool p2 = (tipoForma == "Reta" || tipoForma == "Polígono");
    bool p3 = (tipoForma == "Polígono");
    bool raio = (tipoForma == "Circunferência");
    bool tamanho = (tipoForma == "Cubo");

    ui->lblCoordenadaX2->setVisible(p2); ui->spinX2->setVisible(p2);
    ui->lblCoordenadaY2->setVisible(p2); ui->spinY2->setVisible(p2);
    ui->lblCoordenadaZ2->setVisible(p2); ui->spinZ2->setVisible(p2);

    ui->lblCoordenadaX3->setVisible(p3); ui->spinX3->setVisible(p3);
    ui->lblCoordenadaY3->setVisible(p3); ui->spinY3->setVisible(p3);
    ui->lblCoordenadaZ3->setVisible(p3); ui->spinZ3->setVisible(p3);

    ui->lblRaio->setVisible(raio); ui->spinRaio->setVisible(raio);
    ui->lblTamanho->setVisible(tamanho); ui->spinTamanho->setVisible(tamanho);
}

QString GerenciadorObjetosDialog::tipoObjetoParaString(TipoObjeto tipo) {
    switch (tipo) {
    case TipoObjeto::PONTO: return "Ponto";
    case TipoObjeto::RETA: return "Reta";
    case TipoObjeto::POLIGONO: return "Polígono";
    case TipoObjeto::CIRCUNFERENCIA: return "Circunferência";
    case TipoObjeto::CUBO: return "Cubo";
    default: return "";
    }
}
