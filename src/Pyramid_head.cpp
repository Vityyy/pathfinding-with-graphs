#include "Pyramid_head.hpp"

#include <utility>

using namespace std;

Pyramid_head::Pyramid_head(size_t fila, size_t columna, Tablero tablero_de_juego) {
    set(fila, columna, std::move(tablero_de_juego));
}

void Pyramid_head::set(size_t fila, size_t columna, Tablero tablero_de_juego) {
    coordenada.fil() = fila;
    coordenada.col() = columna;

    // Comprobar arriba
    if (columna != 0 && tablero_de_juego.casilla(columna - 1, fila) != Tablero::PARED) {
        casillas_adyacentes.emplace_back(columna - 1, fila);
    }

    // Comprobar izquierda
    if (fila != 0 && tablero_de_juego.casilla(columna, fila - 1) != Tablero::PARED) {
        casillas_adyacentes.emplace_back(columna, fila - 1);
    }

    // Comprobar derecha
    if (fila < Tablero::TAMANIO_TABLERO - 1 && tablero_de_juego.casilla(columna, fila + 1) != Tablero::PARED) {
        casillas_adyacentes.emplace_back(columna, fila + 1);
    }

    //Comprobar abajo
    if (columna < Tablero::TAMANIO_TABLERO - 1 && tablero_de_juego.casilla(columna + 1, fila) != Tablero::PARED) {
        casillas_adyacentes.emplace_back(columna + 1, fila);
    }
}

CoordenadaMatriz Pyramid_head::posicion() const {
    return coordenada;
}

vector<CoordenadaMatriz> Pyramid_head::adyacentes() {
    return casillas_adyacentes;
}