#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>  // Para std::shared_ptr
#include <QColor>

// Forward declarations para evitar inclusão de headers pesados.
// Isso acelera a compilação.
class FrameDesenho;
class DisplayFile;
class ObjetoGrafico;
class Ponto3D; // Assumindo que pode ser necessário em futuras assinaturas de método

// Forward declaration do namespace da UI gerada pelo Qt Designer
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots para seleção de alvos
    void on_cbDisplayFile_currentIndexChanged(int index);
    void on_cbDFCamera_currentIndexChanged(int index);

    // Slots para aplicar transformações (conectados manualmente)
    void aplicarTranslacaoAtual();
    void aplicarEscalaAtual();
    void aplicarRotacaoAtual();

    // Slots para botões da interface
    void on_btnCriarForma_clicked();
    void on_btnCor_clicked();
    void on_btnLimparSelecao_clicked();
    void on_btnCarregarOBJ_clicked();

    // Adicionado com base na lógica de updateTransformationTargetUIState
    // Mesmo que a implementação não estivesse no .cpp, a UI provavelmente os tem.
    void on_btnModificarForma_clicked();
    void on_btnExcluirForma_clicked();

private:
    // --- MÉTODOS DE INICIALIZAÇÃO E GERENCIAMENTO ---
    void inicializarComponentes();
    void conectarSinais();
    void inicializarUI();
    void popularDisplayFileInicial(); // Método para criar a cena inicial

    // --- MÉTODOS DE ATUALIZAÇÃO DA UI ---
    void resetarControlesTransformacao();
    void atualizarCbDisplayFile();
    void atualizarCbDFCamera();
    void updateTransformationTargetUIState();

    // --- MÉTODOS AUXILIARES ---
    QString gerarNomeFormatadoParaObjeto(const QString& nomeBase,
                                         std::shared_ptr<ObjetoGrafico> objeto,
                                         const QColor& cor);

    // --- MEMBROS PRIVADOS ---
    Ui::MainWindow *ui; // Ponteiro para a classe da interface gráfica gerada

    std::shared_ptr<DisplayFile> displayFile;         // Estrutura de dados principal que contém todos os objetos e câmeras
    std::shared_ptr<ObjetoGrafico> objetoSelecionado; // Ponteiro para o objeto atualmente selecionado para transformação

    QColor corSelecionadaParaDesenho = Qt::white;     // Cor padrão para novos desenhos ou para o seletor de cor
};

#endif // MAINWINDOW_H
