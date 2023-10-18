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
#include <stack>



using namespace std;

// Funci�n para convertir una cadena en un entero
int customAtoi(const std::string& str) {
    int result = 0;
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (isdigit(c)) {
            result = result * 10 + (c - '0');
        }
    }
    return result;
}

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


void borradoIndice(int numeroBorrar){
    std::string archivoOriginal = "Indices.txt";
    std::string archivoTemporal = "temporal.txt";
    
    // Valor de numero2 que deseas borrar
    int numero2ABorrar = numeroBorrar; // Reemplaza con el valor deseado

    std::ifstream entrada(archivoOriginal.c_str());
    std::ofstream salida(archivoTemporal.c_str());

    if (!entrada.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
    }

    if (!salida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida temporal." << std::endl;
    }

    std::string linea;
    while (std::getline(entrada, linea)) {
        size_t pos = linea.find(';');
        if (pos != std::string::npos) {
            // Encontrar la parte de la l�nea que contiene el valor de numero2
            std::string numero2_str = linea.substr(pos + 1);
            
            // Convertir la cadena a un entero utilizando la funci�n personalizada
            int numero2 = customAtoi(numero2_str);
            
            // Si el valor de numero2 coincide con el valor a borrar, omitir la escritura de la l�nea en el archivo temporal
            if (numero2 == numero2ABorrar) {
                continue;
            }
        }
        // Si el valor de numero2 no coincide con el valor a borrar, escribir la l�nea en el archivo temporal
        salida << linea << "\n";
    }

    // Cerrar los archivos
    entrada.close();
    salida.close();

    // Reemplazar el archivo original con el archivo temporal
    if (std::remove(archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al eliminar el archivo original." << std::endl;
    }

    if (std::rename(archivoTemporal.c_str(), archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al renombrar el archivo temporal." << std::endl;
    }

    std::cout << "Contenido del archivo modificado con �xito." << std::endl;
}

void borradoCliente(int primerNumeroBorrar){
    std::string archivoOriginal = "Clientes.txt";
    std::string archivoTemporal = "temporal.txt";
    
    // Valor del primer n�mero que deseas borrar
    int primerNumeroABorrar = primerNumeroBorrar; // Reemplaza con el valor deseado

    std::ifstream entrada(archivoOriginal.c_str());
    std::ofstream salida(archivoTemporal.c_str());

    if (!entrada.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
    }

    if (!salida.is_open()) {
        std::cerr << "Error al abrir el archivo de salida temporal." << std::endl;
    }

    std::string linea;
    while (std::getline(entrada, linea)) {
        int primerNumero = customAtoiCliente(linea); // Obtener el primer n�mero de la l�nea
        
        // Si el primer n�mero coincide con el valor a borrar, omitir la escritura de la l�nea en el archivo temporal
        if (primerNumero == primerNumeroABorrar) {
            continue;
        }
        
        // Si el primer n�mero no coincide con el valor a borrar, escribir la l�nea en el archivo temporal
        salida << linea << "\n";
    }

    // Cerrar los archivos
    entrada.close();
    salida.close();

    // Reemplazar el archivo original con el archivo temporal
    if (std::remove(archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al eliminar el archivo original." << std::endl;
    }

    if (std::rename(archivoTemporal.c_str(), archivoOriginal.c_str()) != 0) {
        std::cerr << "Error al renombrar el archivo temporal." << std::endl;
    }

    std::cout << "Contenido del archivo modificado con �xito." << std::endl;
}

std::string obtenerNombrePorNumero(int numero) {
    // Abre el archivo de texto
    std::ifstream archivo("Clientes.txt");

    if (!archivo.is_open()) {
        // Si no se pudo abrir el archivo, muestra un mensaje de error
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return "";
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        // Divide la l�nea en n�mero y nombre usando el punto y coma como delimitador
        size_t pos = linea.find(";");
        if (pos != std::string::npos) {
            std::istringstream stream(linea.substr(0, pos));
            int numeroEnArchivo;
            stream >> numeroEnArchivo;

            if (!stream.fail() && numeroEnArchivo == numero) {
                std::string nombre = linea.substr(pos + 1);
                archivo.close();
                return nombre;
            }
        }
    }

    // Si no se encuentra el n�mero, cierra el archivo y devuelve una cadena vac�a
    archivo.close();
    return "";
}

class Nodo
{
public:
    string dato;
    int valorNumerico; 

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
    void cargarDesdeArchivo(Nodo*&raizArbolPtr);
    void preOrden(Nodo* nodoPtr);
    void inOrden(Nodo* nodoPtr);
    void CacheMemory();
    string crearCache(int cedula,Nodo* nodoPtr);
    void insertarCliente(Nodo*& nodoPtr);
    string buscarPorCedula(int cedula, Nodo* nodoPtr);
    void eliminarNodo(Nodo*& nodoPtr, int cedula);
    Nodo* encontrarSucesor(Nodo* nodoPtr);
	
};

string Arbol::buscarPorCedula(int cedula, Nodo* nodoPtr) {
    if (nodoPtr == NULL) {
        return "Cedula no encontrada en el �rbol";
    }

    // Buscar el segundo n�mero en la c�dula almacenada en el nodo
    size_t pos = nodoPtr->dato.find(';');
    if (pos != string::npos) {
        string numStr = nodoPtr->dato.substr(pos + 1);
        int num;
        istringstream(numStr) >> num;  // Convierte la parte num�rica a entero

        if (cedula == num) {
			borradoIndice(cedula);
			borradoCliente(cedula);
            return nodoPtr->dato;  // Devuelve el nodo encontrado en forma de string
        } else if (cedula < num) {
            return buscarPorCedula(cedula, nodoPtr->izquierdoPtr);
        } else {
            return buscarPorCedula(cedula, nodoPtr->derechoPtr);
        }
    } else {
        return "Formato de c�dula incorrecto en el �rbol";
    }
}

void Arbol::eliminarNodo(Nodo*& nodoPtr, int cedula) {
	cout<<"entro a eliminar nodo: "<<cedula<<endl;
    if (nodoPtr == NULL) {
    	cout<<"nodo NUlo"<<endl;
        return;
    }
	cout<<"valor de nodo actual: "<<nodoPtr -> dato<<endl;
    if (buscarPorCedula(cedula, nodoPtr) == nodoPtr->dato) {
        cout<<"imprimir nodo a borrar : "<<nodoPtr->valorNumerico<<endl;
        if (nodoPtr->izquierdoPtr == NULL && nodoPtr->derechoPtr == NULL) {
            // Caso 1: El nodo es una hoja (no tiene hijos)
            delete nodoPtr;
            nodoPtr = NULL;
        } else if (nodoPtr->izquierdoPtr == NULL) {
            // Caso 2: El nodo solo tiene un hijo derecho
            Nodo* temp = nodoPtr;
            nodoPtr = nodoPtr->derechoPtr;
            delete temp;
        } else if (nodoPtr->derechoPtr == NULL) {
            // Caso 2: El nodo solo tiene un hijo izquierdo
            Nodo* temp = nodoPtr;
            nodoPtr = nodoPtr->izquierdoPtr;
            delete temp;
        } else {
            // Caso 3: El nodo tiene dos hijos
            Nodo* sucesor = encontrarSucesor(nodoPtr->derechoPtr);
            nodoPtr->dato = sucesor->dato;
            nodoPtr->valorNumerico = sucesor->valorNumerico;
            eliminarNodo(nodoPtr->derechoPtr, sucesor->valorNumerico);
        }
    } else if (cedula < nodoPtr->valorNumerico) {
        eliminarNodo(nodoPtr->izquierdoPtr, cedula);
    } else {
        eliminarNodo(nodoPtr->derechoPtr, cedula);
    }
    
    cout<<"no se encontro el nodo"<<endl;
}


Nodo* Arbol::encontrarSucesor(Nodo* nodoPtr) {
    if (nodoPtr->izquierdoPtr == NULL) {
        return nodoPtr;
    }
    return encontrarSucesor(nodoPtr->izquierdoPtr);
}

void Arbol::insertarCliente(Nodo*& nodoPtr){
	cout<<"agregar cliente"<<endl;
	string cedula, nombre, nuevoValor;
	cout<<"digite el valor de la cedula"<<endl;
	cin >> cedula;
	
	cout<<"digite el nombre de la persona"<<endl;
	cin >> nombre;
	
	nuevoValor = cedula+";"+nombre;
	
	ofstream archivo_escritura("Clientes.txt", ios::app);
	
    if (!archivo_escritura) {
        cout << "Error al abrir el archivo para escribir" << endl;
        return;
    }
	
    	
 	archivo_escritura << nuevoValor << endl;

}

string Arbol::crearCache(int cedula, Nodo* nodoPtr) {
    if (nodoPtr == NULL) {
        return "Cedula no encontrada en el ?rbol";
    }
	ofstream archivo("Cache.txt");
	archivo.close();
	
	int num2;
    string resultado = "";
    stack<Nodo*> nodosStack;
    Nodo* actual = nodoPtr;
    Nodo* primerNodo = nodoPtr;
    Nodo* primerNodoCST = nodoPtr;

    while (true) {  // Usa un bucle infinito para continuar buscando desde el inicio del ?rbol
        while (actual != NULL) {
            nodosStack.push(actual);
            actual = actual->izquierdoPtr;
        }

        if (nodosStack.empty()) {
            break; // Todos los nodos se han visitado
        }

        actual = nodosStack.top();
        nodosStack.pop();

        size_t pos = actual->dato.find(';');
        if (pos != string::npos) {
            string numStr = actual->dato.substr(pos + 1);
            int num;
            istringstream(numStr) >> num;

            if (cedula == num) {
            	ofstream archivoESC("Cache.txt",ios::app);
            	
                resultado += "Nodo encontrado: " + actual->dato + "\n";
				string nombreEncontrado = obtenerNombrePorNumero(cedula);
				string datoGuardar = actual->dato + ";"+ nombreEncontrado;
                archivoESC<<datoGuardar<<endl;
                Nodo* siguiente = NULL; // Declaraci?n fuera del if y else

                if (actual->derechoPtr == NULL) {
                    siguiente = primerNodoCST;
                } else {
                    siguiente = actual->derechoPtr;
                }

                int contador = 0;

                while (siguiente != NULL && contador < 20) {
                    resultado += "Nodo siguiente: " + siguiente->dato + "\n";
                    archivoESC<<siguiente->dato<<endl;
                    if (siguiente == NULL) {
                        siguiente = primerNodoCST;
                    } else {
                        siguiente = siguiente->derechoPtr;
                    }

                    contador++;
                }
                break;   // Termina la b?squeda despu?s de encontrar el nodo
            }
        }

        actual = actual->derechoPtr;
    }

    return resultado.empty() ? "Cedula no encontrada en el ?rbol" : resultado;
    
	//funcion pk
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
        
        size_t pos = valor.find(';');
        if (pos != string::npos) {
            // Obtener la parte despu?s del punto y coma como valor num?rico
            string numStr = valor.substr(pos + 1);
            nodoPtr->valorNumerico = atoi(numStr.c_str()); // Convierte la cadena a entero
        }
        else {
            // Manejo de error si no se encuentra el punto y coma
            nodoPtr->valorNumerico = 0; // O asigna un valor por defecto
        }
        
        nodoPtr->izquierdoPtr = NULL;
        nodoPtr->derechoPtr = NULL;
    }
    else {
        size_t pos = valor.find(';');
        if (pos != string::npos) {
            // Obtener la parte despu?s del punto y coma como valor num?rico
            string numStr = valor.substr(pos + 1);
            int num = atoi(numStr.c_str());
            
            // Contin?a el proceso basado en el n?mero despu?s del punto y coma
            if (num < nodoPtr->valorNumerico) {
                insertarNodo(valor, nodoPtr->izquierdoPtr);
            }
            else if (num > nodoPtr->valorNumerico) {
                insertarNodo(valor, nodoPtr->derechoPtr);
            }
        }
    }
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

    /*cout << "N?meros repetidos:" << endl;
    for (set<string>::iterator it = repeatedNumbers.begin(); it != repeatedNumbers.end(); ++it) {
        cout << *it << endl;
    }*/

    archivo.close();
}

void leerCache(){
    std::ifstream archivo("Cache.txt");

    if (!archivo) {
        std::cerr << "Error al abrir el archivo." << std::endl;
    }

    std::string linea;

    while (std::getline(archivo, linea)) {
        std::cout << linea << " - "; 
    }
	cout<<"\n"<<endl;
    archivo.close();
}



int main(){
	
    bool programa = true;
	int cedula;
	
	leerArchivos();
	
	
    Arbol miArbol;
    Nodo* raizArbolPtr = miArbol.regresaRaiz();
    
    miArbol.cargarDesdeArchivo(raizArbolPtr); 
    
    while(programa){
    	cout<<"-------------------------------------------------"<<endl;
    	cout<<"menu principal"<<endl;
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
                cout << "Digite el numero de la cedula: ";
			    cin >> cedula;
                cout<<miArbol.buscarPorCedula(cedula, raizArbolPtr)<<endl;
                break;
			case 2: 
			    cout << "2. eliminar" << endl;
			    cout << "Digite el numero de la cedula: ";
			    cin >> cedula;
			    miArbol.eliminarNodo(raizArbolPtr,cedula);
			    break;

            case 3: 
                cout<<"3. insertar"<<endl;
                miArbol.insertarCliente(raizArbolPtr);
                leerArchivos();
                miArbol.cargarDesdeArchivo(raizArbolPtr); 
                break;
            case 4: 
                cout<<"4. purgar"<<endl;
                break;
            case 5: 
                cout<<"5. reindexar"<<endl;
                break;
            case 6: 
                cout<<"6. imprimir"<<endl;
                cout << "muestra de inOrden" << endl;
    			miArbol.inOrden(raizArbolPtr);
    			cout<<""<<endl;
    			cout<<""<<endl;
                cout << "muestra de preOrden" << endl;
   				miArbol.preOrden(raizArbolPtr);
   				cout<<""<<endl;
   				cout<<""<<endl;
                cout << "muestra de Cache" << endl;
                leerCache();
   				
                break;
            case 7: 
                cout<<"7. cache"<<endl;
                miArbol.cargarDesdeArchivo(raizArbolPtr);
                cout << "Digite el numero de la cedula: ";
			    cin >> cedula;
                cout<<miArbol.crearCache(cedula, raizArbolPtr)<<endl;
                break; 
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

