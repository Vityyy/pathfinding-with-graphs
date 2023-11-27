#include "Juego.hpp"
#include "Dijkstra.hpp"
#include <iostream>

using namespace std;

int const Juego::layout_1[Tablero::TAMANIO_TABLERO][Tablero::TAMANIO_TABLERO] = {
        {0,  -1, 1,  -1, 2,  -1, 3,  -1, 4},
        {5,  -1, 6,  7,  8,  -1, 9,  -1, 10},
        {11, -1, 12, -1, 13, -1, 14, 15, 16},
        {17, 18, 19, -1, 20, -1, 21, -1, 22},
        {23, -1, 24, -1, 25, 26, 27, -1, 28},
        {29, -1, 30, 31, 32, -1, 33, -1, 34},
        {35, -1, 36, -1, 37, -1, 38, -1, 39},
        {40, 41, 42, -1, 43, -1, 44, -1, 45},
        {46, 47, 48, -1, 49, 50, 51, 52, 53}
};

int const Juego::layout_2[Tablero::TAMANIO_TABLERO][Tablero::TAMANIO_TABLERO] = {
        {0,  1,  2,  3,  4,  5,  6,  7,  8},
        {9,  -1, -1, -1, -1, 1,  10, -1, 11},
        {12, 13, 14, 15, 16, 17, 18, -1, 19},
        {-1, -1, 20, -1, -1, -1, 21, 22, 23},
        {24, 25, 26, 27, 28, 29, 30, -1, 31},
        {32, -1, -1, -1, 33, -1, 34, -1, 35},
        {36, 37, 38, 39, 40, -1, 41, 42, 43},
        {44, -1, 45, -1, 46, -1, 47, -1, -1},
        {48, 49, 50, -1, 51, 52, 53, 54, 55}
};

InventarioDePrioridad Juego::inventario = InventarioDePrioridad();

Matriz Juego::layout_actual = Matriz();

Tablero Juego::tablero_de_juego = Tablero();

Arma *Juego::arma_actual = nullptr;

vector<Pyramid_head> Juego::pyramid_heads = std::vector<Pyramid_head>{};

bool Juego::hay_pyramid_head(size_t casilla) {
    return pyramid_heads[0].posicion() == casilla || pyramid_heads[1].posicion() == casilla;
}

bool Juego::es_adyacente_a_pyramid_head(size_t casilla) {
    size_t iterador_pyramid_heads = 0;
    size_t iterador_adyacentes = 0;
    bool es_adyacente = false;

    while (!es_adyacente && iterador_pyramid_heads < pyramid_heads.size()) {
        while (!es_adyacente && iterador_adyacentes < pyramid_heads[iterador_pyramid_heads].adyacentes().size()) {
            es_adyacente = (pyramid_heads[iterador_pyramid_heads].adyacentes()[iterador_adyacentes] == casilla);
            iterador_adyacentes++;
        }

        iterador_pyramid_heads++;
    }

    return es_adyacente;
}

pair<size_t, size_t> Juego::ubicacion_en_matriz(int casilla) {
    bool encontrado = false;
    size_t i = 0, j = 0;
    pair<size_t, size_t> ubicacion = {0, 0};
    while (!encontrado && i < Tablero::TAMANIO_TABLERO) {
        while (!encontrado && j < Tablero::TAMANIO_TABLERO) {
            if (casilla == layout_actual.elemento(i, j)) {
                encontrado = true;
                ubicacion.first = j;
                ubicacion.second = i;
            }
            j++;
        }
        j = 0;
        i++;
    }

    return ubicacion;
}

vector<size_t> Juego::calcular_camino_minimo(size_t origen, size_t destino) {
    Tablero tablero_actual = tablero_de_juego;
    bool tiene_arma = arma_actual;
    pair<vector<size_t>, int> mejor_camino_minimo;
    mejor_camino_minimo.second = INFINITO;

    size_t indice_ultima_casilla_adyacente;

    pair<vector<size_t>, int> camino_minimo;

    bool hay_pyramid_head_en_casilla = false;
    bool es_adyacente = false;
    bool pasa_por_adyacente = false;
    bool hubo_cambios = false;

    size_t iterador_casillas = 0;

    bool camino_encontrado = false;
    while (!camino_encontrado) {
        camino_minimo = tablero_actual.camino_minimo(origen, destino);
        tiene_arma = arma_actual;
        hay_pyramid_head_en_casilla = false;
        es_adyacente = false;
        hubo_cambios = false;
        pasa_por_adyacente = false;

        while (iterador_casillas < camino_minimo.first.size() && !hay_pyramid_head_en_casilla) {
            hay_pyramid_head_en_casilla = hay_pyramid_head(camino_minimo.first[iterador_casillas]);
            if (hay_pyramid_head_en_casilla) {
                if (!tiene_arma) {
                    desconectar_casilla(tablero_actual, camino_minimo.first[iterador_casillas]);
                } else {
                    tiene_arma = false;
                    hay_pyramid_head_en_casilla = false;
                }
            } else {
                es_adyacente = es_adyacente_a_pyramid_head(camino_minimo.first[iterador_casillas]);
                if (es_adyacente) {
                    if (!tiene_arma) {
                        camino_minimo.second += 40;
                        indice_ultima_casilla_adyacente = iterador_casillas;
                    }
                    pasa_por_adyacente = true;
                }
            }
            iterador_casillas++;
        }

        if (pasa_por_adyacente) {
            desconectar_casilla(tablero_actual, camino_minimo.first[indice_ultima_casilla_adyacente]);
        }

        if (!hay_pyramid_head_en_casilla && camino_minimo.second < mejor_camino_minimo.second) {
            mejor_camino_minimo = camino_minimo;
            hubo_cambios = true;
        }

        if (!hay_pyramid_head_en_casilla && camino_minimo.second >= mejor_camino_minimo.second && !hubo_cambios) {
            camino_encontrado = true;
        }
    }

    return ((mejor_camino_minimo.second != INFINITO) ? (mejor_camino_minimo.first) : (vector<size_t>()));
}

void Juego::desconectar_casilla(Tablero &tablero, std::size_t casilla) {
    pair<size_t, size_t> posicion_en_matrix = ubicacion_en_matriz(int(casilla));

    //@formatter:off
    // Desconectar abajo
    if (posicion_en_matrix.second < Tablero::TAMANIO_TABLERO - 1 && layout_actual.elemento(posicion_en_matrix.second + 1, posicion_en_matrix.first) > 0) {

        tablero.desconectar_casillas(casilla, size_t(layout_actual.elemento(posicion_en_matrix.second + 1, posicion_en_matrix.first)));
        tablero.desconectar_casillas(size_t(layout_actual.elemento(posicion_en_matrix.second + 1, posicion_en_matrix.first)), casilla);
    }

    // Desconectar derecha
    if (posicion_en_matrix.first < Tablero::TAMANIO_TABLERO - 1 && layout_actual.elemento(posicion_en_matrix.second, posicion_en_matrix.first + 1) > 0) {

        tablero.desconectar_casillas(casilla, size_t(layout_actual.elemento(posicion_en_matrix.second, posicion_en_matrix.first + 1)));
        tablero.desconectar_casillas(size_t(layout_actual.elemento(posicion_en_matrix.second, posicion_en_matrix.first + 1)), casilla);
    }

    // Desconectar arriba
    if (posicion_en_matrix.second > 0 && layout_actual.elemento(posicion_en_matrix.second - 1, posicion_en_matrix.first) > 0) {

        tablero.desconectar_casillas(casilla, size_t(layout_actual.elemento(posicion_en_matrix.second - 1, posicion_en_matrix.first)));
        tablero.desconectar_casillas(size_t(layout_actual.elemento(posicion_en_matrix.second - 1, posicion_en_matrix.first)), casilla);
    }

    // Desconectar izquierda
    if (posicion_en_matrix.first > 0 && layout_actual.elemento(posicion_en_matrix.second, posicion_en_matrix.first - 1) > 0) {

        tablero.desconectar_casillas(casilla, size_t(layout_actual.elemento(posicion_en_matrix.second, posicion_en_matrix.first - 1)));
        tablero.desconectar_casillas(size_t(layout_actual.elemento(posicion_en_matrix.second, posicion_en_matrix.first - 1)), casilla);
    }
    //@formatter:on
}

void Juego::ejecutar() {
    for (int _ = 0; _ < Tablero::TAMANIO_TABLERO; _++) {
        layout_actual.expandir();
    }

    cargar_nivel(layout_1);
    tablero_de_juego.modificar(layout_actual);
    pyramid_heads.emplace_back(3, 5, layout_actual);
    pyramid_heads.emplace_back(8, 3, layout_actual);
    vector<size_t> caminito = calcular_camino_minimo(46, 4);
    for (unsigned long &i: caminito) {
        cout << i << " ";
    }
}