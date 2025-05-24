#include "janela_mundo.h"
#include <algorithm> // Para std::min, std::max (se necessário em zoom/pan)

JanelaMundo::JanelaMundo(double xMin, double yMin, double xMax, double yMax)
    : minW(xMin, yMin), maxW(xMax, yMax) {
    if (xMin >= xMax || yMin >= yMax) {
        //qWarning("JanelaMundo: Coordenadas mínimas devem ser menores que as máximas. Ajustando para default.");
        minW.definirX(-1.0); minW.definirY(-1.0);
        maxW.definirX(1.0);  maxW.definirY(1.0);
    }
}

void JanelaMundo::zoom(double fator) {
    if (fator <= 0) return;

    double centroX = (minW.obterX() + maxW.obterX()) / 2.0;
    double centroY = (minW.obterY() + maxW.obterY()) / 2.0;
    double larguraAtual = maxW.obterX() - minW.obterX();
    double alturaAtual = maxW.obterY() - minW.obterY();

    double novaLargura = larguraAtual / fator;
    double novaAltura = alturaAtual / fator;

    minW.definirX(centroX - novaLargura / 2.0);
    maxW.definirX(centroX + novaLargura / 2.0);
    minW.definirY(centroY - novaAltura / 2.0);
    maxW.definirY(centroY + novaAltura / 2.0);
}

void JanelaMundo::deslocar(double dx, double dy) {
    minW.definirX(minW.obterX() + dx);
    maxW.definirX(maxW.obterX() + dx);
    minW.definirY(minW.obterY() + dy);
    maxW.definirY(maxW.obterY() + dy);
}

void JanelaMundo::definirLimites(double xMin, double yMin, double xMax, double yMax) {
    if (xMin >= xMax || yMin >= yMax) {
        //qWarning("JanelaMundo::definirLimites: Coordenadas mínimas devem ser menores que as máximas.");
        return;
    }
    minW.definirX(xMin);
    minW.definirY(yMin);
    maxW.definirX(xMax);
    maxW.definirY(yMax);
}


Ponto2D JanelaMundo::obterMin() const {
    return minW;
}

Ponto2D JanelaMundo::obterMax() const {
    return maxW;
}

double JanelaMundo::obterLargura() const {
    return maxW.obterX() - minW.obterX();
}

double JanelaMundo::obterAltura() const {
    return maxW.obterY() - minW.obterY();
}


Matriz JanelaMundo::obterMatrizNormalizacao() const {
    // Esta matriz transforma um ponto (xw, yw) da janela do mundo
    // para um ponto (xn, yn) no sistema de coordenadas normalizadas (NDC).
    // xn = (xw - xw_min) / (xw_max - xw_min) * (ndc_x_max - ndc_x_min) + ndc_x_min
    // yn = (yw - yw_min) / (yw_max - yw_min) * (ndc_y_max - ndc_y_min) + ndc_y_min

    // Simplificando para NDC = [-1, 1] x [-1, 1]:
    // xn = 2 * (xw - xw_min) / (xw_max - xw_min) - 1
    // yn = 2 * (yw - yw_min) / (yw_max - yw_min) - 1

    // A matriz de transformação T_norm = S * T, onde T translada xw_min,yw_min para a origem,
    // e S escala para o tamanho do NDC e ajusta a origem do NDC.
    // T = | 1  0  -xw_min |
    //     | 0  1  -yw_min |
    //     | 0  0    1     |
    //
    // S = | 2/(xw_max-xw_min)       0                 -1 * (se NDC começa em -1) ou 0 |
    //     | 0                  2/(yw_max-yw_min)      -1 * (se NDC começa em -1) ou 0 |
    //     | 0                       0                  1                            |
    // Se mapear para [ndcXMin, ndcXMax] e [ndcYMin, ndcYMax]:
    // Sx = (ndcXMax - ndcXMin) / (xw_max - xw_min)
    // Sy = (ndcYMax - ndcYMin) / (yw_max - yw_min)
    // Tx = ndcXMin - xw_min * Sx
    // Ty = ndcYMin - yw_min * Sy
    //
    // Matriz de Normalização M_norm:
    // | Sx   0    Tx  |
    // | 0    Sy   Ty  |
    // | 0    0    1   |

    Matriz norm = Matriz::identidade(3);
    double xw_min = minW.obterX();
    double yw_min = minW.obterY();
    double xw_max = maxW.obterX();
    double yw_max = maxW.obterY();

    if (xw_max == xw_min || yw_max == yw_min) { // Evita divisão por zero
        //qWarning("JanelaMundo: Largura ou altura da janela é zero. Retornando matriz identidade.");
        return Matriz::identidade(3);
    }

    double sx = (ndcXMax - ndcXMin) / (xw_max - xw_min);
    double sy = (ndcYMax - ndcYMin) / (yw_max - yw_min); // Se Y do mundo e NDC crescem na mesma direção

    // Se o Y do mundo cresce para cima e o Y do NDC também, esta é a transformação.
    // Se uma das direções Y for invertida (e.g. mundo Y para cima, SCN Y para baixo),
    // então sy ou os limites ndcYMin/Max devem ser ajustados.
    // Assumindo que Y do mundo (yw_min para yw_max) mapeia para Y do SCN (ndcYMin para ndcYMax):
    // yw_min -> ndcYMin
    // yw_max -> ndcYMax

    double tx = ndcXMin - xw_min * sx;
    double ty = ndcYMin - yw_min * sy;


    norm(0,0) = sx; norm(0,2) = tx;
    norm(1,1) = sy; norm(1,2) = ty;

    return norm;
}
