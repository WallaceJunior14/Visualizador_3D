#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <QList>
#include <memory>
#include <QString>
#include "objeto_grafico.h"
#include "camera.h"

/**
 * @brief Atua como um contêiner para todos os elementos de uma cena 3D.
 * @details Esta classe gerencia a lista de objetos gráficos a serem renderizados,
 * a lista de câmeras disponíveis e qual câmera está ativa no momento. É a
 * estrutura de dados central que representa o "mundo" da aplicação.
 */
class DisplayFile {
public:
    /**
     * @brief Construtor padrão da classe DisplayFile.
     */
    DisplayFile();

    /**
     * @brief Adiciona um novo objeto gráfico à cena.
     * @param obj Um std::shared_ptr para o objeto a ser adicionado.
     */
    void adicionarObjeto(std::shared_ptr<ObjetoGrafico> obj);

    /**
     * @brief Remove um objeto da cena com base no seu nome.
     * @param nome O nome (QString) do objeto a ser removido.
     */
    void removerObjeto(const QString& nome);

    /**
     * @brief Procura por um objeto na cena pelo seu nome.
     * @param nome O nome do objeto a ser buscado.
     * @return Um std::shared_ptr para o objeto encontrado, ou `nullptr` se não for encontrado.
     */
    std::shared_ptr<ObjetoGrafico> buscarObjeto(const QString& nome) const;

    /**
     * @brief Retorna uma referência constante para a lista de todos os objetos na cena.
     * @return const QList<std::shared_ptr<ObjetoGrafico>>& A lista de objetos.
     * @note Retornar por referência constante é eficiente pois evita a cópia da lista inteira.
     */
    const QList<std::shared_ptr<ObjetoGrafico>>& obterObjetos() const;

    // --- Gerenciamento de Câmeras ---

    /**
     * @brief Adiciona uma nova câmera à lista de câmeras disponíveis na cena.
     * @param cam Um std::shared_ptr para o objeto Camera a ser adicionado.
     */
    void adicionarCamera(std::shared_ptr<Camera> cam);

    /**
     * @brief Procura por uma câmera na lista pelo seu nome.
     * @param nome O nome da câmera a ser buscada.
     * @return Um std::shared_ptr para a câmera encontrada, ou `nullptr` se não for encontrada.
     */
    std::shared_ptr<Camera> buscarCamera(const QString& nome) const;

    /**
     * @brief Retorna uma referência constante para a lista de todas as câmeras na cena.
     * @return const QList<std::shared_ptr<Camera>>& A lista de câmeras.
     */
    const QList<std::shared_ptr<Camera>>& obterListaCameras() const;

    /**
     * @brief Define a câmera ativa com base no seu nome.
     * @param nome O nome da câmera a ser ativada.
     * @note Internamente, busca a câmera na lista e a define como ativa.
     */
    void definirCameraAtiva(const QString& nome);

    /**
     * @brief Define a câmera ativa diretamente através de um ponteiro compartilhado.
     * @param cam O std::shared_ptr para a câmera a ser ativada. Pode ser `nullptr` para desativar a câmera.
     */
    void definirCameraAtiva(std::shared_ptr<Camera> cam);

    /**
     * @brief Retorna um ponteiro para a câmera atualmente ativa.
     * @return Um std::shared_ptr para a câmera ativa, ou `nullptr` se nenhuma estiver ativa.
     */
    std::shared_ptr<Camera> obterCameraAtiva() const;

    /**
     * @brief Itera sobre todos os objetos da cena e recalcula suas posições no espaço de recorte (NDC).
     * @details Esta função é o coração do pipeline de atualização. Ela chama o método `recalcularPontos`
     * de cada ObjetoGrafico, passando a câmera ativa para que a transformação MVP (Model-View-Projection)
     * seja aplicada. Deve ser chamada antes de cada redesenho da cena.
     */
    void recalcularTodosOsPontos();

    /**
     * @brief Conta quantos objetos de um determinado tipo existem na cena.
     * @param tipo O TipoObjeto a ser contado (ex: PONTO, RETA).
     * @param numVerticesEspecifico Opcional. Usado para subtipos, como contar triângulos (polígono com 3 vértices).
     * @return O número de objetos que correspondem aos critérios.
     * @note Útil para gerar nomes únicos automaticamente (ex: "Reta-3", "Reta-4").
     */
    int contarObjetosPorTipo(TipoObjeto tipo, int numVerticesEspecifico = 0) const;

private:
    QList<std::shared_ptr<ObjetoGrafico>> objetos; ///< Lista de todos os objetos gráficos da cena.
    QList<std::shared_ptr<Camera>> cameras;        ///< Lista de todas as câmeras disponíveis.
    std::shared_ptr<Camera> cameraAtiva;           ///< Ponteiro para a câmera atualmente em uso para renderização.
};

#endif // DISPLAY_FILE_H
