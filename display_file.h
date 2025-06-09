#ifndef DISPLAY_FILE_H
#define DISPLAY_FILE_H

#include <QList>
#include <memory>
#include <QString>
#include "objeto_grafico.h"
#include "camera.h" // Alterado de JanelaMundo para Camera

class DisplayFile {
public:
    DisplayFile();

    void adicionarObjeto(std::shared_ptr<ObjetoGrafico> obj);
    void removerObjeto(const QString& nome);
    std::shared_ptr<ObjetoGrafico> buscarObjeto(const QString& nome) const;
    const QList<std::shared_ptr<ObjetoGrafico>>& obterObjetos() const;

    // Gerenciamento de Câmeras
    void adicionarCamera(std::shared_ptr<Camera> cam);
    std::shared_ptr<Camera> buscarCamera(const QString& nome) const;
    const QList<std::shared_ptr<Camera>>& obterListaCameras() const;

    void definirCameraAtiva(const QString& nome);
    void definirCameraAtiva(std::shared_ptr<Camera> cam);
    std::shared_ptr<Camera> obterCameraAtiva() const;

    // Recalcula todos os pontos usando a câmera ativa (pipeline MVP)
    void recalcularTodosOsPontos();

    int contarObjetosPorTipo(TipoObjeto tipo, int numVerticesEspecifico = 0) const;

private:
    QList<std::shared_ptr<ObjetoGrafico>> objetos;
    QList<std::shared_ptr<Camera>> cameras;
    std::shared_ptr<Camera> cameraAtiva;
};

#endif // DISPLAY_FILE_H
