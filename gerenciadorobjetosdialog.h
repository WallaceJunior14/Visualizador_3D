#ifndef GERENCIADOROBJETOSDIALOG_H
#define GERENCIADOROBJETOSDIALOG_H

#include <QDialog>
#include <memory>
#include <QColor>

// Forward declarations para evitar includes desnecessários no .h
namespace Ui {
class GerenciadorObjetosDialog;
}
class DisplayFile;
class ObjetoGrafico;
enum class TipoObjeto; // Usa enum class para melhor tipagem

class GerenciadorObjetosDialog : public QDialog
{
    Q_OBJECT

public:
    // Construtor para MODO CRIAÇÃO: recebe o DisplayFile para gerar nomes únicos.
    explicit GerenciadorObjetosDialog(std::shared_ptr<DisplayFile> displayFile, QWidget *parent = nullptr);

    // Construtor para MODO EDIÇÃO: recebe o objeto a ser editado.
    explicit GerenciadorObjetosDialog(std::shared_ptr<ObjetoGrafico> objetoParaEditar, QWidget *parent = nullptr);

    ~GerenciadorObjetosDialog();

    // Método público para a MainWindow recuperar o resultado da operação.
    std::shared_ptr<ObjetoGrafico> obterObjetoResultante() const;

public slots:
    // Sobrescreve o slot do botão "OK" para adicionar lógica de validação.
    void accept() override;

private slots:
    // Slots para os widgets da UI.
    void on_btnCor_clicked();
    void on_comboFormas_currentTextChanged(const QString &text);

private:
    // --- Métodos Auxiliares (Helpers) ---
    void setup();
    void conectarSinais();
    void preencherCampos(std::shared_ptr<ObjetoGrafico> obj);
    void limparCampos();
    void gerenciarVisibilidadeInputs(const QString &tipoForma);
    bool construirOuAtualizarObjeto();
    QString tipoObjetoParaString(TipoObjeto tipo);

private:
    Ui::GerenciadorObjetosDialog *ui;
    std::shared_ptr<DisplayFile> m_displayFile;
    std::shared_ptr<ObjetoGrafico> m_objetoResultante;
    QColor m_corSelecionada;
    bool m_modoEdicao;
};

#endif // GERENCIADOROBJETOSDIALOG_H
