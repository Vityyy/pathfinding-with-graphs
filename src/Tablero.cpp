#include "Tablero.hpp"

using namespace std;

Tablero::Tablero() {
    casillas = Grafo(MAXIMO_TAMANIO_TABLERO);
}

void Tablero::conectar_vertices(Matriz tablero) {
    for (size_t i = 0; i < TAMANIO_TABLERO; i++) {
        for (size_t j = 0; j < TAMANIO_TABLERO; j++) {
            if (tablero.elemento(i, j) != PARED) {
                // Comprobación derecha
                if (j < (TAMANIO_TABLERO - 1) && tablero.elemento(i, j + 1) != PARED) {
                    casillas.cambiar_arista(size_t(tablero.elemento(i, j)), size_t(tablero.elemento(i, j + 1)), 10);
                }

                // Comprobación izquierda
                if (j != 0 && tablero.elemento(i, j - 1) != PARED) {
                    casillas.cambiar_arista(size_t(tablero.elemento(i, j)), size_t(tablero.elemento(i, j - 1)), 10);
                }

                // Comprobación abajo
                if (i < (TAMANIO_TABLERO - 1) && tablero.elemento(i + 1, j) != PARED) {
                    casillas.cambiar_arista(size_t(tablero.elemento(i, j)), size_t(tablero.elemento(i + 1, j)), 10);
                }

                // Comprobación arriba
                if (i != 0 && tablero.elemento(i - 1, j) != PARED) {
                    casillas.cambiar_arista(size_t(tablero.elemento(i, j)), size_t(tablero.elemento(i - 1, j)), 10);
                }
            }
        }
    }
}

void Tablero::desconectar_casillas(std::size_t casilla1, std::size_t casilla2) {
    casillas.eliminar_arista(casilla1, casilla2);
}

std::pair<std::vector<std::size_t>, int> Tablero::camino_minimo(std::size_t origen, std::size_t destino) {
    casillas.usar_dijkstra();
    return casillas.obtener_camino_minimo(origen, destino);
}

void Tablero::modificar(Matriz tablero) {
    for (size_t i = 0; i < MAXIMO_TAMANIO_TABLERO - 1; i++) {
        casillas.eliminar_arista(i, i + 1);
    }
    conectar_vertices(tablero);
}