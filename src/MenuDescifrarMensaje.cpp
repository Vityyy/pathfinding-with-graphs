#include "MenuDescifrarMensaje.hpp"
#include <iostream>
#include "ABB.hpp"
#include "Placa.hpp"
#include "bGVjdG9y.hpp"
#include <sstream>

using namespace std;

const unsigned short int MenuDescifrarMensaje::DESCIFRAR_MENSAJE = 0;
const unsigned short int MenuDescifrarMensaje::IMPRIMIR_MENSAJE = 1;
const unsigned short int MenuDescifrarMensaje::VOLVER = 2;
const unsigned short int MenuDescifrarMensaje::OPCION_INVALIDA= 3;

const map<string, unsigned short int> MenuDescifrarMensaje::opciones_menu{
        pair<string, unsigned short int>("descifrar mensaje", DESCIFRAR_MENSAJE),
        pair<string, unsigned short int>("0", DESCIFRAR_MENSAJE),

        pair<string, unsigned short int>("imprimir_mensaje", IMPRIMIR_MENSAJE),
        pair<string, unsigned short int>("1", IMPRIMIR_MENSAJE),

        pair<string, unsigned short int>("volver", VOLVER),
        pair<string, unsigned short int>("2", VOLVER)
};

void MenuDescifrarMensaje::imprimir() {
    cout << ".:MENU DE TESTEO DE DESCIFRADO DE MENSAJES:." << endl;
    cout << "[" << DESCIFRAR_MENSAJE << "] Descifrar Mensaje" << endl;
    cout << "[" << IMPRIMIR_MENSAJE << "] Imprimir mensaje" << endl;
    cout << "[" << VOLVER << "] Volver" << endl;
}

void MenuDescifrarMensaje::pedir_opcion(string &opcion) {
    cout << "Opcion: ";
    getline(cin >> ws, opcion);
}

unsigned int MenuDescifrarMensaje::procesar_opcion(string &opcion) {
    for(char & i : opcion){
        i = (char) tolower(i);
    }

    auto opcion_procesada = opciones_menu.find(opcion);
    return (opcion_procesada != opciones_menu.end()) ? (opcion_procesada->second) : (OPCION_INVALIDA);
}

void MenuDescifrarMensaje::descifrar_mensaje(string &mensaje_descifrado) {
    ABB<Placa *, Placa::menor, Placa::igual> mensaje_desordenado{};
    bGVjdG9y::Y2FyZ2Fy(mensaje_desordenado);

    vector<Placa *> mensaje_ordenado = mensaje_desordenado.preorder();

    stringstream stream_mensaje_descifrado;

    for (auto & i : mensaje_ordenado) {
        stream_mensaje_descifrado << *i;
    }

    mensaje_descifrado = stream_mensaje_descifrado.str();

    for (auto & i : mensaje_ordenado) {
        delete i;
        i = nullptr;
    }

    cout << "El mensaje fue descifrado con éxito" << endl << endl;
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
                (mensaje_descifrado.empty()) ? (cout << "El mensaje no ha sido descifrado" << endl << endl) : (cout << mensaje_descifrado << endl);
                break;

            case VOLVER:
                break;

            default:
                cout << "Esa opción no es válida" << endl;
        }

    } while (opcion_procesada != VOLVER);
}