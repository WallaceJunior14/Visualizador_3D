#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <stdexcept>
#include <QString>
#include <QDebug>

class Ponto3D;

/**
 * @brief Uma classe para representar e manipular matrizes de N x M.
 * @details Esta classe é o núcleo das operações de computação gráfica, sendo especialmente
 * projetada para transformações 3D usando coordenadas homogêneas. Matrizes 4x4 são
 * usadas para representar translação, rotação, escala e projeção. Pontos 3D são
 * tratados como vetores coluna 4x1 [x, y, z, w] durante as multiplicações.
 */
class Matriz {
public:
    /**
     * @brief Construtor que cria uma matriz com dimensões especificadas, inicializada com zeros.
     * @param linhas O número de linhas da matriz.
     * @param colunas O número de colunas da matriz.
     */
    Matriz(int linhas = 4, int colunas = 4);

    /**
     * @brief Construtor de cópia.
     * @param outra A matriz a ser copiada.
     */
    Matriz(const Matriz& outra);

    /**
     * @brief Operador de atribuição de cópia.
     * @param outra A matriz a ser atribuída.
     * @return Uma referência para esta matriz (`*this`).
     */
    Matriz& operator=(const Matriz& outra);

    /**
     * @brief Multiplica esta matriz por um Ponto3D (tratado como um vetor coluna).
     * @param ponto O Ponto3D a ser transformado.
     * @return O novo Ponto3D resultante da transformação.
     * @note Internamente, trata o ponto como um vetor [x, y, z, 1] para a multiplicação.
     */
    Ponto3D operator*(const Ponto3D& ponto) const;

    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~Matriz() = default;

    /**
     * @brief Permite acesso para leitura e escrita a um elemento da matriz.
     * @param linha O índice da linha do elemento (base 0).
     * @param coluna O índice da coluna do elemento (base 0).
     * @return Uma referência ao elemento na posição especificada.
     */
    double& operator()(int linha, int coluna);

    /**
     * @brief Permite acesso somente para leitura a um elemento da matriz.
     * @param linha O índice da linha do elemento (base 0).
     * @param coluna O índice da coluna do elemento (base 0).
     * @return Uma referência constante ao elemento na posição especificada.
     */
    const double& operator()(int linha, int coluna) const;

    /**
     * @brief Multiplica esta matriz por outra matriz (this * outra).
     * @param outra A matriz à direita na operação de multiplicação.
     * @return A matriz resultante da multiplicação.
     * @note A multiplicação de matrizes não é comutativa (A * B != B * A).
     */
    Matriz operator*(const Matriz& outra) const;

    // --- Getters ---
    /** @brief Retorna o número de linhas da matriz. */
    int obterLinhas() const;
    /** @brief Retorna o número de colunas da matriz. */
    int obterColunas() const;

    // --- Funções Estáticas para Transformações Geométricas ---

    /** @brief Cria uma matriz identidade quadrada. @param tamanho A dimensão da matriz (padrão 4). */
    static Matriz identidade(int tamanho = 4);
    /** @brief Cria uma matriz de translação 4x4. @param dx, dy, dz Deslocamento nos eixos X, Y e Z. */
    static Matriz translacao(double dx, double dy, double dz);
    /** @brief Cria uma matriz de escala 4x4 (em relação à origem). @param sx, sy, sz Fatores de escala nos eixos. */
    static Matriz escala(double sx, double sy, double sz);
    /** @brief Cria uma matriz de rotação 4x4 em torno do eixo X. @param anguloGraus O ângulo da rotação, em graus. */
    static Matriz rotacaoX(double anguloGraus);
    /** @brief Cria uma matriz de rotação 4x4 em torno do eixo Y. @param anguloGraus O ângulo da rotação, em graus. */
    static Matriz rotacaoY(double anguloGraus);
    /** @brief Cria uma matriz de rotação 4x4 em torno do eixo Z. @param anguloGraus O ângulo da rotação, em graus. */
    static Matriz rotacaoZ(double anguloGraus);
    /** @brief Cria uma matriz de rotação 4x4 em torno de um eixo arbitrário. @param eixo O eixo de rotação (deve ser um vetor unitário). @param anguloGraus O ângulo da rotação, em graus. */
    static Matriz rotacaoEixoArbitrario(const Ponto3D& eixo, double anguloGraus);

    // --- Funções Estáticas para Câmera ---

    /** @brief Cria uma matriz de visualização (View) do tipo "Look At". @param pos A posição da câmera. @param alvo O ponto para o qual a câmera olha. @param up O vetor "para cima" do mundo (geralmente (0,1,0)). */
    static Matriz lookAt(const Ponto3D& pos, const Ponto3D& alvo, const Ponto3D& up);
    /** @brief Cria uma matriz de projeção perspectiva. @param fovYGraus Campo de visão vertical, em graus. @param aspecto Proporção da tela (largura/altura). @param near Distância do plano de corte próximo. @param far Distância do plano de corte distante. */
    static Matriz perspectiva(double fovYGraus, double aspecto, double near, double far);
    /** @brief Cria uma matriz de projeção ortográfica. @param left,right,bottom,top Coordenadas do volume de visualização. @param near,far Distâncias dos planos de corte. */
    static Matriz ortografica(double left, double right, double bottom, double top, double near, double far);

    /**
     * @brief Imprime o conteúdo da matriz no console de depuração do Qt.
     * @param nome Um nome opcional para identificar a matriz na saída do console.
     */
    void imprimir(QString nome = "Matriz") const;

protected:
    std::vector<std::vector<double>> dados; ///< Armazenamento interno dos dados da matriz.
    int numLinhas;                          ///< Número de linhas da matriz.
    int numColunas;                         ///< Número de colunas da matriz.
};

#endif // MATRIZ_H
