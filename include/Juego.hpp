#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "InventarioDePrioridad.hpp"
#include "Tablero.hpp"
#include "Pyramid_head.hpp"
#include <vector>
#include "James.hpp"
#include <map>

class Juego {
private:
    static James jugador;
    static Tablero tablero_de_juego;
    static std::vector<Pyramid_head> pyramid_heads;
    static bool mostrar_camino_minimo;

    static const CoordenadaMatriz INICIO;
    static const CoordenadaMatriz META;

    static const std::map<std::string, unsigned short int> inputs_jugador;

    // Pre: ~
    // Pos: devuelve true si hay un pyramid head en la casilla.
    static bool hay_pyramid_head(CoordenadaMatriz coordenada);

    // Pre: ~
    // Pos: devuelve true si la casilla es adyacente al pyramid head.
    static bool es_adyacente_a_pyramid_head(CoordenadaMatriz coordenada);

    // Pre: el jugador no tiene armas
    // Pos: devuelve el camino minimo desde origen hasta destino sin armas
    static std::vector<CoordenadaMatriz>
    calcular_camino_minimo_sin_armas(CoordenadaMatriz origen, CoordenadaMatriz destino);

    // Pre: ~
    // Pos: devuelve el camino minimo en general
    // NOTA: sirve también para el caso sin armas y el caso con más o igual armas que pyramid heads pero es menos eficiente
    static std::vector<CoordenadaMatriz>
    calcular_camino_minimo_general(CoordenadaMatriz origen, CoordenadaMatriz destino, std::size_t cantidad_armas);

    // Pre: ~
    // Post: devuelve el camino minimo de una casilla a otra
    static std::vector<CoordenadaMatriz>
    calcular_camino_minimo(CoordenadaMatriz origen, CoordenadaMatriz destino, std::size_t cantidad_armas);

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
    // Pos: pide una accion y la devuelve
    static char pedir_accion();

    // Pre: ~
    // Pos: devuelve true si la accion no es un movimiento
    static bool es_accion(char accion);

    // Pre: ~
    // Pos: devuelve true si el movimiento es un movimiento
    static bool es_movimiento(char movimiento);

    // Pre: ~
    // Pos: realiza una accion del jugador en base a la accion enviada
    static void accion_jugador(char accion);

    // Pre: ~
    // Pos: devuelve true si la coordenada está en el camino minimo
    static bool esta_en_camino_minimo(CoordenadaMatriz coordenada, std::vector<CoordenadaMatriz> camino_minimo);

    // Pre: ~
    // Pos: imprime el terreno por pantalla con el camino minimo a la meta
    static void imprimir_terreno_con_camino_minimo();

    // Pre: ~
    // Pos: imprime el terreno por pantalla sin el camino minimo a la meta
    static void imprimir_terreno_sin_camino_minimo();

    // Pre: ~
    // Pos: imprime el terreno en pantalla, si camino_minimo es true, imprime el camino minimo
    static void imprimir_terreno(bool camino_minimo);

public:

    // Pre: ~
    // Pos: (cambiará en el futuro) calcula e imprime el camino minimo desde el inicio al final del nivel
    static void ejecutar();

};

#endif //JUEGO_HPP
