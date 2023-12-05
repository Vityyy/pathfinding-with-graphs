#include "Juego.hpp"
#include "Dijkstra.hpp"
#include <iostream>
#include "color.hpp"

using namespace std;

James Juego::jugador = James();

Tablero Juego::tablero_de_juego = Tablero();

vector<Pyramid_head> Juego::pyramid_heads = std::vector<Pyramid_head>{};

bool Juego::mostrar_camino_minimo = false;

const CoordenadaMatriz Juego::INICIO = {8, 0};
const CoordenadaMatriz Juego::META = {0, 8};

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

std::vector<CoordenadaMatriz>
Juego::calcular_camino_minimo_sin_armas(CoordenadaMatriz origen, CoordenadaMatriz destino) {
    Tablero tablero_de_juego_aux = tablero_de_juego;

    for (const auto &pyramid_head: pyramid_heads) {
        tablero_de_juego_aux.desconectar_casilla(pyramid_head.posicion());
    }

    bool camino_encontrado = false;

    pair<vector<CoordenadaMatriz>, int> mejor_camino_minimo;
    mejor_camino_minimo.second = INFINITO;

    pair<vector<CoordenadaMatriz>, int> camino_minimo;
    camino_minimo.second = INFINITO;

    bool es_adyacente;
    bool pasa_por_adyacente;

    size_t indice_ultimo_adyacente = 0;

    bool hubo_cambios;

    while (!camino_encontrado) {
        camino_minimo = tablero_de_juego_aux.camino_minimo(origen, destino);
        hubo_cambios = false;
        pasa_por_adyacente = false;

        for (size_t i = 0; i < camino_minimo.first.size(); i++) {
            es_adyacente = es_adyacente_a_pyramid_head(camino_minimo.first[i]);
            if (es_adyacente) {
                camino_minimo.second += 40;
                indice_ultimo_adyacente = i;
                pasa_por_adyacente = true;
            }
        }

        if (pasa_por_adyacente) {
            tablero_de_juego_aux.desconectar_casilla(camino_minimo.first[indice_ultimo_adyacente]);
        }

        if (camino_minimo.second < mejor_camino_minimo.second) {
            mejor_camino_minimo = camino_minimo;
            hubo_cambios = true;
        }

        if (!hubo_cambios) {
            camino_encontrado = true;
        }
    }

    return ((mejor_camino_minimo.second < INFINITO) ? (mejor_camino_minimo.first) : (vector<CoordenadaMatriz>()));
}

std::vector<CoordenadaMatriz>
Juego::calcular_camino_minimo_general(CoordenadaMatriz origen, CoordenadaMatriz destino, std::size_t cantidad_armas) {
    Tablero tablero_de_juego_aux = tablero_de_juego;

    size_t cantidad_armas_aux = cantidad_armas;

    pair<vector<CoordenadaMatriz>, int> mejor_camino_minimo;
    mejor_camino_minimo.second = INFINITO;

    pair<vector<CoordenadaMatriz>, int> camino_minimo;
    camino_minimo.second = INFINITO;

    bool hay_pyramid_head_en_casilla = false;
    bool es_adyacente = false;
    bool pasa_por_adyacente = false;
    bool hubo_cambios = false;
    bool camino_encontrado = false;

    size_t iterador_casillas = 0;

    while (!camino_encontrado) {
        camino_minimo = tablero_de_juego_aux.camino_minimo(origen, destino);
        cantidad_armas_aux = cantidad_armas;
        hay_pyramid_head_en_casilla = false;
        es_adyacente = false;
        hubo_cambios = false;
        pasa_por_adyacente = false;

        iterador_casillas = 0;
        while (iterador_casillas < camino_minimo.first.size() && !hay_pyramid_head_en_casilla) {
            hay_pyramid_head_en_casilla = hay_pyramid_head(camino_minimo.first[iterador_casillas]);
            if (hay_pyramid_head_en_casilla) {
                if (!cantidad_armas_aux) {
                    tablero_de_juego_aux.desconectar_casilla(camino_minimo.first[iterador_casillas]);
                } else {
                    cantidad_armas_aux--;
                    hay_pyramid_head_en_casilla = false;
                }
            }
            iterador_casillas++;
        }

        iterador_casillas = 0;
        while (iterador_casillas < camino_minimo.first.size() && !hay_pyramid_head_en_casilla) {
            es_adyacente = es_adyacente_a_pyramid_head(camino_minimo.first[iterador_casillas]);
            if (es_adyacente) {
                if (!cantidad_armas_aux) {
                    camino_minimo.second += 40;
                }
                pasa_por_adyacente = true;
            }
            iterador_casillas++;
        }

        if (pasa_por_adyacente) {
            tablero_de_juego_aux.desconectar_casilla(camino_minimo.first[iterador_casillas]);
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

vector<CoordenadaMatriz>
Juego::calcular_camino_minimo(CoordenadaMatriz origen, CoordenadaMatriz destino, size_t cantidad_armas) {
    if (cantidad_armas >= pyramid_heads.size()) {
        return tablero_de_juego.camino_minimo(origen, destino).first;
    }

    if (cantidad_armas == 0) {
        return calcular_camino_minimo_sin_armas(origen, destino);
    }

    return calcular_camino_minimo_general(origen, destino, cantidad_armas);
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

            pyramid_heads.emplace_back(coordenada_pyramid_head, tablero_de_juego);
        }
    }
}

bool Juego::hay_pared(CoordenadaMatriz coordenada) {
    return tablero_de_juego.casilla(coordenada.fil(), coordenada.col()) == Tablero::PARED;
}

char Juego::pedir_accion() {
    char accion;
    cin >> accion;
    return accion;
}

bool Juego::es_accion(char accion) {
    return accion == 'e' || accion == 'q' || accion == 'r' || accion == 'f';
}

bool Juego::es_movimiento(char movimiento) {
    return movimiento == 'w' || movimiento == 's' || movimiento == 'a' || movimiento == 'd';
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
                mostrar_camino_minimo = !mostrar_camino_minimo;
                break;

            default:
                break;
        }
    }
}


bool Juego::esta_en_camino_minimo(CoordenadaMatriz coordenada, std::vector<CoordenadaMatriz> camino_minimo) {
    bool esta_en_camino = false;
    size_t iterador_camino = 0;
    while (!esta_en_camino && iterador_camino < camino_minimo.size()) {
        esta_en_camino = (coordenada == camino_minimo[iterador_camino]);
        iterador_camino++;
    }
    return esta_en_camino;
}

void Juego::imprimir_terreno_con_camino_minimo() {
    vector<CoordenadaMatriz> coordenadas_camino_minimo = calcular_camino_minimo(jugador.posicion(), META,
                                                                                jugador.tiene_arma_equipada());

    for (size_t i = 0; i < Tablero::TAMANIO_TABLERO + 2; i++) {
        if (i == 0 || i == 10) {
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO + 1; j++) {
                cout << "#" << " ";
            }
            cout << "#" << endl;

        } else {
            cout << "#" << " ";
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO; j++) {

                if (esta_en_camino_minimo({i - 1, j}, coordenadas_camino_minimo)) {
                    if (hay_pyramid_head({i - 1, j})) {
                        cout << color::rize("4", "Light Magenta", "Blue", "Default", "Default") << " ";

                    } else if (jugador.posicion() == CoordenadaMatriz(i - 1, j)) {
                        cout << color::rize("J", "Light Yellow", "Blue", "Default", "Default") << " ";

                    } else if (CoordenadaMatriz(i - 1, j) == CoordenadaMatriz(0, 8)) {
                        cout << color::rize("F", "Light Green", "Blue", "Default", "Default") << " ";

                    } else if (CoordenadaMatriz(i - 1, j) == CoordenadaMatriz(8, 0)) {
                        cout << color::rize("I", "Light Red", "Blue", "Default", "Default") << " ";

                    } else {
                        cout << color::rize("_", "Default", "Blue", "Default", "Default") << " ";
                    }
                } else {
                    if (hay_pyramid_head({i - 1, j})) {
                        cout << color::rize("4", "Light Magenta", "Default", "Default", "Default") << " ";

                    } else if (jugador.posicion() == CoordenadaMatriz(i - 1, j)) {
                        cout << color::rize("J", "Light Yellow", "Default", "Default", "Default") << " ";

                    } else if (CoordenadaMatriz(i - 1, j) == CoordenadaMatriz(0, 8)) {
                        cout << color::rize("F", "Light Green", "Default", "Default", "Default") << " ";

                    } else if (CoordenadaMatriz(i - 1, j) == CoordenadaMatriz(8, 0)) {
                        cout << color::rize("I", "Light Red", "Default", "Default", "Default") << " ";

                    } else if (hay_pared({i - 1, j})) {
                        cout << color::rize("#", "Default", "Default", "Default", "Default") << " ";

                    } else {
                        cout << color::rize("_", "Default", "Default", "Default", "Default") << " ";
                    }
                }
            }
            cout << "#" << endl;
        }
    }
}

void Juego::imprimir_terreno_sin_camino_minimo() {
    for (size_t i = 0; i < Tablero::TAMANIO_TABLERO + 2; i++) {
        if (i == 0 || i == 10) {
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO + 1; j++) {
                cout << "#" << " ";
            }
            cout << "#" << endl;

        } else {
            cout << "#" << " ";
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO; j++) {
                if (hay_pyramid_head({i - 1, j})) {
                    cout << color::rize("4", "Light Magenta", "Default", "Default", "Default") << " ";

                } else if (jugador.posicion() == CoordenadaMatriz(i - 1, j)) {
                    cout << color::rize("J", "Light Yellow", "Default", "Default", "Default") << " ";

                } else if (CoordenadaMatriz(i - 1, j) == CoordenadaMatriz(0, 8)) {
                    cout << color::rize("F", "Light Green", "Default", "Default", "Default") << " ";

                } else if (CoordenadaMatriz(i - 1, j) == CoordenadaMatriz(8, 0)) {
                    cout << color::rize("I", "Light Red", "Default", "Default", "Default") << " ";

                } else if (hay_pared({i - 1, j})) {
                    cout << color::rize("#", "Default", "Default", "Default", "Default") << " ";

                } else {
                    cout << color::rize("_", "Default", "Default", "Default", "Default") << " ";
                }
            }
            cout << "#" << endl;
        }
    }
}

void Juego::imprimir_terreno(bool camino_minimo) {
    (camino_minimo) ? (imprimir_terreno_con_camino_minimo()) : (imprimir_terreno_sin_camino_minimo());
}

void Juego::ejecutar() {
    /*
    cargar_nivel();
    pyramid_heads.emplace_back(2, 6, tablero_de_juego);
    pyramid_heads.emplace_back(5, 4, tablero_de_juego);
    vector<size_t> camino = calcular_camino_minimo({8, 0}, {0, 8}, 0);
    for (unsigned long &i: camino) {
        cout << i << " ";
    }
     */
    srand((unsigned int) time(nullptr));

    size_t niveles_completados = 0;
    Placa *nueva_placa = nullptr;
    cargar_nivel();
    generar_pyramid_heads();
    jugador.posicion() = {8, 0};
    bool gano = false;

    while (!gano) {
        imprimir_terreno(mostrar_camino_minimo);
        accion_jugador(pedir_accion());


        if (jugador.posicion() == CoordenadaMatriz(0, 8)) {
            niveles_completados++;

            if (niveles_completados < 5) {
                do {
                    delete nueva_placa;
                    nueva_placa = new Placa(generar_placa());
                } while (jugador.tiene_placa(nueva_placa));
                jugador.agregar_placa(nueva_placa);
                nueva_placa = nullptr;

                if (numero_aleatorio_entre(1, 100) <= 20) {
                    auto potencia_arma = (size_t) numero_aleatorio_entre(10, 100);
                    jugador.obtener_arma(Arma("Arma: " + to_string(potencia_arma), potencia_arma));
                }

                cargar_nivel();

                jugador.posicion() = CoordenadaMatriz(8, 0);

                generar_pyramid_heads();
            } else {
                gano = true;
            }
        }
        cout << endl;
    }
}
