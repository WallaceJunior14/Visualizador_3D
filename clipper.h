#ifndef CLIPPER_COHEN_SUTHERLAND_H
#define CLIPPER_COHEN_SUTHERLAND_H

#include "ponto2d.h"
#include <QLineF>
#include <QRectF>

class ClipperCohenSutherland {
public: // <<--- Mova para cá ou certifique-se que estão aqui
    // Códigos de região (outcodes)
    static const int DENTRO = 0; // 0000
    static const int ESQUERDA = 1; // 0001
    static const int DIREITA = 2; // 0010
    static const int BAIXO = 4; // 0100
    static const int CIMA = 8;   // 1000

    ClipperCohenSutherland(double xMinNDC = -1.0, double yMinNDC = -1.0,
                           double xMaxNDC = 1.0, double yMaxNDC = 1.0);

    bool cliparReta(Ponto2D& p1, Ponto2D& p2);
    int calcularCodigoRegiao(const Ponto2D& p) const; // Manter público se usado externamente

private:
    // (Remova os códigos de região daqui se os moveu para public)
    // static const int DENTRO = 0;
    // static const int ESQUERDA = 1;
    // static const int DIREITA = 2;
    // static const int BAIXO = 4;
    // static const int CIMA = 8;

    double xMinClip, yMinClip, xMaxClip, yMaxClip;
    // calcularCodigoRegiao era privado antes, se FrameDesenho precisa chamá-lo diretamente,
    // ele também precisa ser público, o que já foi feito na sua versão anterior do FrameDesenho.
};

#endif // CLIPPER_COHEN_SUTHERLAND_H
