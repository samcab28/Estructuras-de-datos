#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <set>
#include <string> 
#include <cstdlib> 

using namespace std;
class ListaCOM;
class cola;
class listComFact;
int contadorFacturas = 1; // Variable global para el contador de facturas


class nodo {
public:
    nodo(string v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodo(string v, nodo* signodo)
    {
        valor = v;
        siguiente = signodo;
    }

private:
    string valor;
    nodo* siguiente;
    nodo* anterior;

    friend class ArbolPais;
};

typedef nodo* pnodo;

class ArbolPais {
public:
    ArbolPais() { primero = NULL; }
    ~ArbolPais();

    void agregarNodo(string v);
    bool ArbolVacio() { return primero == NULL; }
    void Mostrar();
    int cantNodos();
    void Paises();
    void CargarDesdeArchivo();
    void AgregarPais();
    void ConsultarPaisPorCodigo();
    void ModificarNombre();
    bool Existe(int codigo);
    string ObtenerContenidoComoString();

private:
    pnodo primero;
};


string ArbolPais::ObtenerContenidoComoString() {
        std::stringstream ss;
        nodo* aux = primero;
        
        while (aux) {
            ss << aux->valor << "-> ";
            aux = aux->siguiente;
        }
        
        return ss.str();
}

void ArbolPais::ModificarNombre() {
    int code;
    cout << "Digite el codigo a modificar" << endl;
    cin >> code;

    string newName;
    cout << "Digite el nuevo nombre" << endl;
    cin.ignore();  
    getline(cin, newName);

    pnodo aux = primero;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == code) {
			    std::stringstream sscode;
			    sscode << code;
			
			    string num1 = sscode.str();          	
            	
                aux->valor = num1 + ";" + newName;
                cout << "Nombre del pais modificado exitosamente." << endl;
                return;
            }
        }
        aux = aux->siguiente;
    }

    cout << "No se encontr? un pa?s con el c?digo proporcionado." << endl;
}

void ArbolPais::ConsultarPaisPorCodigo() {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    cout << "Ingrese el codigo del pais a consultar: ";
    int codigo;
    cin >> codigo;

    pnodo aux = primero;
    bool encontrado = false;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == codigo) {
                encontrado = true;
                string nombre = aux->valor.substr(pos + 1);
                cout << "Codigo: " << codigoEnArbol << endl;
                cout << "Nombre: " << nombre << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontro un pais con el codigo " << codigo << " en el arbol." << endl;
    }
}

void ArbolPais::AgregarPais()
{
    cout << "Ingrese el codigo del pais (parte entera): ";
    int codigo;
    cin >> codigo;
    cin.ignore();  // Limpia el buffer del salto de linea

    cout << "Ingrese el nombre del pais: ";
    string nombre;
    getline(cin, nombre);


    bool codigoExistente = false;
    pnodo aux = primero;
    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == codigo) {
                codigoExistente = true;
                cout << "Error: Ya existe un pais con el codigo " << codigo << "." << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!codigoExistente) {
        // Usar ostringstream para convertir el entero a cadena
        ostringstream ss;
        ss << codigo;
        string codigoStr = ss.str();

        string pais = codigoStr + ";" + nombre;
        agregarNodo(pais);
        cout << "Pais agregado exitosamente." << endl;
    }
}

void ArbolPais::CargarDesdeArchivo()
{
    ifstream archivo("Paises.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(';');
        if (pos != string::npos) {
            string codigo = linea.substr(0, pos);
            string nombre = linea.substr(pos + 1);
            
            bool existe = false;
            pnodo aux = primero;
            
            while (aux) {
                size_t posAux = aux->valor.find(';');
                if (posAux != string::npos) {
                    string codigoEnArbol = aux->valor.substr(0, posAux);
                    
                    if (codigoEnArbol == codigo) {
                        existe = true;
                        cout << "Pais con codigo " << codigo << " ya existe en el arbol." << endl;
                        break;
                    }
                }
                aux = aux->siguiente;
            }
            
            if (!existe) {
                agregarNodo(codigo + ";" + nombre);
            }
        }
    }

    archivo.close();
}

void ArbolPais::Paises()
{
	bool ejecucion = true;
	cout<<""<<endl;
	cout<<"bienvenido a paises"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar pais digite 1: "<<endl;
		cout<<"ver paises digite 2: "<<endl;
		cout<<"agregar un pais digite 3:"<<endl;
		cout<<"modificar nombre digite 4: "<<endl;
		cout<<"salir digite 5: "<<endl;
		
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un pais"<<endl;
				cout<<"paises disponibles: "<<endl;
				Mostrar();
				ConsultarPaisPorCodigo();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los paises"<<endl;
				cout<<"se mostraran todos los paises a continuacion: "<<endl;
				Mostrar();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un pais"<<endl;
				AgregarPais();
				Mostrar();
				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4 modificar nombre:"<<endl;
				cout<<"paises disponibles: "<<endl;
				Mostrar();
				ModificarNombre();
				break;		
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a ArbolMenu principal"<<endl;
				ejecucion = false;	
				break;			
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}

ArbolPais::~ArbolPais()
{
   pnodo aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   primero=NULL;
}

int ArbolPais::cantNodos(){
    int cont=0;

    pnodo aux;
    aux = primero;
    if(ArbolVacio()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}

void ArbolPais::agregarNodo(string v)
{
   if (ArbolVacio())
   {
   
     primero = new nodo(v);
       
   }
   else
     { pnodo aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodo(v);
        aux->siguiente->anterior=aux;       
      }    
}
   

void ArbolPais::Mostrar()
{
   nodo *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

bool ArbolPais::Existe(int codigo) {
    if (ArbolVacio()) {
        cout << "El arbol ABB esta vacio" << endl;
        return false;
    }

    std::stringstream ss1;
    ss1 << codigo;
    string num1 = ss1.str();
    string codigosBuscados = num1 + ";";
    pnodo aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        return false;
    }
}


















// CIUDADES
class nodoCIU {
public:
    nodoCIU(const string &v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoCIU(const string &v, nodoCIU *signodoCIU)
    {
        valor = v;
        siguiente = signodoCIU;
    }

private:
    string valor;
    nodoCIU *siguiente;
    nodoCIU *anterior;

    friend class ArbolCiudad;
};
typedef nodoCIU *pnodoCIU;

class ArbolCiudad {
public:
    ArbolCiudad() { primero = NULL; }
    ~ArbolCiudad();

    void agregarNodoIn(string v);
    void agregarNodo(string v);
    void InsertarPos(string v, int pos);
    bool ArbolVacio() { return primero == NULL; }
    void Imprimir();
    void MostrarCIU();
    int cantNodos();
    void CargarDesdeArchivoCIU();
    void ArbolCiudadsCIU(ArbolPais & arbolPais);
    void ComprobacionCIU();
    void AgregarCIU(ArbolPais & arbolPais);
    void ModificarNombreCIU();
    bool ExisteCIU(string codigo);
    string MostrarArbolCiudadesPorPais();
    string GuardarArbolCiudades();
private:
    pnodoCIU primero;
};

string ArbolCiudad::GuardarArbolCiudades() {
    string memoria;

    if (ArbolVacio()) {
        cout << "El árbol de Ciudades está vacío." << endl;
        return "Arbol vacio";
    }

    pnodoCIU aux = primero;
    int i = 0;

    while (i < cantNodos()) {
        memoria += aux->valor + "->";
        aux = aux->siguiente;
        i++;
    }
    
    // Agregar el último elemento (para que no quede un "; //" extra al final)
    memoria += aux->valor;

    return memoria;
}


string ArbolCiudad::MostrarArbolCiudadesPorPais() {
	cout<<"digite el codigo de pais a buscar"<<endl;
	string codigoPais;
	cin >> codigoPais;
	string memoria;
    if (ArbolVacio()) {
        cout << "El arbol de Ciudades esta vacio." << endl;
        return "Arbol vacio";
    }

    pnodoCIU aux = primero;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigoPais) != string::npos) {
            cout << aux->valor << endl;
            memoria += aux -> valor + "; // ";
        }
        aux = aux->siguiente;
        i++;
    }
    
    return memoria;
}


void ArbolCiudad::ModificarNombreCIU() {
    if (ArbolVacio()) {
        cout << "El arbol AVL esta vacio" << endl;
        return;
    }

    int codigo1, codigo2;
    cout << "Ingrese primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;

    std::stringstream ss1, ss2;
    ss1 << codigo1;
    ss2 << codigo2;

    string num1 = ss1.str();
    string num2 = ss2.str();

    string codigosBuscados = num1 + ";" + num2;
    pnodoCIU aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			cout<<"codigo encontrado"<<endl;
			string newName;
			cout<<"digite el nuevo nombre"<<endl;
			cin >> newName;
			
			string modificar = codigosBuscados + ";" + newName;
			aux -> valor = modificar;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol" << endl;
    }

}

void ArbolCiudad::AgregarCIU(ArbolPais & arbolPais){
	int NumPais;
	cout<<"agregar ArbolCiudades"<<endl;
	cout<<"A continuacion se muestran los paises disponibles: "<<endl;		
	arbolPais.Mostrar();
	cout<<"para agregar Ciudades, se debe de verificar la existencia del pais, digite el numero de pais"<<endl;
	cin>>NumPais;
	if(arbolPais.Existe(NumPais)){
		cout<<"el pais si existe, se procede a agregar"<<endl;
		int codigoArbolCiudad;
		cout<<"digite el codigo de la Ciudad"<<endl;
		cin >> codigoArbolCiudad;
		
	    std::stringstream ss1,ss2;
	    ss1 << NumPais;
	    ss2 << codigoArbolCiudad;
	    string num1 = ss1.str();
	    string num2 = ss2.str();
	    
		string NombreNuevo;
		cout<<"digite el nombre de la Ciudad"<<endl;
		cin >> NombreNuevo;
	
		string NuevoValor = num1 + ";" + num2 + ";" + NombreNuevo;
		agregarNodo(NuevoValor);
	
	}else{
		cout<<"el pais no existe, No se agrega"<<endl;
		ArbolCiudadsCIU(arbolPais);
	}
}


void ArbolCiudad::ArbolCiudadsCIU(ArbolPais & arbolPais)
{
	bool ejecucion = true;
	cout<<"bienvenido a Ciudades"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar Ciudades digite 1: "<<endl;
		cout<<"ver Ciudades digite 2: "<<endl;
		cout<<"agregar un Ciudad digite 3:"<<endl;
		cout<<"modificar una Ciudad digite 4:"<<endl;
		cout<<"salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un Ciudad"<<endl;
				cout<<"Ciudads disponibles: "<<endl;
				MostrarCIU();
				ComprobacionCIU();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los Ciudads"<<endl;
				cout<<"se mostraran todos los Ciudads a continuacion: "<<endl;
				MostrarCIU();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un Ciudad"<<endl;
				AgregarCIU(arbolPais);

				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, modificar nombre Ciudad"<<endl;
				cout<<"Ciudades disponibles"<<endl;
				MostrarCIU();
				ModificarNombreCIU();	
				break;
			case 5:
				cout<<""<<endl;
				cout<<"opcion 5, salir a Menu principal"<<endl;
				ejecucion = false;	
				break;				
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


void ArbolCiudad::ComprobacionCIU() {
    if (ArbolVacio()) {
        cout << "El arbol AVL esta vacio" << endl;
        return;
    }

    int codigo1, codigo2;
    cout << "Ingrese primer c?digo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo c?digo: " << endl;
    cin >> codigo2;

    std::stringstream ss1, ss2;
    ss1 << codigo1;
    ss2 << codigo2;

    string num1 = ss1.str();
    string num2 = ss2.str();

    string codigosBuscados = num1 + ";" + num2;
    pnodoCIU aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);

            cout << "Codigos encontrados en el arbol: " << codigosBuscados << endl;
            cout << "Nombre asociado: " << nombre << endl;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol." << endl;
    }
}


void ArbolCiudad::CargarDesdeArchivoCIU() {
    set<string> numero2_set;  

    ifstream archivo("Ciudades.txt");
    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            istringstream iss(linea);
            string numero1, numero2, nombre;
            getline(iss, numero1, ';');
            getline(iss, numero2, ';');
            getline(iss, nombre);

            // Verificar si NUMERO3 es diferente de los anteriores
            if (numero2_set.find(numero2) == numero2_set.end())
            {
                numero2_set.insert(numero2);  // Agregar a conjunto de NUMERO3
                string nuevo_valor = numero1 + ";" + numero2 +  ";" + nombre;
                agregarNodo(nuevo_valor);
            }
            else
            {
                cout << "Advertencia: NUMERO debe ser diferente a los otros NUMERO anteriores." << endl;
            }
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
                
ArbolCiudad::~ArbolCiudad()
{
   pnodoCIU aux;
   pnodoCIU temp;
   
   while(primero) {
      temp = primero;
      aux=primero;
      primero = primero->siguiente;
      while (aux->siguiente!=primero)
           aux= aux->siguiente;
      aux->siguiente=primero;
      
      delete temp;
      primero=NULL;
   }
   primero= NULL;
}
                        
int ArbolCiudad::cantNodos() 
{
    int cont=0;

    pnodoCIU aux = primero->siguiente;
    if(ArbolVacio())
    {
        return cont;
    }
    else
    {   cont=cont+1;
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}

void ArbolCiudad::agregarNodo(string v)
{
   if (ArbolVacio())
     {
     primero = new nodoCIU(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoCIU nuevo = new nodoCIU(v);//1
     nuevo->anterior = primero->anterior;//2
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}
 



void ArbolCiudad::MostrarCIU()
{
   pnodoCIU aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;
} 

bool ArbolCiudad::ExisteCIU(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoCIU aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        return false;
    }
}
















//clase ArbolRestaurante
class nodoRE {
public:
    nodoRE(const string &v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoRE(const string &v, nodoRE *signodoRE)
    {
        valor = v;
        siguiente = signodoRE;
    }

private:
    string valor;
    nodoRE *siguiente;
    nodoRE *anterior;

    friend class ArbolRestaurante;
};
typedef nodoRE *pnodoRE;

class ArbolRestaurante {
public:
    ArbolRestaurante() { primero = NULL; }
    ~ArbolRestaurante();

    void agregarNodoIn(string v);
    void agregarNodo(string v);
    void InsertarPos(string v, int pos);
    bool ArbolVacio() { return primero == NULL; }
    void Imprimir();
    void MostrarRE();
    int cantNodos();
    void CargarDesdeArchivoRE();
    void ArbolRestaurantesRE(ArbolCiudad & arbolCiudad);
    void ComprobacionRE();
    void ModificarNombreRE();
    void agregarRE(ArbolCiudad & arbolCiudad);
    bool ExisteRE(string codigo);
    string MostrarArbolRestaurantesPorArbolCiudad();
    int stringAEnteroRE(const std::string &cadena);
    string EncontrarValorMayorPedido();
    
private:
    pnodoRE primero;
};

string ArbolRestaurante::EncontrarValorMayorPedido() {
    if (ArbolVacio()) {
        cout << "El arbol de Restaurantes esta vacio." << endl;
        return "lista vacia";
    }

    pnodoRE aux = primero;
    int valorMayor = -1;  
    pnodoRE nodoMayor = NULL;  

    while (aux->siguiente != primero) {
        size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
        string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
        int numeroPedido = stringAEnteroRE(pedidoStr);

        if (numeroPedido > valorMayor) {
            valorMayor = numeroPedido;
            nodoMayor = aux;
        }

        aux = aux->siguiente;
    }

    // Comprobar el ?ltimo nodo tambi?n
    size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
    string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
    int numeroPedido = stringAEnteroRE(pedidoStr);

    if (numeroPedido > valorMayor) {
        valorMayor = numeroPedido;
        nodoMayor = aux;
    }

    if (nodoMayor != NULL) {
        cout << "Informacion del Restaurante: " << nodoMayor->valor << endl;
        return "Informacion del Restaurante: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n Restaurante con con consultas." << endl;
    }
}

string ArbolRestaurante::MostrarArbolRestaurantesPorArbolCiudad() {
    cout << "Digite el codigo de pais: ";
    string codigoPais;
    cin >> codigoPais;

    cout << "Digite el codigo de Ciudad: ";
    string codigoArbolCiudad;
    cin >> codigoArbolCiudad;

    string codigosBuscados = codigoPais + ";" + codigoArbolCiudad;
    
    string memoria;
    if (ArbolVacio()) {
        cout << "El arbol de Restaurantes esta vacio." << endl;
        return "arbol vacia";
    }

    pnodoRE aux = primero;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
        	memoria += aux -> valor + "; // ";
            cout << aux->valor << endl;
        }
        aux = aux->siguiente;
        i++;
    }
    return memoria;
}

void ArbolRestaurante::agregarRE(ArbolCiudad & arbolCiudad){
	cout<<"agregar Ciudades"<<endl;
	cout<<"A continuacion muestran paises y Ciudades disponibles: "<<endl;		
	arbolCiudad.MostrarCIU();
	cout<<"para agregar Restaurantes, se debe de verificar la existencia del pais y Ciudad, agregar sus codigos"<<endl;
    int codigo11, codigo21;
    cout << "Ingrese primer codigo: " << endl;
    cin >> codigo11;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo21;

    std::stringstream ss1, ss2;
    ss1 << codigo11;
    ss2 << codigo21;

    string num1 = ss1.str();
    string num2 = ss2.str();

    string codigosBuscados = num1 + ";" + num2;
    
    
	if(arbolCiudad.ExisteCIU(codigosBuscados)){
		cout<<"el pais y Ciudad si existes, se procede a agregar"<<endl;
	    int codigo1a;
	    cout << "Ingrese el codigo del nuevo Restaurante3: " << endl;
	    cin >> codigo1a;

	    std::stringstream ss1a;
	    ss1a << codigo1a;

	    string num1a = ss1.str();
		    
		string NombreNuevo;
		cout<<"digite el nombre del Restaurante"<<endl;
		cin >> NombreNuevo;
	
		string NuevoValor = codigosBuscados + ";" + num1a + ";" + NombreNuevo;
		agregarNodo(NuevoValor);
	
	}else{
		cout<<"el pais no existe, No se agrega"<<endl;
		ArbolRestaurantesRE(arbolCiudad);
	}
}

void ArbolRestaurante::ModificarNombreRE() {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    int codigo1, codigo2,codigo3;
    cout << "Ingrese primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;
    
    cout << "Ingrese el tercer codigo: " << endl;
    cin >> codigo3;

    std::stringstream ss1, ss2, ss3;
    ss1 << codigo1;
    ss2 << codigo2;
    ss3 <<codigo3;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3;
    pnodoRE aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			cout<<"codigo encontrado"<<endl;
			string newName;
			cout<<"digite el nuevo nombre"<<endl;
			cin >> newName;
			
			string modificar = codigosBuscados + ";" + newName;
			aux -> valor = modificar;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol." << endl;
    }

}

void ArbolRestaurante::ArbolRestaurantesRE(ArbolCiudad & listaArbolCiudad2)
{
	bool ejecucion = true;
	cout<<"bienvenido a Restaurantes"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar Restaurantes digite 1: "<<endl;
		cout<<"ver Restaurantes digite 2: "<<endl;
		cout<<"agregar un Restaurante digite 3:"<<endl;
		cout<<"modificar un Restaurante digite 4:"<<endl;
		cout<<"para salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un Restaurante"<<endl;
				cout<<"Restaurantes disponibles: "<<endl;
				MostrarRE();
				ComprobacionRE();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los Restaurantes"<<endl;
				cout<<"se mostraran todos los Restaurantes a continuacion: "<<endl;
				MostrarRE();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un Restaurante"<<endl;
				agregarRE(listaArbolCiudad2);
				break;			

			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, modificar nombre Restaurante"<<endl;
				cout<<"codigos disponibles"<<endl;
				MostrarRE();
				ModificarNombreRE();	
				break;
			case 5:
				cout<<""<<endl;
				cout<<"opcion 5, salir a Menu principal"<<endl;
				ejecucion = false;	
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}





int ArbolRestaurante::stringAEnteroRE(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolRestaurante::ComprobacionRE() {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    int codigo1, codigo2, codigo3;
    cout << "Ingrese el primer c?digo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo c?digo: " << endl;
    cin >> codigo2;

    cout << "Ingrese el tercer c?digo: " << endl;
    cin >> codigo3;

    std::stringstream ss1, ss2, ss3;
    ss1 << codigo1;
    ss2 << codigo2;
    ss3 << codigo3;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3;
    pnodoRE aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroRE(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;

                cout << "Codigos encontrados en el arbol: " << codigosBuscados << endl;
                cout << "Nuevo valor asociado: " << nuevoValor << endl;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
    }
}

void ArbolRestaurante::CargarDesdeArchivoRE() {
    set<string> numero3_set;  

    ifstream archivo("Restaurantes.txt");
    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            istringstream iss(linea);
            string numero1, numero2, numero3, nombre;
            getline(iss, numero1, ';');
            getline(iss, numero2, ';');
            getline(iss, numero3, ';');
            getline(iss, nombre);

            // Verificar si NUMERO3 es diferente de los anteriores
            if (numero3_set.find(numero3) == numero3_set.end())
            {
                numero3_set.insert(numero3);  // Agregar a conjunto de NUMERO3
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + nombre + +";"+"0";
                agregarNodo(nuevo_valor);
            }
            else
            {
                cout << "Advertencia: NUMERO3 debe ser diferente a los otros NUMERO3 anteriores." << endl;
            }
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
                
ArbolRestaurante::~ArbolRestaurante()
{
   pnodoRE aux;
   pnodoRE temp;
   
   while(primero) {
      temp = primero;
      aux=primero;
      primero = primero->siguiente;
      while (aux->siguiente!=primero)
           aux= aux->siguiente;
      aux->siguiente=primero;
      
      delete temp;
      primero=NULL;
   }
   primero= NULL;
}
                           
int ArbolRestaurante::cantNodos() 
{
    int cont=0;

    pnodoRE aux = primero->siguiente;
    if(ArbolVacio())
    {
        return cont;
    }
    else
    {   cont=cont+1;
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}
 
void ArbolRestaurante::agregarNodo(string v)
{
   if (ArbolVacio())
     {
     primero = new nodoRE(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoRE nuevo = new nodoRE(v);//1
     nuevo->anterior = primero->anterior;//2
     /*nuevo->siguiente=primero->anterior->siguiente;opcion para intruccion 3*/
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}



void ArbolRestaurante::MostrarRE()
{
   pnodoRE aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;

} 

bool ArbolRestaurante::ExisteRE(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoRE aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        return false;
    }
}








//clase ArbolMenu
class nodoME {
public:
    nodoME(const string &v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoME(const string &v, nodoME *signodoME)
    {
        valor = v;
        siguiente = signodoME;
    }

private:
    string valor;
    nodoME *siguiente;
    nodoME *anterior;

    friend class ArbolMenu;
};
typedef nodoME *pnodoME;

class ArbolMenu {
public:
    ArbolMenu() { primero = NULL; }
    ~ArbolMenu();

    void agregarNodoIn(string v);
    void agregarNodo(string v);
    void InsertarPos(string v, int pos);
    bool ArbolVacio() { return primero == NULL; }
    void Imprimir();
    void MostrarME();
    int cantNodos();
    void CargarDesdeArchivoME();
    void ArbolMenusME(ArbolRestaurante & arbolRestaurante);
    void ComprobacionME();
    void ModificarNombreME();
    void AgregarME(ArbolRestaurante & arbolRestaurante);
    bool ExisteME(string codigo);
    int stringAEnteroME(const std::string &cadena);
    string EncontrarValorMayorPedido();
private:
    pnodoME primero;
};

string ArbolMenu::EncontrarValorMayorPedido() {
    if (ArbolVacio()) {
        cout << "El arbol de Menu esta vacio." << endl;
        return "Arbol vacio";
    }

    pnodoME aux = primero;
    int valorMayor = -1;  // Inicializamos con un valor menor al m?nimo posible
    pnodoME nodoMayor = NULL;  // Nodo correspondiente al valor m?s alto

    while (aux->siguiente != primero) {
        size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
        string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
        int numeroPedido = stringAEnteroME(pedidoStr);

        if (numeroPedido > valorMayor) {
            valorMayor = numeroPedido;
            nodoMayor = aux;
        }

        aux = aux->siguiente;
    }

    // Comprobar el ?ltimo nodo tambi?n
    size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
    string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
    int numeroPedido = stringAEnteroME(pedidoStr);

    if (numeroPedido > valorMayor) {
        valorMayor = numeroPedido;
        nodoMayor = aux;
    }

    if (nodoMayor != NULL) {
        cout << "Informacion del m: " << nodoMayor->valor << endl;
        return "Informacion del Menu: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n Restaurante con con consultas." << endl;
    }
}

int ArbolMenu::stringAEnteroME(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolMenu::AgregarME(ArbolRestaurante & arbolRestaurante){
	cout<<"agregar Ciudades"<<endl;
	cout<<"A continuacion muestran paises y Ciudades disponibles: "<<endl;		
	arbolRestaurante.MostrarRE();
	cout<<"para agregar Restaurantes, se debe de verificar la existencia del pais, Ciudad y Restaurante, agregar sus codigos"<<endl;
    int codigo12, codigo22,codigo32;
    cout << "Ingrese primer codigo: " << endl;
    cin >> codigo12;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo22;
    
    cout<<"Ingrese el tercer codigo:"<<endl;
    cin >> codigo32;

    std::stringstream ss1, ss2,ss3;
    ss1 << codigo12;
    ss2 << codigo22;
    ss3 << codigo32;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3;
    
    
	if(arbolRestaurante.ExisteRE(codigosBuscados)){
		cout<<"el pais, Ciudad y Restaurante existen, se procede a agregar"<<endl;
	    int codigo1a;
	    cout << "Ingrese el codigo del nuevo Menu: " << endl;
	    cin >> codigo1a;

	    std::stringstream ss1a;
	    ss1a << codigo1a;

	    string num1a = ss1.str();
		    
		string NombreNuevo;
		cout<<"digite el nombre del Menu"<<endl;
		cin >> NombreNuevo;
	
		string NuevoValor = codigosBuscados + ";" + num1a + ";" + NombreNuevo;
		agregarNodo(NuevoValor);
	
	}else{
		cout<<"no existe, No se agrega"<<endl;
		ArbolMenusME(arbolRestaurante);
	}
}

void ArbolMenu::ModificarNombreME() {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    int codigo1, codigo2,codigo3,codigo4;
    cout << "Ingrese primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;
    
    cout << "Ingrese el tercer codigo: " << endl;
    cin >> codigo3;
    
    cout << "Ingrese el cuarto codigo: " << endl;
    cin >> codigo4;

    std::stringstream ss1, ss2, ss3,ss4;
    ss1 << codigo1;
    ss2 << codigo2;
    ss3 <<codigo3;
    ss4 << codigo4;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();
    string num4 = ss4.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3 + ";" + num4;
    pnodoME aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			cout<<"codigo encontrado"<<endl;
			string newName;
			cout<<"digite el nuevo nombre"<<endl;
			cin >> newName;
			
			string modificar = codigosBuscados + ";" + newName;
			aux -> valor = modificar;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol" << endl;
    }

} 

void ArbolMenu::ArbolMenusME(ArbolRestaurante & arbolRestaurante)
{
	bool ejecucion = true;
	cout<<"bienvenido a Menus"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar Menus digite 1: "<<endl;
		cout<<"ver Menus digite 2: "<<endl;
		cout<<"agregar un Menu digite 3:"<<endl;
		cout<<"modificar un ArbolMenu digite 4:"<<endl;
		cout<<"para salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un Menu"<<endl;
				cout<<"Menus disponibles: "<<endl;
				MostrarME();
				ComprobacionME();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los Menus"<<endl;
				cout<<"se mostraran todos los Menus a continuacion: "<<endl;
				MostrarME();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un Menu"<<endl;
				cout<<"se muestran paises, Ciudades y Restaurantes disponibles"<<endl;
				MostrarME();
				AgregarME(arbolRestaurante);
				break;			

			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, modificar nombre"<<endl;
				cout<<"codigos disponibles"<<endl;
				MostrarME();
				ModificarNombreME();
				break;
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a Menu principal"<<endl;
				ejecucion = false;	
				break;		
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}





void ArbolMenu::ComprobacionME() {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    int codigo1, codigo2, codigo3,codigo4;
    cout << "Ingrese el primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;

    cout << "Ingrese el tercer codigo: " << endl;
    cin >> codigo3;
    
    cout << "Ingrese el cuarto codigo: " << endl;
    cin >> codigo4;

    std::stringstream ss1, ss2, ss3,ss4;
    ss1 << codigo1;
    ss2 << codigo2;
    ss3 << codigo3;
    ss4 << codigo4;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();
    string num4 = ss4.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3 + ";" + num4;
    pnodoME aux = primero;
    bool encontrado = false;
    int i =0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroME(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;

                cout << "Codigos encontrados en el arbol: " << codigosBuscados << endl;
                cout << "Nuevo valor asociado: " << nuevoValor << endl;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
    }
}


void ArbolMenu::CargarDesdeArchivoME() {
    set<string> numero4_set;  

    ifstream archivo("Menu.txt");
    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            istringstream iss(linea);
            string numero1, numero2, numero3,numero4, nombre;
            getline(iss, numero1, ';');
            getline(iss, numero2, ';');
            getline(iss, numero3, ';');
            getline(iss, numero4, ';');
            getline(iss, nombre);

            // Verificar si NUMERO3 es diferente de los anteriores
            if (numero4_set.find(numero4) == numero4_set.end())
            {
                numero4_set.insert(numero4);  // Agregar a conjunto de NUMERO3
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + numero4+ ";" + nombre + ";" + "0";
                agregarNodo(nuevo_valor);
            }
            else
            {
                cout << "Advertencia: NUMERO3 debe ser diferente a los otros NUMERO3 anteriores." << endl;
            }
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
                
ArbolMenu::~ArbolMenu()
{
   pnodoME aux;
   pnodoME temp;
   
   while(primero) {
      temp = primero;
      aux=primero;
      primero = primero->siguiente;
      while (aux->siguiente!=primero)
           aux= aux->siguiente;
      aux->siguiente=primero;
      
      delete temp;
      primero=NULL;
   }
   primero= NULL;
}
                           
int ArbolMenu::cantNodos() 
{
    int cont=0;

    pnodoME aux = primero->siguiente;
    if(ArbolVacio())
    {
        return cont;
    }
    else
    {   cont=cont+1;
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}

void ArbolMenu::agregarNodo(string v)
{
   if (ArbolVacio())
     {
     primero = new nodoME(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoME nuevo = new nodoME(v);//1
     nuevo->anterior = primero->anterior;//2
     /*nuevo->siguiente=primero->anterior->siguiente;opcion para intruccion 3*/
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}




void ArbolMenu::MostrarME()
{
   pnodoME aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
}   

bool ArbolMenu::ExisteME(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoME aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        return false;
    }
}






class nodoPRO {
public:
    nodoPRO(const string &v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoPRO(const string &v, nodoPRO *signodoPRO)
    {
        valor = v;
        siguiente = signodoPRO;
    }

private:
    string valor;
    nodoPRO *siguiente;
    nodoPRO *anterior;

    friend class ArbolProducto;
};
typedef nodoPRO *pnodoPRO;

class ArbolProducto {
public:
    ArbolProducto() { primero = NULL; }
    ~ArbolProducto();

    void agregarNodoIn(string v);
    void agregarNodo(string v);
    void InsertarPos(string v, int pos);
    bool ArbolVacio() { return primero == NULL; }
    void Imprimir();
    void MostrarPRO();
    int cantNodos();
    void CargarDesdeArchivoPRO();
    void ArbolProductosPRO(ArbolMenu & arbolMenu);
    void ComprobacionPRO();
    void AgregarPRO(ArbolMenu & arbolMenu);
    void ModificarNombrePRO();
    bool ExistePRO(string codigo);
    int stringAEnteroPRO(const std::string &cadena);
    string EncontrarValorMayorPedido();
    string muestraCantidad(string codigo);
    bool ModificarCantidadPro(string codigosBuscados, int resta);
    string getPrecio(string codigosBuscados);
    string getCantProd(string codigosBuscados);
private:
    pnodoPRO primero;
};

string ArbolProducto::EncontrarValorMayorPedido() {
    if (ArbolVacio()) {
        cout << "El arbol de Menu esta vacio." << endl;
        return "arbol vacio";
    }

    pnodoPRO aux = primero;
    int valorMayor = -1;  // Inicializamos con un valor menor al m?nimo posible
    pnodoPRO nodoMayor = NULL;  // Nodo correspondiente al valor m?s alto

    while (aux->siguiente != primero) {
        size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
        string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
        int numeroPedido = stringAEnteroPRO(pedidoStr);

        if (numeroPedido > valorMayor) {
            valorMayor = numeroPedido;
            nodoMayor = aux;
        }

        aux = aux->siguiente;
    }

    // Comprobar el ?ltimo nodo tambi?n
    size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
    string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
    int numeroPedido = stringAEnteroPRO(pedidoStr);

    if (numeroPedido > valorMayor) {
        valorMayor = numeroPedido;
        nodoMayor = aux;
    }

    if (nodoMayor != NULL) {
        cout << "Informacion del m: " << nodoMayor->valor << endl;
        return "Informacion del Producto: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n Restaurante con con consultas." << endl;
    }
}

int ArbolProducto::stringAEnteroPRO(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolProducto::ModificarNombrePRO() {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    int codigo1, codigo2,codigo3,codigo4,codigo5;
    cout << "Ingrese primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;
    
    cout << "Ingrese el tercer codigo: " << endl;
    cin >> codigo3;
    
    cout << "Ingrese el cuarto codigo: " << endl;
    cin >> codigo4;
    
    cout<<"ingrese el quinto codigo: "<<endl;
    cin >> codigo5;

    std::stringstream ss1, ss2, ss3,ss4,ss5;
    ss1 << codigo1;
    ss2 << codigo2;
    ss3 <<codigo3;
    ss4 << codigo4;
    ss5 << codigo5;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();
    string num4 = ss4.str();
    string num5 = ss5.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3 + ";" + num4 + ";" + num5;
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			cout<<"codigo encontrado"<<endl;
			string newName;
			cout<<"digite el nuevo nombre"<<endl;
			cin >> newName;
			
			int calorias,precio;
			cout<<"digite las nuevas calorias del Producto"<<endl;
			cin >> calorias;
			
			cout<<"digite el nuevo precio del Producto"<<endl;
			cin >> precio;
			
			std::stringstream ss2a,ss2b;
			ss2a << calorias;
			ss2b << precio;
			string caloriaString =  ss2a.str();
			string precioString = ss2b.str();
			
			string modificar = codigosBuscados + ";" + newName + ";" + caloriaString + ";" + precioString;
			aux -> valor = modificar;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol." << endl;
    }

}

void ArbolProducto::ArbolProductosPRO(ArbolMenu & arbolMenu)
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolProductos"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar Productos digite 1: "<<endl;
		cout<<"ver Productos digite 2: "<<endl;
		cout<<"agregar un ArbolProducto digite 3:"<<endl;
		cout<<"modificar un ArbolProducto digite 4:"<<endl;
		cout<<"para salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un Producto"<<endl;
				cout<<"Productos disponibles: "<<endl;
				MostrarPRO();
				ComprobacionPRO();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los Productos"<<endl;
				cout<<"se mostraran todos los Productos a continuacion: "<<endl;
				MostrarPRO();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un Producto"<<endl;
				AgregarPRO(arbolMenu);
				break;			

			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, modificar nombre"<<endl;
				cout<<"opciones de moficicacion disponibles"<<endl;
				MostrarPRO();
				ModificarNombrePRO();
				break;
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a Producto principal"<<endl;
				ejecucion = false;	
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}

void ArbolProducto::AgregarPRO(ArbolMenu & arbolMenu){
	cout<<"agregar ArbolProductos"<<endl;
	cout<<"A continuacion muestran paises, Ciudades, Restaurantes y Menus disponibles: "<<endl;		
	arbolMenu.MostrarME();
	cout<<"para agregar Productos, se debe de verificar la existencia del pais, Ciudad, Restaurante y Menu, agregar sus codigos"<<endl;
    int codigo13, codigo23,codigo33,codigo43;
    cout<<""<<endl;
    cout << "Ingrese primer codigo: " << endl;
    cin >> codigo13;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo23;
    
    cout<<"Ingrese el tercer codigo:"<<endl;
    cin >> codigo33;
    
    cout<<"ingrese el cuarto codigo:"<<endl;
    cin >> codigo43;

    std::stringstream ss1, ss2,ss3,ss4;
    ss1 << codigo13;
    ss2 << codigo23;
    ss3 << codigo33;
    ss4 << codigo43;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();
    string num4 = ss4.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3 + ";" + num4;
    
    
	if(arbolMenu.ExisteME(codigosBuscados)){
		cout<<"el pais, Ciudad, Restaurante y Menu existen, se procede a agregar"<<endl;
	    string codigo1a;
	    cout << "Ingrese el codigo del nuevo Menu: " << endl;
	    cin >> codigo1a;

		    
		string NombreNuevo;
		cout<<"digite el nombre del Menu"<<endl;
		cin >> NombreNuevo;
		
		int calorias,precio;
		cout<<"digite las calorias del Producto"<<endl;
		cin >> calorias;
		
		cout<<"digite el precio del Producto"<<endl;
		cin >> precio;
		
		std::stringstream ss2a,ss2b;
		ss2a << calorias;
		ss2b << precio;
		string caloriaString =  ss2a.str();
		string precioString = ss2b.str();
	
		string NuevoValor = codigosBuscados + ";" + codigo1a + ";" + NombreNuevo + ";" + caloriaString + ";" + precioString + ";" + "20" + ";" + "0";
		agregarNodo(NuevoValor);
	
	}else{
		cout<<"no existe, No se agrega"<<endl;
		ArbolProductosPRO(arbolMenu);
	}
}



void ArbolProducto::ComprobacionPRO() {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    int codigo1, codigo2, codigo3,codigo4,codigo5;
    cout << "Ingrese el primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;

    cout << "Ingrese el tercer codigo: " << endl;
    cin >> codigo3;
    
    cout << "Ingrese el cuarto codigo: " << endl;
    cin >> codigo4;
    
    cout << "Ingrese el quinto codigo: " << endl;
    cin >> codigo5;

    std::stringstream ss1, ss2, ss3,ss4,ss5;
    ss1 << codigo1;
    ss2 << codigo2;
    ss3 << codigo3;
    ss4 << codigo4;
    ss5 << codigo5;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();
    string num4 = ss4.str();
    string num5 = ss5.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3 + ";" + num4 + ";" + num5;
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

	while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroPRO(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;

                cout << "Codigos encontrados en el arbol: " << codigosBuscados << endl;
                cout << "Nuevo valor asociado: " << nuevoValor << endl;
			    std::string cadena = aux -> valor ;
			    std::istringstream stream(cadena);
			    std::string dato;
				int j = 0;
				while (std::getline(stream, dato, ';')) {
						        if (!dato.empty()) {
						        	
						        	if(j == 5){
						        		cout<<"pruducto: "<<dato<<endl;
									}
						        	if(j == 6){
						        		cout<<"calorias: "<<dato<<endl;
									}
						        	if(j == 7){
						        		cout<<"precio: "<<dato<<endl;
									}
									if(j==8){
										cout<<"cantidad de productos: "<<dato<<endl;
									}
									if(j==9){
										cout<<"cantidad de busquedas: "<<dato<<endl;
									}
						            j++;
						        }
						    }
				            break;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
    }
}


void ArbolProducto::CargarDesdeArchivoPRO() {
    set<string> numero4_set;  

    ifstream archivo("Productos.txt");
    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            istringstream iss(linea);
            string numero1, numero2, numero3,numero4,numero5, nombre,numero6,numero7,numero8;
            getline(iss, numero1, ';');
            getline(iss, numero2, ';');
            getline(iss, numero3, ';');
            getline(iss, numero4, ';');
            getline(iss, numero5, ';');
            getline(iss, nombre);
            getline(iss, numero6, ';');
            getline(iss, numero7, ';');
            getline(iss, numero8, ';');

            // Verificar si NUPRORO3 es diferente de los anteriores
            if (numero4_set.find(numero4) == numero4_set.end())
            {
                numero4_set.insert(numero4);  // Agregar a conjunto de NUPRORO3
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + numero4+ ";"+ numero5+ ";" + nombre +";" + numero6 + ";" + numero7 +";" + numero8 + ";"  + "0";
                agregarNodo(nuevo_valor);
            }
            else
            {
                cout << "Advertencia: NUPRORO3 debe ser diferente a los otros NUPRORO3 anteriores." << endl;
            }
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
                
ArbolProducto::~ArbolProducto()
{
   pnodoPRO aux;
   pnodoPRO temp;
   
   while(primero) {
      temp = primero;
      aux=primero;
      primero = primero->siguiente;
      while (aux->siguiente!=primero)
           aux= aux->siguiente;
      aux->siguiente=primero;
      
      delete temp;
      primero=NULL;
   }
   primero= NULL;
}
                          
int ArbolProducto::cantNodos() 
{
    int cont=0;

    pnodoPRO aux = primero->siguiente;
    if(ArbolVacio())
    {
        return cont;
    }
    else
    {   cont=cont+1;
        while(aux!=primero)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }
    
}

void ArbolProducto::agregarNodo(string v)
{
   if (ArbolVacio())
     {
     primero = new nodoPRO(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoPRO nuevo = new nodoPRO(v);//1
     nuevo->anterior = primero->anterior;//2
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}
  
void ArbolProducto::MostrarPRO()
{
   pnodoPRO aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;
}

bool ArbolProducto::ExistePRO(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        return false;
    }
}

string ArbolProducto::muestraCantidad(string codigosBuscados) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return "ARBOL VACIO";
    }
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

	while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroPRO(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;
			    std::string cadena = aux -> valor ;
			    std::istringstream stream(cadena);
			    std::string dato;
				int j = 0;
				while (std::getline(stream, dato, ';')) {
						        if (!dato.empty()) {
									if(j==8){
										return dato;
									}
						            j++;
						        }
						    }
				            break;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        return "no se encontro codigo en el arbol";
    }
}

bool ArbolProducto::ModificarCantidadPro(string codigosBuscados, int resta){
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;
	string nuevo;
	while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroPRO(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;
			    std::string cadena = aux -> valor ;
			    std::istringstream stream(cadena);
			    std::string dato;
				int j = 0;
				string producto, caloria, precio, busquedas, StrnuevaCantidad ;
				while (std::getline(stream, dato, ';')) {
						        if (!dato.empty()) {
						        	
						        	if(j == 5){
						        		producto = dato;
									}
						        	if(j == 6){
						        		caloria = dato;
									}
						        	if(j == 7){
						        		precio = dato;
									}
									if(j==8){
										int valor = stringAEnteroPRO(dato);
										cout<<"cantidad: "<<valor<<endl;
										cout<<"a restar: "<<resta<<endl;
										if(resta > valor){
											cout<<"error la cantidad de compra es mayor que la disponible"<<endl;
											return false;
										}
										int nuevaCantidad = valor - resta;
										std::stringstream ss1;
										ss1 << nuevaCantidad;
										StrnuevaCantidad = ss1.str();
									}
									if(j==9){
										busquedas = dato;
									}
						            j++;
						        }
						    }
						    nuevo = codigosBuscados + ";" + producto + ";" + caloria + ";" + precio + ";" + StrnuevaCantidad + ";" + busquedas;
						    cout<<nuevo<<endl;
						    aux -> valor = nuevo;
						    return true;
				            break;	            
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
                return false;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
        return false;
    }
}

string ArbolProducto::getPrecio(string codigosBuscados){
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

	while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroPRO(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;

                cout << "Codigos encontrados en el arbol: " << codigosBuscados << endl;
                cout << "Nuevo valor asociado: " << nuevoValor << endl;
			    std::string cadena = aux -> valor ;
			    std::istringstream stream(cadena);
			    std::string dato;
				int j = 0;
				while (std::getline(stream, dato, ';')) {
						        if (!dato.empty()) {
						        	
						        	if(j == 5){
						        		cout<<"pruducto: "<<dato<<endl;
									}
						        	if(j == 6){
						        		cout<<"calorias: "<<dato<<endl;
									}
						        	if(j == 7){
						        		cout<<"precio: "<<dato<<endl;
						        		return dato;
									}
									if(j==8){
										cout<<"cantidad de productos: "<<dato<<endl;
									}
									if(j==9){
										cout<<"cantidad de busquedas: "<<dato<<endl;
									}
						            j++;
						        }
						    }
				            break;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
    }
}










//clase ArbolClientes
class nodoCl {
public:
    nodoCl(const string& v) {
        valor = v;
        siguiente = NULL;
        numCompras = 0; // Inicialmente, el cliente no tiene compras.
    }

    nodoCl(const string& v, nodoCl* signodoCl) {
        valor = v;
        siguiente = signodoCl;
    }

    int numCompras; // Agrega un campo para el n?mero de compras.

private:
    string valor;
    nodoCl* siguiente;

    friend class ArbolClientes;
};


typedef nodoCl* pnodoCl;

class ArbolClientes {
public:
    ArbolClientes() { primero = NULL; }
    ~ArbolClientes();

    void agregarNodo(string v);
    bool ArbolVacio() { return primero == NULL; }
    void MostrarCl();
    int cantNodos();
    void CargarDesdeArchivoCl();
    void ConsultarClientePorCodigoCl();
    void ArbolClientesCl();
    void AgregarClienteCl();
    void ModificarNombreCL();
    bool ExisteCl(string codigo);
    string ObtenerContenidoComoString();
    void agregarComprar(string code);
    int stringAEnteroCl(const std::string &cadena);
    string muestraCompradores();

private:
    pnodoCl primero;
};

int ArbolClientes::stringAEnteroCl(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

string ArbolClientes::ObtenerContenidoComoString() {
        std::stringstream ss;
        nodoCl* aux;
	   if (primero== NULL)
	       cout << "No hay elementos AQUI";  
	   else
	   {
	   		aux = primero;
			while(aux) 
			{
			    ss << aux->valor << "-> ";
			    aux = aux->siguiente;
			}
			cout << endl;
	   }
        return ss.str();
}

void ArbolClientes::ModificarNombreCL() {
    int code;
    cout << "Digite el codigo a modificar" << endl;
    cin >> code;

    string newName;
    cout << "Digite el nuevo nombre" << endl;
    cin.ignore();  // Clear the newline character from the buffer
    getline(cin, newName);

    pnodoCl aux = primero;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == code) {
			    std::stringstream sscode;
			    sscode << code;
			
			    string num1 = sscode.str();          	
            	
                aux->valor = num1 + ";" + newName;
                cout << "Nombre del pais modificado exitosamente." << endl;
                return;
            }
        }
        aux = aux->siguiente;
    }

    cout << "No se encontr? un pa?s con el c?digo proporcionado." << endl;
}

void ArbolClientes::ArbolClientesCl()
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolClientes"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar Clientes digite 1: "<<endl;
		cout<<"ver Clientes digite 2: "<<endl;
		cout<<"agregar un cliente digite 3:"<<endl;
		cout<<"modificar un cliente digite 4:"<<endl;
		cout<<"para salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un cliente"<<endl;
				cout<<"ArbolClientes disponibles: "<<endl;
				MostrarCl();
				ConsultarClientePorCodigoCl();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los ArbolClientes"<<endl;
				cout<<"se mostraran todos los Clientes a continuacion: "<<endl;
				MostrarCl();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un cliente"<<endl;
				AgregarClienteCl();
				MostrarCl();
				break;			
	
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, modificar un cliente"<<endl;
				cout<<"nombres disponibles"<<endl;
				MostrarCl();
				ModificarNombreCL();
				break;
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a Menu principal"<<endl;
				ejecucion = false;			
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}

void ArbolClientes::AgregarClienteCl() {
    cout << "Ingrese la c?dula del cliente (parte entera): ";
    int codigo;
    cin >> codigo;
    cin.ignore();  // Limpia el buffer del salto de l?nea

    cout << "Ingrese el nombre del cliente: ";
    string nombre;
    getline(cin, nombre);

    // Verificar si el c?digo ya existe en la lista
    bool codigoExistente = false;
    pnodoCl aux = primero;
    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == codigo) {
                codigoExistente = true;
                cout << "Error: Ya existe un cliente con la misma c?dula " << codigo << "." << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!codigoExistente) {
        // Usar ostringstream para convertir el entero a cadena
        ostringstream ss;
        ss << codigo;
        string codigoStr = ss.str();

        string pais = codigoStr + ";" + nombre;
        agregarNodo(pais);
        cout << "Cliente agregado exitosamente." << endl;
    }
}


void ArbolClientes::ConsultarClientePorCodigoCl() {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    cout << "Ingrese el codigo del pais a consultar: ";
    int codigo;
    cin >> codigo;

    pnodoCl aux = primero;
    bool encontrado = false;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == codigo) {
                encontrado = true;
                string nombre = aux->valor.substr(pos + 1);
                cout << "Codigo: " << codigoEnArbol << endl;
                cout << "Nombre: " << nombre << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontro un pais con el codigo " << codigo << " en el codigo." << endl;
    }
}

void ArbolClientes::CargarDesdeArchivoCl()
{
    ifstream archivo("Clientes.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(';');
        if (pos != string::npos) {
            string codigo = linea.substr(0, pos);
            string nombre = linea.substr(pos + 1);
            
            bool existe = false;
            pnodoCl aux = primero;
            
            while (aux) {
                size_t posAux = aux->valor.find(';');
                if (posAux != string::npos) {
                    string codigoEnArbol = aux->valor.substr(0, posAux);
                    
                    if (codigoEnArbol == codigo) {
                        existe = true;
                        cout << "Cliente con cedula:  " << codigo << " ya existe en el arbol." << endl;
                        break;
                    }
                }
                aux = aux->siguiente;
            }
            
            if (!existe) {
                agregarNodo(codigo + ";" + nombre + ";" + "0");
                cout << "Cliente con cedula: " << codigo << " agregado exitosamente." << endl;
            }
        }
    }

    archivo.close();
}

ArbolClientes::~ArbolClientes() {
    nodoCl* aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

int ArbolClientes::cantNodos(){
    int cont=0;

    pnodoCl aux= primero;
    if(ArbolVacio()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    cout<< endl;
    }
    
}

void ArbolClientes::agregarNodo(string v)//76
{
   if (ArbolVacio())
     primero = new nodoCl(v);
   else
      { 
       pnodoCl aux = primero;
        while ( aux->siguiente != NULL)
         aux= aux->siguiente;
        pnodoCl nuevo=new nodoCl(v);
        aux->siguiente=nuevo;
      }    
}
     
void ArbolClientes::MostrarCl()

{
   nodoCl *aux;
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

bool ArbolClientes::ExisteCl(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoCl aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i < cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        return false;
    }
}

void ArbolClientes::agregarComprar(string code) {
    string codigosBuscados = code;
    pnodoCl aux = primero;
    bool encontrado = false;
    int i = 0;

	while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroCl(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
    }
}

string ArbolClientes::muestraCompradores() {
    string compradores = "";
    pnodoCl aux = primero;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            size_t lastPos = aux->valor.find_last_of(';');
            if (lastPos != string::npos) {
                string nombre = aux->valor.substr(lastPos + 1);
                if (codigoEnArbol % 10 != 0) {
                    stringstream ss;
                    ss << codigoEnArbol;
                    compradores += ss.str() + ";" + nombre + "\n";
                }
            }
        }
        aux = aux->siguiente;
    }

    return compradores;
}








class nodoComFact {
public:
    nodoComFact(string v)
    {
        valor = v;
        siguiente = NULL;
    }

    nodoComFact(string v, nodoComFact* signodoComFact)
    {
        valor = v;
        siguiente = signodoComFact;
    }

private:
    string valor;
    nodoComFact* siguiente;

    friend class listComFact;
};

typedef nodoComFact* pnodoComFact; // Alias

class listComFact {
public:
    listComFact() { primero = NULL; }
    ~listComFact();

    void InsertarInicio(string v);
    void InsertarFinal(string v);
    bool ListaVacia() { return primero == NULL; }
    void Mostrar();
    int largoLista();
    string ObtenerMayorValor1();
    string ObtenerMenorValor1();

private:
    pnodoComFact primero;
};

string listComFact::ObtenerMayorValor1()
{
    if (ListaVacia())
    {
        cout << "La lista est? vac?a." << endl;
        return "";
    }

    pnodoComFact aux = primero;
    string mayorValor1 = aux->valor;

    while (aux != NULL)
    {
        string valor1 = aux->valor;
        size_t pos = valor1.find(";");
        if (pos != string::npos)
        {
            valor1 = valor1.substr(0, pos);
            if (valor1 > mayorValor1)
            {
                mayorValor1 = valor1;
            }
        }

        aux = aux->siguiente;
    }

    return mayorValor1;
}

string listComFact::ObtenerMenorValor1()
{
    if (ListaVacia())
    {
        cout << "La lista est? vac?a." << endl;
        return "";
    }

    pnodoComFact aux = primero;
    string mayorValor1 = aux->valor;

    while (aux != NULL)
    {
        string valor1 = aux->valor;
        size_t pos = valor1.find(";");
        if (pos != string::npos)
        {
            valor1 = valor1.substr(0, pos);
            if (valor1 < mayorValor1)
            {
                mayorValor1 = valor1;
            }
        }

        aux = aux->siguiente;
    }

    return mayorValor1;
}

listComFact::~listComFact()
{
    pnodoComFact aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

int listComFact::largoLista() {
    int cont = 0;
    pnodoComFact aux = primero;

    if (ListaVacia()) {
        return cont;
    }
    else {
        while (aux != NULL) {
            aux = aux->siguiente;
            cont++;
        }
        return cont;
    }
}

void listComFact::InsertarInicio(string v)
{
    if (ListaVacia())
    {
        primero = new nodoComFact(v);
    }
    else
    {
        pnodoComFact nuevo = new nodoComFact(v);
        nuevo->siguiente = primero;
        primero = nuevo;
    }
}

void listComFact::InsertarFinal(string v)
{
    if (ListaVacia())
        primero = new nodoComFact(v);
    else
    {
        pnodoComFact aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        pnodoComFact nuevo = new nodoComFact(v);
        aux->siguiente = nuevo;
    }
}

void listComFact::Mostrar()
{
    nodoComFact* aux;
    if (primero == NULL)
        cout << "No hay elementos AQUI";
    else
    {
        aux = primero;
        while (aux)
        {
            cout << aux->valor << " -> ";
            aux = aux->siguiente;
        }
        cout << endl;
    }
}















class nodoCOM {
public:
    nodoCOM(string v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoCOM(string v, nodoCOM* signodoCOM)
    {
        valor = v;
        siguiente = signodoCOM;
    }

private:
    string valor;
    nodoCOM* siguiente;
    nodoCOM* anterior;

    friend class ListaCOM;
};

typedef nodoCOM* pnodoCOM;

class ListaCOM {
public:
    ListaCOM() { primero = NULL; }
    ~ListaCOM();

    void InsertarFinal(string v);
    bool ArbolVacio() { return primero == NULL; }
    void BorrarFinal();
    void BorrarInicio();
    void MostrarCompra();
    int largoLista();
    void Paises();
    void AgregarCompra(ArbolProducto & arbolProducto, string valor, ArbolClientes & arbolClientes);
    void ConsultarPaisPorCodigo();
    void BorrarPaisPorCodigo(int codigo);
    void ModificarNombre();
    bool Existe(int codigo);
    void BorrarPaisPorSeisCodigos();
    void BorrarComprasPorInicio(string valor);
    void MostrarComprasPorInicio(string valor);
    void facturar(listComFact & compraFactura);
    std::pair<int, std::string> CarritoCliente(int codigo);
    

private:
    pnodoCOM primero;
};


void ListaCOM::MostrarComprasPorInicio(string valor) {
    pnodoCOM aux = primero;

    while (aux) {
        if (aux->valor.find(valor) == 0) {
            // El valor del nodo empieza con el valor proporcionado, lo imprimimos.
            cout << aux->valor << endl;
        }
        aux = aux->siguiente;
    }
}


void ListaCOM::BorrarComprasPorInicio(string valor) {
    pnodoCOM aux = primero;

    while (aux) {
        if (aux->valor.find(valor) == 0) {
            // El valor del nodo empieza con el valor proporcionado, lo borramos.
            pnodoCOM temp = aux;
            aux = aux->siguiente;

            if (temp == primero) {
                BorrarInicio();
            } else if (temp->siguiente == NULL) {
                BorrarFinal();
            } else {
                temp->anterior->siguiente = temp->siguiente;
                temp->siguiente->anterior = temp->anterior;
                delete temp;
            }
        } else {
            aux = aux->siguiente;
        }
    }
}


void ListaCOM::ModificarNombre() {
    int code;
    cout << "Digite el codigo a modificar" << endl;
    cin >> code;

    string newName;
    cout << "Digite el nuevo nombre" << endl;
    cin.ignore();  // Clear the newline character from the buffer
    getline(cin, newName);

    pnodoCOM aux = primero;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnLista;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnLista;

            if (codigoEnLista == code) {
			    std::stringstream sscode;
			    sscode << code;
			
			    string num1 = sscode.str();          	
            	
                aux->valor = num1 + ";" + newName;
                cout << "Nombre del pais modificado exitosamente." << endl;
                return;
            }
        }
        aux = aux->siguiente;
    }

    cout << "No se encontr? un pa?s con el c?digo proporcionado." << endl;
}

void ListaCOM::ConsultarPaisPorCodigo() {
    if (ArbolVacio()) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    cout << "Ingrese el codigo del pais a consultar: ";
    int codigo;
    cin >> codigo;

    pnodoCOM aux = primero;
    bool encontrado = false;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnLista;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnLista;

            if (codigoEnLista == codigo) {
                encontrado = true;
                string nombre = aux->valor.substr(pos + 1);
                cout << "Codigo: " << codigoEnLista << endl;
                cout << "Nombre: " << nombre << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontro un pais con el codigo " << codigo << " en la lista." << endl;
    }
}

void ListaCOM::BorrarPaisPorCodigo(int codigo) {
    if (ArbolVacio()) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    pnodoCOM aux = primero;
    bool encontrado = false;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnLista;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnLista;

            if (codigoEnLista == codigo) {
                encontrado = true;
                if (aux == primero) {
                    BorrarInicio();
                }
                else if (aux->siguiente == NULL) {
                    BorrarFinal();
                }
                else {
                    aux->anterior->siguiente = aux->siguiente;
                    aux->siguiente->anterior = aux->anterior;
                    delete aux;
                }
                cout << "Pais con codigo " << codigo << " borrado exitosamente." << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontro un pais con el codigo " << codigo << " en la lista." << endl;
    }
}

void ListaCOM::BorrarPaisPorSeisCodigos() {
    if (ArbolVacio()) {
        cout << "La lista est? vac?a." << endl;
        return;
    }

    string codigo1, codigo2, codigo3, codigo4, codigo5, codigo6;

    cout << "Ingrese el primer c?digo: ";
    cin >> codigo1;
    cout << "Ingrese el segundo c?digo: ";
    cin >> codigo2;
    cout << "Ingrese el tercer c?digo: ";
    cin >> codigo3;
    cout << "Ingrese el cuarto c?digo: ";
    cin >> codigo4;
    cout << "Ingrese el quinto c?digo: ";
    cin >> codigo5;
    cout << "Ingrese el sexto c?digo: ";
    cin >> codigo6;

    string codigosBuscados = codigo1 + ";" + codigo2 + ";" + codigo3 + ";" + codigo4 + ";" + codigo5 + ";" + codigo6;
    
    pnodoCOM aux = primero;
    bool encontrado = false;

    while (aux) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            cout << "C?digos encontrados en el nodo: " << aux->valor << endl;

            if (aux == primero) {
                BorrarInicio();
            } else if (aux->siguiente == NULL) {
                BorrarFinal();
            } else {
                pnodoCOM temp = aux;
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                aux = aux->siguiente;
                delete temp;
            }
            cout << "Borrado exitoso." << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void ListaCOM::AgregarCompra(ArbolProducto &arbolProducto, string valor,ArbolClientes & arbolClientes) {
    cout << "Se muestran los ArbolProductos disponibles" << endl;
    arbolProducto.MostrarPRO();
    cout << "Proceda a digitar el ArbolProducto que quiere comprar" << endl;

    int codigo1, codigo2, codigo3, codigo4, codigo5;
    cout << "Ingrese el primer c?digo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo c?digo: " << endl;
    cin >> codigo2;

    cout << "Ingrese el tercer c?digo: " << endl;
    cin >> codigo3;

    cout << "Ingrese el cuarto c?digo: " << endl;
    cin >> codigo4;

    cout << "Ingrese el quinto c?digo: " << endl;
    cin >> codigo5;

    std::stringstream ss1, ss2, ss3, ss4, ss5,ss10;
    ss1 << codigo1;
    ss2 << codigo2;
    ss3 << codigo3;
    ss4 << codigo4;
    ss5 << codigo5;
    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();
    string num4 = ss4.str();
    string num5 = ss5.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3 + ";" + num4 + ";" + num5;

    if (arbolProducto.ExistePRO(codigosBuscados)) {
    	cout<<"Producto encontrado, digite la cantidad a comprar: "<<endl;
    	cout<<"cantidad disponible: "<<arbolProducto.muestraCantidad(codigosBuscados)<<endl; 
    	int cantidad;
    	cin >> cantidad;
		ss10 << cantidad;
		string cantidadStr = ss10.str(); 
    	if(arbolProducto.ModificarCantidadPro(codigosBuscados,cantidad)){
	        cout << "ArbolProducto encontrado y agregado de manera exitosa al cliente " << endl;
	        cout<<"comer en restaurante = 1, llevar = 2"<<endl;
	        string ubi;
	        cin>>ubi;
	        string entrada2 = valor +";"+ codigosBuscados + ";" + cantidadStr + ";" + arbolProducto.getPrecio(codigosBuscados) + ";" + ubi;
	        InsertarFinal(entrada2);
	        arbolClientes.agregarComprar(valor);
	        MostrarCompra();	
		}

    } else {
        cout << "ArbolProducto no encontrado" << endl;
    }
}

ListaCOM::~ListaCOM()
{
   pnodoCOM aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   primero=NULL;
}

int ListaCOM::largoLista(){
    int cont=0;

    pnodoCOM aux;
    aux = primero;
    if(ArbolVacio()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}

void ListaCOM::InsertarFinal(string v)
{
   if (ArbolVacio())
   {
   
     primero = new nodoCOM(v);
       
   }
   else
     { pnodoCOM aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoCOM(v);
        aux->siguiente->anterior=aux;       
      }    
}
   
void ListaCOM::BorrarFinal()
{
    if (ArbolVacio()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL)//solo un nodoCOM
		 {
        	pnodoCOM temp=primero;
            primero= NULL;
            delete temp;
            } 
			else 
			{

                pnodoCOM aux = primero;
                while (aux->siguiente->siguiente != NULL) 
                {
                    aux = aux->siguiente;
                }
                
              pnodoCOM temp = aux->siguiente;
              aux->siguiente= NULL;
                      
                delete temp;
            }
        }
}

void ListaCOM::BorrarInicio()
{
    if (ArbolVacio()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
            pnodoCOM temp=primero;
            primero= NULL;
            delete temp;
            } 
			else
			{

                pnodoCOM aux = primero;
                primero=primero->siguiente;   
				primero->anterior=NULL;            
                delete aux;
            }
        }
}

void ListaCOM::MostrarCompra()
{
   nodoCOM *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

bool ListaCOM::Existe(int codigo) {
    if (ArbolVacio()) {
        cout << "La lista est? vac?a." << endl;
        return false;
    }

    std::stringstream ss1;
    ss1 << codigo;
    string num1 = ss1.str();
    string codigosBuscados = num1 + ";";
    pnodoCOM aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= largoLista()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        return false;
    }
}

void ListaCOM::facturar(listComFact & compraFactura) {
	nodoCOM *aux;
    cout << "facturacion de compra" << endl;
    cout << "Lista de clientes: " << endl;
    MostrarCompra();
    cout << "seleccione el cliente a facturar" << endl;
    int cliente;
    cin >> cliente;
    
    if (Existe(cliente)) {
        cout << "cliente encontrado" << endl;
		std::pair<int, std::string> resultado = CarritoCliente(cliente); 
		
		int precioTotal = resultado.first;
		std::string info = resultado.second;
		
		std::stringstream ss31;
        ss31 << precioTotal;
        
        std::stringstream ss32;
        ss32 << cliente;
        
        string nuevoValor = ss31.str()+";" + ss32.str(); 
		compraFactura.InsertarInicio(nuevoValor);
		
        std::stringstream ss;
		ss << contadorFacturas;
        string nombre = "Factura"+ss.str()+".txt";
        ofstream archivo(nombre.c_str(),ios::app);

        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }
		archivo<<""<<endl;

		std::string facturaID = "factura numero: " + ss.str();
        archivo <<facturaID<< endl;
        
        
        std::stringstream ss2;
		ss2 << cliente;
		std::string numCliente = "cliente: " + ss2.str();
        archivo <<numCliente<<endl;
        
        string infoCompra = "Compra: " + info;
        archivo<<infoCompra<<endl;
        
        std::stringstream ss3;
        ss3 << precioTotal;
        string precioCompra = "monto a pagar: " + ss3.str();
        archivo<<precioCompra<<endl;
        

        // Incrementar el contador de facturas para el pr?ximo archivo
        contadorFacturas++;

        return;
    }
    else {
        cout << "cliente NO encontrado" << endl;
        return;
    }
}


std::pair<int, std::string> ListaCOM::CarritoCliente(int codigo) {
    if (ArbolVacio()) {
        cout << "La lista est? vac?a." << endl;
        return std::make_pair(0, ""); // Devuelve un par (0, "") en caso de lista vac?a
    }
    std::string info;
    std::stringstream ss1;
    ss1 << codigo;
    std::string num1 = ss1.str();
    std::string codigosBuscados = num1 + ";";
    pnodoCOM aux = primero;
    bool encontrado = false;
    int i = 0;
    std::string compras;

    int precioTotal = 0; // Inicializa el precio total a 0

    while (i <= largoLista()) {
        if (aux->valor.find(codigosBuscados) != std::string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            size_t posicionPenultimoPuntoComa = aux->valor.find_last_of(';', posicionUltimoPuntoComa - 1);
            size_t posicionAntepenultimoPuntoComa = aux->valor.find_last_of(';', posicionPenultimoPuntoComa - 2);

            if (posicionUltimoPuntoComa != std::string::npos && posicionPenultimoPuntoComa != std::string::npos && posicionAntepenultimoPuntoComa != std::string::npos) {
                std::string cantidadStr = aux->valor.substr(posicionAntepenultimoPuntoComa + 1, posicionPenultimoPuntoComa - posicionAntepenultimoPuntoComa - 1);
                std::string precioStr = aux->valor.substr(posicionPenultimoPuntoComa + 1, posicionUltimoPuntoComa - posicionPenultimoPuntoComa - 1);
                std::string decisionStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
                int intCantidad = 0, intPrecio = 0, intDecision = 0, DescuentoCant = 0;

                if (!cantidadStr.empty()) {
                    int potencia = 1;
                    for (int j = cantidadStr.length() - 1; j >= 0; j--) {
                        intCantidad += (cantidadStr[j] - '0') * potencia;
                        potencia *= 10;
                    }
                }

                if (!precioStr.empty()) {
                    int potencia = 1;
                    for (int j = precioStr.length() - 1; j >= 0; j--) {
                        intPrecio += (precioStr[j] - '0') * potencia;
                        potencia *= 10;
                    }
                }

                if (!decisionStr.empty()) {
                    int potencia = 1;
                    for (int j = decisionStr.length() - 1; j >= 0; j--) {
                        intDecision += (decisionStr[j] - '0') * potencia;
                        potencia *= 10;
                    }
                }

                std::cout << "decision: " << intDecision << std::endl;
                switch (intDecision) {
                case 1:
                    info += "|| Cantidad: " + cantidadStr + ", Precio: " + precioStr + " descuento 0%";
                    std::cout << info << std::endl;
                    precioTotal += intCantidad * intPrecio;
                    std::cout << "Precio total: " << precioTotal << std::endl;
                    break;
                case 2:
                    info += "||Cantidad: " + cantidadStr + ", Precio: " + precioStr + " descuento 3%";
                    std::cout << info << std::endl;
                    DescuentoCant = (3 * (intCantidad * intPrecio)) / 100;
                    precioTotal += (intCantidad * intPrecio) - DescuentoCant;
                    std::cout << "Precio total: " << precioTotal << std::endl;
                    break;
                default:
                    std::cout << "error" << std::endl;
                    break;
                }

                compras += aux->valor + "\n";
                BorrarInicio();
            }
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        return std::make_pair(0, ""); // Devuelve un par (0, "") si no se encontraron elementos con el c?digo especificado.
    }

    std::stringstream ss2;
    ss2 << precioTotal;
    std::string precioTotalStr = ss2.str();
    return std::make_pair(precioTotal, info); // Devuelve un par con precioTotal e info
}





// 7 cantidad y 8 precio 
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
            Cola[i] = ""; // Inicializamos el arreglo de strings con cadenas vac?as
        }
    }

    bool ColaVacia() { return fondo < frente; }
    void insertar(string v);
    void eliminar();
    void imprimir();
    void Agregar(ArbolProducto & arbolProducto, ArbolClientes &  arbolClientes, ListaCOM & ListaCompras);
    void ColaCO(ArbolProducto & arbolProducto, ArbolClientes &  arbolClientes,ListaCOM & ListaCompras);
    bool VerificarNumeroEnCola(string &num1);
    void MostrarCodigoEnPosicion(int posicion);
    void BorrarPorNumeroIdentificacion(ListaCOM & ListaCompras);
    void ModificarPorNumeroIdentificacion(ArbolProducto &arbolProducto, ArbolClientes &arbolClientes);
    string ObtenerValorEntrada();
    void MostrarComprasPorNumeroCliente(ListaCOM &ListaCompras);
   
};

    
void cola::MostrarComprasPorNumeroCliente(ListaCOM &ListaCompras) {
    int numIdentificacion;
    cout << "Ingrese el n?mero de identificacion que desea mostrar: ";
    cin >> numIdentificacion;
    std::stringstream ss10;
    ss10 << numIdentificacion;
    string num10 = ss10.str();

    bool encontrado = false;

    for (int i = frente; i <= fondo; i++) {
        string elemento = Cola[i];
        // Busca el primer conjunto de n?meros en el elemento de la cola
        size_t pos = elemento.find(';');
        if (pos != string::npos) {
            string primerNumero = elemento.substr(0, pos);
            if (primerNumero == num10) {
                encontrado = true;
                cout << "Elemento con n?mero de identificaci?n " << numIdentificacion << " se muestra" << endl;
                ListaCompras.MostrarComprasPorInicio(num10);
            }
        }
    }

    if (!encontrado) {
        cout << "Cliente con n?mero de identificaci?n " << numIdentificacion << " no encontrado en la cola de compras." << endl;
    }
}



string cola::ObtenerValorEntrada()
{
    if (!ColaVacia())
    {
        return Cola[frente];
    }
    else
    {
        cout << "La cola est? vac?a." << endl;
        return "";
    }
}

void cola::ModificarPorNumeroIdentificacion(ArbolProducto &arbolProducto, ArbolClientes &arbolClientes) {
    int numIdentificacion;
    cout << "Ingrese el n?mero de identificacion que desea modificar: ";
    cin >> numIdentificacion;
    
    std::stringstream ss10;
    ss10 << numIdentificacion;
    string num10 = ss10.str();

    for (int i = frente; i <= fondo; i++) {
        string elemento = Cola[i];
        // Busca el primer conjunto de n?meros en el elemento de la cola
        size_t pos = elemento.find(';');
        if (pos != string::npos) {
            string primerNumero = elemento.substr(0, pos);
            if (primerNumero == num10) {
                // El cliente con el n?mero de identificaci?n se encontr? en la cola
                cout << "Cliente con n?mero de identificacion " << numIdentificacion << " encontrado" << endl;

                // Mostrar los ArbolProductos actuales del cliente
                cout << "ArbolProductos actuales del cliente: " << endl;
                MostrarCodigoEnPosicion(i + 1);
                arbolProducto.MostrarPRO();

                // Solicitar nuevos ArbolProductos
                int codigo1, codigo2, codigo3, codigo4, codigo5;
                cout << "Ingrese el primer codigo: " << endl;
                cin >> codigo1;

                cout << "Ingrese el segundo codigo: " << endl;
                cin >> codigo2;

                cout << "Ingrese el tercer codigo: " << endl;
                cin >> codigo3;

                cout << "Ingrese el cuarto codigo: " << endl;
                cin >> codigo4;

                cout << "Ingrese el quinto codigo: " << endl;
                cin >> codigo5;

                // Convertir los nuevos c?digos en cadenas
                std::stringstream ss1, ss2, ss3, ss4, ss5;
                ss1 << codigo1;
                ss2 << codigo2;
                ss3 << codigo3;
                ss4 << codigo4;
                ss5 << codigo5;
                string num1 = ss1.str();
                string num2 = ss2.str();
                string num3 = ss3.str();
                string num4 = ss4.str();
                string num5 = ss5.str();

                // Crear la nueva cadena de ArbolProductos
                string nuevosArbolProductos = num1 + ";" + num2 + ";" + num3 + ";" + num4 + ";" + num5;

                // Actualizar la cola con la nueva cadena de ArbolProductos
                Cola[i] = num10 + ";" + nuevosArbolProductos;

                cout << "ArbolProductos modificados con ?xito." << endl;
                return;
            }
        }
    }

    cout << "N?mero de identificaci?n no encontrado en la cola." << endl;
}


void cola::BorrarPorNumeroIdentificacion(ListaCOM & ListaCompras)
{
    int numIdentificacion;
    cout << "Ingrese el n?mero de identificacion que desea borrar: ";
    cin >> numIdentificacion;
    std::stringstream ss10;
	ss10 << numIdentificacion;
	string num10 = ss10.str();
    

    for (int i = frente; i <= fondo; i++)
    {
        string elemento = Cola[i];
        // Busca el primer conjunto de n?meros en el elemento de la cola
        size_t pos = elemento.find(';');
        if (pos != string::npos)
        {
            string primerNumero = elemento.substr(0, pos);
            if (primerNumero == num10)
            {
                // Borra el elemento completo de la cola
                for (int j = i; j < fondo; j++)
                {
                    Cola[j] = Cola[j + 1];
                }
                Cola[fondo] = "";
                fondo--;
                cout << "Elemento con n?mero de identificacion " << numIdentificacion << " borrado" << endl;
                ListaCompras.BorrarComprasPorInicio(num10);
                i--; // Ajusta el ?ndice para revisar el siguiente elemento
            }
        }
    }
}

void cola::MostrarCodigoEnPosicion(int posicion)
{
    if (posicion >= 1 && posicion <= 5)
    {
        if (Cola[posicion - 1] != "")
        {
            cout << "Posicion " << posicion << ": " << Cola[posicion - 1] << endl;
        }
        else
        {
            cout << "Posicion " << posicion << " est? vacia." << endl;
        }
    }
    else
    {
        cout << "Posicion no v?lida. Debe ser un numero entre 1 y 5." << endl;
    }
}

bool cola::VerificarNumeroEnCola(string &num1) {
    int j = 0; // Valor para poder imprimir
    for (int i = frente; i <= fondo; i++) {
        string elemento = Cola[i];
        // Busca el primer conjunto de n?meros en el elemento de la cola
        size_t pos = elemento.find(';');
        if (pos != string::npos) {
            string primerNumero = elemento.substr(0, pos);
            if (primerNumero == num1) {
                MostrarCodigoEnPosicion(i + 1);
                return true;
            }
        }
        j++;
    }

    cout << "N?mero no encontrado en la cola." << endl;

    return false;
}

void cola::Agregar(ArbolProducto &arbolProducto, ArbolClientes &arbolClientes, ListaCOM &ListaCompras) {
    if (fondo < 5 - 1) {
        cout << "Opciones disponibles de cliente:" << endl;
        arbolClientes.MostrarCl();
        int codigo2;
        cout << "Digite el n?mero de c?dula del cliente: ";
        cin >> codigo2;
		std::stringstream ss1;
		ss1 << codigo2;
		
		string num1 = ss1.str();
        

        if (arbolClientes.ExisteCl(num1)) {
            cout << "Cliente encontrado de manera exitosa" << endl;
            std::stringstream ss10;
            ss10 << codigo2;
            string num10 = ss10.str();

            if (VerificarNumeroEnCola(num10)) {
                // El cliente ya existe en la cola, no es necesario insertarlo nuevamente.
                ListaCompras.AgregarCompra(arbolProducto, num10, arbolClientes);
                ListaCompras.AgregarCompra(arbolProducto, num10, arbolClientes);
            } else {
                // El cliente no est? en la cola, lo insertamos y luego agregamos la compra.
                string entrada = num10 + ";";
                int posicion = fondo + 1;  
                insertar(entrada);  
                cout << "Se procede a agregar el ArbolProducto" << endl;
                ListaCompras.AgregarCompra(arbolProducto, num10, arbolClientes);
            }

        } else {
            cout << "Cliente no encontrado" << endl;
            ColaCO(arbolProducto, arbolClientes, ListaCompras);
        }
    } else {
        cout << "La cola est? llena" << endl;
        ColaCO(arbolProducto, arbolClientes, ListaCompras);
    }
    ColaCO(arbolProducto, arbolClientes, ListaCompras);
}


void cola::ColaCO(ArbolProducto & arbolProducto, ArbolClientes &  arbolClientes,ListaCOM & ListaCompras ){

	bool ejecucion = true;
	cout<<"bienvenido a Compras"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar compras digite 1: "<<endl;
		cout<<"ver compras digite 2: "<<endl;
		cout<<"agregar una compra digite 3:"<<endl;
		cout<<"borrar una compra digite 4: "<<endl;
		cout<<"modificar una compra digite 5"<<endl;
		cout<<"para salir digite 6: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar una compra"<<endl;
				cout<<"compras disponibles: "<<endl;
				imprimir();
				MostrarComprasPorNumeroCliente(ListaCompras);
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos las compras"<<endl;
				cout<<"ArbolClientes en cola"<<endl;
				imprimir();
				cout<<"compras realizadas"<<endl;
				ListaCompras.MostrarCompra();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar una compra"<<endl;
				Agregar(arbolProducto,arbolClientes,ListaCompras);
				imprimir();
				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar una compra"<<endl;
				cout<<"ArbolClientes disponibles: "<<endl;
				cout<<"digite 1 borrar todas las compras de un cliente"<<endl;
				cout<<"digite 2 borrar una compra en especifico"<<endl;
				int ArbolMenuborrar;
				cin >> ArbolMenuborrar;
				switch(ArbolMenuborrar){
					case 1:
						imprimir();
						BorrarPorNumeroIdentificacion(ListaCompras);
						break;
					case 2:
						ListaCompras.MostrarCompra();
						ListaCompras.BorrarPaisPorSeisCodigos();

						break;
					default:
						cout<<"error a la hora de digitar"<<endl;
						ColaCO(arbolProducto, arbolClientes, ListaCompras);
				}
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, modificar una compra"<<endl;
				cout<<"nombres disponibles"<<endl;
				imprimir();
				ModificarPorNumeroIdentificacion(arbolProducto,arbolClientes);
				break;
			case 6: 
				cout<<""<<endl;
				cout<<"opcion 6, salir a ArbolMenu principal"<<endl;
				ejecucion = false;			
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


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
   	ArbolPais arbolPais;
   	arbolPais.CargarDesdeArchivo();
   	string preOrdenPais = FuncionFer(arbolPais.ObtenerContenidoComoString());
   	cout<<preOrdenPais<<endl;
   	
   	
   	
   	ArbolCiudad arbolCiudad;
   	arbolCiudad.CargarDesdeArchivoCIU();
   	string preOrdenCiudad = arbolCiudad.GuardarArbolCiudades();
   	cout<<preOrdenCiudad<<endl;
   	
   	
   	ArbolRestaurante arbolRestaurante;
   	arbolRestaurante.CargarDesdeArchivoRE();
   	
   	
   	ArbolMenu arbolMenu;
   	arbolMenu.CargarDesdeArchivoME();
   	
   	
   	ArbolProducto arbolProducto;
   	arbolProducto.CargarDesdeArchivoPRO();
   	
   	
   	ArbolClientes arbolClientes;
   	arbolClientes.CargarDesdeArchivoCl();
   	
	/*cola ColaCompras;
	
	
    ListaCOM ListaCompras;
    ListaCompras.MostrarCompra();

   	listComFact compraFactura;
   	
	bool ejecucion = true;
	
	while(ejecucion)
	{
		int ArbolMenuPrincipal;
		cout<<""<<endl;
		cout<<"Bienvenido"<<endl;
		cout<<"Pais, digite 1"<<endl;
		cout<<"Ciudad, digite 2"<<endl;
		cout<<"Restaurantes, digite 3"<<endl;
		cout<<"Menu, digite 4"<<endl;
		cout<<"Productos, digite 5"<<endl;
		cout<<"Clientes, digite 6"<<endl;
		cout<<"compras, digite 7"<<endl;
		cout<<"generar factura digite 8"<<endl;
		cout<<"salir, digite 9"<<endl;
		
		cin >> ArbolMenuPrincipal;
		
		switch(ArbolMenuPrincipal)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1 paises "<<endl;
				arbolPais.Paises();
				break;
				
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2 Ciudades"<<endl;
				arbolCiudad.ArbolCiudadsCIU(arbolPais);
				break;
				
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3 Restaurantes"<<endl;
				arbolRestaurante.ArbolRestaurantesRE(arbolCiudad);
				break;
				
			case 4:
				cout<<""<<endl;
				cout<<"opcion 4 Menu"<<endl;
				arbolMenu.ArbolMenusME(arbolRestaurante);
				break;
					
			case 5:
				cout<<""<<endl;
				cout<<"opcion 5 Productos"<<endl;
				arbolProducto.ArbolProductosPRO(arbolMenu);
				break;
				
			case 6:
				cout<<""<<endl;
				cout<<"opcion 6 Clientes"<<endl;
				arbolClientes.ArbolClientesCl();
				break;
			case 7:
				cout<<""<<endl;
				cout<<"opcion 7 compras"<<endl;
				ColaCompras.ColaCO(arbolProducto, arbolClientes, ListaCompras);
				break;
			case 8: 
				cout<<""<<endl;
				cout<<"opcion 8 generar factura"<<endl;
				ListaCompras.facturar(compraFactura);
				break;
			case 9: 
				cout<<""<<endl;
				cout<<"opcion 9 salir"<<endl;
				ejecucion = false;
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;
		}		
	}
	
	cout<<""<<endl;
	cout<<"REPORTES"<<endl;
	
	ofstream archivo("reportes.txt");

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    
    
	string reporte1 = "paises preOrden";
	archivo<<reporte1<<endl;
	
	string reporte2 = "ciudades preOrden";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte2<<endl;

	string reporte3 = "restaurantes preOrden";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte3<<endl;
	
	string reporte4 = "cliente preOrden";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte4<<endl;
	
	string reporte5 = "compras de cliente";;
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte5<<endl;
	string ClientesCompras = arbolClientes.muestraCompradores();
	archivo<<ClientesCompras<<endl;

	
	
	string reporte6 = "restaurante mas buscado";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte6<<endl;
	string RepRestMas = arbolRestaurante.EncontrarValorMayorPedido();
    archivo<<RepRestMas<<endl;
    archivo<<""<<endl;
	
	string reporte111 = "restaurante preOrden";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte111<<endl;
	
	string reporte112 = "producto preOrden";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte112<<endl;
	
	string reporte7 = "menu mas buscado";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte7<<endl;
    archivo<<"Reporte de menu mas buscado"<<endl;
    string RepMeMas = arbolMenu.EncontrarValorMayorPedido();
    archivo<<RepMeMas<<endl;
    archivo<<""<<endl;
	

	string reporte9 = "producto mas comprado";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte9<<endl;
    archivo<<"Reporte de producto mas buscado"<<endl;
    string RepProMas = arbolProducto.EncontrarValorMayorPedido();
    archivo<<RepProMas<<endl;
	
	string reporte10 = "factura mas grande";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte10<<endl;
	string BigFact = compraFactura.ObtenerMayorValor1();
	archivo<<BigFact<<endl;
	
	string reporte11 = "factura mas pequena";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte11<<endl;
	string littleFact = compraFactura.ObtenerMenorValor1(); 
	archivo<<littleFact<<endl;
	
	string reporte12 = "precio de un producto";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte12<<endl;
	cout<<""<<endl;
	cout<<""<<endl;
	cout<<""<<endl;
	cout<<""<<endl;
	cout<<"cantidad de un producto, digite el producto"<<endl;
	cout<<"productos disponibles"<<endl;
	arbolProducto.MostrarPRO();
	int codigo1, codigo2, codigo3,codigo4,codigo5;
    cout << "Ingrese el primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;

    cout << "Ingrese el tercer codigo: " << endl;
    cin >> codigo3;
    
    cout << "Ingrese el cuarto codigo: " << endl;
    cin >> codigo4;
    
    cout << "Ingrese el quinto codigo: " << endl;
    cin >> codigo5;

    std::stringstream ss1, ss2, ss3,ss4,ss5;
    ss1 << codigo1;
    ss2 << codigo2;
    ss3 << codigo3;
    ss4 << codigo4;
    ss5 << codigo5;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();
    string num4 = ss4.str();
    string num5 = ss5.str();

    string codigosBuscados2 = num1 + ";" + num2 + ";" + num3 + ";" + num4 + ";" + num5;
    cout<<"producto a buscar: "<<codigosBuscados2;
    string cantidad2 = arbolProducto.getPrecio(codigosBuscados2);
    cout<<"cantidad: "<<cantidad2<<endl;
    string reporteCantidad2 = "producto: " + codigosBuscados2 + " cantidad: " + cantidad2;
    archivo<<reporteCantidad2<<endl;
	
	
	string reporte13 = "descuento al pagar con tarjeta = 3%";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte13<<endl;
	
	string reporte14 = "cantidad de un producto";
	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo<<reporte14<<endl;
	cout<<""<<endl;
	cout<<""<<endl;
	cout<<""<<endl;
	cout<<""<<endl;
	cout<<"cantidad de un producto, digite el producto"<<endl;
	cout<<"productos disponibles"<<endl;
	arbolProducto.MostrarPRO();
	int codigo11, codigo21, codigo31,codigo41,codigo51;
    cout << "Ingrese el primer codigo: " << endl;
    cin >> codigo11;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo21;

    cout << "Ingrese el tercer codigo: " << endl;
    cin >> codigo31;
    
    cout << "Ingrese el cuarto codigo: " << endl;
    cin >> codigo41;
    
    cout << "Ingrese el quinto codigo: " << endl;
    cin >> codigo51;

    std::stringstream ss11, ss21, ss31,ss41,ss51;
    ss11 << codigo11;
    ss21 << codigo21;
    ss31 << codigo31;
    ss41 << codigo41;
    ss51 << codigo51;

    string num11 = ss11.str();
    string num21 = ss21.str();
    string num31 = ss31.str();
    string num41 = ss41.str();
    string num51 = ss51.str();

    string codigosBuscados = num11 + ";" + num21 + ";" + num31 + ";" + num41 + ";" + num51;
    cout<<"producto a buscar: "<<codigosBuscados;
    string cantidad = arbolProducto.muestraCantidad(codigosBuscados);
    cout<<"cantidad: "<<cantidad<<endl;
    string reporteCantidad = "producto: " + codigosBuscados + " cantidad: " + cantidad;
    archivo<<reporteCantidad<<endl;*/
	
	
   cin.get();
   return 0;
}
