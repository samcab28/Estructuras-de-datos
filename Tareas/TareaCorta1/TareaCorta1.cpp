#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

class nodo {
public:
    char valor;
    nodo* siguiente;

    nodo(char v) {
        valor = v;
        siguiente = NULL;
    }

    nodo(char v, nodo* signodo) {
        valor = v;
        siguiente = signodo;
    }
};

class lista {
private:
    nodo* primero;

public:
    lista() {
        primero = NULL;
    }
    ~lista();

    bool ListaVacia() {
        return primero == NULL;
    }

    void InsertarInicio(char v);
    void InsertarFinal(char v);
    void InsertarPos(char v, int pos);
    void Mostrar();
    void LeerArchivos1();
    void LeerArchivos2();
    void LeerArchivos3();
    void LeerArchivos4();
    void LeerArchivos5();
    int largoLista();
};

lista::~lista() {
    nodo* aux;
    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
}

void lista::LeerArchivos1()
{
	lista l1;
	cout<<""<<endl;
    std::ifstream archivo("Archivos//Arch1.txt");  // Cambia "datos.txt" por el nombre de tu archivo

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    std::string contenidoArchivo;
    char caracter;

    while (archivo.get(caracter)) {
        if (std::isdigit(caracter) || caracter == '(' || caracter == ')' ||
            caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/') {
            contenidoArchivo += caracter;
        }
    }

    archivo.close();

    std::cout << "Contenido del archivo numero 1: " << contenidoArchivo << std::endl;
	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l1.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l1.Mostrar();
}

void lista::LeerArchivos2()
{
	lista l2;
	cout<<""<<endl;
    std::ifstream archivo("Archivos//Arch2.txt");  // Cambia "datos.txt" por el nombre de tu archivo

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    std::string contenidoArchivo;
    char caracter;

    while (archivo.get(caracter)) {
        if (std::isdigit(caracter) || caracter == '(' || caracter == ')' ||
            caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/') {
            contenidoArchivo += caracter;
        }
    }

    archivo.close();

    std::cout << "Contenido del archivo numero 2: " << contenidoArchivo << std::endl;
	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l2.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l2.Mostrar();
}


void lista::LeerArchivos3()
{
	lista l3;
	cout<<""<<endl;
    std::ifstream archivo("Archivos//Arch3.txt");  // Cambia "datos.txt" por el nombre de tu archivo

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    std::string contenidoArchivo;
    char caracter;

    while (archivo.get(caracter)) {
        if (std::isdigit(caracter) || caracter == '(' || caracter == ')' ||
            caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/') {
            contenidoArchivo += caracter;
        }
    }

    archivo.close();

    std::cout << "Contenido del archivo numero 3: " << contenidoArchivo << std::endl;
	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l3.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l3.Mostrar();
}

void lista::LeerArchivos4()
{
	lista l4;
	cout<<""<<endl;
    std::ifstream archivo("Archivos//Arch4.txt");  // Cambia "datos.txt" por el nombre de tu archivo

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    std::string contenidoArchivo;
    char caracter;

    while (archivo.get(caracter)) {
        if (std::isdigit(caracter) || caracter == '(' || caracter == ')' ||
            caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/') {
            contenidoArchivo += caracter;
        }
    }

    archivo.close();

    std::cout << "Contenido del archivo numero 4: " << contenidoArchivo << std::endl;
	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l4.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l4.Mostrar();
}

void lista::LeerArchivos5()
{
	lista l5;
	cout<<""<<endl;
    std::ifstream archivo("Archivos//Arch5.txt");  // Cambia "datos.txt" por el nombre de tu archivo

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    std::string contenidoArchivo;
    char caracter;

    while (archivo.get(caracter)) {
        if (std::isdigit(caracter) || caracter == '(' || caracter == ')' ||
            caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/') {
            contenidoArchivo += caracter;
        }
    }

    archivo.close();

    std::cout << "Contenido del archivo numero 5: " << contenidoArchivo << std::endl;
	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l5.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l5.Mostrar();
}

void lista::InsertarInicio(char v) {
    nodo* nuevo = new nodo(v);
    nuevo->siguiente = primero;
    primero = nuevo;
}

void lista::InsertarFinal(char v) {
    nodo* nuevo = new nodo(v);
    if (ListaVacia()) {
        primero = nuevo;
    } else {
        nodo* aux = primero;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

void lista::InsertarPos(char v, int pos) {
    if (pos <= 1 || ListaVacia()) {
        InsertarInicio(v);
    } else {
        nodo* aux = primero;
        int i = 2;
        while (i < pos && aux->siguiente != NULL) {
            aux = aux->siguiente;
            i++;
        }
        nodo* nuevo = new nodo(v);
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
}

void lista::Mostrar() {
    nodo* aux = primero;
    while (aux != NULL) {
        cout << aux->valor << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL" << endl;
}

int lista::largoLista() {
    int cont = 0;
    nodo* aux = primero;
    while (aux != NULL) {
        aux = aux->siguiente;
        cont++;
    }
    return cont;
}



int main() {
   lista Lista1;//instancia null
   
   cout<< "***************************************************************************************"<<endl;
	Lista1.LeerArchivos1();
	Lista1.LeerArchivos2();
	Lista1.LeerArchivos3();
	Lista1.LeerArchivos4();
	Lista1.LeerArchivos5();
	
    return 0;
}

