#include "MenuDescifrarMensaje.hpp"

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