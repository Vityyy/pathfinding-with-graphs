#ifndef COORDENADAMATRIZ_HPP
#define COORDENADAMATRIZ_HPP

#include <cstddef>

class CoordenadaMatriz {
private:
    std::size_t fila{};
    std::size_t columna{};

public:
    CoordenadaMatriz() = default;

    CoordenadaMatriz(std::size_t fil, std::size_t col);

    std::size_t &fil();

    std::size_t &col();

    bool operator==(const CoordenadaMatriz &coordenada) const;

    bool operator!=(const CoordenadaMatriz &coordenada) const;
};


#endif //COORDENADAMATRIZ_HPP
