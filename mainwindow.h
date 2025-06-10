#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QColor>
#include "frame_desenho.h"

// Forward declarations
namespace Ui { class MainWindow; }
class DisplayFile;
class ObjetoGrafico;
class Camera; // Alterado: de JanelaMundo para Camera

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots de criação/seleção de objetos (assinaturas inalteradas)
    void on_comboFormas_currentIndexChanged(int index);
    void on_btnCor_clicked();
    void on_btnModificarForma_clicked();
    void on_btnDesenhar_clicked();
    void on_btnExcluirForma_clicked();
    void on_btnLimparSelecao_clicked();
    void on_btnCarregarOBJ_clicked();

    // Slots de Transformação (ATUALIZADOS PARA 3D)
    void on_spinTranslacaoX_valueChanged(double arg1);
    void on_spinTranslacaoY_valueChanged(double arg1);
    void on_spinTranslacaoZ_valueChanged(double arg1); // NOVO

    void on_spinEscalaX_valueChanged(double value);
    void on_spinEscalaY_valueChanged(double value);
    void on_spinEscalaZ_valueChanged(double value); // NOVO

    void on_hsRotacaoX_valueChanged(int value); // NOVO: Rotação em torno do eixo X
    void on_hsRotacaoY_valueChanged(int value); // NOVO: Rotação em torno do eixo Y
    void on_hsRotacaoZ_valueChanged(int value); // Antigo hsRotacaoX, agora com nome claro para eixo Z

    // Slots de seleção de objeto e câmera
    void on_cbDisplayFile_currentIndexChanged(int index);
    void on_cbDFCamera_currentIndexChanged(int index);

    void on_btnCriarForma_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<DisplayFile> displayFile;
    QColor corSelecionadaParaDesenho;

    // Alvos de transformação (pode ser um objeto ou a câmera ativa)
    std::shared_ptr<ObjetoGrafico> objetoSelecionado = nullptr;
    // std::shared_ptr<JanelaMundo> janelaSelecionada foi removido
    // A câmera ativa é obtida diretamente do DisplayFile

    // Métodos auxiliares (assinaturas maiormente inalteradas, lógica muda no .cpp)
    void inicializarUI();
    void gerenciarVisibilidadeSpinners(const QString& tipoForma);
    void atualizarCbDisplayFile();
    void atualizarCbDFCamera(); // Lógica interna muda para usar Camera
    void atualizarObjetoComDadosDaUI(std::shared_ptr<ObjetoGrafico>& objeto);
    QString gerarNomeFormatadoParaObjeto(const QString& nomeBase,
                                         std::shared_ptr<ObjetoGrafico> objeto,
                                         const QColor& cor);
    QString tipoObjetoParaStringUI(TipoObjeto tipo, int numPontos = 0);
    void updateTransformationTargetUIState();

    // Métodos de aplicação de transformação (lógica interna muda no .cpp)
    void aplicarTranslacaoAtual();
    void aplicarEscalaAtual();
    void aplicarRotacaoAtual();

    void inicializarObjetosIniciais(DisplayFile* df);
};

#endif // MAINWINDOW_H
