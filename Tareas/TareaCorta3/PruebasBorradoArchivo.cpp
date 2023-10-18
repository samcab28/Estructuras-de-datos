#include <iostream>
#include <vector>

int main() {
    // Declarar una matriz 20x3 utilizando std::vector
    std::vector<std::vector<int> > matriz(20, std::vector<int>(3));

    // Inicializar la matriz (opcional)
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 3; j++) {
            matriz[i][j] = i * 3 + j; // Puedes usar cualquier valor que desees
        }
    }

    // Acceder y mostrar elementos de la matriz (opcional)
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

