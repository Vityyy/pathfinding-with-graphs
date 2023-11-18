#include "MenuDescifrarMensaje.hpp"
#include <iostream>
#include "ABB.hpp"
#include "Placa.hpp"
#include "bGVjdG9y.hpp"
#include <sstream>

const unsigned int MenuDescifrarMensaje::DESCIFRAR_MENSAJE = 0;
const unsigned int MenuDescifrarMensaje::IMPRIMIR_MENSAJE = 1;
const unsigned int MenuDescifrarMensaje::VOLVER = 2;

const std::map<std::string, unsigned int> MenuDescifrarMensaje::opciones_menu{
        std::pair<std::string, unsigned int>("descifrar mensaje", DESCIFRAR_MENSAJE),
        std::pair<std::string, unsigned int>("0", DESCIFRAR_MENSAJE),

        std::pair<std::string, unsigned int>("imprimir_mensaje", IMPRIMIR_MENSAJE),
        std::pair<std::string, unsigned int>("1", IMPRIMIR_MENSAJE),

        std::pair<std::string, unsigned int>("volver", VOLVER),
        std::pair<std::string, unsigned int>("2", VOLVER)
};

void MenuDescifrarMensaje::imprimir() {
    std::cout << ".:MENU DE TESTEO DE DESCIFRADO DE MENSAJES:." << std::endl;
    std::cout << "[" << DESCIFRAR_MENSAJE << "] Descifrar Mensaje" << std::endl;
    std::cout << "[" << IMPRIMIR_MENSAJE << "] Imprimir mensaje" << std::endl;
    std::cout << "[" << VOLVER << "] Volver" << std::endl;
}

void MenuDescifrarMensaje::pedir_opcion(std::string &opcion) {
    std::cout << "Opcion: ";
    getline(std::cin >> std::ws, opcion);
}

unsigned int MenuDescifrarMensaje::procesar_opcion(std::string &opcion) {
    for(char & i : opcion){
        i = (char) tolower(i);
    }

    return opciones_menu.find(opcion)->second;
}

void MenuDescifrarMensaje::descifrar_mensaje(std::string &mensaje_descifrado) {
    ABB<Placa *, Placa::menor, Placa::igual> mensaje_desordenado{};
    bGVjdG9y::Y2FyZ2Fy(mensaje_desordenado);

    std::vector<Placa *> mensaje_ordenado = mensaje_desordenado.preorder();

    std::stringstream stream_mensaje_descifrado;

    for (auto & i : mensaje_ordenado) {
        stream_mensaje_descifrado << *i << std::endl;
    }

    mensaje_descifrado = stream_mensaje_descifrado.str();

    for (auto & i : mensaje_ordenado) {
        delete i;
        i = nullptr;
    }
}

void MenuDescifrarMensaje::ejecutar(std::string &mensaje_descifrado) {
    std::string opcion;
    unsigned int opcion_procesada = 0;

    do {
        imprimir();
        pedir_opcion(opcion);
        opcion_procesada = procesar_opcion(opcion);

        switch (opcion_procesada) {
            case DESCIFRAR_MENSAJE:
                descifrar_mensaje(mensaje_descifrado);
                break;

            case IMPRIMIR_MENSAJE:
                std::cout << mensaje_descifrado;
                break;

            case VOLVER:
                system("clear");
                break;

            default:
                std::cout << "Esa opción no es válida" << std::endl;
        }

    } while (opcion_procesada != VOLVER);
}