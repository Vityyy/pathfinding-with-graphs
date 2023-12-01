#ifndef TP3_GRUPO_NULLPTRS_JAMES_HPP
#define TP3_GRUPO_NULLPTRS_JAMES_HPP

#include "InventarioDePrioridad.hpp"

class James {
private:
    InventarioDePrioridad armas{};
    Arma arma_actual{};

public:
    James() = default;

    void equipar_arma_fuerte();

    void equipar_arma_debil();

    std::size_t cantidad_de_armas();

    bool tiene_arma_equipada();

    Arma arma_equipada();
};


#endif //TP3_GRUPO_NULLPTRS_JAMES_HPP
