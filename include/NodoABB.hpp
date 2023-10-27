#ifndef NODOABB_H
#define NODOABB_H

#include <vector>
#include <queue>

template<typename T, bool menor(T, T), bool igual(T, T)>
class NodoABB {

private:
    T dato{};
    NodoABB<T, menor, igual> *padre;
    NodoABB<T, menor, igual> *hijo_izquierdo;
    NodoABB<T, menor, igual> *hijo_derecho;
public:
    // Constructor.
    NodoABB(T dato);

    // Pre: -
    // Post: Agrega el dato al árbol.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    void alta(T dato_insertar);

    // Pre: -
    // Post: Elimina el dato del árbol y devuelve la nueva raiz, de haberla.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    NodoABB<T, menor, igual> *baja(T dato_bajar);

    // Pre: -
    // Post: Devuelve true si el dato está en el subárbol.
    bool consulta(T dato_consultar);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido inorder.
    void inorder(std::vector<T> &datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido preorder.
    void preorder(std::vector<T> &datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido postorder.
    void postorder(std::vector<T> &datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido en ancho.
    void ancho(std::queue<NodoABB<T, menor, igual> *> &nodos, std::vector<T> &datos);

    // Pre: -
    // Post: Ejecuta el método/función en el subárbol.
    void ejecutar(void metodo(T));

    // Destructor.
    ~NodoABB();
};

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual>::NodoABB(T dato) {
    this->dato = dato;
    padre = nullptr;
    hijo_derecho = nullptr;
    hijo_izquierdo = nullptr;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::alta(T dato_insertar) {
    if (menor(dato_insertar, dato)) {
        if (hijo_izquierdo != nullptr) {
            hijo_izquierdo->alta(dato_insertar);
        } else {
            hijo_izquierdo = new NodoABB<T, menor, igual>(dato_insertar);
            hijo_izquierdo->padre = this;
        }
    } else {
        if (hijo_derecho != nullptr) {
            hijo_derecho->alta(dato_insertar);
        } else {
            hijo_derecho = new NodoABB<T, menor, igual>(dato_insertar);
            hijo_derecho->padre = this;
        }
    }
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
bool NodoABB<T, menor, igual>::consulta(T dato_consultar) {
    if (igual(dato_consultar, dato)) {
        return true;
    }

    if (menor(dato_consultar, dato)) {
        if (hijo_izquierdo != nullptr) {
            return hijo_izquierdo->consulta(dato_consultar);
        }

        return false;
    }

    if (hijo_derecho != nullptr) {
        return hijo_derecho->consulta(dato_consultar);
    }

    return false;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::inorder(std::vector<T> &datos) {
    if (hijo_izquierdo != nullptr) {
        hijo_izquierdo->inorder(datos);
    }

    datos.push_back(dato);

    if (hijo_derecho != nullptr) {
        hijo_derecho->inorder(datos);
    }
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::preorder(std::vector<T> &datos) {
    datos.push_back(dato);

    if (hijo_izquierdo != nullptr) {
        hijo_izquierdo->preorder(datos);
    }

    if (hijo_derecho != nullptr) {
        hijo_derecho->preorder(datos);
    }
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::postorder(std::vector<T> &datos) {
    if (hijo_izquierdo != nullptr) {
        hijo_izquierdo->postorder(datos);
    }

    if (hijo_derecho != nullptr) {
        hijo_derecho->postorder(datos);
    }

    datos.push_back(dato);
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::ejecutar(void (*metodo)(T)) {
    if (hijo_izquierdo != nullptr) {
        hijo_izquierdo->metodo();
    }

    if (hijo_derecho != nullptr) {
        hijo_derecho->metodo();
    }

    this->metodo();
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual>::~NodoABB() {
    padre = nullptr;
    hijo_derecho = nullptr;
    hijo_izquierdo = nullptr;
}

#endif