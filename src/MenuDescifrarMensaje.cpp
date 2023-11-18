#include "MenuDescifrarMensaje.hpp"
#include <iostream>

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