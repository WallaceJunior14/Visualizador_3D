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
enum class TipoObjeto; // Usa enum class para melhor tipagem e segurança

/**
 * @brief Uma janela de diálogo para criar novos objetos gráficos ou editar existentes.
 * @details Esta classe fornece uma interface unificada para o usuário. Ela pode operar em dois modos distintos,
 * determinados pelo construtor que é chamado:
 * 1.  **Modo Criação:** Permite ao usuário definir as propriedades de um novo objeto a ser adicionado à cena.
 * 2.  **Modo Edição:** Preenche a interface com as propriedades de um objeto existente, permitindo a modificação.
 */
class GerenciadorObjetosDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor para operar em **Modo Criação**.
     * @param displayFile Ponteiro para o DisplayFile da cena, usado para gerar nomes únicos para novos objetos.
     * @param parent O widget pai, como de praxe no Qt.
     */
    explicit GerenciadorObjetosDialog(std::shared_ptr<DisplayFile> displayFile, QWidget *parent = nullptr);

    /**
     * @brief Construtor para operar em **Modo Edição**.
     * @param objetoParaEditar Ponteiro para o objeto gráfico que será modificado. Seus dados serão usados para preencher o diálogo.
     * @param parent O widget pai.
     */
    explicit GerenciadorObjetosDialog(std::shared_ptr<ObjetoGrafico> objetoParaEditar, QWidget *parent = nullptr);

    /**
     * @brief Destrutor padrão.
     */
    ~GerenciadorObjetosDialog();

    /**
     * @brief Obtém o objeto que foi criado ou modificado com sucesso pelo diálogo.
     * @return Um std::shared_ptr para o ObjetoGrafico resultante.
     * @note Deve ser chamado pela classe que abriu o diálogo (ex: MainWindow) somente após
     * a execução do diálogo ter retornado `QDialog::Accepted`.
     */
    std::shared_ptr<ObjetoGrafico> obterObjetoResultante() const;

public slots:
    /**
     * @brief Sobrescreve o slot padrão `accept()` do QDialog.
     * @details Este slot é acionado quando o usuário clica no botão "OK". Em vez de fechar o diálogo
     * imediatamente, ele chama a lógica interna (`construirOuAtualizarObjeto`) para validar os dados
     * e criar/atualizar o objeto. O diálogo só é fechado se a operação for bem-sucedida.
     */
    void accept() override;

private slots:
    /**
     * @brief Slot acionado quando o botão de seleção de cor é clicado. Abre um QColorDialog.
     */
    void on_btnCor_clicked();

    /**
     * @brief Slot acionado quando o usuário seleciona um tipo de forma diferente no ComboBox.
     * @param text O texto do item selecionado (ex: "Ponto", "Reta").
     * @note É usado para mostrar ou esconder os campos de input relevantes para cada tipo de forma.
     */
    void on_comboFormas_currentTextChanged(const QString &text);

private:
    // --- Métodos Auxiliares (Helpers) ---

    /**
     * @brief Realiza a configuração inicial da UI, como preencher o ComboBox de formas.
     */
    void setup();

    /**
     * @brief Centraliza a conexão dos sinais dos widgets da UI aos slots correspondentes.
     */
    void conectarSinais();

    /**
     * @brief Preenche os campos de input da UI com os dados de um objeto existente (usado no Modo Edição).
     * @param obj O objeto cujos dados serão exibidos no diálogo.
     */
    void preencherCampos(std::shared_ptr<ObjetoGrafico> obj);

    /**
     * @brief Limpa ou reseta todos os campos de input para seus valores padrão.
     */
    void limparCampos();

    /**
     * @brief Mostra ou esconde grupos de widgets de input com base no tipo de forma selecionada.
     * @param tipoForma O nome da forma selecionada (ex: "Polígono").
     */
    void gerenciarVisibilidadeInputs(const QString &tipoForma);

    /**
     * @brief A lógica principal do diálogo. Lê os valores dos campos, valida-os e cria um
     * novo objeto ou atualiza um existente.
     * @return true se a operação foi bem-sucedida, false caso contrário.
     */
    bool construirOuAtualizarObjeto();

    /**
     * @brief Converte um valor do enum TipoObjeto para sua representação em QString.
     * @param tipo O valor do enum a ser convertido.
     * @return A string correspondente (ex: "Ponto").
     */
    QString tipoObjetoParaString(TipoObjeto tipo);

private:
    Ui::GerenciadorObjetosDialog *ui;                  ///< Ponteiro para a classe da UI gerada pelo Qt Designer.
    std::shared_ptr<DisplayFile> m_displayFile;        ///< Ponteiro para a cena (usado apenas no Modo Criação).
    std::shared_ptr<ObjetoGrafico> m_objetoResultante; ///< Armazena o objeto criado/modificado para ser recuperado pela MainWindow.
    QColor m_corSelecionada;                           ///< Guarda a cor escolhida pelo usuário no QColorDialog.
    bool m_modoEdicao;                                 ///< Flag que indica se o diálogo está em Modo Edição (`true`) ou Criação (`false`).
};

#endif // GERENCIADOROBJETOSDIALOG_H
