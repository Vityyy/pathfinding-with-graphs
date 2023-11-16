#ifndef MENU_DESCIFRAR_MENSAJE_HPP
#define MENU_DESCIFRAR_MENSAJE_HPP

#include <map>
#include <string>

class MenuDescifrarMensaje {
private:

    static const unsigned int DESCIFRAR_MENSAJE;
    static const unsigned int IMPRIMIR_MENSAJE;
    static const unsigned int VOLVER;

    static const std::map<std::string, unsigned int> opciones_menu;

    // Pre: ~
    // Pos: imprime las opciones del menu de descifrado de mensaje
    static void imprimir();

    // Pre: ~
    // Pos: pide la opción al usuario y la guarda en opcion
    static void pedir_opcion(std::string &opcion);

    // Pre: ~
    // Pos: devuelve el valor relacionado a opcion, si la opción no es válida devuelve el máximo del tipo 'unsigned int'
    static unsigned int procesar_opcion(const std::string &opcion);

public:

    // Pre: ~
    // Pos: ejecuta el menu para descifrar el mensaje
    static void ejecutar(std::string mensaje_descifrado);
};

#endif //MENU_DESCIFRAR_MENSAJE_HPP
