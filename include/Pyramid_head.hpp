#ifndef PYRAMID_HEAD_HPP
#define PYRAMID_HEAD_HPP

#include <vector>
#include "Tablero.hpp"

class Pyramid_head {
private:
    std::size_t localizacion{};
    std::size_t coordenada_x{};
    std::size_t coordenada_y{};
    std::vector<std::size_t> casillas_adyacentes;

public:

    // Constructores
    Pyramid_head() = default;

    // Pre: coordenada_x es menor a la cantidad de "filas" de layout_actual,
    //      coordenada_y es menor a la cantidad de "columnas" de layout_actual
    //      layout_en_uso[coordenada_y][coodenada_x] es un numero positivo

    // Pos: crea un pyramid head ubicado en layout_en_uso[coordenada_y][coordenada_x]
    Pyramid_head(std::size_t coordenada_x, std::size_t coordenada_y, Matriz layout_actual);

    // Pre: coordenada_x es menor a la cantidad de "filas" de layout_actual,
    //      coordenada_y es menor a la cantidad de "columnas" de layout_actual
    //      layout_en_uso[coordenada_y][coodenada_x] es un numero positivo

    // Pos: setea al pyramid head en la posicion layout_en_uso[coordenada_y][coordenada_x]
    void set(std::size_t nueva_coordenada_x, std::size_t nueva_coordenada_y, Matriz layout_actual);

    // Pre: ~
    // Pos: devuelve la localizacion del pyramid head
    [[nodiscard]] std::size_t posicion() const;

    // Pre: ~
    // Pos: devuelve la coordenada en x del pyramid head
    [[nodiscard]] std::size_t x() const;

    // Pre: ~
    // Pos: devuelve la coordenada en y del pyramid head
    [[nodiscard]] std::size_t y() const;

    // Pre: ~
    // Pos: devuelve las casillas adyacentes al pyramid head
    std::vector<std::size_t> adyacentes();
};

#endif //PYRAMID_HEAD_HPP
