#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Necesario para la función atoi

// Función para convertir una cadena en un entero
int customAtoi(const std::string& str) {
    int result = 0;
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (isdigit(c)) {
            result = result * 10 + (c - '0');
        }
    }
    return result;
}

int customAtoiCliente(const std::string& str) {
    int result = 0;
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (isdigit(c)) {
            result = result * 10 + (c - '0');
        } else if (c == ';') {
            break; // Detener la conversión al encontrar el primer punto y coma
        }
    }
    return result;
}


void borradoIndice(int numeroBorrar){
    std::string archivoOriginal = "Indices.txt";
    std::string archivoTemporal = "temporal.txt";
    
    // Valor de numero2 que deseas borrar
    int numero2ABorrar = numeroBorrar; // Reemplaza con el valor deseado

    std::ifstream entrada(archivoOriginal.c_str());
    std::ofstream salida(archivoTemporal.c_str());

    if (!entrada.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
    }

    if (!salida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida temporal." << std::endl;
    }

    std::string linea;
    while (std::getline(entrada, linea)) {
        size_t pos = linea.find(';');
        if (pos != std::string::npos) {
            // Encontrar la parte de la línea que contiene el valor de numero2
            std::string numero2_str = linea.substr(pos + 1);
            
            // Convertir la cadena a un entero utilizando la función personalizada
            int numero2 = customAtoi(numero2_str);
            
            // Si el valor de numero2 coincide con el valor a borrar, omitir la escritura de la línea en el archivo temporal
            if (numero2 == numero2ABorrar) {
                continue;
            }
        }
        // Si el valor de numero2 no coincide con el valor a borrar, escribir la línea en el archivo temporal
        salida << linea << "\n";
    }

    // Cerrar los archivos
    entrada.close();
    salida.close();

    // Reemplazar el archivo original con el archivo temporal
    if (std::remove(archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al eliminar el archivo original." << std::endl;
    }

    if (std::rename(archivoTemporal.c_str(), archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al renombrar el archivo temporal." << std::endl;
    }

    std::cout << "Contenido del archivo modificado con éxito." << std::endl;
}

void borradoCliente(int primerNumeroBorrar){
    std::string archivoOriginal = "Clientes.txt";
    std::string archivoTemporal = "temporal.txt";
    
    // Valor del primer número que deseas borrar
    int primerNumeroABorrar = primerNumeroBorrar; // Reemplaza con el valor deseado

    std::ifstream entrada(archivoOriginal.c_str());
    std::ofstream salida(archivoTemporal.c_str());

    if (!entrada.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
    }

    if (!salida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida temporal." << std::endl;
    }

    std::string linea;
    while (std::getline(entrada, linea)) {
        int primerNumero = customAtoiCliente(linea); // Obtener el primer número de la línea
        
        // Si el primer número coincide con el valor a borrar, omitir la escritura de la línea en el archivo temporal
        if (primerNumero == primerNumeroABorrar) {
            continue;
        }
        
        // Si el primer número no coincide con el valor a borrar, escribir la línea en el archivo temporal
        salida << linea << "\n";
    }

    // Cerrar los archivos
    entrada.close();
    salida.close();

    // Reemplazar el archivo original con el archivo temporal
    if (std::remove(archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al eliminar el archivo original." << std::endl;
    }

    if (std::rename(archivoTemporal.c_str(), archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al renombrar el archivo temporal." << std::endl;
    }

    std::cout << "Contenido del archivo modificado con éxito." << std::endl;
}



int main() {
	
	borradoIndice(123);
	borradoCliente(101);
	
    return 0;
}

