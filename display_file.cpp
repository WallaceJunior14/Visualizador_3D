#include "display_file.h"
#include "poligono_obj.h"
#include <QDebug>

DisplayFile::DisplayFile() {
    // Cria uma câmera padrão ao inicializar
    auto cameraDefault = std::make_shared<Camera>(
        Ponto3D(0, 0, 20),      // Forneça uma posição inicial válida
        Ponto3D(0, 0, 0),       // Forneça um alvo inicial válido
        "Câmera Principal"        // O nome que já estava lá
        );
    adicionarCamera(cameraDefault);
    definirCameraAtiva(cameraDefault);
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

// --- Gerenciamento de Câmeras ---
void DisplayFile::adicionarCamera(std::shared_ptr<Camera> cam) {
    if (cam && !buscarCamera(cam->obterNome())) {
        cameras.append(cam);
    }
}

std::shared_ptr<Camera> DisplayFile::buscarCamera(const QString& nome) const {
    for (const auto& cam : cameras) {
        if (cam && cam->obterNome() == nome) {
            return cam;
        }
    }
    return nullptr;
}

const QList<std::shared_ptr<Camera>>& DisplayFile::obterListaCameras() const {
    return cameras;
}

void DisplayFile::definirCameraAtiva(const QString& nome) {
    auto cam = buscarCamera(nome);
    if (cam) {
        cameraAtiva = cam;
    } else {
        qWarning() << "DisplayFile: Câmera com nome '" << nome << "' não encontrada.";
    }
}

void DisplayFile::definirCameraAtiva(std::shared_ptr<Camera> cam) {
    if (std::find(cameras.begin(), cameras.end(), cam) != cameras.end()) {
        cameraAtiva = cam;
    } else if (cam) {
        adicionarCamera(cam);
        cameraAtiva = cam;
    }
}

std::shared_ptr<Camera> DisplayFile::obterCameraAtiva() const {
    return cameraAtiva;
}

// Método principal do pipeline, agora em 3D.
void DisplayFile::recalcularTodosOsPontos() {
    if(!cameraAtiva){
        qWarning("DisplayFile: Nenhuma câmera ativa para recalcular pontos.");
            return;
    }

    // Obtém as matrizes View e Projection da câmera ativa
    Matriz matView = cameraAtiva->obterMatrizView();
    Matriz matProj = cameraAtiva->obterMatrizProjecao();

    for(auto& objeto: objetos){
        if (objeto){
            // CORREÇÃO: Passa a câmera, não as matrizes separadas.
            objeto->recalcularPontos(*cameraAtiva);
        }
    }
}

/**
 * @brief Conta quantos objetos de um determinado tipo existem no DisplayFile.
 * @param tipo O TipoObjeto a ser contado (PONTO, RETA, POLIGONO, etc.).
 * @param numVerticesEspecifico Se o tipo for POLIGONO e este valor for > 0,
 * conta apenas os polígonos com este número exato de vértices (ex: 3 para triângulos).
 * @return O número de objetos encontrados que correspondem aos critérios.
 */
int DisplayFile::contarObjetosPorTipo(TipoObjeto tipo, int numVerticesEspecifico) const
{
    // 1. Inicializa o contador.
    int contagem = 0;

    // 2. Itera sobre todos os objetos gráficos no DisplayFile.
    for (const auto& objeto : objetos)
    {
        // 3. Verifica se o tipo do objeto atual corresponde ao tipo solicitado.
        if (objeto && objeto->obterTipo() == tipo)
        {
            // 4. CASO ESPECIAL: Se estivermos procurando por polígonos com um número específico de vértices.
            if (tipo == TipoObjeto::POLIGONO && numVerticesEspecifico > 0)
            {
                // Tenta converter o ponteiro do objeto base (ObjetoGrafico) para o tipo derivado (PoligonoObj).
                // dynamic_pointer_cast é a maneira segura de fazer isso com shared_ptr.
                auto poligono = std::dynamic_pointer_cast<PoligonoObj>(objeto);

                // Se a conversão foi bem-sucedida e o número de vértices corresponde, incrementa a contagem.
                if (poligono && poligono->obterVertices().size() == numVerticesEspecifico) {
                    contagem++;
                }
            }
            // 5. CASO PADRÃO: Para todos os outros tipos de objeto, ou para polígonos quando não especificamos
            // o número de vértices.
            else
            {
                contagem++;
            }
        }
    }

    // 6. Retorna o total da contagem.
    return contagem;
}
