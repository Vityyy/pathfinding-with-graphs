#include "CoordenadaMatriz.hpp"

CoordenadaMatriz::CoordenadaMatriz(std::size_t fila, std::size_t columna) {
    this->fila = fila;
    this->columna = columna;
}

std::size_t &CoordenadaMatriz::fil() {
    return fila;
}

std::size_t &CoordenadaMatriz::col() {
    return columna;
}
