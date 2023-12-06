#ifndef TP3_GRUPO_NULLPTRS_JAMES_HPP
#define TP3_GRUPO_NULLPTRS_JAMES_HPP

#include "InventarioDePrioridad.hpp"
#include "CoordenadaMatriz.hpp"
#include "ABB.hpp"
#include "Placa.hpp"

class James {
private:

    CoordenadaMatriz coordenada{8, 0};
    InventarioDePrioridad armas{};
    Arma *arma_actual = nullptr;
    ABB<Placa *, Placa::menor, Placa::igual> placas{};

    // Pre: ~
    // Pos: libera la memoria de las placas
    void liberar_placas();

public:
    // Constructor default
    James() = default;

    // Pre: ~
    // Pos: devuelve la coordenada
    CoordenadaMatriz &posicion();

    // Pre: ~
    // Pos: agrega un arma al inventario
    void obtener_arma(const Arma &arma);

    // Pre: ~
    // Pos: equipa el arma más fuerte
    void equipar_arma_fuerte();

    // Pre: ~
    // Pos: equipa el arma más débil
    void equipar_arma_debil();

    // Pre: ~
    // Pos: desequipa el arma actual, si no tiene un arma equipada hace nada
    void desequipar_arma();

    // Pre: ~
    // Pos: devuelve la cantidad de armas que tiene james
    std::size_t cantidad_de_armas();

    // Pre: ~
    // Pos: devuelve true si tiene un arma equipada
    bool tiene_arma_equipada();

    // Pre: ~
    // Pos: pierde el arma equipada
    void perder_arma_equipada();

    // Pre: no existe una placa con ese id
    //Pos: agrega una placa al arbol de placas
    void agregar_placa(Placa *placa);

    // Pre: ~
    // Pos: devuelve true si tiene una placa con ese id
    bool tiene_placa(Placa *placa);

    // Pre: ~
    // Pos: devuelve la altura de las placas
    std::size_t altura_placas();

    // Destructor
    // Pre: ~
    // Pos: libera la memoria de arma_actual
    ~James();
};

#endif //TP3_GRUPO_NULLPTRS_JAMES_HPP
