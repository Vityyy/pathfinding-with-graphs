#ifndef PYRAMID_HEAD_HPP
#define PYRAMID_HEAD_HPP

#include <vector>
#include "Tablero.hpp"
#include "CoordenadaMatriz.hpp"

class Pyramid_head {
private:
    CoordenadaMatriz coordenada{0, 0};
    std::vector<CoordenadaMatriz> casillas_adyacentes{};

public:

    // Pre: ~
    // Pos: crea un pyramid head ubicado en (fila, columna)
    Pyramid_head(CoordenadaMatriz coordenada, Tablero tablero_de_juego);

    // Pre: ~
    // Pos: devuelve la localizacion del pyramid head
    [[nodiscard("Se ignora el retorno de posicion()")]] CoordenadaMatriz posicion() const;

    // Pre: ~
    // Pos: devuelve las casillas adyacentes al pyramid head
    [[nodiscard("Se ignora el retorno de adyacentes()")]] std::vector<CoordenadaMatriz> adyacentes();
};

#endif //PYRAMID_HEAD_HPP
