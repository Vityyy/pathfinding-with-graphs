#include "James.hpp"
#include <iostream>

using namespace std;

CoordenadaMatriz &James::posicion() {
    return coordenada;
}

void James::equipar_arma_fuerte() {
    if (armas.vacio()) {
        cout << "No hay armas en el inventario" << endl;

    } else if (tiene_arma_equipada()) {
        cout << "Ya hay un arma equipada" << endl;

    } else {
        arma_actual = new Arma(armas.baja_arma_fuerte());
    }
}

void James::equipar_arma_debil() {
    if (armas.vacio()) {
        cout << "No hay armas en el inventario" << endl;

    } else if (tiene_arma_equipada()) {
        cout << "Ya hay un arma equipada" << endl;

    } else {
        arma_actual = new Arma(armas.baja_arma_debil());
    }
}

void James::desequipar_arma() {
    delete arma_actual;
    arma_actual = nullptr;
}
