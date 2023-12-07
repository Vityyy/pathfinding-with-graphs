#include "Juego.hpp"
#include "Dijkstra.hpp"
#include <iostream>
#include "color.hpp"

using namespace std;

James Juego::jugador = James();

Tablero Juego::tablero_de_juego = Tablero();

vector<Pyramid_head> Juego::pyramid_heads = std::vector<Pyramid_head>{};

bool Juego::mostrar_camino_minimo = false;

size_t Juego::puntaje_actual = 0;

size_t Juego::costo_camino_minimo = 0;

const unsigned short int Juego::MOVER_ARRIBA = 0;
const unsigned short int Juego::MOVER_ABAJO = 1;
const unsigned short int Juego::MOVER_DERECHA = 2;
const unsigned short int Juego::MOVER_IZQUIERDA = 3;
const unsigned short int Juego::EQUIPAR_ARMA_FUERTE = 4;
const unsigned short int Juego::EQUIPAR_ARMA_DEBIL = 5;
const unsigned short int Juego::DESEQUIPAR_ARMA = 6;
const unsigned short int Juego::MOSTRAR_CAMINO_MINIMO = 7;
const unsigned short int Juego::IMPRIMIR_CAMINO_MINIMO_GENERAL = 8;
const unsigned short int Juego::COMPLETAR_NIVEL = 9;
const unsigned short int Juego::MOSTRAR_CONTROLES = 10;
const unsigned short int Juego::NO_EXISTE = 11;

const int Juego::COSTO_CAMINAR = 10;
const int Juego::COSTO_CAMINAR_ADYACENTE = 50;

const int Juego::MINIMO_ID_PLACA = 100;
const int Juego::MAXIMO_ID_PLACA = 666;

const int Juego::CANTIDAD_DE_PYRAMID_HEADS = 2;

const int Juego::FILA_SUPERIOR = 0;
const int Juego::FILA_INFERIOR = 10;

const int Juego::MINIMA_POTENCIA_ARMA = 10;
const int Juego::MAXIMA_POTENCIA_ARMA = 100;

const int Juego::CANTIDAD_INICIAL_DE_ARMAS = 2;

const map<string, unsigned short int> Juego::inputs_jugador = {
        pair<string, unsigned short int>("w", MOVER_ARRIBA),
        pair<string, unsigned short int>("arriba", MOVER_ARRIBA),

        pair<string, unsigned short int>("s", MOVER_ABAJO),
        pair<string, unsigned short int>("abajo", MOVER_ABAJO),

        pair<string, unsigned short int>("a", MOVER_IZQUIERDA),
        pair<string, unsigned short int>("izquierda", MOVER_IZQUIERDA),
        pair<string, unsigned short int>("izq", MOVER_IZQUIERDA),

        pair<string, unsigned short int>("d", MOVER_DERECHA),
        pair<string, unsigned short int>("derecha", MOVER_DERECHA),
        pair<string, unsigned short int>("der", MOVER_DERECHA),

        pair<string, unsigned short int>("e", EQUIPAR_ARMA_FUERTE),
        pair<string, unsigned short int>("arma fuerte", EQUIPAR_ARMA_FUERTE),
        pair<string, unsigned short int>("fuerte", EQUIPAR_ARMA_FUERTE),

        pair<string, unsigned short int>("q", EQUIPAR_ARMA_DEBIL),
        pair<string, unsigned short int>("arma debil", EQUIPAR_ARMA_DEBIL),
        pair<string, unsigned short int>("debil", EQUIPAR_ARMA_DEBIL),

        pair<string, unsigned short int>("r", DESEQUIPAR_ARMA),
        pair<string, unsigned short int>("desequipar", DESEQUIPAR_ARMA),

        pair<string, unsigned short int>("f", MOSTRAR_CAMINO_MINIMO),
        pair<string, unsigned short int>("camino minimo", MOSTRAR_CAMINO_MINIMO),

        pair<string, unsigned short int>("z", IMPRIMIR_CAMINO_MINIMO_GENERAL),
        pair<string, unsigned short int>("camino minimo general", IMPRIMIR_CAMINO_MINIMO_GENERAL),

        pair<string, unsigned short int>("x", COMPLETAR_NIVEL),
        pair<string, unsigned short int>("completar nivel", COMPLETAR_NIVEL),

        pair<string, unsigned short int>("c", MOSTRAR_CONTROLES),
        pair<string, unsigned short int>("mostrar constroles", MOSTRAR_CONTROLES)
};

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

    size_t indice_primer_adyacente = 0;

    bool hubo_cambios;

    while (!camino_encontrado) {
        camino_minimo = tablero_de_juego_aux.camino_minimo(origen, destino);
        hubo_cambios = false;
        pasa_por_adyacente = false;

        for (size_t i = 0; i < camino_minimo.first.size(); i++) {
            es_adyacente = es_adyacente_a_pyramid_head(camino_minimo.first[i]);
            if (es_adyacente) {
                camino_minimo.second += COSTO_CAMINAR_ADYACENTE - COSTO_CAMINAR;
                if(!pasa_por_adyacente){
                    indice_primer_adyacente = i;
                }
                pasa_por_adyacente = true;
            }
        }

        if (pasa_por_adyacente) {
            tablero_de_juego_aux.desconectar_casilla(camino_minimo.first[indice_primer_adyacente]);
        }

        if (camino_minimo.second < mejor_camino_minimo.second) {
            mejor_camino_minimo = camino_minimo;
            hubo_cambios = true;
        }

        if (!hubo_cambios) {
            camino_encontrado = true;
        }
    }

    costo_camino_minimo = (size_t) mejor_camino_minimo.second;
    return ((mejor_camino_minimo.second <= INFINITO) ? (mejor_camino_minimo.first) : (vector<CoordenadaMatriz>()));
}

std::vector<CoordenadaMatriz>
Juego::calcular_camino_minimo_general(CoordenadaMatriz origen, CoordenadaMatriz destino, std::size_t cantidad_armas) {
    Tablero tablero_de_juego_aux = tablero_de_juego;

    size_t cantidad_armas_aux;

    pair<vector<CoordenadaMatriz>, int> mejor_camino_minimo;
    mejor_camino_minimo.second = INFINITO;

    pair<vector<CoordenadaMatriz>, int> camino_minimo;
    camino_minimo.second = INFINITO;

    bool hay_pyramid_head_en_casilla;
    bool paso_por_pyramid_head = false;
    bool es_adyacente;
    bool pasa_por_adyacente;
    bool hubo_cambios;
    bool camino_encontrado = false;

    size_t iterador_casillas;

    while (!camino_encontrado) {
        camino_minimo = tablero_de_juego_aux.camino_minimo(origen, destino);
        cantidad_armas_aux = cantidad_armas;
        hay_pyramid_head_en_casilla = false;
        es_adyacente = false;
        hubo_cambios = false;
        pasa_por_adyacente = false;
        size_t indice_primer_adyacente = 0;

        iterador_casillas = 0;
        while (iterador_casillas < camino_minimo.first.size() && !hay_pyramid_head_en_casilla) {
            hay_pyramid_head_en_casilla = hay_pyramid_head(camino_minimo.first[iterador_casillas]);
            if (hay_pyramid_head_en_casilla) {
                if (!cantidad_armas_aux && !paso_por_pyramid_head) {
                    tablero_de_juego_aux.desconectar_casilla(camino_minimo.first[iterador_casillas]);
                } else {
                    cantidad_armas_aux--;
                    hay_pyramid_head_en_casilla = false;
                    paso_por_pyramid_head = true;
                }
            }
            iterador_casillas++;
        }

        iterador_casillas = 0;
        while (iterador_casillas < camino_minimo.first.size() && !hay_pyramid_head_en_casilla) {
            es_adyacente = es_adyacente_a_pyramid_head(camino_minimo.first[iterador_casillas]);
            if (es_adyacente) {
                if (!cantidad_armas_aux) {
                    camino_minimo.second += COSTO_CAMINAR_ADYACENTE - COSTO_CAMINAR;
                }

                if(!pasa_por_adyacente){
                    indice_primer_adyacente = iterador_casillas;
                }

                pasa_por_adyacente = true;


            }
            iterador_casillas++;
        }

        if (pasa_por_adyacente) {
            tablero_de_juego_aux.desconectar_casilla(camino_minimo.first[indice_primer_adyacente]);
        }

        if (!hay_pyramid_head_en_casilla && camino_minimo.second < mejor_camino_minimo.second) {
            mejor_camino_minimo = camino_minimo;
            hubo_cambios = true;
        }

        if (!hay_pyramid_head_en_casilla && camino_minimo.second >= mejor_camino_minimo.second && !hubo_cambios) {
            camino_encontrado = true;
        }
    }

    costo_camino_minimo = (size_t) mejor_camino_minimo.second;
    return ((mejor_camino_minimo.second <= INFINITO) ? (mejor_camino_minimo.first) : (vector<CoordenadaMatriz>()));
}

vector<CoordenadaMatriz>
Juego::calcular_camino_minimo(CoordenadaMatriz origen, CoordenadaMatriz destino, size_t cantidad_armas) {
    if (cantidad_armas >= pyramid_heads.size()) {
        pair<vector<CoordenadaMatriz>, int> camino_minimo = tablero_de_juego.camino_minimo(origen, destino);
        costo_camino_minimo = (size_t) camino_minimo.second;
        return camino_minimo.first;
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
    int nuevo_id = numero_aleatorio_entre(MINIMO_ID_PLACA, MAXIMO_ID_PLACA);
    return {"Placa: " + to_string(nuevo_id), "Leyenda: " + to_string(nuevo_id), nuevo_id};
}

void Juego::generar_pyramid_heads() {
    pyramid_heads.clear();
    CoordenadaMatriz coordenada_pyramid_head;

    for (size_t i = 0; i < CANTIDAD_DE_PYRAMID_HEADS; i++) {
        if (numero_aleatorio_entre(1, 100) <= 20) {
            do {
                coordenada_pyramid_head = {(size_t) numero_aleatorio_entre(0, 8),
                                           (size_t) numero_aleatorio_entre(0, 8)};

            } while (hay_pared(coordenada_pyramid_head) || hay_pyramid_head(coordenada_pyramid_head) ||
                     coordenada_pyramid_head == META || coordenada_pyramid_head == INICIO);

            pyramid_heads.emplace_back(coordenada_pyramid_head, tablero_de_juego);
        }
    }
}

bool Juego::hay_pared(CoordenadaMatriz coordenada) {
    return tablero_de_juego.casilla(coordenada.fil(), coordenada.col()) == Tablero::PARED;
}

void Juego::pedir_accion(string &accion) {
    cout << "Movimiento: ";
    getline(cin >> ws, accion);
}

unsigned short int Juego::procesar_accion(string accion) {
    for (char &letra: accion) {
        letra = (char) tolower(letra);
    }

    return (inputs_jugador.find(accion) == inputs_jugador.end()) ? (NO_EXISTE) : (inputs_jugador.find(accion)->second);
}

bool Juego::puede_caminar(CoordenadaMatriz nueva_posicion) {
    return !hay_pared(nueva_posicion) && (!hay_pyramid_head(nueva_posicion) || jugador.tiene_arma_equipada());
}


void Juego::mostrar_controles() {
    cout << "Controles: " << endl;
    cout << "wasd para moverte" << endl;
    cout << "e: equipar tu arma mas fuerte" << endl;
    cout << "q: equipar arma debil" << endl;
    cout << "r: desequipar arma" << endl;
    cout << "f: mostrar camino minimo" << endl;
    cout << "z: mostrar mejor camino minimo general" << endl;
    cout << "x: completar nivel de ser posible" << endl;
    cout << "c: mostrar controles" << endl;
    cout << endl;
}


void Juego::accion_jugador(unsigned short int accion) {
    vector<CoordenadaMatriz> coordenadas_camino_minimo;
    CoordenadaMatriz nueva_posicion;
    bool completado = false;
    size_t iterador = 0;

    switch (accion) {
        case MOVER_ARRIBA:
            nueva_posicion = CoordenadaMatriz(jugador.posicion().fil() - 1, jugador.posicion().col());
            if (jugador.posicion().fil() > 0 && puede_caminar(nueva_posicion)) {
                jugador.posicion().fil()--;
                (es_adyacente_a_pyramid_head(nueva_posicion)) ? (puntaje_actual += COSTO_CAMINAR_ADYACENTE)
                                                              : (puntaje_actual += COSTO_CAMINAR);

            } else {
                cout << "Movimiento invalido" << endl;
            }

            break;

        case MOVER_ABAJO:
            nueva_posicion = CoordenadaMatriz(jugador.posicion().fil() + 1, jugador.posicion().col());
            if (jugador.posicion().fil() < Tablero::TAMANIO_TABLERO - 1 && puede_caminar(nueva_posicion)) {
                jugador.posicion().fil()++;
                (es_adyacente_a_pyramid_head(nueva_posicion)) ? (puntaje_actual += COSTO_CAMINAR_ADYACENTE)
                                                              : (puntaje_actual += COSTO_CAMINAR);

            } else {
                cout << "Movimiento invalido" << endl;
            }

            break;

        case MOVER_IZQUIERDA:
            nueva_posicion = CoordenadaMatriz(jugador.posicion().fil(), jugador.posicion().col() - 1);
            if (jugador.posicion().col() > 0 && puede_caminar(nueva_posicion)) {
                jugador.posicion().col()--;
                (es_adyacente_a_pyramid_head(nueva_posicion)) ? (puntaje_actual += COSTO_CAMINAR_ADYACENTE)
                                                              : (puntaje_actual += COSTO_CAMINAR);

            } else {
                cout << "Movimiento invalido" << endl;
            }

            break;

        case MOVER_DERECHA:
            nueva_posicion = CoordenadaMatriz(jugador.posicion().fil(), jugador.posicion().col() + 1);
            if (jugador.posicion().col() < Tablero::TAMANIO_TABLERO - 1 && puede_caminar(nueva_posicion)) {
                jugador.posicion().col()++;
                (es_adyacente_a_pyramid_head(nueva_posicion)) ? (puntaje_actual += COSTO_CAMINAR_ADYACENTE)
                                                              : (puntaje_actual += COSTO_CAMINAR);

            } else {
                cout << "Movimiento invalido" << endl;
            }

            break;

        case EQUIPAR_ARMA_FUERTE:
            jugador.equipar_arma_fuerte();
            cout << endl;
            cout << "Equipaste tu arma mas fuerte" << endl;
            break;

        case EQUIPAR_ARMA_DEBIL:
            jugador.equipar_arma_debil();
            cout << endl;
            cout << "Equipaste tu arma mas debil" << endl;
            break;

        case DESEQUIPAR_ARMA:
            jugador.desequipar_arma();
            cout << endl;
            cout << "Desequipaste el arma" << endl;
            break;

        case MOSTRAR_CAMINO_MINIMO:
            mostrar_camino_minimo = !mostrar_camino_minimo;
            break;

        case IMPRIMIR_CAMINO_MINIMO_GENERAL:
            cout << "Mejor camino minimo en general: " << endl;
            coordenadas_camino_minimo = calcular_camino_minimo(INICIO, META, jugador.cantidad_de_armas());
            imprimir_terreno_con_camino_minimo(coordenadas_camino_minimo);
            cout << "Costo: " << costo_camino_minimo << endl;
            break;

        case COMPLETAR_NIVEL:
            coordenadas_camino_minimo = calcular_camino_minimo(jugador.posicion(), META, jugador.tiene_arma_equipada());
            if (coordenadas_camino_minimo.empty()) {
                cout << "No es posible completar el nivel" << endl;
            } else {
                while (!completado && iterador < coordenadas_camino_minimo.size()) {
                    completado = (hay_pyramid_head(coordenadas_camino_minimo[iterador]));

                    if (completado) {
                        jugador.perder_arma_equipada();
                    }

                    iterador++;
                }
                puntaje_actual += costo_camino_minimo;
                jugador.posicion() = META;
            }

            break;

        case MOSTRAR_CONTROLES:
            cout << endl;
            mostrar_controles();
            break;

        default:
            cout << "Opcion invalida" << endl;
            mostrar_controles();
            break;
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

void Juego::imprimir_terreno_con_camino_minimo(const vector<CoordenadaMatriz> &coordenadas_camino_minimo) {
    for (size_t i = 0; i < Tablero::TAMANIO_TABLERO + 2; i++) {
        if (i == FILA_SUPERIOR || i == FILA_INFERIOR) {
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO + 1; j++) {
                cout << "#" << " ";
            }
            cout << "#" << endl;

        } else {
            cout << "#" << " ";
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO; j++) {

                if (esta_en_camino_minimo({i - 1, j}, coordenadas_camino_minimo)) {
                    if (jugador.posicion() == CoordenadaMatriz(i - 1, j)) {
                        cout << color::rize("J", "Light Yellow", "Blue", "Default", "Default") << " ";

                    } else if (hay_pyramid_head({i - 1, j})) {
                        cout << color::rize("4", "Light Magenta", "Blue", "Default", "Default") << " ";

                    } else if (CoordenadaMatriz(i - 1, j) == CoordenadaMatriz(0, 8)) {
                        cout << color::rize("F", "Light Green", "Blue", "Default", "Default") << " ";

                    } else if (CoordenadaMatriz(i - 1, j) == CoordenadaMatriz(8, 0)) {
                        cout << color::rize("I", "Light Red", "Blue", "Default", "Default") << " ";

                    } else {
                        cout << color::rize("_", "Default", "Blue", "Default", "Default") << " ";
                    }
                } else {
                    if (jugador.posicion() == CoordenadaMatriz(i - 1, j)) {
                        cout << color::rize("J", "Light Yellow", "Default", "Default", "Default") << " ";

                    } else if (hay_pyramid_head({i - 1, j})) {
                        cout << color::rize("4", "Light Magenta", "Default", "Default", "Default") << " ";

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
        if (i == FILA_SUPERIOR || i == FILA_INFERIOR) {
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO + 1; j++) {
                cout << "#" << " ";
            }
            cout << "#" << endl;

        } else {
            cout << "#" << " ";
            for (size_t j = 0; j < Tablero::TAMANIO_TABLERO; j++) {
                if (jugador.posicion() == CoordenadaMatriz(i - 1, j)) {
                    cout << color::rize("J", "Light Yellow", "Default", "Default", "Default") << " ";

                } else if (hay_pyramid_head({i - 1, j})) {
                    cout << color::rize("4", "Light Magenta", "Default", "Default", "Default") << " ";

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
    if (camino_minimo) {
        vector<CoordenadaMatriz> coordenadas_camino_minimo = calcular_camino_minimo(jugador.posicion(), META,
                                                                                    jugador.tiene_arma_equipada());
        imprimir_terreno_con_camino_minimo(coordenadas_camino_minimo);

    } else {
        imprimir_terreno_sin_camino_minimo();
    }
}

void Juego::mostrar_informacion() {
    cout << "Cantidad de armas: " << jugador.cantidad_de_armas() << endl;
    string respuesta = (jugador.tiene_arma_equipada()) ? ("Si") : ("No");
    cout << "Tiene arma equipada: " << respuesta << endl;
    cout << "Costo total hasta el momento: " << puntaje_actual << endl;
    if (mostrar_camino_minimo) {
        if (costo_camino_minimo >= INFINITO) {
            cout << "No existe camino minimo" << endl;

        } else {
            cout << "Costo camino minimo: " << costo_camino_minimo << endl;
        }
    }
}

bool Juego::seguir_jugando() {
    string seguir_jugando;

    while(seguir_jugando != "no" && seguir_jugando != "si"){
        cout << "Quiere jugar otra vez?: ";
        getline(cin >> ws, seguir_jugando);

        for (char & letra : seguir_jugando) {
            letra = (char) tolower(letra);
        }

        if(seguir_jugando != "no" && seguir_jugando != "si"){
            cout << "Esa opcion no es valida" << endl;
        }
    }

    return !(seguir_jugando == "si");
}

void Juego::borrar_armas() {
    if (jugador.tiene_arma_equipada()) {
        jugador.perder_arma_equipada();
    }

    size_t cantidad_armas = jugador.cantidad_de_armas();
    for (size_t i = 0 ; i < cantidad_armas ; i++) {
        jugador.equipar_arma_fuerte();
        jugador.perder_arma_equipada();
    }
}

void Juego::ejecutar() {
    srand((unsigned int) time(nullptr));

    size_t niveles_completados;
    Placa *nueva_placa;
    cargar_nivel();
    generar_pyramid_heads();
    jugador.posicion();
    bool juego_terminado;
    bool finalizado = false;
    string accion;

    size_t potencia_del_arma;

    while(!finalizado){

        mostrar_controles();
        niveles_completados = 0;
        nueva_placa = nullptr;
        cargar_nivel();
        generar_pyramid_heads();
        jugador.posicion() = INICIO;
        puntaje_actual = 0;
        juego_terminado = false;
        borrar_armas();

        for (size_t i = 0; i < CANTIDAD_INICIAL_DE_ARMAS; i++) {
            potencia_del_arma = (size_t) numero_aleatorio_entre(MINIMA_POTENCIA_ARMA, MAXIMA_POTENCIA_ARMA);
            jugador.obtener_arma({"Arma: " + to_string(potencia_del_arma), potencia_del_arma});
        }

        while (!juego_terminado) {
            if (calcular_camino_minimo(INICIO, META, jugador.cantidad_de_armas()).empty()) {
                cout << "No es posible completar el nivel" << endl;
                cout << "Perdiste :(" << endl;
                juego_terminado = true;

            } else {
                imprimir_terreno(mostrar_camino_minimo);
                mostrar_informacion();
                pedir_accion(accion);
                accion_jugador(procesar_accion(accion));

                if (hay_pyramid_head(jugador.posicion())) {
                    jugador.perder_arma_equipada();
                    pyramid_heads.clear();
                    cout << "Ahuyentaste a los pyramid heads" << endl;
                    cout << "Perdiste un arma" << endl;
                }


                if (jugador.posicion() == META) {
                    niveles_completados++;

                    if (niveles_completados < 5) {
                        do {
                            delete nueva_placa;
                            nueva_placa = new Placa(generar_placa());
                        } while (jugador.tiene_placa(nueva_placa));
                        jugador.agregar_placa(nueva_placa);
                        nueva_placa = nullptr;

                        if (numero_aleatorio_entre(1, 100) <= 20) {
                            auto potencia_arma = (size_t) numero_aleatorio_entre(MINIMA_POTENCIA_ARMA, MAXIMA_POTENCIA_ARMA);
                            jugador.obtener_arma(Arma("Arma: " + to_string(potencia_arma), potencia_arma));
                        }

                        cargar_nivel();

                        jugador.posicion() = CoordenadaMatriz(8, 0);

                        generar_pyramid_heads();
                    } else {
                        juego_terminado = true;
                        std::cout << endl;
                        std::cout << "Felicidades! Has completado los 5 niveles." << endl;
                        std::cout << "Costo final: " << puntaje_actual << endl;
                    }
                }
                cout << endl;
            }
        }
        finalizado = seguir_jugando();
        cout << endl;
    }
}
