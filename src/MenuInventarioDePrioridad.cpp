#include "MenuInventarioDePrioridad.hpp"

const unsigned int MenuInventarioDePrioridad::ALTA = 0;
const unsigned int MenuInventarioDePrioridad::BAJA_ARMA_FUERTE = 1;
const unsigned int MenuInventarioDePrioridad::BAJA_ARMA_DEBIL = 2;
const unsigned int MenuInventarioDePrioridad::CONSULTA_ARMA_FUERTE = 3;
const unsigned int MenuInventarioDePrioridad::CONSULTA_ARMA_DEBIL = 4;
const unsigned int MenuInventarioDePrioridad::VOLVER = 5;

const std::map<std::string, unsigned int> MenuInventarioDePrioridad::opciones_menu = {
        std::pair<std::string, unsigned int>("alta", ALTA),
        std::pair<std::string, unsigned int>("0", ALTA),

        std::pair<std::string, unsigned int>("baja arma fuerte", BAJA_ARMA_FUERTE),
        std::pair<std::string, unsigned int>("1", BAJA_ARMA_FUERTE),

        std::pair<std::string, unsigned int>("baja arma debil", BAJA_ARMA_DEBIL),
        std::pair<std::string, unsigned int>("2", BAJA_ARMA_DEBIL),

        std::pair<std::string, unsigned int>("consulta arma fuerte", CONSULTA_ARMA_FUERTE),
        std::pair<std::string, unsigned int>("3", CONSULTA_ARMA_FUERTE),

        std::pair<std::string, unsigned int>("consulta arma debil", CONSULTA_ARMA_DEBIL),
        std::pair<std::string, unsigned int>("4", CONSULTA_ARMA_DEBIL),

        std::pair<std::string, unsigned int>("volver", VOLVER),
        std::pair<std::string, unsigned int>("5", VOLVER)
};
