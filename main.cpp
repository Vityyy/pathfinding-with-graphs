#include "bGVjdG9y.hpp"
#include "Placa.hpp"
#include "ABB.hpp"
#include <iostream>

using namespace std;

int main() {
    ABB<Placa *, Placa::menor, Placa::igual> arbol{};
    bGVjdG9y::Y2FyZ2Fy(arbol);

    vector<Placa *> mensaje_descifrado = arbol.preorder();

    for (size_t i = 0; i < mensaje_descifrado.size(); i++) {
        cout << *(mensaje_descifrado[i]);
    }

    for (size_t i = 0; i < mensaje_descifrado.size(); i++) {
        delete mensaje_descifrado[i];
    }

    return 0;
}