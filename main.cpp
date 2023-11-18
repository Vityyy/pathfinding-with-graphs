#include <string>
#include "InventarioDePrioridad.hpp"
#include "Menu.hpp"

using namespace std;

int main() {
    string mensaje_descifrado;
    InventarioDePrioridad inventario;
    Menu::ejecutar(mensaje_descifrado, inventario);

    return 0;
}