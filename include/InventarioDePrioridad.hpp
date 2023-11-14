#ifndef INVENTARIO_DE_PRIORIDAD_HPP
#define INVENTARIO_DE_PRIORIDAD_HPP

#include "Heap.hpp"
#include "Arma.hpp"
#include <vector>

class InventarioDePrioridad {
private:
    Heap<Arma *, Arma::mayor> armas;

    const Arma ARMA_NO_VALIDA = Arma("\n", 0);

public:

    // Constructor
    InventarioDePrioridad();

    // Pre: ~
    // Pos: agrega un arma al inventario
    void alta(const Arma &nuevo_arma);

    // Pre: ~
    // Pos: retorna el arma más fuerte, si el inventario está vacío retorna un arma no válida
    Arma baja_arma_fuerte();

    // Pre: ~
    // Pos: retorna el arma más debil, si el inventario está vacío retorna un arma no válida
    Arma baja_arma_debil();

    // Pre: ~
    // Pos: retorna true si el inventario está vacío
    bool vacio();

    // Destructor
    ~InventarioDePrioridad();
};

#endif //INVENTARIO_DE_PRIORIDAD_HPP