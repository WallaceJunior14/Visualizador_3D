#include "camera.h"

Camera::Camera(const QString& nome) : nome(nome) {
    // Padrões de uma câmera em perspectiva razoável
    posicao = Ponto3D(0, 0, 500); // Posição um pouco afastada na direção Z
    alvo = Ponto3D(0, 0, 0);       // Olhando para a origem
    vetorUp = Ponto3D(0, 1, 0);    // Eixo Y é para cima

    tipoProjecao = TipoProjecao::PERSPECTIVA;
    definirProjecaoPerspectiva(45.0, 1.0, 0.1, 1000.0); // fov 45 graus, aspect 1.0, near/far
}

// --- View ---
void Camera::definirPosicao(const Ponto3D& pos) { posicao = pos; }
void Camera::definirAlvo(const Ponto3D& alvo) { this->alvo = alvo; }
void Camera::definirVetorUp(const Ponto3D& up) { vetorUp = up; }
Ponto3D Camera::obterPosicao() const { return posicao; }
Ponto3D Camera::obterAlvo() const { return alvo; }
Ponto3D Camera::obterVetorUp() const { return vetorUp; }

// --- Projection ---
void Camera::definirTipoProjecao(TipoProjecao tipo) { tipoProjecao = tipo; }
TipoProjecao Camera::obterTipoProjecao() const { return tipoProjecao; }

void Camera::definirProjecaoPerspectiva(double fovY, double aspectRatio, double near, double far) {
    this->fovY = fovY;
    this->aspectRatio = aspectRatio;
    this->nearPlane = near;
    this->farPlane = far;
}

void Camera::definirProjecaoOrtografica(double left, double right, double bottom, double top, double near, double far) {
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->nearPlane = near;
    this->farPlane = far;
}

Matriz Camera::obterMatrizView() const {
    // Utiliza uma função estática "lookAt" que você precisará adicionar à sua classe Matriz
    return Matriz::lookAt(posicao, alvo, vetorUp);
}

Matriz Camera::obterMatrizProjecao() const {
    if (tipoProjecao == TipoProjecao::PERSPECTIVA) {
        // Utiliza uma função estática "perspectiva" que você precisará adicionar à Matriz
        return Matriz::perspectiva(fovY, aspectRatio, nearPlane, farPlane);
    } else {
        // Utiliza uma função estática "ortografica" que você precisará adicionar à Matriz
        return Matriz::ortografica(left, right, bottom, top, nearPlane, farPlane);
    }
}


QString Camera::obterNome() const {
    return nome;
}
