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

Arma InventarioDePrioridad::baja_arma_debil() {
    if (vacio()) {
        return ARMA_NO_VALIDA;
    }

    Heap<Arma *, Arma::menor> armas_aux;

    while (!armas.vacio()) {
        armas_aux.alta(armas.baja());
    }

    Arma arma_debil = *armas_aux.primero();
    delete armas_aux.baja();

    while (!armas_aux.vacio()) {
        armas.alta(armas_aux.baja());
    }

    return arma_debil;
}

Arma InventarioDePrioridad::consulta_arma_fuerte() {
    if (vacio()) {
        return ARMA_NO_VALIDA;
    }

    return *armas.primero();
}

Arma InventarioDePrioridad::consulta_arma_debil() {
    if (vacio()) {
        return ARMA_NO_VALIDA;
    }

    Heap<Arma *, Arma::menor> armas_aux;

    while (!armas.vacio()) {
        armas_aux.alta(armas.baja());
    }

    Arma arma_debil = *armas_aux.primero();

    while (!armas_aux.vacio()) {
        armas.alta(armas_aux.baja());
    }

    return arma_debil;
}

bool InventarioDePrioridad::vacio() {
    return armas.vacio();
}

size_t InventarioDePrioridad::cantidad_armas() {
    return armas.tamanio();
}

InventarioDePrioridad::~InventarioDePrioridad() {
    while (!armas.vacio()) {
        delete armas.baja();
    }
}