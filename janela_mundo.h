// janela_mundo.h
#ifndef JANELA_MUNDO_H
#define JANELA_MUNDO_H

#include "ponto2d.h" // Assume que Ponto2D inclui Matriz
#include "matriz.h"  // Inclua Matriz diretamente se Ponto2D não o fizer por completo
#include <QString>   // Para o nome

// Definições dos limites do NDC (Normalized Device Coordinates)
const double ndcXMin = -1.0;
const double ndcXMax = 1.0;
const double ndcYMin = -1.0;
const double ndcYMax = 1.0;

class JanelaMundo {
public:
    // Construtor modificado para incluir nome
    JanelaMundo(const QString& nomeJanela, double xMin, double yMin, double xMax, double yMax);

    void zoom(double fator);
    void deslocar(double dx, double dy);
    // Método conceitual para rotação. Implementação completa em obterMatrizNormalizacao é complexa.
    void rotacionar(double deltaAnguloGraus);


    void definirLimites(double xMin, double yMin, double xMax, double yMax);

    Ponto2D obterMin() const;
    Ponto2D obterMax() const;
    double obterLargura() const;
    double obterAltura() const;

    QString obterNome() const;
    void definirNome(const QString& novoNome);

    Matriz obterMatrizNormalizacao() const;

private:
    Ponto2D minW;
    Ponto2D maxW;
    QString nome;
    double anguloRotacao = 0.0; // Ângulo de rotação da janela em graus
};

#endif // JANELA_MUNDO_H
