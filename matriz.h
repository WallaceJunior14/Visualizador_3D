#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <stdexcept> // Para std::out_of_range
#include <QDebug>    // Para depuração

// Classe para representar e manipular matrizes, usada para transformações 2D homogêneas.
// As transformações 2D são normalmente representadas por matrizes 3x3.
// Pontos são representados como matrizes coluna 3x1 (x, y, w).
class Matriz {
public:
    // Construtor: cria uma matriz com 'linhas' e 'colunas' especificadas, inicializada com zeros.
    Matriz(int linhas = 3, int colunas = 3);

    // Construtor de cópia
    Matriz(const Matriz& outra);

    // Operador de atribuição
    Matriz& operator=(const Matriz& outra);

    // Destrutor
    virtual ~Matriz() = default; // Virtual para permitir herança (ex: Ponto2D)

    // Acesso aos elementos da matriz (linha, coluna).
    double& operator()(int linha, int coluna);
    const double& operator()(int linha, int coluna) const;

    // Multiplicação de matrizes
    Matriz operator*(const Matriz& outra) const;

    // Getters para dimensões
    int obterLinhas() const;
    int obterColunas() const;

    // Funções estáticas para criar matrizes de transformação comuns
    static Matriz identidade(int tamanho = 3);
    static Matriz translacao(double dx, double dy);
    static Matriz escala(double sx, double sy);
    static Matriz rotacao(double anguloGraus); // Rotação em torno da origem

    // Imprime a matriz no console (para depuração)
    void imprimir(QString nome = "Matriz") const;

protected:
    std::vector<std::vector<double>> dados;
    int numLinhas;
    int numColunas;
};

#endif // MATRIZ_H
