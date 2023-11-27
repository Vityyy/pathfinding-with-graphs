#include "Pyramid_head.hpp"

using namespace std;

Pyramid_head::Pyramid_head(size_t coordenada_x, size_t coordenada_y, Matriz layout_actual) {
    set(coordenada_x, coordenada_y, layout_actual);
}

void Pyramid_head::set(size_t nueva_coordenada_x, size_t nueva_coordenada_y, Matriz layout_actual) {
    coordenada_x = nueva_coordenada_x;
    coordenada_y = nueva_coordenada_y;
    localizacion = size_t(layout_actual.elemento(nueva_coordenada_y, nueva_coordenada_x));

    // Comprobar arriba
    if (nueva_coordenada_y != 0 &&
        layout_actual.elemento(nueva_coordenada_y - 1, nueva_coordenada_x) != Tablero::PARED) {
        casillas_adyacentes.push_back(size_t(layout_actual.elemento(nueva_coordenada_y - 1, nueva_coordenada_x)));
    }

    // Comprobar izquierda
    if (nueva_coordenada_x != 0 &&
        layout_actual.elemento(nueva_coordenada_y, nueva_coordenada_x - 1) != Tablero::PARED) {
        casillas_adyacentes.push_back(size_t(layout_actual.elemento(nueva_coordenada_y, nueva_coordenada_x - 1)));
    }

    // Comprobar derecha
    if (nueva_coordenada_x < Tablero::TAMANIO_TABLERO - 1 &&
        layout_actual.elemento(nueva_coordenada_y, nueva_coordenada_x + 1) != Tablero::PARED) {

        casillas_adyacentes.push_back(size_t(layout_actual.elemento(nueva_coordenada_y, nueva_coordenada_x + 1)));
    }

    //Comprobar abajo
    if (nueva_coordenada_y < Tablero::TAMANIO_TABLERO - 1 &&
        layout_actual.elemento(nueva_coordenada_y + 1, nueva_coordenada_x) != Tablero::PARED) {

        casillas_adyacentes.push_back(size_t(layout_actual.elemento(nueva_coordenada_y + 1, nueva_coordenada_x)));
    }
}

size_t Pyramid_head::posicion() const {
    return localizacion;
}

size_t Pyramid_head::x() const {
    return coordenada_x;
}

size_t Pyramid_head::y() const {
    return coordenada_y;
}

vector<size_t> Pyramid_head::adyacentes() {
    return casillas_adyacentes;
}