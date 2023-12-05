#include "James.hpp"
#include <iostream>

using namespace std;

CoordenadaMatriz &James::posicion() {
    return coordenada;
}

void James::obtener_arma(const Arma &arma) {
    armas.alta(arma);
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
    } else {
        std::cout << "Ningun arma disponible/equipada." << endl;
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

void James::agregar_placa(Placa *placa) {
    placas.alta(placa);
}

std::size_t James::altura_placas() {
    return placas.altura();
}

James::~James() {
    delete arma_actual;
    arma_actual = nullptr;
}

bool James::tiene_placa(Placa *placa) {
    return placas.consulta(placa);
}
