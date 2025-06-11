#include "carregador_obj.h"
#include "malha_obj.h"
#include "ponto3d.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QSet>

std::shared_ptr<MalhaObj> CarregadorOBJ::carregar(const QString& caminhoArquivo) {
    QFile file(caminhoArquivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Se não conseguir abrir o arquivo, retorna ponteiro nulo
        return nullptr;
    }

    QList<Ponto3D> vertices;
    // Usamos um QSet para armazenar as arestas e evitar duplicatas (ex: aresta 1-2 e 2-1)
    QSet<QPair<int, int>> arestas;
    QString nomeObjeto = QFileInfo(caminhoArquivo).baseName(); // Nome padrão é o nome do arquivo

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);

        if (parts.isEmpty()) {
            continue;
        }

        QString type = parts.first();
        if (type == "o") {
            // Se encontrar uma definição de nome de objeto, usa ela
            nomeObjeto = parts.value(1, nomeObjeto);
        } else if (type == "v") {
            // Definição de vértice: v x y z
            if (parts.size() >= 4) {
                double x = parts.value(1).toDouble();
                double y = parts.value(2).toDouble();
                double z = parts.value(3).toDouble();
                vertices.append(Ponto3D(x, y, z));
            }
        } else if (type == "f") {
            // Definição de face: f v1 v2 v3 ...
            QList<int> indicesFace;
            for (int i = 1; i < parts.size(); ++i) {
                // O formato pode ser "v/vt/vn", pegamos apenas o índice do vértice "v"
                QStringList vertexParts = parts.value(i).split('/');
                int index = vertexParts.first().toInt();
                // Arquivos .obj são 1-based, nossa lista é 0-based
                if (index > 0) {
                    indicesFace.append(index - 1);
                } else { // Handle de índices negativos (relativos ao final da lista de vértices)
                    indicesFace.append(vertices.size() + index);
                }
            }

            // Cria as arestas da face para o modo wireframe
            if (indicesFace.size() > 1) {
                for (int i = 0; i < indicesFace.size(); ++i) {
                    int idx1 = indicesFace.at(i);
                    int idx2 = indicesFace.at((i + 1) % indicesFace.size()); // Conecta com o próximo, fechando a face

                    // Normaliza a aresta para evitar duplicatas (sempre armazena do menor para o maior índice)
                    if (idx1 < idx2) {
                        arestas.insert({idx1, idx2});
                    } else {
                        arestas.insert({idx2, idx1});
                    }
                }
            }
        }
    }
    file.close();

    if (vertices.isEmpty() || arestas.isEmpty()) {
        return nullptr; // Nenhum dado válido encontrado
    }

    // Cria e retorna o novo objeto MalhaObj com os dados carregados
    return std::make_shared<MalhaObj>(nomeObjeto, vertices, arestas.values());
}
