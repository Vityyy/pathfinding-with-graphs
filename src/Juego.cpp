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

void Juego::generar_pyramid_heads() {
    pyramid_heads.clear();
    CoordenadaMatriz coordenada_pyramid_head;

    for (size_t i = 0; i < 2; i++) {
        if (numero_aleatorio_entre(1, 100) <= 50) {
            do {
                coordenada_pyramid_head = {(size_t) numero_aleatorio_entre(0, 8),
                                           (size_t) numero_aleatorio_entre(0, 8)};

            } while (hay_pared(coordenada_pyramid_head) || hay_pyramid_head(coordenada_pyramid_head) ||
                     coordenada_pyramid_head == CoordenadaMatriz(0, 8) ||
                     coordenada_pyramid_head == CoordenadaMatriz(8, 0));

            pyramid_heads.emplace_back(coordenada_pyramid_head.fil(), coordenada_pyramid_head.col(), tablero_de_juego);
        }
    }
}

bool Juego::hay_pared(CoordenadaMatriz coordenada) {
    return tablero_de_juego.casilla(coordenada.fil(), coordenada.col()) == Tablero::PARED;
}

void Juego::cargar_terreno(string terreno[Tablero::TAMANIO_TABLERO][Tablero::TAMANIO_TABLERO]) {
    for (size_t i = 0; i < Tablero::TAMANIO_TABLERO; i++) {
        for (size_t j = 0; j < Tablero::TAMANIO_TABLERO; j++) {
            terreno[i][j] = "_";

            if (hay_pared({i, j})) {
                terreno[i][j] = "#";
            }

            if (hay_pyramid_head({i, j})) {
                terreno[i][j] = "4";
            }

            if (i == 0 && j == 8) {
                terreno[i][j] = "F";
            }

            if (i == 8 && j == 0) {
                terreno[i][j] = "I";
            }

            if (CoordenadaMatriz(i, j) == jugador.posicion()) {
                terreno[i][j] = "J";
            }
        }
    }
}

void Juego::imprimir_terreno() {
    string terreno[Tablero::TAMANIO_TABLERO][Tablero::TAMANIO_TABLERO];
    cargar_terreno(terreno);
    for (size_t i = 0; i < Tablero::TAMANIO_TABLERO + 2; i++) {
        if (i == 0 || i == 10) {
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO + 2; j++) {
                cout << "#" << " ";
            }

        } else {
            cout << "#" << " ";
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO; j++) {
                if (terreno[i - 1][j] == "4") {
                    cout << color::rize(string(terreno[i - 1][j]), "Light Magenta", "Default", "Default", "Default")
                         << " ";

                } else if (terreno[i - 1][j] == "J") {
                    cout << color::rize(string(terreno[i - 1][j]), "Light Yellow", "Default", "Default", "Default")
                         << " ";

                } else if (terreno[i - 1][j] == "F") {
                    cout << color::rize(string(terreno[i - 1][j]), "Light Green", "Default", "Default", "Default")
                         << " ";

                } else if (terreno[i - 1][j] == "I") {
                    cout << color::rize(string(terreno[i - 1][j]), "Light Red", "Default", "Default", "Default") << " ";

                } else {
                    cout << terreno[i - 1][j] << " ";
                }
            }
            cout << "#" << " ";
        }
        cout << endl;
    }
}


void Juego::accion_jugador(char accion) {
    if (es_movimiento(accion)) {
        switch (accion) {
            case 'w':
                if (jugador.posicion().fil() > 0 &&
                    !hay_pared(CoordenadaMatriz(jugador.posicion().fil() - 1, jugador.posicion().col())) &&
                    (!hay_pyramid_head(CoordenadaMatriz(jugador.posicion().fil() - 1, jugador.posicion().col())) ||
                     jugador.tiene_arma_equipada())) {

                    jugador.posicion().fil()--;
                }
                break;

            case 's':
                if (jugador.posicion().fil() < Tablero::TAMANIO_TABLERO - 1 &&
                    !hay_pared(CoordenadaMatriz(jugador.posicion().fil() + 1, jugador.posicion().col())) &&
                    (!hay_pyramid_head(CoordenadaMatriz(jugador.posicion().fil() + 1, jugador.posicion().col())) ||
                     jugador.tiene_arma_equipada())) {

                    jugador.posicion().fil()++;
                }

                break;

            case 'a':
                if (jugador.posicion().col() > 0 &&
                    !hay_pared(CoordenadaMatriz(jugador.posicion().fil(), jugador.posicion().col() - 1)) &&
                    (!hay_pyramid_head(CoordenadaMatriz(jugador.posicion().fil(), jugador.posicion().col() - 1)) ||
                     jugador.tiene_arma_equipada())) {

                    jugador.posicion().col()--;
                }
                break;

            case 'd':
                if (jugador.posicion().col() < Tablero::TAMANIO_TABLERO - 1 &&
                    !hay_pared(CoordenadaMatriz(jugador.posicion().fil(), jugador.posicion().col() + 1)) &&
                    (!hay_pyramid_head(CoordenadaMatriz(jugador.posicion().fil(), jugador.posicion().col() + 1)) ||
                     jugador.tiene_arma_equipada())) {

                    jugador.posicion().col()++;
                }
                break;

            default:
                break;
        }
    }
    if (es_accion(accion)) {
        switch (accion) {
            case 'e':
                jugador.equipar_arma_fuerte();
                break;

            case 'q':
                jugador.equipar_arma_debil();
                break;

            case 'r':
                jugador.desequipar_arma();
                break;

            case 'f':
                imprimir_camino_minimo();
                break;

            default:
                break;
        }
    }
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