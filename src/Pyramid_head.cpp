#include "Pyramid_head.hpp"

#include <utility>

using namespace std;

Pyramid_head::Pyramid_head(CoordenadaMatriz coordenada, Tablero tablero_de_juego) {
    this->coordenada.fil() = coordenada.fil();
    this->coordenada.col() = coordenada.col();

    // Comprobar arriba
    if (coordenada.fil() > 0 && tablero_de_juego.casilla(coordenada.fil() - 1, coordenada.col()) != Tablero::PARED) {
        casillas_adyacentes.emplace_back(coordenada.fil() - 1, coordenada.col());
    }

    // Comprobar izquierda
    if (coordenada.col() < Tablero::TAMANIO_TABLERO - 1 &&
        tablero_de_juego.casilla(coordenada.fil(), coordenada.col() + 1) != Tablero::PARED) {

        casillas_adyacentes.emplace_back(coordenada.fil(), coordenada.col() + 1);
    }

    // Comprobar derecha
    if (coordenada.col() > 0 && tablero_de_juego.casilla(coordenada.fil(), coordenada.col() - 1) != Tablero::PARED) {
        casillas_adyacentes.emplace_back(coordenada.fil(), coordenada.col() + 1);
    }

    //Comprobar abajo
    if (coordenada.fil() < Tablero::TAMANIO_TABLERO - 1 &&
        tablero_de_juego.casilla(coordenada.fil() + 1, coordenada.col()) != Tablero::PARED) {

        casillas_adyacentes.emplace_back(coordenada.fil() + 1, coordenada.col());
    }
}

CoordenadaMatriz Pyramid_head::posicion() const {
    return coordenada;
}

vector<CoordenadaMatriz> Pyramid_head::adyacentes() {
    return casillas_adyacentes;
}