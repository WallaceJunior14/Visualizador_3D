#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QColor>
#include "frame_desenho.h"

namespace Ui { class MainWindow; }
class DisplayFile;
class ObjetoGrafico;
class Ponto2D;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots da interface gráfica
    void on_comboFormas_currentIndexChanged(int index);
    void on_btnCor_clicked();
    void on_btnModificarForma_clicked();
    void on_btnDesenhar_clicked();
    void on_btnExcluirForma_clicked();
    void on_btnLimparSelecao_clicked();
    void on_btnCarregarOBJ_clicked(); // Placeholder

    // Transformações
    void on_spinTranslacaoX_valueChanged(double arg1);
    void on_spinTranslacaoY_valueChanged(double arg1);
    void on_spinEscalaX_valueChanged(double value);
    void on_spinEscalaY_valueChanged(double value);
    void on_hsRotacaoX_valueChanged(int value); // Interpretação como rotação em Z

    void on_cbDisplayFile_currentIndexChanged(int index);

    void on_cbDFCamera_currentIndexChanged(int index);

    // Slots para zoom/pan
    // void zoomIn();
    // void zoomOut();
    // void panEsquerda();
    // void panDireita();
    // void panCima();
    // void panBaixo();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<DisplayFile> displayFile;
    std::shared_ptr<ObjetoGrafico> objetoSelecionado = nullptr;
    std::shared_ptr<JanelaMundo> janelaSelecionada = nullptr;
    QColor corSelecionadaParaDesenho;

    void inicializarUI(); // Inicializa comboboxes, estados iniciais, etc.
    void gerenciarVisibilidadeSpinners(const QString& tipoForma);
    void atualizarCbDisplayFile();
    void atualizarCbDFCamera();
    void atualizarObjetoComDadosDaUI(std::shared_ptr<ObjetoGrafico>& objeto);
    QString gerarNomeFormatadoParaObjeto(const QString& nomeBase,
                                         std::shared_ptr<ObjetoGrafico> objeto,
                                         const QColor& cor);
    QString tipoObjetoParaStringUI(TipoObjeto tipo, int numPontos = 0);
    void updateTransformationTargetUIState();

    // Aplicam transformações conforme os valores atuais dos controles
    void aplicarTranslacaoAtual();
    void aplicarEscalaAtual();
    void aplicarRotacaoAtual();
};

#endif // MAINWINDOW_H
