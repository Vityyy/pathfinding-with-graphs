#ifndef INVENTARIO_DE_PRIORIDAD_HPP
#define INVENTARIO_DE_PRIORIDAD_HPP

#include "Heap.hpp"
#include "Arma.hpp"
#include <vector>

class Inventario_de_prioridad {
private:
    Heap<Arma *, Arma::mayor> armas;

public:

    // Constructor
    Inventario_de_prioridad();

    // Pre: ~
    // Pos: agrega un arma al inventario
    void alta(const Arma &nuevo_arma);

    // Pre: ~
    // Pos: retorna el arma más fuerte, si el inventario está vacío retorna nullptr
    Arma *baja_arma_fuerte();

    // Pre: ~
    // Pos: retorna el arma más debil, si el inventario está vacío retorna nullptr
    Arma *baja_arma_debil();

    // Destructor
    ~Inventario_de_prioridad();
};

#endif //INVENTARIO_DE_PRIORIDAD_HPP