#include "ponto2d.h"
#include <stdexcept> // Para std::runtime_error

Ponto2D::Ponto2D(double x, double y, double w) : Matriz(3, 1) {
    if (w == 0) {
        // qDebug() << "Atenção: Coordenada homogênea w não pode ser zero para um ponto afim. Usando 1.";
        // w = 1.0; // Ou lançar exceção, dependendo da política de erro
    }
    dados[0][0] = x;
    dados[1][0] = y;
    dados[2][0] = w;
}

Ponto2D::Ponto2D(const Matriz& m) : Matriz(3,1) {
    if (m.obterLinhas() != 3 || m.obterColunas() != 1) {
        //qDebug() << "Erro: Matriz base para Ponto2D deve ser 3x1.";
        // Inicializa como ponto na origem em caso de erro
        dados[0][0] = 0;
        dados[1][0] = 0;
        dados[2][0] = 1;
        // Lançar exceção seria mais robusto:
        // throw std::runtime_error("Matriz base para Ponto2D deve ser 3x1.");
        return;
    }
    dados[0][0] = m(0,0);
    dados[1][0] = m(1,0);
    dados[2][0] = m(2,0);
}


double Ponto2D::obterX() const {
    if (dados[2][0] == 0) return dados[0][0]; // Ponto no infinito, retorna x
    return dados[0][0] / dados[2][0];
}

double Ponto2D::obterY() const {
    if (dados[2][0] == 0) return dados[1][0]; // Ponto no infinito, retorna y
    return dados[1][0] / dados[2][0];
}

double Ponto2D::obterW() const {
    return dados[2][0];
}

void Ponto2D::definirX(double x) {
    // Assume w=1 para definição direta de x cartesiano
    dados[0][0] = x * dados[2][0]; // Se w != 1, ajusta para manter x cartesiano
    // Ou mais simples: dados[0][0] = x; se w sempre for 1 ao definir.
    // Para manter consistência com x = X/W, então X = x*W
    dados[0][0] = x; // Assumindo que ao definir X, W é 1 ou será ajustado.
    // Para o contexto de coordenadas de mundo iniciais, w=1.
    // Se w for diferente de 1, o usuário está trabalhando com coordenadas homogêneas diretamente.
}

void Ponto2D::definirY(double y) {
    dados[1][0] = y;
}

void Ponto2D::definirW(double w) {
    if (w == 0) {
        //qDebug() << "Atenção: Coordenada homogênea w não pode ser zero para um ponto afim. Mantendo valor anterior ou 1.";
        //return; // Ou definir para 1 se o anterior também era 0.
    }
    dados[2][0] = w;
}

void Ponto2D::normalizar() {
    if (dados[2][0] != 0 && dados[2][0] != 1.0) {
        dados[0][0] /= dados[2][0];
        dados[1][0] /= dados[2][0];
        dados[2][0] = 1.0;
    }
}
