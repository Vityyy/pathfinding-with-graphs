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
    static size_t puntaje_actual;
    static size_t costo_camino_minimo;

    static const CoordenadaMatriz INICIO;
    static const CoordenadaMatriz META;

    static const unsigned short int MOVER_ARRIBA;
    static const unsigned short int MOVER_ABAJO;
    static const unsigned short int MOVER_DERECHA;
    static const unsigned short int MOVER_IZQUIERDA;
    static const unsigned short int EQUIPAR_ARMA_FUERTE;
    static const unsigned short int EQUIPAR_ARMA_DEBIL;
    static const unsigned short int DESEQUIPAR_ARMA;
    static const unsigned short int MOSTRAR_CAMINO_MINIMO;
    static const unsigned short int IMPRIMIR_CAMINO_MINIMO_GENERAL;
    static const unsigned short int COMPLETAR_NIVEL;
    static const unsigned short int NO_EXISTE;

    static const int COSTO_CAMINAR;
    static const int COSTO_CAMINAR_ADYACENTE;

    static const int MINIMO_ID_PLACA;
    static const int MAXIMO_ID_PLACA;

    static const int CANTIDAD_DE_PYRAMID_HEADS;

    static const int FILA_SUPERIOR;
    static const int FILA_INFERIOR;

    static const int MINIMA_POTENCIA_ARMA;
    static const int MAXIMA_POTENCIA_ARMA;

    static const int CANTIDAD_INICIAL_DE_ARMAS;

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
    static void pedir_accion(std::string &accion);

    // Pre: ~
    // Pos: procesa la accion y devuelve un id de la misma, si no la encuentra devuelve el máximo de accion
    static unsigned short int procesar_accion(std::string accion);

    // Pre: ~
    // Pos: devuelve true si el jugador puede caminar a la nueva posicion
    static bool puede_caminar(CoordenadaMatriz nueva_posicion);

    // Pre: ~
    // Pos: imprime los controles por pantalla
    static void mostrar_controles();

    // Pre: ~
    // Pos: realiza una accion del jugador en base a la accion enviada
    static void accion_jugador(unsigned short int accion);

    // Pre: ~
    // Pos: devuelve true si la coordenada está en el camino minimo
    static bool esta_en_camino_minimo(CoordenadaMatriz coordenada, std::vector<CoordenadaMatriz> camino_minimo);

    // Pre: ~
    // Pos: imprime el terreno con el camino minimo que se le envíe
    static void imprimir_terreno_con_camino_minimo(const std::vector<CoordenadaMatriz> &);

    // Pre: ~
    // Pos: imprime el terreno por pantalla sin el camino minimo a la meta
    static void imprimir_terreno_sin_camino_minimo();

    // Pre: ~
    // Pos: imprime el terreno en pantalla, si camino_minimo es true, imprime el camino minimo
    static void imprimir_terreno(bool camino_minimo);

    // Pre: ~
    // Pos: muestra la informacion del juego en pantalla
    static void mostrar_informacion();

    // Pre: ~
    // Pos: retorna true si el jugador quiere seguir jugando
    static bool seguir_jugando();

    // Pre: ~
    //Pos: borra las armas en el inventario del jugador para que comience una nueva partida
    static void borrar_armas();

public:

    // Pre: ~
    // Pos: (cambiará en el futuro) calcula e imprime el camino minimo desde el inicio al final del nivel
    static void ejecutar();

};

#endif //JUEGO_HPP
