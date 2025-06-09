#include "matriz.h"
#include "ponto3d.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// O construtor, operadores de cópia, atribuição e acesso estão corretos.
// (Nenhuma alteração nos métodos abaixo)
Matriz::Matriz(int linhas, int colunas) : numLinhas(linhas), numColunas(colunas) {
    if (linhas <= 0 || colunas <= 0) {
        throw std::invalid_argument("Dimensões da matriz devem ser positivas.");
    }
    dados.resize(numLinhas, std::vector<double>(numColunas, 0.0));
}

Matriz::Matriz(const Matriz& outra) : numLinhas(outra.numLinhas), numColunas(outra.numColunas), dados(outra.dados) {}

Matriz& Matriz::operator=(const Matriz& outra) {
    if (this == &outra) {
        return *this;
    }
    numLinhas = outra.numLinhas;
    numColunas = outra.numColunas;
    dados = outra.dados;
    return *this;
}

double& Matriz::operator()(int linha, int coluna) {
    if (linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) {
        throw std::out_of_range("Acesso fora dos limites da matriz.");
    }
    return dados[linha][coluna];
}

const double& Matriz::operator()(int linha, int coluna) const {
    if (linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) {
        throw std::out_of_range("Acesso fora dos limites da matriz.");
    }
    return dados[linha][coluna];
}

Matriz Matriz::operator*(const Matriz& outra) const {
    if (numColunas != outra.numLinhas) {
        throw std::invalid_argument("Dimensões de matriz inválidas para multiplicação.");
    }
    Matriz resultado(numLinhas, outra.numColunas);
    for (int i = 0; i < numLinhas; ++i) {
        for (int j = 0; j < outra.numColunas; ++j) {
            for (int k = 0; k < numColunas; ++k) {
                resultado(i, j) += dados[i][k] * outra(k, j);
            }
        }
    }
    return resultado;
}

// --- Funções Corrigidas ---

/**
 * @brief Multiplicação de Matriz por Ponto3D.
 */
Ponto3D Matriz::operator*(const Ponto3D& ponto) const {
    if (this->numLinhas != 4 || this->numColunas != 4) {
        // qWarning("Multiplicação Matriz*Ponto requer uma matriz 4x4.");
        return Ponto3D(0, 0, 0);
    }

    // CORREÇÃO: Obter o 'w' do ponto de entrada, não forçar para 1.0.
    // Isso é crucial para transformar vetores (w=0) corretamente.
    double x = ponto.obterX();
    double y = ponto.obterY();
    double z = ponto.obterZ();
    double w = ponto.obterW();

    // CORREÇÃO: Usar o membro 'dados' para acessar os elementos da matriz.
    double resX = dados[0][0] * x + dados[0][1] * y + dados[0][2] * z + dados[0][3] * w;
    double resY = dados[1][0] * x + dados[1][1] * y + dados[1][2] * z + dados[1][3] * w;
    double resZ = dados[2][0] * x + dados[2][1] * y + dados[2][2] * z + dados[2][3] * w;
    double resW = dados[3][0] * x + dados[3][1] * y + dados[3][2] * z + dados[3][3] * w;

    return Ponto3D(resX, resY, resZ, resW);
}

/**
 * @brief Função para criar uma matriz de visualização (View)
 */
Matriz Matriz::lookAt(const Ponto3D& pos, const Ponto3D& alvo, const Ponto3D& up) {
    // CORREÇÃO: Não é necessário criar cópias locais p_pos, p_alvo, p_up.
    // Usamos os parâmetros diretamente.

    // Eixo Z da câmera (vetor para frente), normalizado
    Ponto3D z_cam = (pos - alvo).normalizarVetor();
    // Eixo X da câmera (vetor para direita), normalizado
    Ponto3D x_cam = Ponto3D::produtoVetorial(up, z_cam).normalizarVetor();
    // Eixo Y da câmera (vetor para cima)
    Ponto3D y_cam = Ponto3D::produtoVetorial(z_cam, x_cam);

    // CORREÇÃO: Usar os getters obterX(), obterY(), etc. da classe Ponto3D.
    Matriz orientacao = identidade(4);
    orientacao(0,0) = x_cam.obterX(); orientacao(0,1) = x_cam.obterY(); orientacao(0,2) = x_cam.obterZ();
    orientacao(1,0) = y_cam.obterX(); orientacao(1,1) = y_cam.obterY(); orientacao(1,2) = y_cam.obterZ();
    orientacao(2,0) = z_cam.obterX(); orientacao(2,1) = z_cam.obterY(); orientacao(2,2) = z_cam.obterZ();

    Matriz translacaoMat = identidade(4); // Renomeado para evitar conflito de nome com a função
    translacaoMat(0,3) = -pos.obterX();
    translacaoMat(1,3) = -pos.obterY();
    translacaoMat(2,3) = -pos.obterZ();

    return orientacao * translacaoMat;
}


// (O restante do arquivo, a partir daqui, não precisava de alterações)
int Matriz::obterLinhas() const { return numLinhas; }
int Matriz::obterColunas() const { return numColunas; }
// ... (imprimir, identidade, translacao, escala, rotacoes, perspectiva, ortografica, etc.) ...
// (O código para estas funções, que você já tinha, permanece o mesmo)
Matriz Matriz::identidade(int tamanho) {
    Matriz id(tamanho, tamanho);
    for (int i = 0; i < tamanho; ++i) {
        id(i, i) = 1.0;
    }
    return id;
}
// ... e assim por diante para todas as outras funções estáticas ...
