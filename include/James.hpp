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
    James() = default;

    CoordenadaMatriz &posicion();

    void equipar_arma_fuerte();

    void equipar_arma_debil();

    void desequipar_arma();

    std::size_t cantidad_de_armas();

    bool tiene_arma_equipada();

    void perder_arma_equipada();

    ~James();
};

#endif //TP3_GRUPO_NULLPTRS_JAMES_HPP
