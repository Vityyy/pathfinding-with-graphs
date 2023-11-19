#include <iostream>
#include "Menu.hpp"
#include "MenuDescifrarMensaje.hpp"
#include "MenuInventarioDePrioridad.hpp"

using namespace std;

const unsigned int Menu::DESCIFRAR_MENSAJE = 0;
const unsigned int Menu::INVENTARIO_DE_PRIORIDAD = 1;
const unsigned int Menu::SALIR = 2;

const map<string, unsigned int> Menu::opciones_menu = {
        pair<string, unsigned int>("descifrar mensaje", DESCIFRAR_MENSAJE),
        pair<string, unsigned int>("0", DESCIFRAR_MENSAJE),

        pair<string, unsigned int>("inventario de prioridad", INVENTARIO_DE_PRIORIDAD),
        pair<string, unsigned int>("1", INVENTARIO_DE_PRIORIDAD),

        pair<string, unsigned int>("salir", SALIR),
        pair<string, unsigned int>("2", SALIR)
};

void Menu::imprimir() {
    cout << ".:MENU DE TESTEO DEL REMAKE DE SILENT HILL 2:." << endl;
    cout << "[" << DESCIFRAR_MENSAJE << "] Descifrar Mensaje" << endl;
    cout << "[" << INVENTARIO_DE_PRIORIDAD << "] Inventario de prioridad" << endl;
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

    return opciones_menu.find(opcion)->second;
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
                break;

            case INVENTARIO_DE_PRIORIDAD:
                MenuInventarioDePrioridad::ejecutar(inventario);
                break;

            case SALIR:
                break;

            default:
                cout << "Esa opción no es válida" << endl;
        }

    } while (opcion_procesada != SALIR);
}