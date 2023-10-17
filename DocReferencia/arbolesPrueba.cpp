#include <iostream>
#include <queue>
#include <windows.h>
#include <string>

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
    void gotoxy(int x, int y);

public:
    Arbol();
    ~Arbol();
    Nodo*& regresaRaiz();
    void insertarNodo(const string& valor, Nodo*& nodoPtr);
    void muestraAcostado(int nivel, Nodo* nodoPtr);
    void inOrden(Nodo* nodoPtr);
    void preOrden(Nodo* nodoPtr);
    void postOrden(Nodo* nodoPtr);
    void busqueda(const string& x, Nodo* nodoPtr);
    void podarArbol(Nodo*& nodoPtr);
    Nodo* buscaMenor(Nodo* nodoPtr);
    Nodo* buscaMayor(Nodo* nodoPtr);
    void eliminarPredecesor(const string& x, Nodo*& nodoPtr);
    void eliminarSucesor(const string& x, Nodo*& nodoPtr);
    int altura(Nodo* nodoPtr);
    int contarHojas(Nodo* nodoPtr);
    int contarNodos(Nodo* nodoPtr);
    void recorridoNiveles(Nodo* nodoPtr);
    bool esLleno(Nodo* nodoPtr);
    bool esCompleto(Nodo* nodoPtr);
    void graficarArbol(Nodo* nodoPtr, int x, int y, int nivel, int distancia);
};

Arbol::Arbol()
{
    raizPtr = NULL;
}

Arbol::~Arbol()
{
    podarArbol(raizPtr);
}

Nodo*& Arbol::regresaRaiz()
{
    return raizPtr;
}

void Arbol::insertarNodo(const string& valor, Nodo*& nodoPtr)
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

void Arbol::inOrden(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }

    inOrden(nodoPtr->izquierdoPtr);
    cout << nodoPtr->dato << " - ";
    inOrden(nodoPtr->derechoPtr);
}

void Arbol::preOrden(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }

    cout << nodoPtr->dato << " - ";
    preOrden(nodoPtr->izquierdoPtr);
    preOrden(nodoPtr->derechoPtr);
}

void Arbol::postOrden(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }

    postOrden(nodoPtr->izquierdoPtr);
    postOrden(nodoPtr->derechoPtr);
    cout << nodoPtr->dato << " - ";
}

void Arbol::busqueda(const string& x, Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        cout << "elemento No encontrado" << endl;
    }
    else if (x < nodoPtr->dato)
    {
        return busqueda(x, nodoPtr->izquierdoPtr);
    }
    else if (x > nodoPtr->dato)
    {
        return busqueda(x, nodoPtr->derechoPtr);
    }
    else
    {
        cout << "elemento encontrado" << endl;
    }
}

void Arbol::podarArbol(Nodo*& nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }

    podarArbol(nodoPtr->izquierdoPtr);
    podarArbol(nodoPtr->derechoPtr);
    delete nodoPtr;
    nodoPtr = NULL;
}

Nodo* Arbol::buscaMenor(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return NULL;
    }
    else if (nodoPtr->izquierdoPtr == NULL)
    {
        cout << "nodo menor: " << nodoPtr->dato << endl;
        return nodoPtr;
    }
    else
    {
        return buscaMenor(nodoPtr->izquierdoPtr);
    }
}

Nodo* Arbol::buscaMayor(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return NULL;
    }
    else if (nodoPtr->derechoPtr == NULL)
    {
        cout << "nodo mayor: " << nodoPtr->dato << endl;
        return nodoPtr;
    }
    else
    {
        return buscaMayor(nodoPtr->derechoPtr);
    }
}

void Arbol::eliminarPredecesor(const string& x, Nodo*& nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }
    else if (x < nodoPtr->dato)
    {
        eliminarPredecesor(x, nodoPtr->izquierdoPtr);
    }
    else if (x > nodoPtr->dato)
    {
        eliminarPredecesor(x, nodoPtr->derechoPtr);
    }
    else if (nodoPtr->izquierdoPtr && nodoPtr->derechoPtr)
    {
        Nodo* mayor = buscaMayor(nodoPtr->izquierdoPtr);
        nodoPtr->dato = mayor->dato;
        eliminarPredecesor(mayor->dato, nodoPtr->izquierdoPtr);
    }
    else
    {
        Nodo* temp = nodoPtr;
        if (nodoPtr->izquierdoPtr == NULL)
        {
            nodoPtr = nodoPtr->derechoPtr;
        }
        else if (nodoPtr->derechoPtr == NULL)
        {
            nodoPtr = nodoPtr->izquierdoPtr;
        }

        delete temp;
    }
}

void Arbol::eliminarSucesor(const string& x, Nodo*& nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }
    else if (x < nodoPtr->dato)
    {
        eliminarSucesor(x, nodoPtr->izquierdoPtr);
    }
    else if (x > nodoPtr->dato)
    {
        eliminarSucesor(x, nodoPtr->derechoPtr);
    }
    else if (nodoPtr->izquierdoPtr && nodoPtr->derechoPtr)
    {
        Nodo* menor = buscaMenor(nodoPtr->derechoPtr);
        nodoPtr->dato = menor->dato;
        eliminarSucesor(menor->dato, nodoPtr->derechoPtr);
    }
    else
    {
        Nodo* temp = nodoPtr;
        if (nodoPtr->izquierdoPtr == NULL)
        {
            nodoPtr = nodoPtr->derechoPtr;
        }
        else if (nodoPtr->derechoPtr == NULL)
        {
            nodoPtr = nodoPtr->izquierdoPtr;
        }

        delete temp;
    }
}

int Arbol::altura(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return 0;
    }
    return (1 + max(altura(nodoPtr->izquierdoPtr), altura(nodoPtr->derechoPtr)));
}

int Arbol::contarHojas(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return 0;
    }
    if (nodoPtr->derechoPtr == NULL && nodoPtr->izquierdoPtr == NULL)
    {
        return 1;
    }
    else
    {
        return contarHojas(nodoPtr->izquierdoPtr) + contarHojas(nodoPtr->derechoPtr);
    }
}

int Arbol::contarNodos(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return 0;
    }
    return 1 + contarNodos(nodoPtr->izquierdoPtr) + contarNodos(nodoPtr->derechoPtr);
}

void Arbol::recorridoNiveles(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }

    queue<Nodo*> cola;
    cola.push(nodoPtr);

    while (!cola.empty())
    {
        Nodo* nodoActual = cola.front();
        cola.pop();

        cout << nodoActual->dato << " - ";

        if (nodoActual->izquierdoPtr)
        {
            cola.push(nodoActual->izquierdoPtr);
        }

        if (nodoActual->derechoPtr)
        {
            cola.push(nodoActual->derechoPtr);
        }
    }
}

bool Arbol::esLleno(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        cout << "el arbol si esta lleno" << endl;
        return true;
    }

    if (nodoPtr->derechoPtr == NULL && nodoPtr->izquierdoPtr == NULL)
    {
        cout << "el arbol si esta lleno" << endl;
        return true;
    }

    if (nodoPtr->derechoPtr && nodoPtr->izquierdoPtr)
    {
        return (esLleno(nodoPtr->izquierdoPtr) && esLleno(nodoPtr->derechoPtr));
    }

    cout << "el arbol NO esta lleno" << endl;
    return false;
}

bool Arbol::esCompleto(Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        cout << "arbol si esta completo" << endl;
        return true;
    }

    Nodo* nodoAuxiliar;
    queue<Nodo*> colaAuxiliar;
    colaAuxiliar.push(nodoPtr);
    bool nodoNoLleno = false;

    while (!colaAuxiliar.empty())
    {
        nodoAuxiliar = colaAuxiliar.front();
        colaAuxiliar.pop();

        if (nodoAuxiliar->izquierdoPtr)
        {
            if (nodoNoLleno == true)
            {
                cout << "arbol NO completo" << endl;
                return false;
            }
            colaAuxiliar.push(nodoAuxiliar->izquierdoPtr);
        }
        else
        {
            nodoNoLleno = true;
        }

        if (nodoAuxiliar->derechoPtr)
        {
            if (nodoNoLleno == true)
            {
                cout << "arbol NO completo" << endl;
                return false;
            }
            colaAuxiliar.push(nodoAuxiliar->derechoPtr);
        }
        else
        {
            nodoNoLleno = true;
        }
    }
    cout << "arbol si esta completo" << endl;
    return true;
}

void Arbol::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Arbol::graficarArbol(Nodo* nodoPtr, int x, int y, int nivel, int distancia)
{
    if (nodoPtr == NULL)
        return;

    int delta_x = 4;

    gotoxy(x, y);
    cout << nodoPtr->dato;

    if (nodoPtr->izquierdoPtr != NULL)
    {
        int hijo_x = x - distancia;
        int hijo_y = y + 2;
        gotoxy(hijo_x, hijo_y);
        cout << '/';
        graficarArbol(nodoPtr->izquierdoPtr, hijo_x, hijo_y, nivel + 1, distancia / 2);
    }
    if (nodoPtr->derechoPtr != NULL)
    {
        int hijo_x = x + distancia;
        int hijo_y = y + 2;
        gotoxy(hijo_x, hijo_y);
        cout << '\\';
        graficarArbol(nodoPtr->derechoPtr, hijo_x, hijo_y, nivel + 1, distancia / 2);
    }
}

int main()
{
    Arbol miArbol;
    Nodo* raizArbolPtr = miArbol.regresaRaiz();

    miArbol.insertarNodo("Alice", raizArbolPtr);
    miArbol.insertarNodo("Bob", raizArbolPtr);
    miArbol.insertarNodo("Carlos", raizArbolPtr);
    miArbol.insertarNodo("Diana", raizArbolPtr);
    miArbol.insertarNodo("Eduardo", raizArbolPtr);
    miArbol.insertarNodo("Fernando", raizArbolPtr);
    miArbol.insertarNodo("Samir", raizArbolPtr);
    miArbol.insertarNodo("Hannah", raizArbolPtr);

    cout << "" << endl;
    cout << "muestra de acostado" << endl;
    miArbol.muestraAcostado(0, raizArbolPtr);

    cout << "" << endl;
    cout << "muestra de inOrden" << endl;
    miArbol.inOrden(raizArbolPtr);

    cout << "" << endl;
    cout << "muestra de preOrden" << endl;
    miArbol.preOrden(raizArbolPtr);

    cout << "" << endl;
    cout << "muestra de postOrden" << endl;
    miArbol.postOrden(raizArbolPtr);

    cout << "" << endl;
    cout << "implementacion de busqueda" << endl;
    miArbol.busqueda("Eduardo", raizArbolPtr);

    cout << "" << endl;
    cout << "implementacion de buscaMenor" << endl;
    miArbol.buscaMenor(raizArbolPtr);

    cout << "" << endl;
    cout << "implementacion de buscaMayor" << endl;
    miArbol.buscaMayor(raizArbolPtr);

    cout << "" << endl;
    cout << "implementacion de eliminar predecesor" << endl;
    miArbol.eliminarPredecesor("Fernando", raizArbolPtr);
    miArbol.muestraAcostado(0, raizArbolPtr);

    cout << "" << endl;
    cout << "implementacion de eliminar sucesor" << endl;
    miArbol.eliminarSucesor("Carlos", raizArbolPtr);
    miArbol.muestraAcostado(0, raizArbolPtr);

    cout << "" << endl;
    cout << "implementacion de altura" << endl;
    int alturaArbol = miArbol.altura(raizArbolPtr);
    cout << "Altura del arbol: " << alturaArbol << endl;

    cout << "" << endl;
    cout << "implementacion de conteo de hojas" << endl;
    int hojasArbol = miArbol.contarHojas(raizArbolPtr);
    cout << "Hojas del arbol: " << hojasArbol << endl;

    cout << "" << endl;
    cout << "implementacion de conteo de nodos" << endl;
    int conteoNodos = miArbol.contarNodos(raizArbolPtr);
    cout << "Cantidad de nodos: " << conteoNodos << endl;

    cout << "" << endl;
    cout << "implementacion de recorrido por niveles" << endl;
    miArbol.recorridoNiveles(raizArbolPtr);

    cout << "" << endl;
    cout << "" << endl;
    cout << "implementacion de comprobacion, llenura" << endl;
    miArbol.esLleno(raizArbolPtr);

    cout << "" << endl;
    cout << "implementacion de comprobacion, completo" << endl;
    miArbol.esCompleto(raizArbolPtr);

    return 0;
}
