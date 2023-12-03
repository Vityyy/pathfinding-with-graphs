#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "InventarioDePrioridad.hpp"
#include "Tablero.hpp"
#include "Pyramid_head.hpp"
#include <vector>
#include "James.hpp"

class Juego {
private:
    static James jugador;
    static Tablero tablero_de_juego;
    static std::vector<Pyramid_head> pyramid_heads;

    // Pre:~
    // Post: devuelve el camino minimo de una casilla a otra
    //@formatter:off
    static std::vector<CoordenadaMatriz> calcular_camino_minimo(CoordenadaMatriz origen, CoordenadaMatriz destino, std::size_t cantidad_armas);
    //@formatter:on

    // Pre: ~
    // Pos: desconecta una casilla con sus adyacentes.
    static void desconectar_casilla(CoordenadaMatriz coordenada, Tablero &tablero);

    // Pre: ~
    // Pos: devuelve true si hay un pyramid head en la casilla.
    static bool hay_pyramid_head(CoordenadaMatriz coordenada);

    // Pre: ~
    // Pos: devuelve true si la casilla es adyacente al pyramid head.
    static bool es_adyacente_a_pyramid_head(CoordenadaMatriz coordenada);

    // Pre: ~
    // Pos: carga un nivel en base a la altura de placas de james
    static void cargar_nivel();

    // Pre: ~
    // Pos: devuelve un numero aleatorio entre minimo y maximo
    static int numero_aleatorio_entre(int minimo, int maximo);

    // Pre: ~
    // Pos: genera una placa aleatoria
    static Placa generar_placa();

    // Pre: ~
    // Pos: genera dos pyramid heads con una chance del 50% a cada uno de que aparezcan, y los posiciona aleatoriamente
    static void generar_pyramid_heads();

    // Pre: ~
    // Pos: devuelve true si hay una pared en la coordenada
    static bool hay_pared(CoordenadaMatriz coordenada);

    // Pre: ~
    // Pos: carga el terreno que luego se imprimirá en pantalla (quizá el método se pueda eliminar)
    static void cargar_terreno(std::string terreno[Tablero::TAMANIO_TABLERO][Tablero::TAMANIO_TABLERO]);

    // Pre: ~
    // Pos: imprime el terreno en pantalla
    static void imprimir_terreno();

    /* En los próximos dos métodos deberíamos mapear strings con un int que represente la accion para validar el input */
    // Pre: ~
    // Pos: realiza una accion del jugador en base a la accion enviada
    static void accion_jugador(char accion);

    // Pre: ~
    // Pos: pide una accion y la devuelve
    static char pedir_accion();

    // Pre: ~
    // Pos: devuelve true si la accion no es un movimiento
    static bool es_accion(char accion);

    // Pre: ~
    // Pos: devuelve true si el movimiento es un movimiento
    static bool es_movimiento(char movimiento);

    // Pre: ~
    // Pos: imprime una matriz con los datos actuales y el camino minimo
    static void imprimir_camino_minimo();

    // Pre: ~
    // Pos: devuelve true si la coordenada está en el camino minimo
    static bool esta_en_camino_minimo(CoordenadaMatriz coordenada, std::vector<CoordenadaMatriz> camino_minimo);

public:

    // Pre: ~
    // Pos: (cambiará en el futuro) calcula e imprime el camino minimo desde el inicio al final del nivel
    static void ejecutar();

};

#endif //JUEGO_HPP
