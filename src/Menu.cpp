#include <iostream>
#include "Menu.hpp"
#include "MenuDescifrarMensaje.hpp"
#include "MenuInventarioDePrioridad.hpp"
#include "Juego.hpp"

using namespace std;

const unsigned short int Menu::DESCIFRAR_MENSAJE = 0;
const unsigned short int Menu::INVENTARIO_DE_PRIORIDAD = 1;
const unsigned short int Menu::JUGAR_LABERINTO = 2;
const unsigned short int Menu::SALIR = 3;
const unsigned short int Menu::OPCION_INVALIDA = 4;

const map<string, unsigned short int> Menu::opciones_menu = {
        pair<string, unsigned short int>("descifrar mensaje", DESCIFRAR_MENSAJE),
        pair<string, unsigned short int>("0", DESCIFRAR_MENSAJE),

        pair<string, unsigned short int>("inventario de prioridad", INVENTARIO_DE_PRIORIDAD),
        pair<string, unsigned short int>("1", INVENTARIO_DE_PRIORIDAD),

        pair<string, unsigned short int>("jugar laberinto", JUGAR_LABERINTO),
        pair<string, unsigned short int>("2", JUGAR_LABERINTO),

        pair<string, unsigned short int>("salir", SALIR),
        pair<string, unsigned short int>("3", SALIR),
};

void Menu::imprimir() {
    cout << ".:MENU DE TESTEO DEL REMAKE DE SILENT HILL 2:." << endl;
    cout << "[" << DESCIFRAR_MENSAJE << "] Descifrar Mensaje" << endl;
    cout << "[" << INVENTARIO_DE_PRIORIDAD << "] Inventario de prioridad" << endl;
    cout << "[" << JUGAR_LABERINTO << "] Laberinto" << endl;
    cout << "[" << SALIR << "] Salir" << endl;
}

void Menu::pedir_opcion(string &opcion) {
    cout << "Opcion: ";
    getline(cin >> ws, opcion);
}

unsigned int Menu::procesar_opcion(std::string &opcion) {
    for(char & i : opcion){
        i = (char) tolower(i);
    }

    auto opcion_procesada = opciones_menu.find(opcion);
    return (opcion_procesada != opciones_menu.end()) ? (opcion_procesada->second) : (OPCION_INVALIDA);
}

void Menu::ejecutar(std::string &mensaje_descifrado, InventarioDePrioridad &inventario) {
    std::string opcion;
    unsigned int opcion_procesada = 0;

    do {
        imprimir();
        pedir_opcion(opcion);
        opcion_procesada = procesar_opcion(opcion);

        switch (opcion_procesada) {
            case DESCIFRAR_MENSAJE:
                MenuDescifrarMensaje::ejecutar(mensaje_descifrado);
                std::cout << endl;
                break;

            case INVENTARIO_DE_PRIORIDAD:
                MenuInventarioDePrioridad::ejecutar(inventario);
                std::cout << endl;
                break;

            case JUGAR_LABERINTO:
                Juego::ejecutar();
                std::cout << endl;

            case SALIR:
                break;

            default:
                cout << "Esa opción no es válida" << endl;
                std::cout << endl;
        }

    } while (opcion_procesada != SALIR);
}