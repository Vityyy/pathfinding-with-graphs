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