#include "bounding_box.h"
#include <limits>   // Para std::numeric_limits
#include <algorithm> // Para std::min e std::max

// Construtor padrão: inicializa com valores "infinitos" invertidos.
// Qualquer ponto adicionado irá imediatamente definir a caixa.
BoundingBox::BoundingBox() {
    double max_val = std::numeric_limits<double>::max();
    double min_val = std::numeric_limits<double>::lowest(); // O menor valor possível

    m_min = Ponto3D(max_val, max_val, max_val);
    m_max = Ponto3D(min_val, min_val, min_val);
}

// Construtor para um único ponto: a caixa é o próprio ponto.
BoundingBox::BoundingBox(const Ponto3D& ponto)
    : m_min(ponto), m_max(ponto) {}

// Construtor a partir de dois pontos: calcula o min/max para cada coordenada.
BoundingBox::BoundingBox(const Ponto3D& p1, const Ponto3D& p2) {
    m_min = Ponto3D(std::min(p1.obterX(), p2.obterX()),
                    std::min(p1.obterY(), p2.obterY()),
                    std::min(p1.obterZ(), p2.obterZ()));
    m_max = Ponto3D(std::max(p1.obterX(), p2.obterX()),
                    std::max(p1.obterY(), p2.obterY()),
                    std::max(p1.obterZ(), p2.obterZ()));
}

// Expande a caixa para incluir um novo ponto.
void BoundingBox::expandir(const Ponto3D& ponto) {
    m_min.definirX(std::min(m_min.obterX(), ponto.obterX()));
    m_min.definirY(std::min(m_min.obterY(), ponto.obterY()));
    m_min.definirZ(std::min(m_min.obterZ(), ponto.obterZ()));

    m_max.definirX(std::max(m_max.obterX(), ponto.obterX()));
    m_max.definirY(std::max(m_max.obterY(), ponto.obterY()));
    m_max.definirZ(std::max(m_max.obterZ(), ponto.obterZ()));
}

// Expande a caixa para incluir outra caixa (união).
void BoundingBox::expandir(const BoundingBox& outraBBox) {
    if (outraBBox.ehValida()) {
        expandir(outraBBox.m_min);
        expandir(outraBBox.m_max);
    }
}

// Calcula o centro da caixa.
Ponto3D BoundingBox::obterCentro() const {
    return (m_min + m_max) / 2.0;
}

Ponto3D BoundingBox::obterMin() const {
    return m_min;
}

Ponto3D BoundingBox::obterMax() const {
    return m_max;
}

// Uma caixa é válida se min <= max em todos os eixos.
bool BoundingBox::ehValida() const {
    return (m_min.obterX() <= m_max.obterX() &&
            m_min.obterY() <= m_max.obterY() &&
            m_min.obterZ() <= m_max.obterZ());
}
