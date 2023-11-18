#include <iostream>
#include "Menu.hpp"
#include "MenuDescifrarMensaje.hpp"
#include "MenuInventarioDePrioridad.hpp"

const unsigned int Menu::DESCIFRAR_MENSAJE = 0;
const unsigned int Menu::INVENTARIO_DE_PRIORIDAD = 1;
const unsigned int Menu::SALIR = 2;

const std::map<std::string, unsigned int> Menu::opciones_menu = {
        std::pair<std::string, unsigned int>("descifrar mensaje", DESCIFRAR_MENSAJE),
        std::pair<std::string, unsigned int>("0", DESCIFRAR_MENSAJE),

        std::pair<std::string, unsigned int>("inventario de prioridad", INVENTARIO_DE_PRIORIDAD),
        std::pair<std::string, unsigned int>("1", INVENTARIO_DE_PRIORIDAD),

        std::pair<std::string, unsigned int>("salir", SALIR),
        std::pair<std::string, unsigned int>("2", SALIR)
};

void Menu::imprimir() {
    std::cout << ".:MENU DE TESTEO DEL REMAKE DE SILENT HILL 2:." << std::endl;
    std::cout << "[" << DESCIFRAR_MENSAJE << "] Descifrar Mensaje" << std::endl;
    std::cout << "[" << INVENTARIO_DE_PRIORIDAD << "] Inventario de prioridad" << std::endl;
    std::cout << "[" << SALIR << "] Salir" << std::endl;
}

void Menu::pedir_opcion(std::string &opcion) {
    std::cout << "Opcion: ";
    getline(std::cin >> std::ws, opcion);
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
                MenuDescifrarMensaje::ejecutar();
                break;

            case INVENTARIO_DE_PRIORIDAD:
                MenuInventarioDePrioridad::ejecutar();
                break;

            case SALIR:
                break;

            default:
                std::cout << "Esa opción no es válida" << std::endl;
        }

    } while (opcion_procesada != SALIR);
}