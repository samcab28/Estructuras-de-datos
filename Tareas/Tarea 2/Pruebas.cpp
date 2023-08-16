#include <iostream>
#include <cmath>  // Para usar la función std::abs

bool esEntero(double numero) {
    return std::abs(numero - static_cast<int>(numero)) < 1e-9;  // Pequeña tolerancia para manejar errores de precisión
}

int main() {
    int num1 = 5;
    double num2 = 5.5;

    if (esEntero(num1)) {
        std::cout << num1 << " es un número entero." << std::endl;
    } else {
        std::cout << num1 << " no es un número entero." << std::endl;
    }

    if (esEntero(num2)) {
        std::cout << num2 << " es un número entero." << std::endl;
    } else {
        std::cout << num2 << " no es un número entero." << std::endl;
    }

    return 0;
}


