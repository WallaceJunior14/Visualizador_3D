#include "display_file.h"
#include <QDebug>

DisplayFile::DisplayFile() {
    // Cria uma janela/câmera padrão ao inicializar
    auto janelaDefault = std::make_shared<JanelaMundo>("Câmera Principal", -300, -300, 300, 300);
    adicionarJanelaMundo(janelaDefault);
    definirJanelaMundoAtiva(janelaDefault); // Define como ativa
}

void DisplayFile::adicionarObjeto(std::shared_ptr<ObjetoGrafico> obj) {
    objetos.append(obj);
}

void DisplayFile::removerObjeto(const QString& nome) {
    objetos.erase(std::remove_if(objetos.begin(), objetos.end(),
                                 [&](const std::shared_ptr<ObjetoGrafico>& obj){ return obj && obj->obterNome() == nome; }),
                  objetos.end());
}

std::shared_ptr<ObjetoGrafico> DisplayFile::buscarObjeto(const QString& nome) const {
    for (const auto& obj : objetos) {
        if (obj && obj->obterNome() == nome) {
            return obj;
        }
    }
    return nullptr;
}

const QList<std::shared_ptr<ObjetoGrafico>>& DisplayFile::obterObjetos() const {
    return objetos;
}

// --- Gerenciamento de Janelas/Câmeras ---
void DisplayFile::adicionarJanelaMundo(std::shared_ptr<JanelaMundo> janela) {
    if (janela && !buscarJanelaMundo(janela->obterNome())) { // Evita duplicados pelo nome
        janelasMundo.append(janela);
    }
}

std::shared_ptr<JanelaMundo> DisplayFile::buscarJanelaMundo(const QString& nome) const {
    for (const auto& jm : janelasMundo) {
        if (jm && jm->obterNome() == nome) {
            return jm;
        }
    }
    return nullptr;
}

const QList<std::shared_ptr<JanelaMundo>>& DisplayFile::obterListaJanelasMundo() const {
    return janelasMundo;
}

void DisplayFile::definirJanelaMundoAtiva(const QString& nome) {
    std::shared_ptr<JanelaMundo> janela = buscarJanelaMundo(nome);
    if (janela) {
        janelaMundoAtiva = janela;
    } else {
        qWarning() << "DisplayFile: JanelaMundo com nome '" << nome << "' não encontrada para definir como ativa.";
    }
}

void DisplayFile::definirJanelaMundoAtiva(std::shared_ptr<JanelaMundo> janela) {
    if (std::find(janelasMundo.begin(), janelasMundo.end(), janela) != janelasMundo.end()) {
        janelaMundoAtiva = janela;
    } else if (janela) { // Se a janela não está na lista, mas é válida, adiciona e define como ativa.
        qWarning() << "DisplayFile: JanelaMundo '" << janela->obterNome() << "' não estava na lista. Adicionando e definindo como ativa.";
        adicionarJanelaMundo(janela);
        janelaMundoAtiva = janela;
    } else {
        qWarning() << "DisplayFile: Tentativa de definir janelaMundoAtiva nula.";
    }
}


std::shared_ptr<JanelaMundo> DisplayFile::obterJanelaMundoAtiva() const {
    return janelaMundoAtiva;
}

void DisplayFile::recalcularTodosPontosSCN() {
    if (!janelaMundoAtiva) {
        qWarning("DisplayFile: Nenhuma JanelaMundo ativa para recalcular SCNs.");
        return;
    }
    Matriz matNorm = janelaMundoAtiva->obterMatrizNormalizacao();
    for (auto& objeto : objetos) {
        if (objeto) {
            objeto->recalcularPontosTransformados(matNorm);
        }
    }
}
