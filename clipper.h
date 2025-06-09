#ifndef CLIPPER_3D_H
#define CLIPPER_3D_H

#include "ponto3d.h"

// Realiza o recorte de linhas 3D usando o algoritmo Cohen-Sutherland estendido.
class Clipper3D {
public:
    // Códigos de Região (Region Codes) para 3D (6 bits)
    static const int DENTRO = 0b000000;
    static const int ESQUERDA = 0b000001;
    static const int DIREITA  = 0b000010;
    static const int BAIXO    = 0b000100;
    static const int CIMA     = 0b001000;
    static const int TRAS     = 0b010000; // Plano de recorte Z Near (perto)
    static const int FRENTE   = 0b100000; // Plano de recorte Z Far (longe)

    // Construtor define o volume de recorte canônico por padrão.
    Clipper3D(double xMin = -1.0, double yMin = -1.0, double zMin = -1.0,
              double xMax = 1.0,  double yMax = 1.0,  double zMax = 1.0);

    // Recorta uma reta (segmento) definida por p1 e p2.
    // Retorna 'true' se alguma parte da reta estiver dentro do volume.
    // Os pontos p1 e p2 são modificados para conter o segmento recortado.
    bool cliparReta(Ponto3D& p1, Ponto3D& p2);

    // Calcula o código de região de 6 bits para um ponto 3D.
    int calcularCodigoRegiao(const Ponto3D& p) const;

private:
    // Limites do volume de recorte.
    double xMinClip, yMinClip, zMinClip;
    double xMaxClip, yMaxClip, zMaxClip;
};

#endif // CLIPPER_3D_H
