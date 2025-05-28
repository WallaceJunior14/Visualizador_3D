// display_file.h
#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <QList>
#include <memory>
#include <QString>
#include "objeto_grafico.h"
#include "janela_mundo.h"

class DisplayFile {
public:
    // Construtor: pode inicializar com uma JanelaMundo default
    DisplayFile(); // Ou DisplayFile(const QString& nomePrimeiraJanela, double xMin, ...);

    void adicionarObjeto(std::shared_ptr<ObjetoGrafico> obj);
    void removerObjeto(const QString& nome);
    std::shared_ptr<ObjetoGrafico> buscarObjeto(const QString& nome) const;
    const QList<std::shared_ptr<ObjetoGrafico>>& obterObjetos() const;

    // Gerenciamento de Janelas/Câmeras
    void adicionarJanelaMundo(std::shared_ptr<JanelaMundo> janela);
    std::shared_ptr<JanelaMundo> buscarJanelaMundo(const QString& nome) const;
    const QList<std::shared_ptr<JanelaMundo>>& obterListaJanelasMundo() const;

    void definirJanelaMundoAtiva(const QString& nome); // Pode ser por nome ou ponteiro
    void definirJanelaMundoAtiva(std::shared_ptr<JanelaMundo> janela);
    std::shared_ptr<JanelaMundo> obterJanelaMundoAtiva() const;

    void recalcularTodosPontosSCN(); // Usa a janelaMundoAtiva

private:
    QList<std::shared_ptr<ObjetoGrafico>> objetos;
    QList<std::shared_ptr<JanelaMundo>> janelasMundo;
    std::shared_ptr<JanelaMundo> janelaMundoAtiva;
};

#endif // DISPLAY_FILE_H
