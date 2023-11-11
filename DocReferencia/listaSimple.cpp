#include <iostream>
#include <string>
using namespace std;

// Clase nodo para país
class nodoPa {
public:
    nodoPa(string v) : pais(v), siguiente(NULL) {}
private:
    string pais;
    nodoPa* siguiente;
    friend class listaPa;
};

// Clase lista para país
class listaPa {
public:
    listaPa() { primero = NULL; }
    ~listaPa();
    void InsertarPais(string v);
    string obtenerPaises();
    bool ListaVacia() { return primero == NULL; }

private:
    nodoPa* primero;
};

listaPa::~listaPa()
{
    nodoPa* aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

void listaPa::InsertarPais(string v)
{
    if (ListaVacia())
        primero = new nodoPa(v);
    else
    {
        nodoPa* aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        nodoPa* nuevo = new nodoPa(v);
        aux->siguiente = nuevo;
    }
}

string listaPa::obtenerPaises()
{
    string result = "";
    nodoPa* aux = primero;
    while (aux) {
        result += aux->pais + " -> ";
        aux = aux->siguiente;
    }
    return result;
}

// Clase nodo para ciudad
class nodoCiu {
public:
    nodoCiu(string v) : ciudad(v), siguiente(NULL) {}
private:
    string ciudad;
    nodoCiu* siguiente;
    friend class listaCiu;
};

// Clase lista para ciudad
class listaCiu {
public:
    listaCiu() { primero = NULL; }
    ~listaCiu();
    void InsertarCiudad(string v);
    string obtenerCiudades();
    bool ListaVacia() { return primero == NULL; }

private:
    nodoCiu* primero;
};

listaCiu::~listaCiu()
{
    nodoCiu* aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

void listaCiu::InsertarCiudad(string v)
{
    if (ListaVacia())
        primero = new nodoCiu(v);
    else
    {
        nodoCiu* aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        nodoCiu* nuevo = new nodoCiu(v);
        aux->siguiente = nuevo;
    }
}

string listaCiu::obtenerCiudades()
{
    string result = "";
    nodoCiu* aux = primero;
    while (aux) {
        result += aux->ciudad + " -> ";
        aux = aux->siguiente;
    }
    return result;
}

class nodoRes {
public:
    nodoRes(string v) : restaurante(v), siguiente(NULL) {}
private:
    string restaurante;
    nodoRes* siguiente;
    friend class listaRes;
};

// Clase lista para restaurante
class listaRes {
public:
    listaRes() { primero = NULL; }
    ~listaRes();
    void InsertarRestaurante(string v);
    string obtenerRestaurantes();
    bool ListaVacia() { return primero == NULL; }

private:
    nodoRes* primero;
};

listaRes::~listaRes()
{
    nodoRes* aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

void listaRes::InsertarRestaurante(string v)
{
    if (ListaVacia())
        primero = new nodoRes(v);
    else
    {
        nodoRes* aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        nodoRes* nuevo = new nodoRes(v);
        aux->siguiente = nuevo;
    }
}

string listaRes::obtenerRestaurantes()
{
    string result = "";
    nodoRes* aux = primero;
    while (aux) {
        result += aux->restaurante + " -> ";
        aux = aux->siguiente;
    }
    return result;
}

// Clase nodo para menú
class nodoMe {
public:
    nodoMe(string v) : menu(v), siguiente(NULL) {}
private:
    string menu;
    nodoMe* siguiente;
    friend class listaMe;
};

// Clase lista para menú
class listaMe {
public:
    listaMe() { primero = NULL; }
    ~listaMe();
    void InsertarMenu(string v);
    string obtenerMenus();
    bool ListaVacia() { return primero == NULL; }

private:
    nodoMe* primero;
};

listaMe::~listaMe()
{
    nodoMe* aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

void listaMe::InsertarMenu(string v)
{
    if (ListaVacia())
        primero = new nodoMe(v);
    else
    {
        nodoMe* aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        nodoMe* nuevo = new nodoMe(v);
        aux->siguiente = nuevo;
    }
}

string listaMe::obtenerMenus()
{
    string result = "";
    nodoMe* aux = primero;
    while (aux) {
        result += aux->menu + " -> ";
        aux = aux->siguiente;
    }
    return result;
}

// Clase nodo para producto
class nodoPro {
public:
    nodoPro(string v) : producto(v), siguiente(NULL) {}
private:
    string producto;
    nodoPro* siguiente;
    friend class listaPro;
};

// Clase lista para producto
class listaPro {
public:
    listaPro() { primero = NULL; }
    ~listaPro();
    void InsertarProducto(string v);
    string obtenerProductos();
    bool ListaVacia() { return primero == NULL; }

private:
    nodoPro* primero;
};

listaPro::~listaPro()
{
    nodoPro* aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

void listaPro::InsertarProducto(string v)
{
    if (ListaVacia())
        primero = new nodoPro(v);
    else
    {
        nodoPro* aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        nodoPro* nuevo = new nodoPro(v);
        aux->siguiente = nuevo;
    }
}

string listaPro::obtenerProductos()
{
    string result = "";
    nodoPro* aux = primero;
    while (aux) {
        result += aux->producto + " -> ";
        aux = aux->siguiente;
    }
    return result;
}


int main()
{
    // Pruebas para la lista de países
    listaPa paises;
    paises.InsertarPais("México");
    paises.InsertarPais("Estados Unidos");
    paises.InsertarPais("Canadá");

    cout << "Países: " << paises.obtenerPaises() << endl;

    // Pruebas para la lista de ciudades
    listaCiu ciudades;
    ciudades.InsertarCiudad("Ciudad de México");
    ciudades.InsertarCiudad("Los Angeles");
    ciudades.InsertarCiudad("Toronto");

    cout << "Ciudades: " << ciudades.obtenerCiudades() << endl;

    // Pruebas para la lista de restaurantes
    listaRes restaurantes;
    restaurantes.InsertarRestaurante("Restaurante A");
    restaurantes.InsertarRestaurante("Restaurante B");
    restaurantes.InsertarRestaurante("Restaurante C");

    cout << "Restaurantes: " << restaurantes.obtenerRestaurantes() << endl;

    // Pruebas para la lista de menús
    listaMe menus;
    menus.InsertarMenu("Menú 1");
    menus.InsertarMenu("Menú 2");
    menus.InsertarMenu("Menú 3");

    cout << "Menús: " << menus.obtenerMenus() << endl;

    // Pruebas para la lista de productos
    listaPro productos;
    productos.InsertarProducto("Producto X");
    productos.InsertarProducto("Producto Y");
    productos.InsertarProducto("Producto Z");

    cout << "Productos: " << productos.obtenerProductos() << endl;

    return 0;
}

