/*
tarea corta 
*/

#include <iostream>
#include <queue>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <set>



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
    void podarArbol(Nodo*& nodoPtr);
    void insertarNodo(const string& valor, Nodo*& nodoPtr);
    void muestraAcostado(int nivel, Nodo* nodoPtr);
    void cargarDesdeArchivo(Nodo*&raizArbolPtr);
};

void Arbol::cargarDesdeArchivo(Nodo*& raizArbolPtr)
{
    ifstream archivo("Indices.txt");

    if (!archivo)
    {
        cout << "Error al abrir el archivo " <<  endl;
        return;
    }

    string linea;
    while (getline(archivo, linea))
    {
        insertarNodo(linea, raizArbolPtr);
    }

    archivo.close();
}




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



void leerArchivos() {
    ifstream archivo("Clientes.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    set<string> uniqueNumbers;
    set<string> repeatedNumbers;

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(';');
        if (pos != string::npos) {
            string numero = linea.substr(0, pos);
            if (uniqueNumbers.find(numero) != uniqueNumbers.end()) {
                repeatedNumbers.insert(numero);
            } else {
                uniqueNumbers.insert(numero);
            }
        }
    }
	ofstream archivo2("Indices.txt");
	archivo2.close();
	int contador = 1;
    for (set<string>::iterator it = uniqueNumbers.begin(); it != uniqueNumbers.end(); ++it) {
        //cout << *it << endl;
        ofstream archivo_escritura("Indices.txt", ios::app);

	    if (!archivo_escritura) {
	        cout << "Error al abrir el archivo para escribir" << endl;
	        return;
	    }
	
		std::stringstream ss1;
    	ss1 << contador;
    	string num1 = ss1.str();
    	
	    archivo_escritura << num1+";"+*it << endl;

    	archivo_escritura.close();
    	contador++;
    }

    cout << "Números repetidos:" << endl;
    for (set<string>::iterator it = repeatedNumbers.begin(); it != repeatedNumbers.end(); ++it) {
        cout << *it << endl;
    }

    archivo.close();
}





int main(){
	
    bool programa = true;
	
	leerArchivos();
	
	
    Arbol miArbol;
    Nodo* raizArbolPtr = miArbol.regresaRaiz();
    
    miArbol.cargarDesdeArchivo(raizArbolPtr); // Corrected line
    
    while(programa){
        cout<<"\n1 para buscar"<<endl;
        cout<<"2 para eliminar"<<endl;
        cout<<"3 para insertar"<<endl;
        cout<<"4 para purgar"<<endl;
        cout<<"5 para reindexar"<<endl;
        cout<<"6 para imprimir"<<endl;
        cout<<"7 para cache"<<endl;
        cout<<"8 para salir"<<endl;
        cout<<"\n digite la opcion: "<<endl;
        int x;
        cin >> x;
        switch(x){
            case 1:
                cout<<"1. buscar"<<endl;
                break;
            case 2: 
                cout<<"2. eliminar"<<endl;
                break;
            case 3: 
                cout<<"3. insertar"<<endl;
                break;
            case 4: 
                cout<<"4. purgar"<<endl;
                break;
            case 5: 
                cout<<"5. reindexar"<<endl;
                break;
            case 6: 
                cout<<"6. imprimir"<<endl;
                miArbol.muestraAcostado(0, raizArbolPtr);
                break;
            case 7: 
                cout<<"7. cache"<<endl;
                break; // You missed the break statement here
            case 8:
                cout<<"salir"<<endl;
                programa = false;
                break;
            default:
                cout<<"error a la hora de digitar"<<endl;
                break;
        }
    }
	
    return 0;
}

