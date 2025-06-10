#include "clipper.h"
#include <algorithm> // Para std::swap

Clipper3D::Clipper3D(double xMin, double yMin, double zMin, double xMax, double yMax, double zMax)
    : xMinClip(xMin), yMinClip(yMin), zMinClip(zMin),
    xMaxClip(xMax), yMaxClip(yMax), zMaxClip(zMax) {
    // Garante que min < max para todos os eixos
    if (xMinClip > xMaxClip) std::swap(xMinClip, xMaxClip);
    if (yMinClip > yMaxClip) std::swap(yMinClip, yMaxClip);
    if (zMinClip > zMaxClip) std::swap(zMinClip, zMaxClip);
}

int Clipper3D::calcularCodigoRegiao(const Ponto3D& p) const {
    int codigo = DENTRO;
    // Os pontos vêm do pipeline MVP e já estão normalizados (NDC)
    if (p.obterX() < xMinClip) codigo |= ESQUERDA;
    else if (p.obterX() > xMaxClip) codigo |= DIREITA;

    if (p.obterY() < yMinClip) codigo |= BAIXO;
    else if (p.obterY() > yMaxClip) codigo |= CIMA;

    if (p.obterZ() < zMinClip) codigo |= TRAS;
    else if (p.obterZ() > zMaxClip) codigo |= FRENTE;

    return codigo;
}

bool Clipper3D::cliparReta(Ponto3D& p1, Ponto3D& p2) {
    int codigo1 = calcularCodigoRegiao(p1);
    int codigo2 = calcularCodigoRegiao(p2);
    bool aceito = false;

    while (true) {
        if ((codigo1 == DENTRO) && (codigo2 == DENTRO)) { // Aceitação trivial
            aceito = true;
            break;
        } else if ((codigo1 & codigo2) != 0) { // Rejeição trivial
            break;
        } else { // Reta precisa ser recortada
            int codigoFora;
            double x = 0.0, y = 0.0, z = 0.0;

            // Escolhe um ponto que está fora do volume
            codigoFora = (codigo1 != DENTRO) ? codigo1 : codigo2;

            double dx = p2.obterX() - p1.obterX();
            double dy = p2.obterY() - p1.obterY();
            double dz = p2.obterZ() - p1.obterZ();

            // Calcula a interseção da reta com o plano de recorte correspondente
            if (codigoFora & FRENTE) {
                if (dz != 0.0) { // <-- VERIFICAÇÃO
                    x = p1.obterX() + dx * (zMaxClip - p1.obterZ()) / dz;
                    y = p1.obterY() + dy * (zMaxClip - p1.obterZ()) / dz;
                }
                z = zMaxClip;
            } else if (codigoFora & TRAS) {
                if (dz != 0.0) { // <-- VERIFICAÇÃO
                    x = p1.obterX() + dx * (zMinClip - p1.obterZ()) / dz;
                    y = p1.obterY() + dy * (zMinClip - p1.obterZ()) / dz;
                }
                z = zMinClip;
            } else if (codigoFora & CIMA) {
                if (dy != 0.0) { // <-- VERIFICAÇÃO
                    x = p1.obterX() + dx * (yMaxClip - p1.obterY()) / dy;
                    z = p1.obterZ() + dz * (yMaxClip - p1.obterY()) / dy;
                }
                y = yMaxClip;
            } else if (codigoFora & BAIXO) {
                if (dy != 0.0) { // <-- VERIFICAÇÃO
                    x = p1.obterX() + dx * (yMinClip - p1.obterY()) / dy;
                    z = p1.obterZ() + dz * (yMinClip - p1.obterY()) / dy;
                }
                y = yMinClip;
            } else if (codigoFora & DIREITA) {
                if (dx != 0.0) { // <-- VERIFICAÇÃO
                    y = p1.obterY() + dy * (xMaxClip - p1.obterX()) / dx;
                    z = p1.obterZ() + dz * (xMaxClip - p1.obterX()) / dx;
                }
                x = xMaxClip;
            } else if (codigoFora & ESQUERDA) {
                if (dx != 0.0) { // <-- VERIFICAÇÃO
                    y = p1.obterY() + dy * (xMinClip - p1.obterX()) / dx;
                    z = p1.obterZ() + dz * (xMinClip - p1.obterX()) / dx;
                }
                x = xMinClip;
            } else {
                // Situação inesperada
                break;
            }

            // Atualiza o ponto que estava fora com o novo ponto de interseção
            // e recalcula seu código de região para o próximo loop.
            if (codigoFora == codigo1) {
                p1.definirX(x); p1.definirY(y); p1.definirZ(z);
                codigo1 = calcularCodigoRegiao(p1);
            } else {
                p2.definirX(x); p2.definirY(y); p2.definirZ(z);
                codigo2 = calcularCodigoRegiao(p2);
            }
        }
    }
    return aceito;
}
