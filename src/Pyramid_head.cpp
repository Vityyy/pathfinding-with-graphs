#include "Pyramid_head.hpp"

using namespace std;

Pyramid_head::Pyramid_head(size_t fila, size_t columna, Matriz layout_actual) {
    set(fila, columna, layout_actual);
}

void Pyramid_head::set(size_t fila, size_t columna, Matriz layout_actual) {
    coordenada.fil() = fila;
    coordenada.col() = columna;

    // Comprobar arriba
    if (columna != 0 && layout_actual.elemento(columna - 1, fila) != Tablero::PARED) {
        casillas_adyacentes.emplace_back(columna - 1, fila);
    }

    // Comprobar izquierda
    if (fila != 0 && layout_actual.elemento(columna, fila - 1) != Tablero::PARED) {
        casillas_adyacentes.emplace_back(columna, fila - 1);
    }

    // Comprobar derecha
    if (fila < Tablero::TAMANIO_TABLERO - 1 && layout_actual.elemento(columna, fila + 1) != Tablero::PARED) {

        casillas_adyacentes.emplace_back(columna, fila + 1);
    }

    //Comprobar abajo
    if (columna < Tablero::TAMANIO_TABLERO - 1 && layout_actual.elemento(columna + 1, fila) != Tablero::PARED) {

        casillas_adyacentes.emplace_back(columna + 1, fila);
    }
}

CoordenadaMatriz Pyramid_head::posicion() const {
    return coordenada;
}

vector<CoordenadaMatriz> Pyramid_head::adyacentes() {
    return casillas_adyacentes;
}