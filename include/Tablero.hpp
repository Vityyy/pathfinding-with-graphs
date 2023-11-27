#ifndef TABLERO_HPP
#define TABLERO_HPP

#include "Grafo.hpp"

class Tablero {
public:
    static const int TAMANIO_TABLERO = 9;
    static const int PARED = -1;
    static const std::size_t MAXIMO_TAMANIO_TABLERO = 81;

private:
    Grafo casillas{};

    // Pre: ~
    // Pos: conecta los vertices de casillas basandose en tablero
    void conectar_vertices(Matriz tablero);

public:

    // Crea un tablero de 81 casillas
    Tablero();

    // Pre: ~
    // Pos: conecta las casillas basandose en tablero
    void modificar(Matriz tablero);

    // Pre: ~
    // Pos: impide el paso entre dos casillas del tablero
    void desconectar_casillas(std::size_t casilla1, std::size_t casilla2);

    // Pre: ~
    // Pos: devuelve el camino mínimo desde el origen hasta el destino
    std::pair<std::vector<std::size_t>, int> camino_minimo(std::size_t origen, std::size_t destino);
};

#endif //TABLERO_HPP
