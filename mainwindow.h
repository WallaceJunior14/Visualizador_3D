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
    void on_btnDesenhar_clicked();
    void on_btnExcluirForma_clicked();
    void on_btnCarregarOBJ_clicked(); // Placeholder

    // Transformações
    void on_spinTranslacaoX_valueChanged(double arg1);
    void on_spinTranslacaoY_valueChanged(double arg1);
    void on_hsEscalaX_valueChanged(int value);
    void on_hsEscalaY_valueChanged(int value);
    void on_hsRotacaoX_valueChanged(int value); // Interpretação como rotação em Z

    void on_cbDisplayFile_currentIndexChanged(int index);

    // Slots para zoom/pan (opcional)
    // void zoomIn();
    // void zoomOut();
    // void panEsquerda();
    // void panDireita();
    // void panCima();
    // void panBaixo();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<DisplayFile> displayFile;
    std::shared_ptr<ObjetoGrafico> objetoSelecionado;
    QColor corSelecionadaParaDesenho;

    void inicializarUI(); // Inicializa comboboxes, estados iniciais, etc.
    void gerenciarVisibilidadeSpinners(const QString& tipoForma);
    void atualizarCbDisplayFile();

    // Aplicam transformações conforme os valores atuais dos controles
    void aplicarTranslacaoAtual();
    void aplicarEscalaAtual();
    void aplicarRotacaoAtual();
};

#endif // MAINWINDOW_H
