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