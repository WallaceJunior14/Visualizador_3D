#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <stdexcept>
#include <QDebug>
class Ponto3D;

// Classe para representar e manipular matrizes, usada para transformações 3D homogêneas.
// As transformações 3D são representadas por matrizes 4x4.
// Pontos são representados como matrizes coluna 4x1 (x, y, z, w).
class Matriz {
public:
    // Construtor: cria uma matriz com 'linhas' e 'colunas' especificadas. Padrão 4x4.
    Matriz(int linhas = 4, int colunas = 4);

    // Construtor de cópia
    Matriz(const Matriz& outra);

    // Operador de atribuição
    Matriz& operator=(const Matriz& outra);
    Ponto3D operator*(const Ponto3D& ponto) const;

    // Destrutor
    virtual ~Matriz() = default;

    // Acesso aos elementos da matriz (linha, coluna).
    double& operator()(int linha, int coluna);
    const double& operator()(int linha, int coluna) const;

    // Multiplicação de matrizes
    Matriz operator*(const Matriz& outra) const;

    // Getters para dimensões
    int obterLinhas() const;
    int obterColunas() const;

    // Funções estáticas para criar matrizes de transformação 3D comuns
    static Matriz identidade(int tamanho = 4);
    static Matriz translacao(double dx, double dy, double dz);
    static Matriz escala(double sx, double sy, double sz);

    // Rotação em 3D ocorre em torno de um eixo.
    static Matriz rotacaoX(double anguloGraus); // Rotação em torno do eixo X
    static Matriz rotacaoY(double anguloGraus); // Rotação em torno do eixo Y
    static Matriz rotacaoZ(double anguloGraus); // Rotação em torno do eixo Z

    // Imprime a matriz no console (para depuração)
    void imprimir(QString nome = "Matriz") const;

    // NOVAS FUNÇÕES ESTÁTICAS PARA CÂMERA
    static Matriz lookAt(const Ponto3D& pos, const Ponto3D& alvo, const Ponto3D& up);
    static Matriz perspectiva(double fovYGraus, double aspecto, double near, double far);
    static Matriz ortografica(double left, double right, double bottom, double top, double near, double far);

    static Matriz rotacaoEixoArbitrario(const Ponto3D& eixo, double anguloGraus);

protected:
    std::vector<std::vector<double>> dados;
    int numLinhas;
    int numColunas;
};

#endif // MATRIZ_H
