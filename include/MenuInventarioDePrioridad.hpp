#ifndef MENU_INVENTARIO_DE_PRIORIDAD_HPP
#define MENU_INVENTARIO_DE_PRIORIDAD_HPP

#include <map>
#include <string>
#include <InventarioDePrioridad.hpp>

class MenuInventarioDePrioridad {
private:

    static const unsigned short int ALTA;
    static const unsigned short int BAJA_ARMA_FUERTE;
    static const unsigned short int BAJA_ARMA_DEBIL;
    static const unsigned short int CONSULTA_ARMA_FUERTE;
    static const unsigned short int CONSULTA_ARMA_DEBIL;
    static const unsigned short int VOLVER;
    static const unsigned short int OPCION_INVALIDA;

    static const std::string MENSAJE_INVENTARIO_VACIO;

    static const std::map<std::string, unsigned short int> opciones_menu;

    // Pre: ~
    // Pos: imprime las opciones del menu de inventario de prioridad
    static void imprimir();

    // Pre: ~
    // Pos: pide la opcion al usuario y la guarda en opcion
    static void pedir_opcion(std::string &opcion);

    // Pre: ~
    // Pos: devuelve el valor relacionado a opcion, si la opción no es válida devuelve el máximo del tipo 'unsigned int'
    static unsigned int procesar_opcion(std::string &opcion);

    static void pedir_arma(std::string &nombre_nuevo_arma, std::size_t &potencia_nuevo_arma);

public:

    // Pre: ~
    // Pos: ejecuta el menu de inventario de prioridad
    static void ejecutar(InventarioDePrioridad &inventario);
};

#endif //MENU_INVENTARIO_DE_PRIORIDAD_HPP
