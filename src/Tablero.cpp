#include "Tablero.hpp"
#include <iostream>

using namespace std;

void Tablero::conectar_vertices(Matriz tablero) {
    for (size_t i = 0; i < TAMANIO_TABLERO; i++) {
        for (size_t j = 0; j < TAMANIO_TABLERO; j++) {
            size_t vertice = TAMANIO_TABLERO * i + j;

            if (tablero.elemento(i, j) != PARED) {
                // Comprobación derecha
                if (j < (TAMANIO_TABLERO - 1) && tablero.elemento(i, j + 1) != PARED) {
                    grafo_casillas.cambiar_arista(vertice, vertice + 1, 10);
                    grafo_casillas.cambiar_arista(vertice + 1, vertice, 10);
                }

                // Comprobación izquierda
                if (j != 0 && tablero.elemento(i, j - 1) != PARED) {
                    grafo_casillas.cambiar_arista(vertice, vertice - 1, 10);
                    grafo_casillas.cambiar_arista(vertice - 1, vertice, 10);
                }

                // Comprobación abajo
                if (i < (TAMANIO_TABLERO - 1) && tablero.elemento(i + 1, j) != PARED) {
                    grafo_casillas.cambiar_arista(vertice, vertice + TAMANIO_TABLERO, 10);
                    grafo_casillas.cambiar_arista(vertice + TAMANIO_TABLERO, vertice, 10);
                }

                // Comprobación arriba
                if (i != 0 && tablero.elemento(i - 1, j) != PARED) {
                    grafo_casillas.cambiar_arista(vertice, vertice - TAMANIO_TABLERO, 10);
                    grafo_casillas.cambiar_arista(vertice - TAMANIO_TABLERO, vertice, 10);
                }
            }
        }
    }
}

std::vector<std::string> Tablero::split(const string &linea, char separador) {
    vector<string> resultado;
    string palabra;
    for (char i: linea) {
        if (i != separador) {
            palabra += i;
        } else {
            resultado.push_back(palabra);
            palabra = "";
        }
    }
    resultado.push_back(palabra);
    return resultado;
}

void Tablero::descargar_nivel() {
    for (size_t i = 0; i < MAXIMO_TAMANIO_TABLERO; i++) {
        // Comprobación "derecha"
        if (i < MAXIMO_TAMANIO_TABLERO - 1) {
            grafo_casillas.eliminar_arista(i, i + 1);
            grafo_casillas.eliminar_arista(i + 1, i);
        }

        // Comprobación "izquierda"
        if (i != 0) {
            grafo_casillas.eliminar_arista(i, i - 1);
            grafo_casillas.eliminar_arista(i - 1, i);
        }

        // Comprobación "abajo"
        if (i < MAXIMO_TAMANIO_TABLERO - TAMANIO_TABLERO) {
            grafo_casillas.eliminar_arista(i, i + TAMANIO_TABLERO);
            grafo_casillas.eliminar_arista(i + TAMANIO_TABLERO, i);
        }

        // Comprobación "arriba"
        if (i >= TAMANIO_TABLERO) {
            grafo_casillas.eliminar_arista(i, i - TAMANIO_TABLERO);
            grafo_casillas.eliminar_arista(i - TAMANIO_TABLERO, i);
        }
    }
}

void Tablero::cargar_nivel(const std::string &nombre_archivo) {
    descargar_nivel();
    ifstream archivo_nivel("layouts/" + nombre_archivo + ".csv");

    if (!archivo_nivel.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    string linea;
    vector<string> linea_separada;

    size_t i = 0;
    while (getline(archivo_nivel, linea)) {
        linea_separada.clear();
        linea_separada = split(linea, ',');
        for (size_t j = 0; j < TAMANIO_TABLERO; j++) {
            casillas.elemento(i, j) = stoi(linea_separada[j]);
        }
        i++;
    }

    for (size_t j = 0; j < TAMANIO_TABLERO; j++) {
        for (size_t k = 0; k < TAMANIO_TABLERO; k++) {
            cout << casillas.elemento(j, k);
        }
        cout << endl;
    }

    conectar_vertices(casillas);
}

void Tablero::desconectar_casilla(CoordenadaMatriz casilla) {

    const size_t id_casilla = TAMANIO_TABLERO * casilla.fil() + casilla.col();

    // Desconectar "arriba""
    if (id_casilla > TAMANIO_TABLERO - 1) {
        grafo_casillas.eliminar_arista(id_casilla, id_casilla - TAMANIO_TABLERO);
        grafo_casillas.eliminar_arista(id_casilla - TAMANIO_TABLERO, id_casilla);
    }

    // Desconectar "abajo"
    if (id_casilla < MAXIMO_TAMANIO_TABLERO - TAMANIO_TABLERO) {
        grafo_casillas.eliminar_arista(id_casilla, id_casilla + TAMANIO_TABLERO);
        grafo_casillas.eliminar_arista(id_casilla + TAMANIO_TABLERO, id_casilla);
    }

    // Desconectar "izquierda"
    if (id_casilla > 0) {
        grafo_casillas.eliminar_arista(id_casilla, id_casilla - 1);
        grafo_casillas.eliminar_arista(id_casilla - 1, id_casilla);
    }

    // Desconectar "derecha"
    if (id_casilla < MAXIMO_TAMANIO_TABLERO - 1) {
        grafo_casillas.eliminar_arista(id_casilla, id_casilla + 1);
        grafo_casillas.eliminar_arista(id_casilla + 1, id_casilla);
    }
}

std::pair<std::vector<CoordenadaMatriz>, int>
Tablero::camino_minimo(CoordenadaMatriz origen, CoordenadaMatriz destino) {
    grafo_casillas.usar_dijkstra();
    std::pair<std::vector<size_t>, int> camino_minimo = grafo_casillas.obtener_camino_minimo(
            TAMANIO_TABLERO * origen.fil() + origen.col(),
            TAMANIO_TABLERO * destino.fil() + destino.col());

    std::pair<std::vector<CoordenadaMatriz>, std::size_t> coordenadas_camino_minimo;

    for (unsigned long i: camino_minimo.first) {
        coordenadas_camino_minimo.first.emplace_back((i - i % TAMANIO_TABLERO) / TAMANIO_TABLERO, i % TAMANIO_TABLERO);
    }

    return coordenadas_camino_minimo;
}

int Tablero::casilla(std::size_t fila, std::size_t columna) {
    return casillas.elemento(fila, columna);
}
