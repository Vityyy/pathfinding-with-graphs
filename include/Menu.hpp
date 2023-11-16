#ifndef MENU_HPP
#define MENU_HPP

#include <map>
#include <string>
#include "InventarioDePrioridad.hpp"

class Menu {
private:

    static const unsigned int DESCIFRAR_MENSAJE;
    static const unsigned int INVENTARIO_DE_PRIORIDAD;
    static const unsigned int SALIR;

    static const std::map<std::string, unsigned int> opciones_menu;

    // Pre: ~
    // Pos: imprime las opciones del menu
    static void imprimir();

    // Pre: ~
    // Pos: pide la opcion al usuario y la guarda en opcion
    static void pedir_opcion(std::string &opcion);

    // Pre: ~
    // Pos: devuelve el valor relacionado a opcion, si la opción no es válida devuelve el máximo del tipo 'unsigned int'
    static unsigned int procesar_opcion(const std::string &opcion);

public:

    // Pre: ~
    // Pos: ejecuta el menu
    static void ejecutar(std::string mensaje_descifrado, InventarioDePrioridad &inventario);
};

#endif //MENU_HPP
