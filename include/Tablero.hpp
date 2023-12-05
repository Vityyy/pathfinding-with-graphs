#ifndef TABLERO_HPP
#define TABLERO_HPP

#include "Grafo.hpp"
#include <string>
#include <fstream>
#include "CoordenadaMatriz.hpp"

class Tablero {
public:
    static const int TAMANIO_TABLERO = 9;
    static const int PARED = 1;
    static const std::size_t MAXIMO_TAMANIO_TABLERO = 81;

private:
    Matriz casillas{TAMANIO_TABLERO};
    Grafo grafo_casillas{MAXIMO_TAMANIO_TABLERO};

    // Pre: ~
    // Pos: conecta los vertices de casillas basandose en tablero
    void conectar_vertices(Matriz tablero);

    // Pre: ~
    // Pos: devuelve un vector con las palabras separadas por el separador
    std::vector<std::string> split(const std::string &linea, char separador);

    // Pre: ~
    // Pos: elimina las aristas que conectan a las casillas
    void descargar_nivel();

public:

    // Pre: ~
    // Pos: Crea un tablero de 81 casillas
    Tablero() = default;

    // Pre: el archivo existe y es válido, el nombre_archivo no debe contener la extension
    // Pos: carga un nivel en base al archivo
    void cargar_nivel(const std::string &nombre_archivo);

    // Pre: ~
    // Pos: desconecta una casilla de sus casillas adyacentes
    void desconectar_casilla(CoordenadaMatriz casilla);

    // Pre: ~
    // Pos: devuelve el camino mínimo desde el origen hasta el destino
    std::pair<std::vector<CoordenadaMatriz>, int> camino_minimo(CoordenadaMatriz origen, CoordenadaMatriz destino);

    // Pre: ~
    // Pos: devuelve la casilla en la posicion (fila, columna)
    [[nodiscard("Se ignora el retorno de casilla()")]] int casilla(std::size_t fila, std::size_t columna);
};

#endif //TABLERO_HPP
