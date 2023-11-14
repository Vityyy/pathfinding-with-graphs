#include "InventarioDePrioridad.hpp"

InventarioDePrioridad::InventarioDePrioridad() = default;

void InventarioDePrioridad::alta(const Arma &nuevo_arma) {
    armas.alta(new Arma(nuevo_arma));
}

Arma InventarioDePrioridad::baja_arma_fuerte() {
    if (vacio()) {
        return ARMA_NO_VALIDA;
    }

    Arma arma_fuerte = *armas.primero();
    delete armas.baja();
    return arma_fuerte;
}

bool InventarioDePrioridad::vacio() {
    return armas.vacio();
}