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

    static const size_t DOS_HIJOS = 2;
    static const size_t UN_HIJO = 1;
    static const size_t SIN_HIJOS = 0;

    // Pre: ~
    // Pos: retorna la cantidad de hijos que tiene un nodo
    size_t cantidad_hijos();

    // Pre: nodo != nullptr
    // Pos: devuelve el mínimo del subarbol
    NodoABB<T, menor, igual> *minimo(NodoABB<T, menor, igual> *nodo);

    // Pre: ~
    // Pos: retorna el nodo sucesor al nodo que contiene dato
    NodoABB<T, menor, igual> *sucesor();

    // Pre: ~
    // Pos: retorna true si el nodo es hijo izquierdo de su nodo padre
    bool es_hijo_izquierdo();

    // Pre: el nodo es hoja
    // Pos: desconecta al nodo de su padre
    void desconectar();

    //pre:
    //post: desconecta a los hijos de su padre
    void desconectar_hijos();

    // Pre: el nodo tiene un hijo
    // Pos: conecta al hijo correspondiente del nodo con su padre, asignando el hijo correcto al padre
    void bypass();

    // Pre: ~
    // Pos: reemplaza el nodo por nodo_reemplazo
    void reemplazar(NodoABB<T, menor, igual> *nodo_reemplazo);

    // Pre: padre == nullptr
    // Pos: Elimina la raiz y devuelve la nueva raiz.

    NodoABB<T, menor, igual> *baja_0_hijos();

    NodoABB<T, menor, igual> *baja_1_hijo();

    NodoABB<T, menor, igual> *baja_2_hijos();

    // Pre: padre != nullptr
    // Pos: elimina el nodo
    NodoABB<T, menor, igual> *baja_interna();

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
size_t NodoABB<T, menor, igual>::cantidad_hijos() {
    if (hijo_izquierdo != nullptr && hijo_derecho != nullptr) {
        return DOS_HIJOS;
    }

    if (hijo_izquierdo != nullptr || hijo_derecho != nullptr) {
        return UN_HIJO;
    }

    return SIN_HIJOS;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual> *NodoABB<T, menor, igual>::minimo(NodoABB<T, menor, igual> *nodo) {
    if (nodo->hijo_izquierdo != nullptr) {
        return nodo->minimo(nodo->hijo_izquierdo);
    }

    return nodo;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual> *NodoABB<T, menor, igual>::sucesor() {
    if (hijo_derecho != nullptr) {
        return minimo(hijo_derecho);
    }

    NodoABB<T, menor, igual> *padre_aux = padre;
    NodoABB<T, menor, igual> *this_aux = this;
    while (padre_aux != nullptr && this_aux == padre->hijo_derecho) {
        this_aux = padre_aux;
        padre_aux = this_aux->padre;
    }

    if (padre_aux != nullptr) {
        return padre_aux;
    }

    return nullptr;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
bool NodoABB<T, menor, igual>::es_hijo_izquierdo() {
    if (padre == nullptr) {
        return false;
    }

    if (menor(this->dato, padre->dato)) {
        return true;
    }

    return false;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::desconectar() {
    if (es_hijo_izquierdo()) {
        padre->hijo_izquierdo = nullptr;
    } else {
        padre->hijo_derecho = nullptr;
    }
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::desconectar_hijos() {
    hijo_izquierdo = nullptr;
    hijo_derecho = nullptr;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::bypass() {
    if (es_hijo_izquierdo()) {
        padre->hijo_izquierdo = hijo_derecho;
        hijo_derecho->padre = padre;
    } else {
        padre->hijo_derecho = hijo_derecho;
        hijo_derecho->padre = padre;
    }
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::reemplazar(NodoABB<T, menor, igual> *nodo_reemplazo) {
    nodo_reemplazo->padre = padre;
    nodo_reemplazo->hijo_derecho = hijo_derecho;
    nodo_reemplazo->hijo_izquierdo = hijo_izquierdo;

    if (padre != nullptr) {
        if (es_hijo_izquierdo()) {
            padre->hijo_izquierdo = nodo_reemplazo;
        } else {
            padre->hijo_derecho = nodo_reemplazo;
        }
    }

    if (hijo_izquierdo != nullptr) {
        hijo_izquierdo->padre = nodo_reemplazo;
    }

    if (hijo_derecho != nullptr) {
        hijo_derecho->padre = nodo_reemplazo;
    }
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual> *NodoABB<T, menor, igual>::baja_0_hijos() {
    if (padre != nullptr) {
        if (es_hijo_izquierdo()) {
            padre->hijo_izquierdo = nullptr;
        } else {
            padre->hijo_derecho = nullptr;
        }
    }

    delete this;
    return nullptr;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual> *NodoABB<T, menor, igual>::baja_1_hijo() {
    if (padre == nullptr) {
        NodoABB<T, menor, igual> *nueva_raiz;
        if (hijo_izquierdo != nullptr) {
            hijo_izquierdo->padre = nullptr;
            nueva_raiz = hijo_izquierdo;
            desconectar_hijos();
            delete this;
            return nueva_raiz;
        }

        hijo_derecho->padre = nullptr;
        nueva_raiz = hijo_derecho;
        desconectar_hijos();
        delete this;
        return nueva_raiz;
    }

    if (hijo_izquierdo != nullptr) {
        if (es_hijo_izquierdo()) {
            padre->hijo_izquierdo = hijo_izquierdo;
        } else {
            padre->hijo_derecho = hijo_izquierdo;
        }

        hijo_izquierdo->padre = padre;
    } else {
        if (es_hijo_izquierdo()) {
            padre->hijo_izquierdo = hijo_derecho;
        } else {
            padre->hijo_derecho = hijo_derecho;
        }

        hijo_derecho->padre = padre;
    }

    desconectar_hijos();
    delete this;
    return nullptr;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual> *NodoABB<T, menor, igual>::baja_2_hijos() {
    NodoABB<T, menor, igual> *nodo_reemplazo = sucesor();

    if (padre == nullptr) {
        switch (nodo_reemplazo->cantidad_hijos()) {
            case SIN_HIJOS:
                nodo_reemplazo->desconectar();
                break;

            default:
                nodo_reemplazo->bypass();
        }

        reemplazar(nodo_reemplazo);

        desconectar_hijos();
        delete this;
        return nodo_reemplazo;
    }

    switch (nodo_reemplazo->cantidad_hijos()) {
        case SIN_HIJOS:
            nodo_reemplazo->desconectar();

        default:
            nodo_reemplazo->bypass();
    }
    reemplazar(nodo_reemplazo);
    desconectar_hijos();
    delete this;
    return nullptr;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual> *NodoABB<T, menor, igual>::baja_interna() {
    switch (cantidad_hijos()) {
        case SIN_HIJOS:
            return baja_0_hijos();

        case UN_HIJO:
            return baja_1_hijo();

        default:
            return baja_2_hijos();
    }
}

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
NodoABB<T, menor, igual> *NodoABB<T, menor, igual>::baja(T dato_bajar) {
    if (menor(dato_bajar, dato) && hijo_izquierdo != nullptr) {
        return hijo_izquierdo->baja(dato_bajar);
    }

    if (!igual(dato_bajar, dato) && hijo_derecho != nullptr) {
        return hijo_derecho->baja(dato_bajar);
    }

    return baja_interna();
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
void NodoABB<T, menor, igual>::ancho(std::queue<NodoABB<T, menor, igual> *> &nodos, std::vector<T> &datos) {
    datos.push_back(dato);

    if (hijo_izquierdo != nullptr) {
        nodos.push(hijo_izquierdo);
    }

    if (hijo_derecho != nullptr) {
        nodos.push(hijo_derecho);
    }
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void NodoABB<T, menor, igual>::ejecutar(void (*metodo)(T)) {
    if (hijo_izquierdo != nullptr) {
        hijo_izquierdo->ejecutar(metodo);
    }

    if (hijo_derecho != nullptr) {
        hijo_derecho->ejecutar(metodo);
    }

    metodo();
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
NodoABB<T, menor, igual>::~NodoABB() {
    padre = nullptr;
    delete hijo_izquierdo;
    delete hijo_derecho;
    hijo_derecho = nullptr;
    hijo_izquierdo = nullptr;
}

#endif