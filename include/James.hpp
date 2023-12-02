#ifndef TP3_GRUPO_NULLPTRS_JAMES_HPP
#define TP3_GRUPO_NULLPTRS_JAMES_HPP

#include "InventarioDePrioridad.hpp"
#include "CoordenadaMatriz.hpp"

class James {
private:

    CoordenadaMatriz coordenada{8, 0};
    InventarioDePrioridad armas{};
    Arma *arma_actual = nullptr;

public:
    // Constructor default
    James() = default;

    // Pre: ~
    // Pos: devuelve la coordenada
    CoordenadaMatriz &posicion();

    // Pre: ~
    // Pos: equipa el arma más fuerte
    void equipar_arma_fuerte();

    // Pre: ~
    // Pos: equipa el arma más débil
    void equipar_arma_debil();

    // Pre: ~
    // Pos: desequipa el arma actual
    void desequipar_arma();

    // Pre: ~
    // Pos: devuelve la cantidad de armas que tiene james
    std::size_t cantidad_de_armas();

    // Pre: ~
    // Pos: devuelve true si tiene un arma equipada
    bool tiene_arma_equipada();

    // Pre: ~
    // Pos: pierde el arma equipada
    void perder_arma_equipada();

    // Destructor
    // Pre: ~
    // Pos: libera la memoria de arma_actual
    ~James();
};

#endif //TP3_GRUPO_NULLPTRS_JAMES_HPP
