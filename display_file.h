#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <QList>
#include <memory> // Para std::shared_ptr ou std::unique_ptr
#include "objeto_grafico.h"

// Gerencia a lista de todos os objetos gráficos a serem exibidos. [cite: 6]
class DisplayFile {
public:
    DisplayFile();

    void adicionarObjeto(std::shared_ptr<ObjetoGrafico> objeto);
    void removerObjeto(const QString& nomeObjeto);
    std::shared_ptr<ObjetoGrafico> buscarObjeto(const QString& nomeObjeto);

    const QList<std::shared_ptr<ObjetoGrafico>>& obterObjetos() const;
    QList<std::shared_ptr<ObjetoGrafico>>& obterObjetosMutavel();


    // Recalcula os pontos SCN de todos os objetos.
    // Necessário quando a janela de visualização (mundo) muda.
    void recalcularTodosPontosSCN(const Matriz& matrizNormalizacao);

    // Limpa todos os objetos do display file.
    void limpar();

private:
    QList<std::shared_ptr<ObjetoGrafico>> listaDeObjetos;
};

#endif // DISPLAY_FILE_H
