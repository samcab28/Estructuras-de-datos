#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <set>
#include <string> 
#include <cstdlib> 

using namespace std;

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

    void InsertarFinal(string v);
    bool ListaVacia() { return primero == NULL; }
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
            int codigoenArbola;
            istringstream(aux->valor.substr(0, pos)) >> codigoenArbola;

            if (codigoenArbola == code) {
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
    if (ListaVacia()) {
        cout << "El arbol esta vacio." << endl;
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
            int codigoenArbola;
            istringstream(aux->valor.substr(0, pos)) >> codigoenArbola;

            if (codigoenArbola == codigo) {
                encontrado = true;
                string nombre = aux->valor.substr(pos + 1);
                cout << "Codigo: " << codigoenArbola << endl;
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

void ArbolPais::AgregarPais()
{
    cout << "Ingrese el codigo del pais (parte entera): ";
    int codigo;
    cin >> codigo;
    cin.ignore(); 

    cout << "Ingrese el nombre del pais: ";
    string nombre;
    getline(cin, nombre);

    bool codigoExistente = false;
    pnodo aux = primero;
    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoenArbola;
            istringstream(aux->valor.substr(0, pos)) >> codigoenArbola;

            if (codigoenArbola == codigo) {
                codigoExistente = true;
                cout << "Error: Ya existe un pais con el codigo " << codigo << "." << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!codigoExistente) {
        ostringstream ss;
        ss << codigo;
        string codigoStr = ss.str();

        string pais = codigoStr + ";" + nombre;
        InsertarFinal(pais);
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
                    string codigoenArbola = aux->valor.substr(0, posAux);
                    
                    if (codigoenArbola == codigo) {
                        existe = true;
                        cout << "Pais con codigo " << codigo << " ya existe en el arbol." << endl;
                        break;
                    }
                }
                aux = aux->siguiente;
            }
            
            if (!existe) {
                InsertarFinal(codigo + ";" + nombre);
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
				cout<<"opcion 4 modoficar nombre:"<<endl;
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
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}

void ArbolPais::InsertarFinal(string v)
{
   if (ListaVacia())
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
    if (ListaVacia()) {
        cout << "El arbol esta vacia." << endl;
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

    void InsertarInicio(string v);
    void InsertarFinal(string v);
    void InsertarPos(string v, int pos);
    bool ListaVacia() { return primero == NULL; }
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
private:
    pnodoCIU primero;
};

string ArbolCiudad::MostrarArbolCiudadesPorPais() {
	cout<<"digite el codigo de pais a buscar"<<endl;
	string codigoPais;
	cin >> codigoPais;
	string memoria;
    if (ListaVacia()) {
        cout << "El arbol de ArbolCiudades esta vacio." << endl;
        return "arbol vacia";
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
    if (ListaVacia()) {
        cout << "El arbol esta vacio." << endl;
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
        cout << "No se encontraron los codigos en la lista." << endl;
    }

}

void ArbolCiudad::AgregarCIU(ArbolPais & arbolPais){
	int NumPais;
	cout<<"agregar ArbolCiudades"<<endl;
	cout<<"A continuacion se muestran los paises disponibles: "<<endl;		
	arbolPais.Mostrar();
	cout<<"para agregar ArbolCiudades, se debe de verificar la existencia del pais, digite el numero de pais"<<endl;
	cin>>NumPais;
	if(arbolPais.Existe(NumPais)){
		cout<<"el pais si existe, se procede a agregar"<<endl;
		int codigoArbolCiudad;
		cout<<"digite el codigo de la ArbolCiudad"<<endl;
		cin >> codigoArbolCiudad;
		
	    std::stringstream ss1,ss2;
	    ss1 << NumPais;
	    ss2 << codigoArbolCiudad;
	    string num1 = ss1.str();
	    string num2 = ss2.str();
	    
		string NombreNuevo;
		cout<<"digite el nombre de la ArbolCiudad"<<endl;
		cin >> NombreNuevo;
	
		string NuevoValor = num1 + ";" + num2 + ";" + NombreNuevo;
		InsertarFinal(NuevoValor);
	
	}else{
		cout<<"el pais no existe, No se agrega"<<endl;
		ArbolCiudadsCIU(arbolPais);
	}
}


void ArbolCiudad::ArbolCiudadsCIU(ArbolPais & arbolPais)
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolCiudades"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar ArbolCiudades digite 1: "<<endl;
		cout<<"ver ArbolCiudades digite 2: "<<endl;
		cout<<"agregar un ArbolCiudad digite 3:"<<endl;
		cout<<"modificar una ArbolCiudad digite 4:"<<endl;
		cout<<"salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un ArbolCiudad"<<endl;
				cout<<"ArbolCiudads disponibles: "<<endl;
				MostrarCIU();
				ComprobacionCIU();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los ArbolCiudads"<<endl;
				cout<<"se mostraran todos los ArbolCiudads a continuacion: "<<endl;
				MostrarCIU();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un ArbolCiudad"<<endl;
				AgregarCIU(arbolPais);

				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, modificar nombre ArbolCiudad"<<endl;
				cout<<"ArbolCiudades disponibles"<<endl;
				MostrarCIU();
				ModificarNombreCIU();	
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


void ArbolCiudad::ComprobacionCIU() {
    if (ListaVacia()) {
        cout << "El arbol esta vacio." << endl;
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

            cout << "Codigos encontrados en la lista: " << codigosBuscados << endl;
            cout << "Nombre asociado: " << nombre << endl;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos ." << endl;
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
                InsertarFinal(nuevo_valor);
            }
            else
            {
                cout << "Advertencia: NUMERO2 debe ser diferente a los otros NUMERO2 anteriores." << endl;
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
    if(ListaVacia())
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

void ArbolCiudad::InsertarFinal(string v)
{
   if (ListaVacia())
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
    if (ListaVacia()) {
        cout << "La arbol est? vac?a." << endl;
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

    void InsertarInicio(string v);
    void InsertarFinal(string v);
    void InsertarPos(string v, int pos);
    bool ListaVacia() { return primero == NULL; }
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
    if (ListaVacia()) {
        cout << "El arbol de ArbolRestaurantes esta vacio." << endl;
        return "arbol vacio";
    }

    pnodoRE aux = primero;
    int valorMayor = -1;  // Inicializamos con un valor menor al m?nimo posible
    pnodoRE nodoMayor = NULL;  // Nodo correspondiente al valor m?s alto

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
        cout << "Informacion del ArbolRestaurante: " << nodoMayor->valor << endl;
        return "Informacion del ArbolRestaurante: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n ArbolRestaurante  con consultas." << endl;
    }
}

string ArbolRestaurante::MostrarArbolRestaurantesPorArbolCiudad() {
    cout << "Digite el codigo de pais: ";
    string codigoPais;
    cin >> codigoPais;

    cout << "Digite el codigo de ArbolCiudad: ";
    string codigoArbolCiudad;
    cin >> codigoArbolCiudad;

    string codigosBuscados = codigoPais + ";" + codigoArbolCiudad;
    
    string memoria;
    if (ListaVacia()) {
        cout << "El arbol de ArbolRestaurantes esta vacio." << endl;
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
	cout<<"agregar ArbolCiudades"<<endl;
	cout<<"A continuacion muestran paises y ArbolCiudades disponibles: "<<endl;		
	arbolCiudad.MostrarCIU();
	cout<<"para agregar ArbolRestaurantes, se debe de verificar la existencia del pais y ArbolCiudad, agregar sus codigos"<<endl;
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
		cout<<"el pais y ArbolCiudad si existen, se procede a agregar"<<endl;
	    int codigo1a;
	    cout << "Ingrese el codigo del nuevo ArbolRestaurante3: " << endl;
	    cin >> codigo1a;

	    std::stringstream ss1a;
	    ss1a << codigo1a;

	    string num1a = ss1.str();
		    
		string NombreNuevo;
		cout<<"digite el nombre del ArbolRestaurante"<<endl;
		cin >> NombreNuevo;
	
		string NuevoValor = codigosBuscados + ";" + num1a + ";" + NombreNuevo;
		InsertarFinal(NuevoValor);
	
	}else{
		cout<<"el pais no existe, No se agrega"<<endl;
		ArbolRestaurantesRE(arbolCiudad);
	}
}

void ArbolRestaurante::ModificarNombreRE() {
    if (ListaVacia()) {
        cout << "El arbol esta vacio." << endl;
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
        cout << "No se encontraron los codigos en la lista." << endl;
    }

}

void ArbolRestaurante::ArbolRestaurantesRE(ArbolCiudad & arbolCiudad2)
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolRestaurantes"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar ArbolRestaurantes digite 1: "<<endl;
		cout<<"ver ArbolRestaurantes digite 2: "<<endl;
		cout<<"agregar un ArbolRestaurante digite 3:"<<endl;
		cout<<"modificar un ArbolRestaurante digite 4:"<<endl;
		cout<<"para salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un ArbolRestaurante"<<endl;
				cout<<"ArbolRestaurantes disponibles: "<<endl;
				MostrarRE();
				ComprobacionRE();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los ArbolRestaurantes"<<endl;
				cout<<"se mostraran todos los ArbolRestaurantes a continuacion: "<<endl;
				MostrarRE();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un ArbolRestaurante"<<endl;
				agregarRE(arbolCiudad2);
				break;			

			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, modificar nombre ArbolRestaurante"<<endl;
				cout<<"codigos disponibles"<<endl;
				MostrarRE();
				ModificarNombreRE();	
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





int ArbolRestaurante::stringAEnteroRE(const std::string &cadena) {
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
            std::cerr << "Error: La cadena contiene caracteres no numericos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolRestaurante::ComprobacionRE() {
    if (ListaVacia()) {
        cout << "Ek arbol esta vacio" << endl;
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

                cout << "Codigos encontrados en El Arbol: " << codigosBuscados << endl;
                cout << "Nuevo valor asociado: " << nuevoValor << endl;
            } else {
                cout << "No se encontro el ultimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los codigos." << endl;
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
                InsertarFinal(nuevo_valor);
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
    if(ListaVacia())
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
 
void ArbolRestaurante::InsertarFinal(string v)
{
   if (ListaVacia())
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
    if (ListaVacia()) {
        cout << "El arbol esta vacio." << endl;
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









	
int main()
{

   	ArbolPais arbolPais;
   	arbolPais.CargarDesdeArchivo();
   	
   	
   	ArbolCiudad arbolCiudad;
   	arbolCiudad.CargarDesdeArchivoCIU();
   	
   	
   	ArbolRestaurante arbolRestaurante;
   	arbolRestaurante.CargarDesdeArchivoRE();
   	
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
		cout<<"generar reporte digite 8"<<endl;
		cout<<"salir, digite 9"<<endl;
		
		cin >> ArbolMenuPrincipal;
		
		switch(ArbolMenuPrincipal)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1 Paises "<<endl;
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
				break;
					
			case 5:
				cout<<""<<endl;
				cout<<"opcion 5 Productos"<<endl;
				break;
				
			case 6:
				cout<<""<<endl;
				cout<<"opcion 6 Clientes"<<endl;
				break;
			case 7:
				cout<<""<<endl;
				cout<<"opcion 7 Compras"<<endl;
				break;
			case 8: 
				cout<<""<<endl;
				cout<<"opcion 8 generar reportes"<<endl;
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

   cin.get();
   return 0;
}
