#ifndef CAMERA_H
#define CAMERA_H

#include <QString>
#include "ponto3d.h"
#include "matriz.h"

enum class TipoProjecao {
    PERSPECTIVA,
    ORTOGRAFICA
};

class Camera {
public:
    // Construtor cria uma câmera perspectiva padrão.
    Camera(const QString& nome);

    // Getters e Setters para a Matriz de Visualização (View)
    void definirPosicao(const Ponto3D& pos);
    void definirAlvo(const Ponto3D& alvo);
    void definirVetorUp(const Ponto3D& up);
    Ponto3D obterPosicao() const;
    Ponto3D obterAlvo() const;
    Ponto3D obterVetorUp() const;

    // Getters e Setters para a Matriz de Projeção (Projection)
    void definirTipoProjecao(TipoProjecao tipo);
    TipoProjecao obterTipoProjecao() const;
    void definirProjecaoPerspectiva(double fovY, double aspectRatio, double near, double far);
    void definirProjecaoOrtografica(double left, double right, double bottom, double top, double near, double far);

    // Obtém as matrizes de transformação calculadas
    Matriz obterMatrizView() const;
    Matriz obterMatrizProjecao() const;

    QString obterNome() const;

private:
    QString nome;

    // Parâmetros da Matriz View (LookAt)
    Ponto3D posicao;
    Ponto3D alvo;
    Ponto3D vetorUp;

    // Parâmetros da Matriz de Projeção
    TipoProjecao tipoProjecao;
    // Perspectiva
    double fovY;         // Campo de visão vertical em graus
    double aspectRatio;  // Proporção da tela (largura / altura)
    // Ortográfica
    double left, right, bottom, top;
    // Comum a ambas
    double nearPlane, farPlane;
};

#endif // CAMERA_H
