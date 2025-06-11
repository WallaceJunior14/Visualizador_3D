#include "camera.h"

#include "transformador_geometrico.h"

#include "matriz.h"


Camera::Camera(const Ponto3D& pos, const Ponto3D& target, const QString& nome)
    : posicao(pos), alvo(target), nome(nome) {
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
    // Isso garante que o movimento seja proporcional ao 'fator',
    // independentemente da distância atual até o alvo.
    // (Supondo que você tenha um método para normalizar em Ponto3D)
    vetorDirecao.normalizarVetor();

    // 3. Calcula o vetor de deslocamento multiplicando a direção pelo fator.
    Ponto3D deslocamento = vetorDirecao * fator;

    // 4. Adiciona o deslocamento à posição atual da câmera.
    // O ponto 'alvo' não se move em um dolly.
    this->posicao = this->posicao + deslocamento;
}

void Camera::orbitar(double deltaYaw, double deltaPitch)
{
    // 1. Obtenha o vetor que vai do alvo até a posição atual da câmera.
    // É este vetor que vamos rotacionar.
    Ponto3D vetorCamera = this->posicao - this->alvo;

    // 2. Crie a matriz de rotação para o Yaw (rotação horizontal).
    // Esta rotação acontece em torno do eixo Y do mundo.
    Matriz rotYaw = TransformadorGeometrico::rotacaoY(deltaYaw);

    // 3. Aplique a rotação de Yaw ao vetor da câmera.
    vetorCamera = rotYaw * vetorCamera;

    // 4. Calcule o eixo para o Pitch (rotação vertical).
    // Este eixo é um vetor que aponta para a "direita" da câmera.
    // Ele é calculado com o produto vetorial entre o vetor 'up' do mundo e o vetor da câmera.
    Ponto3D upMundo(0.0, 1.0, 0.0);
    Ponto3D eixoPitch = Ponto3D::produtoVetorial(upMundo, vetorCamera);
    eixoPitch.normalizarVetor(); // É crucial normalizar o eixo de rotação

    // 5. Crie a matriz de rotação para o Pitch em torno do eixo calculado.
    // (Supondo que você tenha uma função para rotacionar em torno de um eixo arbitrário)
    Matriz rotPitch = TransformadorGeometrico::rotacaoEixoArbitrario(eixoPitch, deltaPitch);

    // 6. Aplique a rotação de Pitch ao vetor da câmera.
    vetorCamera = rotPitch * vetorCamera;

    // 7. A nova posição da câmera é o ponto 'alvo' mais o vetor rotacionado.
    this->posicao = this->alvo + vetorCamera;
}
