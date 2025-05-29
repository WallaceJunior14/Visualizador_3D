#ifndef PONTO_OBJ_H
#define PONTO_OBJ_H

#include "objeto_grafico.h"

// Representa um objeto gráfico do tipo Ponto.
// Um ponto é definido por uma única coordenada no mundo.
class PontoObj : public ObjetoGrafico {
public:
    // Construtor: nome e coordenada do ponto.
    PontoObj(const QString& nome, const Ponto2D& coordenada, const QColor& corPonto = Qt::black);

    // Sobrescreve o cálculo do centro geométrico (é o próprio ponto).
    Ponto2D calcularCentroGeometrico() const override;

    // Define a coordenada do ponto. Isto irá limpar quaisquer pontos anteriores
    // e adicionar o novo ponto à lista de pontosOriginaisMundo.
    void definirCoordenada(const Ponto2D& coordenada);
    Ponto2D obterCoordenada() const; // Retorna a primeira (e única) coordenada original.
};

#endif // PONTO_OBJ_H
