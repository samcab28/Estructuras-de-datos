#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    // Nombre del archivo a leer
    std::string nombreArchivo = "//Archivos//Arch1.txt";

    // Abrir el archivo en modo lectura
    std::ifstream archivo(nombreArchivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1; // Terminar el programa con código de error
    }

    // Leer y construir la palabra
    std::string palabra;
    std::string linea;
    while (std::getline(archivo, linea)) {
        palabra += linea;
    }

    // Cerrar el archivo
    archivo.close();

    // Imprimir la palabra formada
    std::cout << "Palabra formada: " << palabra << std::endl;

    return 0; // Terminar el programa exitosamente
}
