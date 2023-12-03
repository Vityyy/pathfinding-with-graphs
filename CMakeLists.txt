cmake_minimum_required(VERSION 3.22)
project(TP3_Grupo_Nullptrs)

set(CMAKE_C_STANDARD 23)

add_compile_options(-Wall -Werror -Wconversion)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
set(CXXFLAGS "-Wall -Werror -Wconversion")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

include_directories(include)
include_directories(src)
include_directories(bGVjdG9y)

add_executable(TP3_Grupo_Nullptrs
        include/ABB.hpp
        include/CaminoMinimo.hpp
        include/Heap.hpp
        include/NodoABB.hpp
        src/Placa.cpp
        src/Arma.cpp
        src/Grafo.cpp
        src/Floyd.cpp
        src/Dijkstra.cpp
        src/Matriz.cpp
        bGVjdG9y/bGVjdG9y.cpp
        bGVjdG9y/ZGVjb2Rl.cpp
        main.cpp
        src/InventarioDePrioridad.cpp
        include/InventarioDePrioridad.hpp
        src/Menu.cpp
        include/Menu.hpp
        src/MenuDescifrarMensaje.cpp
        include/MenuDescifrarMensaje.hpp
        src/MenuInventarioDePrioridad.cpp
        include/MenuInventarioDePrioridad.hpp
        src/Juego.cpp
        src/Tablero.cpp
        src/Pyramid_head.cpp
        src/CoordenadaMatriz.cpp
        src/James.cpp
        include/color.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")