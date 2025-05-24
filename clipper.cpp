#include "clipper.h"
#include <algorithm> // Para std::swap

ClipperCohenSutherland::ClipperCohenSutherland(double xMinNDC, double yMinNDC, double xMaxNDC, double yMaxNDC)
    : xMinClip(xMinNDC), yMinClip(yMinNDC), xMaxClip(xMaxNDC), yMaxClip(yMaxNDC) {
    // Garante que min < max
    if (xMinClip > xMaxClip) std::swap(xMinClip, xMaxClip);
    if (yMinClip > yMaxClip) std::swap(yMinClip, yMaxClip);
}

int ClipperCohenSutherland::calcularCodigoRegiao(const Ponto2D& p) const {
    int codigo = DENTRO;
    // Os pontos já estão em SCN (normalizados)
    // então p.obterX(), p.obterY() são as coordenadas SCN.

    if (p.obterX() < xMinClip) codigo |= ESQUERDA;
    else if (p.obterX() > xMaxClip) codigo |= DIREITA;

    if (p.obterY() < yMinClip) codigo |= BAIXO; // Assumindo que yMinClip é "mais baixo" que yMaxClip
    else if (p.obterY() > yMaxClip) codigo |= CIMA;

    return codigo;
}

bool ClipperCohenSutherland::cliparReta(Ponto2D& p1, Ponto2D& p2) {
    // p1 e p2 são pontos em SCN, já normalizados (W=1, exceto pontos no infinito)
    int codigo1 = calcularCodigoRegiao(p1);
    int codigo2 = calcularCodigoRegiao(p2);
    bool aceito = false;

    while (true) {
        if ((codigo1 == DENTRO) && (codigo2 == DENTRO)) { // Ambos dentro: aceitação trivial
            aceito = true;
            break;
        } else if ((codigo1 & codigo2) != 0) { // Ambos fora na mesma região: rejeição trivial
            break;
        } else { // Reta precisa ser clipada
            int codigoFora;
            double x = 0.0, y = 0.0; // Coordenadas do ponto de interseção

            // Pelo menos um ponto está fora. Escolhe ele.
            if (codigo1 != DENTRO) {
                codigoFora = codigo1;
            } else {
                codigoFora = codigo2;
            }

            // Encontra o ponto de interseção usando as equações da reta.
            // y = y1 + m * (x - x1)
            // x = x1 + (y - y1) / m
            // m = (p2.y - p1.y) / (p2.x - p1.x)

            double dx = p2.obterX() - p1.obterX();
            double dy = p2.obterY() - p1.obterY();

            if (codigoFora & CIMA) {           // Ponto acima da janela
                // Interseção com y = yMaxClip
                // x = x1 + (yMaxClip - y1) * dx / dy
                if (dy == 0) { x = p1.obterX() + dx; } // Linha horizontal, pode estar toda fora ou dentro verticalmente
                else { x = p1.obterX() + (yMaxClip - p1.obterY()) * dx / dy; }
                y = yMaxClip;
            } else if (codigoFora & BAIXO) { // Ponto abaixo da janela
                // Interseção com y = yMinClip
                // x = x1 + (yMinClip - y1) * dx / dy
                if (dy == 0) { x = p1.obterX() + dx; }
                else { x = p1.obterX() + (yMinClip - p1.obterY()) * dx / dy; }
                y = yMinClip;
            } else if (codigoFora & DIREITA) {  // Ponto à direita da janela
                // Interseção com x = xMaxClip
                // y = y1 + (xMaxClip - x1) * dy / dx
                if (dx == 0) { y = p1.obterY() + dy; } // Linha vertical
                else { y = p1.obterY() + (xMaxClip - p1.obterX()) * dy / dx; }
                x = xMaxClip;
            } else if (codigoFora & ESQUERDA) { // Ponto à esquerda da janela
                // Interseção com x = xMinClip
                // y = y1 + (xMinClip - x1) * dy / dx
                if (dx == 0) { y = p1.obterY() + dy; }
                else { y = p1.obterY() + (xMinClip - p1.obterX()) * dy / dx; }
                x = xMinClip;
            } else {
                // Situação inesperada, deve ter uma borda
                break;
            }


            // Atualiza o ponto que estava fora com o ponto de interseção.
            if (codigoFora == codigo1) {
                p1.definirX(x);
                p1.definirY(y);
                p1.definirW(1.0); // Pontos de interseção são afins
                codigo1 = calcularCodigoRegiao(p1);
            } else {
                p2.definirX(x);
                p2.definirY(y);
                p2.definirW(1.0);
                codigo2 = calcularCodigoRegiao(p2);
            }
        }
    }
    return aceito;
}
