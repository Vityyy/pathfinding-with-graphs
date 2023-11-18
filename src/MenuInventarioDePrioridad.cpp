#include "MenuInventarioDePrioridad.hpp"
#include <iostream>

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

void MenuInventarioDePrioridad::imprimir() {
    std::cout << ".:MENU DE TESTEO DEL INVENTARIO DE PRIORIDAD:." << std::endl;
    std::cout << "[" << ALTA << "] Alta" << std::endl;
    std::cout << "[" << BAJA_ARMA_FUERTE << "] Baja arma fuerte" << std::endl;
    std::cout << "[" << BAJA_ARMA_DEBIL << "] Baja arma debil" << std::endl;
    std::cout << "[" << CONSULTA_ARMA_FUERTE << "] Consulta arma fuerte" << std::endl;
    std::cout << "[" << CONSULTA_ARMA_DEBIL << "] Consulta arma debil" << std::endl;
    std::cout << "[" << VOLVER << "] Volver" << std::endl;
}

void MenuInventarioDePrioridad::pedir_opcion(std::string &opcion) {
    std::cout << "Opcion: ";
    getline(std::cin >> std::ws, opcion);
}

unsigned int MenuInventarioDePrioridad::procesar_opcion(std::string &opcion) {
    for(char & i : opcion){
        i = (char) tolower(i);
    }

    return opciones_menu.find(opcion)->second;
}

void MenuInventarioDePrioridad::pedir_arma(std::string &nombre_nuevo_arma, size_t &potencia_nuevo_arma) {
    std::cout << "Nombre del arma: ";
    getline(std::cin >> std::ws, nombre_nuevo_arma);

    std::cout << "Potencia del arma: ";
    std::cin >> potencia_nuevo_arma;
}

void MenuInventarioDePrioridad::ejecutar(InventarioDePrioridad &inventario) {
    std::string opcion;
    unsigned int opcion_procesada = 0;

    std::string nombre_nuevo_arma;
    std::size_t potencia_nuevo_arma;

    do {
        imprimir();
        pedir_opcion(opcion);
        opcion_procesada = procesar_opcion(opcion);

        switch (opcion_procesada) {
            case ALTA:
                pedir_arma(nombre_nuevo_arma, potencia_nuevo_arma);
                inventario.alta(Arma(nombre_nuevo_arma, potencia_nuevo_arma));
                break;

            case BAJA_ARMA_FUERTE:
                std::cout << "El arma " << inventario.baja_arma_fuerte() << " fue dada de baja con exito" << std::endl;
                break;

            case BAJA_ARMA_DEBIL:
                std::cout << "El arma " << inventario.baja_arma_debil() << " fue dada de baja con exito" << std::endl;
                break;

            case CONSULTA_ARMA_FUERTE:
                std::cout << "Arma mas fuerte: " << inventario.consulta_arma_fuerte() << std::endl;
                break;

            case CONSULTA_ARMA_DEBIL:
                std::cout << "Arma mas debil: " << inventario.consulta_arma_debil() << std::endl;
                break;

            case VOLVER:
                system("clear");
                break;

            default:
                std::cout << "Esa opción no es válida" << std::endl;
        }

    } while (opcion_procesada != VOLVER);
}
