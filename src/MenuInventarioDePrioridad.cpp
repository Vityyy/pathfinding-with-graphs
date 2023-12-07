#include "MenuInventarioDePrioridad.hpp"
#include <iostream>

using namespace std;

const unsigned short int MenuInventarioDePrioridad::ALTA = 0;
const unsigned short int MenuInventarioDePrioridad::BAJA_ARMA_FUERTE = 1;
const unsigned short int MenuInventarioDePrioridad::BAJA_ARMA_DEBIL = 2;
const unsigned short int MenuInventarioDePrioridad::CONSULTA_ARMA_FUERTE = 3;
const unsigned short int MenuInventarioDePrioridad::CONSULTA_ARMA_DEBIL = 4;
const unsigned short int MenuInventarioDePrioridad::VOLVER = 5;
const unsigned short int MenuInventarioDePrioridad::OPCION_INVALIDA = 6;

const map<string, unsigned short int> MenuInventarioDePrioridad::opciones_menu = {
        pair<string, unsigned short int>("alta", ALTA),
        pair<string, unsigned short int>("0", ALTA),

        pair<string, unsigned short int>("baja arma fuerte", BAJA_ARMA_FUERTE),
        pair<string, unsigned short int>("1", BAJA_ARMA_FUERTE),

        pair<string, unsigned short int>("baja arma debil", BAJA_ARMA_DEBIL),
        pair<string, unsigned short int>("2", BAJA_ARMA_DEBIL),

        pair<string, unsigned short int>("consulta arma fuerte", CONSULTA_ARMA_FUERTE),
        pair<string, unsigned short int>("3", CONSULTA_ARMA_FUERTE),

        pair<string, unsigned short int>("consulta arma debil", CONSULTA_ARMA_DEBIL),
        pair<string, unsigned short int>("4", CONSULTA_ARMA_DEBIL),

        pair<string, unsigned short int>("volver", VOLVER),
        pair<string, unsigned short int>("5", VOLVER)
};

void MenuInventarioDePrioridad::imprimir() {
    cout << ".:MENU DE TESTEO DEL INVENTARIO DE PRIORIDAD:." << endl;
    cout << "[" << ALTA << "] Alta" << endl;
    cout << "[" << BAJA_ARMA_FUERTE << "] Baja arma fuerte" << endl;
    cout << "[" << BAJA_ARMA_DEBIL << "] Baja arma debil" << endl;
    cout << "[" << CONSULTA_ARMA_FUERTE << "] Consulta arma fuerte" << endl;
    cout << "[" << CONSULTA_ARMA_DEBIL << "] Consulta arma debil" << endl;
    cout << "[" << VOLVER << "] Volver" << endl;
}

void MenuInventarioDePrioridad::pedir_opcion(string &opcion) {
    cout << "Opcion: ";
    getline(cin >> ws, opcion);
}

unsigned int MenuInventarioDePrioridad::procesar_opcion(string &opcion) {
    for(char & i : opcion){
        i = (char) tolower(i);
    }

    auto opcion_procesada = opciones_menu.find(opcion);
    return (opcion_procesada != opciones_menu.end()) ? (opcion_procesada->second) : (OPCION_INVALIDA);
}

void MenuInventarioDePrioridad::pedir_arma(string &nombre_nuevo_arma, size_t &potencia_nuevo_arma) {
    cout << "Nombre del arma: ";
    getline(cin >> ws, nombre_nuevo_arma);

    cout << "Potencia del arma: ";
    cin >> potencia_nuevo_arma;
}

void MenuInventarioDePrioridad::ejecutar(InventarioDePrioridad &inventario) {
    string opcion;
    unsigned int opcion_procesada = 0;

    string nombre_nuevo_arma;
    size_t potencia_nuevo_arma;

    do {
        imprimir();
        pedir_opcion(opcion);
        opcion_procesada = procesar_opcion(opcion);

        switch (opcion_procesada) {
            case ALTA:
                pedir_arma(nombre_nuevo_arma, potencia_nuevo_arma);
                inventario.alta(Arma(nombre_nuevo_arma, potencia_nuevo_arma));
                cout << "Se dió de alta el arma " << nombre_nuevo_arma << endl << endl;
                break;

            case BAJA_ARMA_FUERTE:
                (inventario.vacio()) ? (cout << "El inventario está vacío" << endl << endl) : (cout << "Se dió de baja el arma " << inventario.baja_arma_fuerte() << endl);
                break;

            case BAJA_ARMA_DEBIL:
                (inventario.vacio()) ? (cout << "El inventario está vacío" << endl << endl) : (cout << "Se dió de baja el arma " << inventario.baja_arma_debil() << endl);
                break;

            case CONSULTA_ARMA_FUERTE:
                (inventario.vacio()) ? (cout << "El inventario está vacío" << endl << endl) : (cout << "Arma más fuerte " << inventario.consulta_arma_fuerte() << endl);
                break;

            case CONSULTA_ARMA_DEBIL:
                (inventario.vacio()) ? (cout << "El inventario está vacío" << endl << endl) : (cout << "Arma más debil " << inventario.consulta_arma_debil() << endl);
                break;

            case VOLVER:
                break;

            default:
                cout << "Esa opción no es válida" << endl << endl;
        }

    } while (opcion_procesada != VOLVER);
}
