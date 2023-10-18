#include <iostream>
#include <fstream>
#include <string>

// Definición de la función que busca el contenido de un cliente por número
std::string buscarContenidoCliente(const std::string& numeroBuscado) {
    std::ifstream archivo("Clientes.txt");

    if (!archivo.is_open()) {
        return "Error: No se pudo abrir el archivo.";
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        size_t pos = linea.find(';');
        if (pos != std::string::npos) {
            std::string numero = linea.substr(0, pos);
            std::string nombre = linea.substr(pos + 1);
            if (numero == numeroBuscado) {
                archivo.close();
                return numero + ";" + nombre;
            }
        }
    }

    archivo.close();
    return "Cliente no encontrado.";
}

int main() {
    std::string numeroBuscado = "321"; // Cambia esto al número que desees buscar

    std::string resultado = buscarContenidoCliente(numeroBuscado);
    std::cout << "Resultado: " << resultado << std::endl;

    return 0;
}

