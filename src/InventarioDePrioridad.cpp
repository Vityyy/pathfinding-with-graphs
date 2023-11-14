#include "InventarioDePrioridad.hpp"

InventarioDePrioridad::InventarioDePrioridad() = default;

void InventarioDePrioridad::alta(const Arma &nuevo_arma) {
    armas.alta(new Arma(nuevo_arma));
}