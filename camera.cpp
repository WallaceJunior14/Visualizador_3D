#include "camera.h"

#include "transformador_geometrico.h"

#include "matriz.h"


Camera::Camera(const Ponto3D& pos, const Ponto3D& target, const QString& nome)
    : posicao(pos), alvo(target), nome(nome) {
    // Padrões de uma câmera em perspectiva razoável
    posicao = Ponto3D(0, 0, 30); // Posição um pouco afastada na direção Z
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

// --- Projecão ---
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

void Camera::definirNome(const QString& novoNome)
{
    this->nome = novoNome;
}


void Camera::transladar(double dx, double dy, double dz)
{
    // Move a posição da câmera
    Ponto3D posAtual = this->obterPosicao();
    this->definirPosicao(Ponto3D(posAtual.obterX() + dx,
                                 posAtual.obterY() + dy,
                                 posAtual.obterZ() + dz));

    // Move o alvo da câmera
    Ponto3D alvoAtual = this->obterAlvo();
    this->definirAlvo(Ponto3D(alvoAtual.obterX() + dx,
                              alvoAtual.obterY() + dy,
                              alvoAtual.obterZ() + dz));
}

void Camera::dolly(double fator)
{
    // 1. Calcula o vetor que aponta da posição da câmera para o alvo.
    // Este é o vetor de direção da visão.
    Ponto3D vetorDirecao = this->alvo - this->posicao;

    // 2. Normaliza o vetor (transforma em um vetor de comprimento 1).
    vetorDirecao.normalizarVetor();

    // 3. Calcula o vetor de deslocamento multiplicando a direção pelo fator.
    Ponto3D deslocamento = vetorDirecao * fator;

    // 4. Adiciona o deslocamento à posição atual da câmera.
    // O ponto 'alvo' não se move em um dolly.
    this->posicao = this->posicao + deslocamento;
}

// Em camera.cpp

void Camera::orbitar(double deltaYaw, double deltaPitch, double deltaRoll)
{
    // Vetor que vai da posição da câmera até o alvo (direção da visão)
    Ponto3D vetorDirecao = (this->alvo - this->posicao).normalizarVetor();
    // Vetor que vai do alvo até a posição da câmera (usado para rotação)
    Ponto3D vetorPosicaoRelativa = this->posicao - this->alvo;

    // --- 1. Rotação Pitch (Eixo X local) ---
    // O eixo de rotação Pitch é o eixo "direito" da câmera.
    // Calculamos com o produto vetorial entre a direção e o vetor UP da câmera.
    Ponto3D eixoPitch = Ponto3D::produtoVetorial(vetorDirecao, this->vetorUp).normalizarVetor();
    // Previne instabilidade se o eixo for inválido (câmera olhando para cima/baixo)
    if (eixoPitch.magnitude() > 0.001) {
        Matriz rotPitch = Matriz::rotacaoEixoArbitrario(eixoPitch, deltaPitch);
        vetorPosicaoRelativa = rotPitch * vetorPosicaoRelativa;
        // Também rotacionamos o vetor UP para que ele acompanhe o movimento
        this->vetorUp = rotPitch * this->vetorUp;
    }

    // --- 2. Rotação Yaw (Eixo Y do Mundo) ---
    // A rotação Yaw geralmente é mais intuitiva em torno do eixo Y global.
    Matriz rotYaw = Matriz::rotacaoY(deltaYaw);
    vetorPosicaoRelativa = rotYaw * vetorPosicaoRelativa;
    this->vetorUp = rotYaw * this->vetorUp;

    // --- 3. Rotação Roll (Eixo Z local) ---
    // A rotação Roll gira o vetor UP da câmera em torno da direção da visão.
    // O eixo de rotação é o próprio vetor de direção.
    if (abs(deltaRoll) > 0.001) {
        Matriz rotRoll = Matriz::rotacaoEixoArbitrario(vetorDirecao, deltaRoll);
        this->vetorUp = rotRoll * this->vetorUp;
    }

    // Normaliza o vetor UP para evitar acúmulo de erros de ponto flutuante
    this->vetorUp.normalizarVetor();

    // 4. Atualiza a posição final da câmera
    this->posicao = this->alvo + vetorPosicaoRelativa;
}
