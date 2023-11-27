#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "InventarioDePrioridad.hpp"
#include "Tablero.hpp"
#include "Pyramid_head.hpp"
#include <vector>

class Juego {
private:
    static InventarioDePrioridad inventario;
    static Tablero tablero_de_juego;
    static std::vector<Pyramid_head> pyramid_heads;
    static Arma *arma_actual;
    static Matriz layout_actual;

    static const int layout_1[Tablero::TAMANIO_TABLERO][Tablero::TAMANIO_TABLERO];
    static const int layout_2[Tablero::TAMANIO_TABLERO][Tablero::TAMANIO_TABLERO];

    // Pre:~
    // Post: devuelve el camino minimo de una casilla a otra.
    static std::vector<std::size_t> calcular_camino_minimo(std::size_t origen, std::size_t destino);

    // Pre: ~
    // Pos: desconecta una casilla con sus adyacentes.
    static void desconectar_casilla(Tablero &tablero, std::size_t casilla);

    // Pre: ~
    // Pos: devuelve true si hay un pyramid head en la casilla.
    static bool hay_pyramid_head(std::size_t casilla);

    // Pre: ~
    // Pos: devuelve true si la casilla es adyacente al pyramid head.
    static bool es_adyacente_a_pyramid_head(std::size_t casilla);

    // Pre: ~
    // Pos: devuelve la ubicacion de la casilla en el layout en uso.
    static std::pair<size_t, size_t> ubicacion_en_matriz(int casilla);

    // Pre: ~
    // Pos: carga el nivel en base a layout
    static void cargar_nivel(const int layout[Tablero::TAMANIO_TABLERO][Tablero::TAMANIO_TABLERO]);

public:

    static void ejecutar();

};


#endif //JUEGO_HPP
