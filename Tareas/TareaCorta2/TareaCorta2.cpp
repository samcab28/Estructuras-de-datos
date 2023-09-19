/*
tarea corta 2
samir cabrera y fernando abarca
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class nodo {
public:
	nodo()
	{
		valor ="";
		siguiente = NULL;
	}
	nodo(string v)
	{
		valor = v;
		siguiente = NULL;
	}
	nodo(string v, nodo * signodo){
		valor = v;
		siguiente = signodo;
	}
	
private:
	string valor;
	nodo * siguiente;
	
	friend class lista;
	friend class pila;
};

typedef nodo * pnodo;


class pila {
private:
    int Tope;
    string Pila[50]; // Cambiado el tipo de datos a string
    friend class lista;

public:
    pila() {
        Tope = -1;
        for (int i = 0; i < 50; i++) {
            Pila[i] = "";
        }
    }

    bool pilaVacia() { return Tope < 0; }
    void push(string v); 
    void pop();
    void imprimir();
    void Ejecucion();
    string verValorEspecifico(int posicion);
    void verContenido();
};

void pila::verContenido() {
    for (int i = Tope; i >= 0; i--) {
        cout << Pila[i] << endl;
    }
}

string pila::verValorEspecifico(int posicion) {
    if (posicion >= 0 && posicion <= Tope) {
    	cout<<Pila[posicion]<<endl;
        return Pila[posicion];
    } else {
        return "Posición inválida";
    }
}

void pila::push(string v) {
    if (Tope < (50 - 1)) {
        Tope++;
        Pila[Tope] = v;
    } else {
        cout << "La pila está llena";
    }
}

void pila::pop() {
    if (!pilaVacia()) {
        Tope--;
    } else {
        cout << "La pila está vacía";
    }
}

void pila::imprimir() {
    for (int i = Tope; i >= 0; i--) {
        cout << Pila[i] << "->";
    }
}

void pila::Ejecucion()
{
	
}

class lista {
   public:
    lista() { primero =  NULL; }//constructor
    ~lista();//destructor
    
    void crearCola(pnodo Cola[]);
    void mostrarExpresion(pnodo primerl);
    void evaluarExpresion(pnodo primerl);
    void listaAuxilio(string valor);
	void InsertarFinal(string v);
	void Mostrar();
	bool ListaVacia() { return primero == NULL; }
	void evaluarExpresion(pnodo primerl, pila& pilaSimbolos, pila& pilaNumeros);
   private:
    pnodo primero;
    friend class pila;
   
};

lista::~lista()
{
   pnodo aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   primero= NULL;
}

void lista::InsertarFinal(string v)
{
   if (ListaVacia())
     primero = new nodo(v);
   else
      { 
       pnodo aux = primero;
        while ( aux->siguiente != NULL)
         aux= aux->siguiente;
        pnodo nuevo=new nodo(v);
        aux->siguiente=nuevo;
      }    
}

void lista::Mostrar()
{
   nodo *aux;
   if (primero== NULL)
       cout << "No hay elementos AQUI";  
   else
   {
   
       
   		aux = primero;
		while(aux) 
		{
		    cout << aux->valor << "-> ";
		    aux = aux->siguiente;
		}
		cout << endl;
   }
}

void lista::crearCola(pnodo Cola[])
{
	string str;
	ifstream archivo;
	
	int primer = 0;
	pnodo aux;
	archivo.open("Archivos//Arch1.txt");
	Cola[0] -> valor= "(";
	while (getline(archivo, str))
	{
		aux = Cola[0];
		while(aux -> siguiente != NULL)
		{
			aux = aux -> siguiente;
		}
		aux -> siguiente = new nodo (str);
	}
	aux -> siguiente -> siguiente = new nodo(")");
	archivo.close();
	
	//********************************************
	
	str = "";
	primer = 0;
	archivo.open("Archivos//Arch2.txt");
	Cola[1] -> valor= "(";
	while (getline(archivo, str))
	{
		aux = Cola[1];
		while(aux -> siguiente != NULL)
		{
			aux = aux -> siguiente;
		}
		aux -> siguiente = new nodo (str);
	}
	aux -> siguiente -> siguiente = new nodo(")");
	archivo.close();
	
	//********************************************
	
	str = "";
	primer = 0;
	archivo.open("Archivos//Arch3.txt");
	Cola[2] -> valor= "(";
	while (getline(archivo, str))
	{
		aux = Cola[2];
		while(aux -> siguiente != NULL)
		{
			aux = aux -> siguiente;
		}
		aux -> siguiente = new nodo (str);
	}
	aux -> siguiente -> siguiente = new nodo(")");
	archivo.close();
	
	//********************************************
	
	str = "";
	primer = 0;
	archivo.open("Archivos//Arch4.txt");
	Cola[3] -> valor= "(";
	while (getline(archivo, str))
	{
		aux = Cola[3];
		while(aux -> siguiente != NULL)
		{
			aux = aux -> siguiente;
		}
		aux -> siguiente = new nodo (str);
	}
	aux -> siguiente -> siguiente = new nodo(")");
	archivo.close();
	
	//********************************************
	
	str = "";
	primer = 0;
	archivo.open("Archivos//Arch5.txt");
	Cola[4] -> valor= "(";
	while (getline(archivo, str))
	{
		aux = Cola[4];
		while(aux -> siguiente != NULL)
		{
			aux = aux -> siguiente;
		}
		aux -> siguiente = new nodo (str);
	}
	aux -> siguiente -> siguiente = new nodo(")");
	archivo.close();
}

void lista::mostrarExpresion(pnodo primerl){
	pnodo aux;
	aux = primerl -> siguiente;
	if (aux == NULL)
	{
		cout<< "no hay elementos"<<endl;
	}
	else
	{
		while(aux -> siguiente != NULL)
		{
			cout << aux -> valor;
			aux = aux -> siguiente;
		}
		cout<<endl;
	}
}

void lista::evaluarExpresion(pnodo primerl, pila& pilaSimbolos, pila& pilaNumeros) {
    pnodo aux = primerl->siguiente;

    while (aux != NULL) {
        string valor = aux->valor;

        if (isdigit(valor[0])) {
            // Es un número, colócalo en la pila de números
            pilaNumeros.push(valor);
        } else {
            // No es un número, colócalo en la pila de símbolos
            pilaSimbolos.push(valor);
        }

        aux = aux->siguiente;
    }
}





int main(){
	
	lista L;
	pila pilaSimbolos;
	pila pilaNumeros;
 
	
	pnodo primerol1 = new nodo();
	pnodo primerol2 = new nodo();
	pnodo primerol3 = new nodo();
	pnodo primerol4 = new nodo();
	pnodo primerol5 = new nodo();
	
	pnodo Cola[5] = {primerol1, primerol2, primerol3, primerol4, primerol5};
	
	L.crearCola(Cola);
	
	cout<<"Mostrar Lista 1: "<<endl;
	L.mostrarExpresion(Cola[0]);
	cout<<""<<endl;
	cout<<"Mostrar Lista 2: "<<endl;
	L.mostrarExpresion(Cola[1]);
	cout<<""<<endl;
	cout<<"Mostrar Lista 3: "<<endl;
	L.mostrarExpresion(Cola[2]);
	cout<<""<<endl;
	cout<<"Mostrar Lista 4: "<<endl;
	L.mostrarExpresion(Cola[3]);
	cout<<""<<endl;
	cout<<"Mostrar Lista 5: "<<endl;
	L.mostrarExpresion(Cola[4]);
	cout<<""<<endl;
	
	 L.evaluarExpresion(Cola[0], pilaSimbolos, pilaNumeros);

	cout << "Contenido de la pilaSimbolos:" << endl;
	pilaSimbolos.verContenido();
	
	cout << "Contenido de la pilaNumeros:" << endl;
	pilaNumeros.verContenido();

	
	return 0;
}
