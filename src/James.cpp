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
    if (tiene_arma_equipada()) {
        armas.alta(*arma_actual);
        delete arma_actual;
        arma_actual = nullptr;
    }
}

std::size_t James::cantidad_de_armas() {
    return armas.cantidad_armas();
}

bool James::tiene_arma_equipada() {
    return arma_actual;
}

void James::perder_arma_equipada() {
    delete arma_actual;
    arma_actual = nullptr;
}

James::~James() {
    delete arma_actual;
    arma_actual = nullptr;
}
