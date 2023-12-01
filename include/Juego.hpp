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

    // Pre:~
    // Post: devuelve el camino minimo de una casilla a otra.
    static std::vector<std::size_t> calcular_camino_minimo(CoordenadaMatriz origen, CoordenadaMatriz destino);

    // Pre: ~
    // Pos: desconecta una casilla con sus adyacentes.
    static void desconectar_casilla(CoordenadaMatriz coordenada, Tablero &tablero);

    // Pre: ~
    // Pos: devuelve true si hay un pyramid head en la casilla.
    static bool hay_pyramid_head(CoordenadaMatriz coordenada);

    // Pre: ~
    // Pos: devuelve true si la casilla es adyacente al pyramid head.
    static bool es_adyacente_a_pyramid_head(CoordenadaMatriz coordenada);

public:

    // Pre: ~
    // Pos: (cambiará en el futuro) calcula e imprime el camino minimo desde el inicio al final del nivel
    static void ejecutar();

};


#endif //JUEGO_HPP
