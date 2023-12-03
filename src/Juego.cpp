#include "Juego.hpp"
#include "Dijkstra.hpp"
#include <iostream>
#include "color.hpp"

using namespace std;

James Juego::jugador = James();

Tablero Juego::tablero_de_juego = Tablero();

vector<Pyramid_head> Juego::pyramid_heads = std::vector<Pyramid_head>{};

bool Juego::hay_pyramid_head(CoordenadaMatriz coordenada) {
    size_t iterador_pyramid_heads = 0;
    bool hay_pyramid_head = false;
    while (!hay_pyramid_head && iterador_pyramid_heads < pyramid_heads.size()) {
        hay_pyramid_head = (pyramid_heads[iterador_pyramid_heads].posicion() == coordenada);
        iterador_pyramid_heads++;
    }

    return hay_pyramid_head;
}

bool Juego::es_adyacente_a_pyramid_head(CoordenadaMatriz coordenada) {
    size_t iterador_pyramid_heads = 0;
    size_t iterador_adyacentes = 0;
    bool es_adyacente = false;

    while (!es_adyacente && iterador_pyramid_heads < pyramid_heads.size()) {
        while (!es_adyacente && iterador_adyacentes < pyramid_heads[iterador_pyramid_heads].adyacentes().size()) {
            es_adyacente = (pyramid_heads[iterador_pyramid_heads].adyacentes()[iterador_adyacentes] == coordenada);
            iterador_adyacentes++;
        }
        iterador_pyramid_heads++;
    }

    return es_adyacente;
}

vector<CoordenadaMatriz>
Juego::calcular_camino_minimo(CoordenadaMatriz origen, CoordenadaMatriz destino, size_t cantidad_armas) {
    Tablero tablero_actual = tablero_de_juego;
    size_t cantidad_armas_actual = cantidad_armas;
    pair<vector<CoordenadaMatriz>, int> mejor_camino_minimo;
    mejor_camino_minimo.second = INFINITO;
    pair<vector<CoordenadaMatriz>, int> camino_minimo;

    bool hay_pyramid_head_en_casilla = false;
    bool es_adyacente = false;
    bool pasa_por_adyacente = false;
    bool hubo_cambios = false;

    size_t iterador_casillas = 0;
    bool camino_encontrado = false;
    while (!camino_encontrado) {
        camino_minimo = tablero_actual.camino_minimo(origen, destino);
        cantidad_armas_actual = cantidad_armas;
        hay_pyramid_head_en_casilla = false;
        es_adyacente = false;
        hubo_cambios = false;
        pasa_por_adyacente = false;

        iterador_casillas = 0;
        while (iterador_casillas < camino_minimo.first.size() && !hay_pyramid_head_en_casilla) {
            hay_pyramid_head_en_casilla = hay_pyramid_head(camino_minimo.first[iterador_casillas]);
            if (hay_pyramid_head_en_casilla) {
                if (!cantidad_armas_actual) {
                    desconectar_casilla(camino_minimo.first[iterador_casillas], tablero_actual);
                } else {
                    cantidad_armas_actual--;
                    hay_pyramid_head_en_casilla = false;
                }
            }
            iterador_casillas++;
        }

        iterador_casillas = 0;
        while (iterador_casillas < camino_minimo.first.size() && !hay_pyramid_head_en_casilla) {
            es_adyacente = es_adyacente_a_pyramid_head(camino_minimo.first[iterador_casillas]);
            if (es_adyacente) {
                if (!cantidad_armas) {
                    camino_minimo.second += 40;
                }
                pasa_por_adyacente = true;
            }
            iterador_casillas++;
        }

        if (pasa_por_adyacente) {
            desconectar_casilla(camino_minimo.first[iterador_casillas], tablero_actual);
        }

        if (!hay_pyramid_head_en_casilla && camino_minimo.second < mejor_camino_minimo.second) {
            mejor_camino_minimo = camino_minimo;
            hubo_cambios = true;
        }

        if (!hay_pyramid_head_en_casilla && camino_minimo.second >= mejor_camino_minimo.second && !hubo_cambios) {
            camino_encontrado = true;
        }
    }

    return ((mejor_camino_minimo.second != INFINITO) ? (mejor_camino_minimo.first) : (vector<CoordenadaMatriz>()));
}

void Juego::desconectar_casilla(CoordenadaMatriz coordenada, Tablero &tablero) {
    // Desconectar abajo
    if (coordenada.fil() < Tablero::TAMANIO_TABLERO - 1) {
        tablero.desconectar_casillas(coordenada, CoordenadaMatriz(coordenada.fil() + 1, coordenada.col()));
    }

    // Comprobación arriba
    if (coordenada.fil() > 0) {
        tablero.desconectar_casillas(coordenada, CoordenadaMatriz(coordenada.fil() - 1, coordenada.col()));
    }

    // Comprobación derecha
    if (coordenada.col() < Tablero::TAMANIO_TABLERO - 1) {
        tablero.desconectar_casillas(coordenada, CoordenadaMatriz(coordenada.fil(), coordenada.col() + 1));
    }

    // Comprobación izquierda
    if (coordenada.col() > 0) {
        tablero.desconectar_casillas(coordenada, CoordenadaMatriz(coordenada.fil(), coordenada.col() - 1));
    }
}

void Juego::cargar_nivel() {
    //@formatter:off
    (jugador.altura_placas() % 2 == 0) ? (tablero_de_juego.cargar_nivel("layout_1")) : (tablero_de_juego.cargar_nivel("layout_2"));
    //@formatter:on
}

int Juego::numero_aleatorio_entre(int minimo, int maximo) {
    return rand() % (maximo - minimo + 1) + minimo;
}

Placa Juego::generar_placa() {
    int nuevo_id = numero_aleatorio_entre(100, 666);
    return {"Placa: " + to_string(nuevo_id), "Leyenda: " + to_string(nuevo_id), nuevo_id};
}

void Juego::ejecutar() {
    cargar_nivel();
    pyramid_heads.emplace_back(2, 6, tablero_de_juego);
    pyramid_heads.emplace_back(5, 4, tablero_de_juego);
    vector<size_t> camino = calcular_camino_minimo({8, 0}, {0, 8}, 0);
    for (unsigned long &i: camino) {
        cout << i << " ";
    }
}