#include <iostream>
#include <string>
using namespace std;

class cola
{
private:
    int frente;
    int fondo;
    string Cola[5]; // Cambiamos el tipo de datos a string

public:
    cola()
    {
        frente = 0;
        fondo = -1;
        for (int i = 0; i < 5; i++)
        {
            Cola[i] = ""; // Inicializamos el arreglo de strings con cadenas vacías
        }
    }

    bool ColaVacia() { return fondo < frente; }
    void insertar(string v);
    void eliminar();
    void imprimir();
};

void cola::insertar(string v)
{
    if (fondo <= 5 - 1)
    {
        fondo++;
        Cola[fondo] = v;
    }
    else
    {
        cout << "La cola esta llena";
    }
}

void cola::eliminar()
{
    if (!ColaVacia())
    {
        frente++;
    }
    else
    {
        cout << "La cola esta vacia";
    }
}

void cola::imprimir()
{
    for (int i = frente; i <= fondo; i++)
    {
        cout << Cola[i] << " -> ";
    }
    cout << endl;
}

int main()
{
    cola miCola;

    miCola.insertar("gato");
    miCola.insertar("perro");
    miCola.insertar("pájaro");
    miCola.imprimir();

    miCola.eliminar();
    miCola.insertar("pájaro");
    miCola.eliminar();
    miCola.eliminar();
    miCola.insertar("p\o");
    miCola.imprimir();

    cin.get();
    return 0;
}

