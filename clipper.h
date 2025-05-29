#ifndef CLIPPER_COHEN_SUTHERLAND_H
#define CLIPPER_COHEN_SUTHERLAND_H

#include "ponto2d.h"
#include <QLineF>
#include <QRectF>

class ClipperCohenSutherland {
public:
    // RC: Regions Codes
    static const int DENTRO = 0; // 0000
    static const int ESQUERDA = 1; // 0001
    static const int DIREITA = 2; // 0010
    static const int BAIXO = 4; // 0100
    static const int CIMA = 8;   // 1000

    ClipperCohenSutherland(double xMinNDC = -1.0, double yMinNDC = -1.0,
                           double xMaxNDC = 1.0, double yMaxNDC = 1.0);

    bool cliparReta(Ponto2D& p1, Ponto2D& p2);
    int calcularCodigoRegiao(const Ponto2D& p) const;

private:
    double xMinClip, yMinClip, xMaxClip, yMaxClip;
};

#endif // CLIPPER_COHEN_SUTHERLAND_H
