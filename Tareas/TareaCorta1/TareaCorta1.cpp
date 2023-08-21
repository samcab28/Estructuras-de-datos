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
    string LeerArchivos1();
    string LeerArchivos2();
    string LeerArchivos3();
    string LeerArchivos4();
    string LeerArchivos5();
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

string lista::LeerArchivos1()
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

	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l1.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l1.Mostrar();
	
	return contenidoArchivo;
}

string lista::LeerArchivos2()
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

	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l2.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l2.Mostrar();
	return contenidoArchivo;
}


string lista::LeerArchivos3()
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

	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l3.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l3.Mostrar();
	return contenidoArchivo;
}

string lista::LeerArchivos4()
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

	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l4.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l4.Mostrar();
	return contenidoArchivo;
}

string lista::LeerArchivos5()
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

	
	while(!contenidoArchivo.empty()){
		char temporal = contenidoArchivo[0];
		l5.InsertarFinal(temporal);
		contenidoArchivo.erase(0,1);
	}
	
	l5.Mostrar();
	return contenidoArchivo;
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

class cola 
{
   private:
   int frente;
   int fondo;
   std::string Cola[5];

public:
       cola(){
       frente = 0;
       fondo = -1;
       for(int i = 0; i < 5; i++){
         Cola[i] = "";    
           }
       }
       
      bool ColaVacia(){ return fondo < frente; }        
	  void insertar(const std::string &v);
	  void eliminar();
	  void imprimir();
	  void consulta(int pos);
	  void UsoMostrar();
};

void cola::consulta(int pos)
{
	cout<<"consulta de posicion de cola: "<<pos<<endl;
	cout<<Cola[pos]<<endl;
}

void cola::insertar(const std::string &v)
{
    if(fondo < 5 - 1){
        fondo++;
        Cola[fondo] = v; 
    }
    else{
        std::cout << "La cola esta llena" << std::endl;  
    }
}   

void cola::eliminar()
{
    if(!ColaVacia()){
        frente++;
    }
    else{
        std::cout << "La cola esta vacia" << std::endl;  
    }
}  

void cola::imprimir()
{
    for(int i = frente; i <= fondo; i++){ // Corregido el bucle para incluir el fondo
        std::cout << Cola[i] << "->" << std::endl;    
    }
}

void cola::UsoMostrar()
{
	lista ObjetoMostrar;
	
	ObjetoMostrar.Mostrar();
}

int main() {
   lista L;//instancia null
   cola c;
   
   cout<< "***************************************************************************************"<<endl;

	string lista1;
	string lista2;
	string lista3;
	string lista4;
	string lista5;
	
	lista1 = L.LeerArchivos1();
	lista2 = L.LeerArchivos2();
	lista3 = L.LeerArchivos3();
	lista4 = L.LeerArchivos4();
	lista5 = L.LeerArchivos5();
	
	cout<<endl;
	cout <<"inicio de cola:"<<endl; // Print the contents of the processed file
	c.insertar(lista1);
	c.insertar(lista2);
	c.insertar(lista3);
	c.insertar(lista4);
	c.insertar(lista5);
	
	c.imprimir();
	c.consulta(0);
	c.consulta(1);
	c.UsoMostrar();
	
    return 0;
}

