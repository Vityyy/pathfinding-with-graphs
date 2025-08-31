# 🗺️ James's Challenges — Path Finding with Graphs

<div align="center">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" />
  <img src="https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" />
  <img src="https://img.shields.io/badge/Algorithms-FF6B35?style=for-the-badge&logo=algorithms&logoColor=white" />
  <img src="https://img.shields.io/badge/Graph_Theory-2E8B57?style=for-the-badge&logo=graphql&logoColor=white" />
</div>

<div align="center">
  <img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">
</div>

> **📚 Academic Project Notice**  
> This project was developed during our **second year** of the Computer Engineering program at the University of Buenos Aires. _This repository **does not** reflect our current programming level or professional skills. It is kept here as an academic and knowledge record._

---

## 🤖 About

**James's Challenges**, _(Los Desafíos de James)_, is an advanced **pathfinding and graph algorithms** implementation developed for the **Algorithms and Programming 2** course at **FIUBA**. This project demonstrates sophisticated graph traversal techniques, shortest path algorithms, and optimal route finding in complex network structures.

### 🎯 Core Features
- **🔍 Advanced Pathfinding** algorithms (Dijkstra, A*, BFS, DFS)
- **📊 Graph Data Structures** with efficient representation
- **🚀 Optimized Performance** using C++ STL containers
- **🧪 Comprehensive Testing** suite for algorithm validation
- **📐 Multiple Graph Types** support (weighted, unweighted, directed, undirected)

### 🔧 Technical Implementation
- **Modern C++** with STL algorithms and data structures
- **CMake build system** for cross-platform compilation
- **Template-based design** for generic graph operations
- **Memory-efficient** adjacency list and matrix representations

---

## 🛠️ Compilation

### Using CMake (Recommended)
```bash
# Create build directory
mkdir build && cd build

# Configure and compile
cmake ..
make
```

### Manual Compilation
```bash
g++ -I include src/*.cpp main.cpp -o main -Wall -Werror -Wconversion
```

### CMake Configuration
When using CMake, add all `.cpp` files to the executable line:
```cmake
add_executable(ayp2_plantilla_tp_grupal_2c2023 main.cpp 
    src/graph.cpp 
    src/pathfinding.cpp 
    # Add other .cpp files here
)
```

---

## 🧪 Testing & Validation

### Run Test Suite
```bash
# Navigate to tests directory
cd tests/

# Compile and run tests using CMake
mkdir build && cd build
cmake ..
make
./test_runner
```

### Test Coverage
The testing suite validates:
- **Graph construction** and manipulation
- **Pathfinding algorithm** correctness
- **Edge cases** and boundary conditions
- **Performance benchmarks** for large graphs

---

## 🏗️ Project Structure

```
├── src/                    # Implementation files (.cpp)
│   ├── graph.cpp          # Graph data structure
│   ├── pathfinding.cpp    # Pathfinding algorithms
│   └── utilities.cpp      # Helper functions
├── include/               # Header files (.h/.hpp)
│   ├── graph.h           # Graph class definitions
│   ├── pathfinding.h     # Algorithm declarations
│   └── utilities.h       # Utility functions
├── tests/                # Testing framework
│   ├── CMakeLists.txt    # Test compilation setup
│   └── test_*.cpp        # Individual test files
├── main.cpp              # Main application entry
└── CMakeLists.txt        # Build configuration
```

---

## 📊 Algorithms Implemented

### 🔍 Pathfinding Algorithms
- **Dijkstra's Algorithm** — Shortest path in weighted graphs
- **A* Search** — Heuristic-based optimal pathfinding
- **Breadth-First Search (BFS)** — Unweighted shortest path
- **Depth-First Search (DFS)** — Graph traversal and exploration

### 📈 Graph Operations
- **Graph Construction** — Dynamic node and edge addition
- **Connectivity Analysis** — Component detection and analysis
- **Cycle Detection** — Finding cycles in directed/undirected graphs
- **Minimum Spanning Tree** — Optimal tree construction

---

## 🔧 Development Guidelines

### Compiler Flags
The project uses strict compilation flags for code quality:
- `-Wall` — Enable all warnings
- `-Werror` — Treat warnings as errors
- `-Wconversion` — Warn about type conversions

### Code Organization
- **Separation of concerns** between headers and implementation
- **Modular design** for easy testing and maintenance
- **CMake integration** for professional build management

---

<div align="center">
  <img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">
  
  **Built with ⚡ C++ & 📊 Graph Theory at Universidad de Buenos Aires**
</div>
