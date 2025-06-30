#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QColor>

// Forward declarations para evitar inclusão de headers pesados e acelerar a compilação.
class FrameDesenho;
class DisplayFile;
class ObjetoGrafico;
class Ponto3D;

// Forward declaration do namespace da UI gerada pelo Qt Designer.
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief A janela principal da aplicação de visualização e manipulação 3D.
 * @details Esta classe atua como o controlador central da aplicação. Ela gerencia a
 * interface do usuário (UI), orquestra as interações do usuário (como seleção e
 * transformação de objetos), e conecta a lógica de negócios (representada pelo
 * DisplayFile e seus objetos) com os componentes de visualização (FrameDesenho).
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construtor da MainWindow.
     * @param parent O widget pai, como de praxe no Qt.
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Destrutor da MainWindow.
     */
    ~MainWindow();

private slots:
    // --- Slots para seleção de alvos ---
    /**
     * @brief Slot acionado quando o usuário seleciona um objeto diferente no ComboBox de objetos.
     * @param index O novo índice do item selecionado no ComboBox.
     */
    void on_cbDisplayFile_currentIndexChanged(int index);

    /**
     * @brief Slot acionado quando o usuário seleciona uma câmera diferente no ComboBox de câmeras.
     * @param index O novo índice do item selecionado no ComboBox.
     */
    void on_cbDFCamera_currentIndexChanged(int index);

    // --- Slots para aplicar transformações ---
    /**
     * @brief Aplica a transformação de translação com base nos valores atuais dos spin boxes.
     */
    void aplicarTranslacaoAtual();
    /**
     * @brief Aplica a transformação de escala com base nos valores atuais dos spin boxes.
     */
    void aplicarEscalaAtual();
    /**
     * @brief Aplica a transformação de rotação com base nos valores atuais dos sliders.
     */
    void aplicarRotacaoAtual();

    // --- Slots para botões da interface ---
    /**
     * @brief Abre o diálogo para criar uma nova forma geométrica.
     */
    void on_btnCriarForma_clicked();
    /**
     * @brief Abre um seletor de cores para definir a cor do objeto selecionado.
     */
    void on_btnCor_clicked();
    /**
     * @brief Limpa a seleção atual de objeto no ComboBox.
     */
    void on_btnLimparSelecao_clicked();
    /**
     * @brief Slot para o botão de carregar um arquivo .OBJ (funcionalidade futura).
     */
    void on_btnCarregarOBJ_clicked();
    /**
     * @brief Abre o diálogo para modificar o objeto atualmente selecionado.
     */
    void on_btnModificarForma_clicked();
    /**
     * @brief Exclui o objeto atualmente selecionado da cena, após confirmação.
     */
    void on_btnExcluirForma_clicked();

private:
    // --- Métodos de Inicialização e Gerenciamento ---
    /**
     * @brief Configura os componentes centrais da aplicação, como o DisplayFile e a cena inicial.
     */
    void inicializarComponentes();
    /**
     * @brief Realiza a conexão de todos os sinais dos widgets da UI aos slots correspondentes.
     */
    void conectarSinais();
    /**
     * @brief Define o estado inicial dos widgets da interface gráfica.
     */
    void inicializarUI();
    /**
     * @brief Cria a cena 3D inicial com objetos e/ou câmeras padrão.
     */
    void popularDisplayFileInicial();

    // --- Métodos de Atualização da UI ---
    /**
     * @brief Reseta os valores dos controles de transformação (sliders, spin boxes) para o estado inicial.
     */
    void resetarControlesTransformacao();
    /**
     * @brief Atualiza o conteúdo do ComboBox de objetos com base nos objetos presentes no DisplayFile.
     */
    void atualizarCbDisplayFile();
    /**
     * @brief Atualiza o conteúdo do ComboBox de câmeras com base nas câmeras presentes no DisplayFile.
     */
    void atualizarCbDFCamera();
    /**
     * @brief Gerencia o estado da UI (habilitar/desabilitar widgets) com base no que está selecionado (objeto ou câmera).
     */
    void updateTransformationTargetUIState();

    // --- Métodos Auxiliares ---
    /**
     * @brief Cria uma string descritiva para um objeto a ser exibida na UI.
     * @param nomeBase O nome original do objeto.
     * @param objeto O ponteiro para o objeto gráfico, para extrair detalhes.
     * @param cor A cor do objeto.
     * @return A string formatada para exibição.
     */
    QString gerarNomeFormatadoParaObjeto(const QString& nomeBase,
                                         std::shared_ptr<ObjetoGrafico> objeto,
                                         const QColor& cor);
    /**
     * @brief Ajusta a câmera ativa para enquadrar um objeto específico na viewport.
     * @param objeto O objeto no qual a câmera deve focar.
     */
    void focarNoObjeto(std::shared_ptr<ObjetoGrafico> objeto);

    // --- Membros Privados ---
    Ui::MainWindow *ui; ///< Ponteiro para a classe da interface gráfica gerada pelo Qt Designer.

    std::shared_ptr<DisplayFile> displayFile;           ///< Estrutura de dados da cena, contendo todos os objetos e câmeras.
    std::shared_ptr<ObjetoGrafico> objetoSelecionado;   ///< Ponteiro para o objeto gráfico atualmente selecionado pelo usuário.

    QColor corSelecionadaParaDesenho = Qt::white;       ///< Armazena a cor padrão para a criação de novos objetos.
};

#endif // MAINWINDOW_H
