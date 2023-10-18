#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

std::string obtenerNombrePorNumero(int numero) {
    // Abre el archivo de texto
    std::ifstream archivo("Clientes.txt");

    if (!archivo.is_open()) {
        // Si no se pudo abrir el archivo, muestra un mensaje de error
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return "";
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        // Divide la línea en número y nombre usando el punto y coma como delimitador
        size_t pos = linea.find(";");
        if (pos != std::string::npos) {
            std::istringstream stream(linea.substr(0, pos));
            int numeroEnArchivo;
            stream >> numeroEnArchivo;

            if (!stream.fail() && numeroEnArchivo == numero) {
                std::string nombre = linea.substr(pos + 1);
                archivo.close();
                return nombre;
            }
        }
    }

    // Si no se encuentra el número, cierra el archivo y devuelve una cadena vacía
    archivo.close();
    return "";
}

int main() {
    int numeroBuscado = 54; // Reemplaza con el número que desees buscar
    std::string nombreEncontrado = obtenerNombrePorNumero(numeroBuscado);

    if (!nombreEncontrado.empty()) {
        std::cout << "Nombre encontrado: " << nombreEncontrado << std::endl;
    } else {
        std::cout << "Número no encontrado en el archivo." << std::endl;
    }

    return 0;
}

