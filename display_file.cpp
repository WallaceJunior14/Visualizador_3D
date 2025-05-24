#include "display_file.h"

DisplayFile::DisplayFile() {}

void DisplayFile::adicionarObjeto(std::shared_ptr<ObjetoGrafico> objeto) {
    if (objeto) {
        listaDeObjetos.append(objeto);
    }
}

void DisplayFile::removerObjeto(const QString& nomeObjeto) {
    for (int i = 0; i < listaDeObjetos.size(); ++i) {
        if (listaDeObjetos[i] && listaDeObjetos[i]->obterNome() == nomeObjeto) {
            listaDeObjetos.removeAt(i);
            return;
        }
    }
}

std::shared_ptr<ObjetoGrafico> DisplayFile::buscarObjeto(const QString& nomeObjeto) {
    for (const auto& objeto : listaDeObjetos) {
        if (objeto && objeto->obterNome() == nomeObjeto) {
            return objeto;
        }
    }
    return nullptr; // Retorna nullptr se não encontrar
}

const QList<std::shared_ptr<ObjetoGrafico>>& DisplayFile::obterObjetos() const {
    return listaDeObjetos;
}

QList<std::shared_ptr<ObjetoGrafico>>& DisplayFile::obterObjetosMutavel() {
    return listaDeObjetos;
}

void DisplayFile::recalcularTodosPontosSCN(const Matriz& matrizNormalizacao) {
    for (const auto& objeto : listaDeObjetos) {
        if (objeto) {
            objeto->recalcularPontosTransformados(matrizNormalizacao);
        }
    }
}

void DisplayFile::limpar() {
    listaDeObjetos.clear();
}
