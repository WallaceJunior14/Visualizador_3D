#include "viewport_tela.h"

ViewportTela::ViewportTela(int x, int y, int largura, int altura)
    : vpX(x), vpY(y), vpLargura(largura), vpAltura(altura) {
    if (largura <= 0 || altura <= 0) {
        //qWarning("ViewportTela: Largura e altura devem ser positivas.");
        // Definir um padrão seguro
        vpLargura = 1;
        vpAltura = 1;
    }
}

void ViewportTela::definirParametros(int x, int y, int largura, int altura) {
    vpX = x;
    vpY = y;
    if (largura > 0) vpLargura = largura;
    if (altura > 0) vpAltura = altura;
}

int ViewportTela::obterX() const {
    return vpX;
}

int ViewportTela::obterY() const {
    return vpY;
}

int ViewportTela::obterLargura() const {
    return vpLargura;
}

int ViewportTela::obterAltura() const {
    return vpAltura;
}

QRect ViewportTela::obterRect() const {
    return QRect(vpX, vpY, vpLargura, vpAltura);
}

Matriz ViewportTela::obterMatrizTransformacaoViewport() const {
    // Esta matriz transforma um ponto (xn, yn) do NDC [-1,1]x[-1,1]
    // para um ponto (xs, ys) na viewport da tela.
    // xs = (xn - ndc_x_min) / (ndc_x_max - ndc_x_min) * vp_largura + vp_x
    // ys = (yn - ndc_y_min) / (ndc_y_max - ndc_y_min) * vp_altura + vp_y

    // Considerando NDC [-1, 1] para x e y:
    // ndc_x_max - ndc_x_min = 2
    // ndc_y_max - ndc_y_min = 2

    // xs = (xn - (-1)) / 2 * vp_largura + vp_x = (xn + 1) * vp_largura / 2 + vp_x
    // ys = (yn - (-1)) / 2 * vp_altura + vp_y = (yn + 1) * vp_altura / 2 + vp_y (Se Y do NDC e tela crescem na mesma direção)

    // No Qt, o Y da tela cresce para BAIXO. Se o NDC tem Y crescendo para CIMA (-1 embaixo, 1 em cima):
    // Para mapear NDC Y para Tela Y:
    // NDC Y=-1 (baixo)  -> Tela Y = vp_y + vp_altura
    // NDC Y=1  (cima) -> Tela Y = vp_y
    // Portanto, ys = ( (1 - yn) / 2 ) * vp_altura + vp_y
    // ys = ( (ndcYMax - yn) / (ndcYMax - ndcYMin) ) * vp_altura + vp_y  (se ndcYMin < ndcYMax)

    Matriz Tvp = Matriz::identidade(3);

    // Escala para as dimensões da viewport e translada para a origem da viewport
    // Componente X:
    // Sx = vpLargura / (ndcXMax - ndcXMin)
    // Tx = vpX - ndcXMin * Sx
    Tvp(0,0) = static_cast<double>(vpLargura) / (ndcXMax - ndcXMin);
    Tvp(0,2) = static_cast<double>(vpX) - ndcXMin * Tvp(0,0);

    // Componente Y (com inversão, pois Y do Qt é para baixo):
    // Mapeia [ndcYMin, ndcYMax] para [vpY + vpAltura, vpY]
    // Sy = -vpAltura / (ndcYMax - ndcYMin)  (negativo para inverter)
    // Ty = vpY - ndcYMax * Sy
    // ou
    // Sy = vpAltura / (ndcYMin - ndcYMax) (se ndcYMin > ndcYMax, ou seja, Y invertido no NDC)
    // Ty = vpY - ndcYMin * Sy

    // Assumindo NDC Y de -1 (baixo) para 1 (cima)
    // e Tela Y de vpY (cima) para vpY + vpAltura (baixo)
    Tvp(1,1) = static_cast<double>(vpAltura) / (ndcYMin - ndcYMax); //  vpAltura / (-1.0 - 1.0) = vpAltura / -2.0
    Tvp(1,2) = static_cast<double>(vpY) - ndcYMax * Tvp(1,1);       //  vpY - 1.0 * (vpAltura / -2.0) = vpY + vpAltura / 2.0
    // Teste:
    // y_ndc = -1 (baixo): y_tela = (-1 * vpAltura/-2) + vpY + vpAltura/2 = vpAltura/2 + vpY + vpAltura/2 = vpY + vpAltura
    // y_ndc =  1 (cima): y_tela = ( 1 * vpAltura/-2) + vpY + vpAltura/2 = -vpAltura/2 + vpY + vpAltura/2 = vpY

    return Tvp;
}
