#include "Floyd.hpp"

Floyd::Floyd() {}

void Floyd::inicializar_matrices() {
    matriz_caminos = Matriz(cantidad_vertices);
    for (size_t i = 0; i < cantidad_vertices; i++) {
        for (size_t j = 0; j < cantidad_vertices; j++) {
            matriz_caminos.elemento(i, j) = (int) j;
        }
    }

    matriz_costos = matriz_adyacencia;
}

std::vector<size_t> Floyd::obtener_camino(size_t origen, size_t destino) {
    std::vector<size_t> camino;

    bool terminado = false;
    size_t actual = origen;

    while (!terminado) {
        actual = size_t(matriz_caminos.elemento(actual, destino));
        camino.push_back(actual);

        if (size_t(matriz_caminos.elemento(actual, destino)) == destino) {
            terminado = true;
            camino.insert(camino.begin(), origen);
            camino.push_back(destino);
        }
    }

    return camino;
}

std::vector<size_t>
Floyd::calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino, bool hay_cambios) {
    if (hay_cambios) {
        matriz_adyacencia = adyacencia;
        cantidad_vertices = vertices;
        inicializar_matrices();

        for (size_t k = 0; k < cantidad_vertices; k++) {
            for (size_t i = 0; i < cantidad_vertices; i++) {
                for (size_t j = 0; j < cantidad_vertices; j++) {
                    if (matriz_costos.elemento(i, j) > matriz_costos.elemento(i, k) + matriz_costos.elemento(k, j)) {
                        matriz_costos.elemento(i, j) = matriz_costos.elemento(i, k) + matriz_costos.elemento(k, j);
                        matriz_caminos.elemento(i, j) = matriz_caminos.elemento(i, k);
                    }
                }
            }
        }
    }

    return obtener_camino(origen, destino);
}

Floyd::~Floyd() {}