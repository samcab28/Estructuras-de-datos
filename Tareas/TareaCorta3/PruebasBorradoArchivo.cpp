#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int customAtoiCliente(const std::string& str) {
    int result = 0;
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (isdigit(c)) {
            result = result * 10 + (c - '0');
        } else if (c == ';') {
            break; // Detener la conversi�n al encontrar el primer punto y coma
        }
    }
    return result;
}

void modificarCliente(int cedula) {
    std::string archivoOriginal = "Clientes.txt";
    std::string archivoTemporal = "temporal.txt";

    std::ifstream entrada(archivoOriginal.c_str());
    std::ofstream salida(archivoTemporal.c_str());

    if (!entrada.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
    }

    if (!salida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida temporal." << std::endl;
    }

    std::string linea;
    bool encontrado = false;
    while (std::getline(entrada, linea)) {
        int primerNumero = customAtoiCliente(linea); // Obtener el primer n�mero de la l�nea

        if (primerNumero == cedula) {
            // Modificar la l�nea agregando ";1" al final
            linea += ";1";
            encontrado = true;
        }

        // Escribir la l�nea en el archivo temporal
        salida << linea << "\n";
    }

    // Cerrar los archivos
    entrada.close();
    salida.close();

    if (!encontrado) {
        std::cerr << "La c�dula no se encontr� en el archivo." << std::endl;
    } else {
        // Reemplazar el archivo original con el archivo temporal
        if (std::remove(archivoOriginal.c_str()) != 0) {
            std::cerr << "Error al eliminar el archivo original." << std::endl;
        }

        if (std::rename(archivoTemporal.c_str(), archivoOriginal.c_str()) != 0) {
            std::cerr << "Error al renombrar el archivo temporal." << std::endl;
        }
    }
}

void borradoCliente() {
    std::string archivoOriginal = "Clientes.txt";
    std::string archivoTemporal = "temporal.txt";

    std::ifstream entrada(archivoOriginal.c_str());
    std::ofstream salida(archivoTemporal.c_str());

    if (!entrada.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
        return;
    }

    if (!salida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida temporal." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(entrada, linea)) {
        // Verificar si la l�nea termina con ";1"
        if (linea.length() >= 2 && linea.substr(linea.length() - 2) == ";1") {
            // Omitir la escritura de la l�nea en el archivo temporal
            continue;
        }

        // Escribir la l�nea en el archivo temporal
        salida << linea << "\n";
    }

    // Cerrar los archivos
    entrada.close();
    salida.close();

    // Reemplazar el archivo original con el archivo temporal
    if (std::remove(archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al eliminar el archivo original." << std::endl;
        return;
    }

    if (std::rename(archivoTemporal.c_str(), archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al renombrar el archivo temporal." << std::endl;
    }
}

int main() {
    int cedula;
    cout << "Ingrese el valor de la c�dula a modificar: ";
    cin >> cedula;

    modificarCliente(cedula);
    borradoCliente();

    return 0;
}

