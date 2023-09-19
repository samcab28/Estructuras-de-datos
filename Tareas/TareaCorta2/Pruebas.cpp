#include <iostream>
#include <queue> // Necesario para utilizar la cola
#include <windows.h> 

using namespace std;

class Nodo
{
public:
    string dato;  
    Nodo* izquierdoPtr;
    Nodo* derechoPtr;
};


class Arbol
{
private:
    Nodo* raizPtr;
    bool esVacio();
    void gotoxy(int x,int y);

public:
    Arbol();
    ~Arbol();
    Nodo*& regresaRaiz();
    void insertarNodo(string valor, Nodo*& nodoPtr);
    void muestraAcostado(int nivel, Nodo* nodoPtr);
    void inOrden(Nodo * nodoPtr);
    void preOrden(Nodo * nodoPtr);
    void postOrden(Nodo * nodoPtr);
    void busqueda(int x, Nodo * nodoPtr);
    void podarArbol(Nodo *&nodoPtr);
    Nodo * buscaMenor(Nodo * nodoPtr);
    Nodo * buscaMayor(Nodo * nodoPtr);
    void eliminarPredecesor(int x, Nodo *&nodoPtr);
    void eliminarSucesor(int x, Nodo *& nodoPtr);
    int altura(Nodo * nodoPtr);
    int contarHojas(Nodo * nodoPtr);
    int contarNodos(Nodo * nodoPtr);
    void recorridoNiveles(Nodo * nodoPtr);
    bool esLleno(Nodo * nodoPtr);
    bool esCompleto(Nodo * nodoPtr);
    void graficarArbol(Nodo* nodoPtr, int x, int y, int nivel, int distancia);
};

Arbol::Arbol()
{
    raizPtr = NULL;
}

Arbol::~Arbol()
{
    //podarArbol(raizPtr);
}

Nodo*& Arbol::regresaRaiz()
{
    return raizPtr;
}

void Arbol::insertarNodo(string valor, Nodo*& nodoPtr)
{
    if (nodoPtr == NULL)
    {
        nodoPtr = new Nodo();
        nodoPtr->dato = valor;
        nodoPtr->izquierdoPtr = NULL;
        nodoPtr->derechoPtr = NULL;
    }
    else if (valor < nodoPtr->dato)
    {
        insertarNodo(valor, nodoPtr->izquierdoPtr);
    }
    else if (valor > nodoPtr->dato)
    {
        insertarNodo(valor, nodoPtr->derechoPtr);
    }
}


void Arbol::muestraAcostado(int nivel, Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }

    muestraAcostado(nivel + 1, nodoPtr->derechoPtr);

    for (int i = 0; i < nivel; i++)
    {
        cout << "  ";
    }

    cout << nodoPtr->dato << endl;

    muestraAcostado(nivel + 1, nodoPtr->izquierdoPtr);
}


int main()
{
    Arbol miArbol;  // Crear el objeto Arbol
    Nodo * raizArbolPtr = miArbol.regresaRaiz();

    // Ejemplo de c?mo usar la inserci?n de nodos
    miArbol.insertarNodo("hola",raizArbolPtr);
    miArbol.insertarNodo("jesus",raizArbolPtr);
    miArbol.insertarNodo("pedro",raizArbolPtr);
    miArbol.insertarNodo("samir",raizArbolPtr);
    miArbol.insertarNodo("alejandro",raizArbolPtr);
    miArbol.insertarNodo("ramses",raizArbolPtr);
    miArbol.insertarNodo("belice",raizArbolPtr);


    cout<<""<<endl;
    cout<<"muestra de acostado"<<endl;
    miArbol.muestraAcostado(0,raizArbolPtr);

    return 0;
}

