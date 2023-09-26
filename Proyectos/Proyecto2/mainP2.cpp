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
    int largoLista();
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
    cin.ignore();  // Clear the newline character from the buffer
    getline(cin, newName);

    pnodo aux = primero;

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

void ArbolPais::ConsultarPaisPorCodigo() {
    if (ListaVacia()) {
        cout << "La lista esta vacia." << endl;
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

void ArbolPais::AgregarPais()
{
    cout << "Ingrese el codigo del pais (parte entera): ";
    int codigo;
    cin >> codigo;
    cin.ignore();  // Limpia el buffer del salto de linea

    cout << "Ingrese el nombre del pais: ";
    string nombre;
    getline(cin, nombre);

    // Verificar si el codigo ya existe en la lista
    bool codigoExistente = false;
    pnodo aux = primero;
    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnLista;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnLista;

            if (codigoEnLista == codigo) {
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
                    string codigoEnLista = aux->valor.substr(0, posAux);
                    
                    if (codigoEnLista == codigo) {
                        existe = true;
                        cout << "Pais con codigo " << codigo << " ya existe en la lista." << endl;
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
				cout<<"opcion 5 modoficar nombre"<<endl;
				cout<<"paises disponibles: "<<endl;
				Mostrar();
				ModificarNombre();
				break;		
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 6, salir a ArbolMenu principal"<<endl;
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

int ArbolPais::largoLista(){
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
        cout << "La lista est? vac?a." << endl;
        return false;
    }

    std::stringstream ss1;
    ss1 << codigo;
    string num1 = ss1.str();
    string codigosBuscados = num1 + ";";
    pnodo aux = primero;
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
    void Borrar(string v);
    void MostrarCIU();
    void BorrarFinal();
    void BorrarInicio();
    void BorrarPosicion(int pos);
    int largoLista();
    void CargarDesdeArchivoCIU();
    void ArbolCiudadsCIU(ArbolPais & ListaArbolPais);
    void ComprobacionCIU();
    void BorrarPorCodigosCIU();
    void AgregarCIU(ArbolPais & ListaArbolPais);
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
        cout << "La lista de ArbolCiudades esta vacia." << endl;
        return "lista vacia";
    }

    pnodoCIU aux = primero;
    int i = 0;

    while (i <= largoLista()) {
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
        cout << "La lista est? vac?a." << endl;
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

    while (i <= largoLista()) {
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

void ArbolCiudad::AgregarCIU(ArbolPais & ListaArbolPais){
	int NumPais;
	cout<<"agregar ArbolCiudades"<<endl;
	cout<<"A continuacion se muestran los paises disponibles: "<<endl;		
	ListaArbolPais.Mostrar();
	cout<<"para agregar ArbolCiudades, se debe de verificar la existencia del pais, digite el numero de pais"<<endl;
	cin>>NumPais;
	if(ListaArbolPais.Existe(NumPais)){
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
		ArbolCiudadsCIU(ListaArbolPais);
	}
}


void ArbolCiudad::ArbolCiudadsCIU(ArbolPais & ListaArbolPais)
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolCiudades"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar ArbolCiudades digite 1: "<<endl;
		cout<<"ver ArbolCiudades digite 2: "<<endl;
		cout<<"agregar un ArbolCiudad digite 3:"<<endl;
		cout<<"borrar un ArbolCiudad digite 4: "<<endl;
		cout<<"modificar una ArbolCiudad digite 5"<<endl;
		cout<<"salir digite 6: "<<endl;
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
				AgregarCIU(ListaArbolPais);

				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un ArbolCiudad"<<endl;
				cout<<"ArbolCiudads disponibles: "<<endl;
				MostrarCIU();
				BorrarPorCodigosCIU();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, modificar nombre ArbolCiudad"<<endl;
				cout<<"ArbolCiudades disponibles"<<endl;
				MostrarCIU();
				ModificarNombreCIU();	
				break;
			case 6:
				cout<<""<<endl;
				cout<<"opcion 6, salir a ArbolMenu principal"<<endl;
				ejecucion = false;	
				break;				
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}

void ArbolCiudad::BorrarPorCodigosCIU() {
    if (ListaVacia()) {
        cout << "La lista esta vac?a." << endl;
        return;
    }
    
    int codigo1, codigo2;
    cout << "Ingrese el primer codigo: " << endl;
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

    while (i <= largoLista()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            if (aux == primero) {
                BorrarInicio();
            } else if (aux->siguiente == primero) {
                BorrarFinal();
            } else {
                pnodoCIU temp = aux;
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                aux = aux->siguiente;
                delete temp;
            }

            cout << "nodoCIU con los codigos " << codigosBuscados << " borrado exitosamente." << endl;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        cout << "No se encontraron los codigos en la lista." << endl;
    }
}

void ArbolCiudad::ComprobacionCIU() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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

    while (i <= largoLista()) {
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
        cout << "No se encontraron los codigos en la lista." << endl;
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
                        
int ArbolCiudad::largoLista() 
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
 
void ArbolCiudad::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoCIU temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoCIU aux = primero; //1
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoCIU temp = aux->siguiente;//2
         aux->siguiente= primero;//3
         primero->anterior=aux;//4
         delete temp;//5
      }
    }
}

void ArbolCiudad::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoCIU temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoCIU aux = primero->anterior;//1
        pnodoCIU temp= primero;//2
        aux->siguiente=primero->siguiente;//3
        primero=primero->siguiente; //4
        primero->anterior=aux;//5
        delete temp;//6
      }
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
        cout << "La lista est? vac?a." << endl;
        return false;
    }
    
    pnodoCIU aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= largoLista()) {
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
    void Borrar(string v);
    void MostrarRE();
    void BorrarFinal();
    void BorrarInicio();
    void BorrarPosicion(int pos);
    int largoLista();
    void CargarDesdeArchivoRE();
    void ArbolRestaurantesRE(ArbolCiudad & ListaArbolCiudad);
    void ComprobacionRE();
    void BorrarPorCodigosRE();
    void ModificarNombreRE();
    void agregarRE(ArbolCiudad & ListaArbolCiudad);
    bool ExisteRE(string codigo);
    string MostrarArbolRestaurantesPorArbolCiudad();
    int stringAEnteroRE(const std::string &cadena);
    string EncontrarValorMayorPedido();
    
private:
    pnodoRE primero;
};

string ArbolRestaurante::EncontrarValorMayorPedido() {
    if (ListaVacia()) {
        cout << "La lista de ArbolRestaurantes est? vac?a." << endl;
        return "lista vacia";
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
        cout << "No se encontr? ning?n ArbolRestaurante con con consultas." << endl;
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
        cout << "La lista de ArbolRestaurantes esta vacia." << endl;
        return "lista vacia";
    }

    pnodoRE aux = primero;
    int i = 0;

    while (i <= largoLista()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
        	memoria += aux -> valor + "; // ";
            cout << aux->valor << endl;
        }
        aux = aux->siguiente;
        i++;
    }
    return memoria;
}

void ArbolRestaurante::agregarRE(ArbolCiudad & ListaArbolCiudad){
	cout<<"agregar ArbolCiudades"<<endl;
	cout<<"A continuacion muestran paises y ArbolCiudades disponibles: "<<endl;		
	ListaArbolCiudad.MostrarCIU();
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
    
    
	if(ListaArbolCiudad.ExisteCIU(codigosBuscados)){
		cout<<"el pais y ArbolCiudad si existes, se procede a agregar"<<endl;
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
		ArbolRestaurantesRE(ListaArbolCiudad);
	}
}

void ArbolRestaurante::ModificarNombreRE() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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

    while (i <= largoLista()) {
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

void ArbolRestaurante::ArbolRestaurantesRE(ArbolCiudad & listaArbolCiudad2)
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolRestaurantes"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar ArbolRestaurantes digite 1: "<<endl;
		cout<<"ver ArbolRestaurantes digite 2: "<<endl;
		cout<<"agregar un ArbolRestaurante digite 3:"<<endl;
		cout<<"borrar un ArbolRestaurante digite 4: "<<endl;
		cout<<"modificar un ArbolRestaurante digite 5:"<<endl;
		cout<<"para salir digite 6: "<<endl;
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
				agregarRE(listaArbolCiudad2);
				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un ArbolRestaurante"<<endl;
				cout<<"ArbolRestaurantes disponibles: "<<endl;
				MostrarRE();
				BorrarPorCodigosRE();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, modificar nombre ArbolRestaurante"<<endl;
				cout<<"codigos disponibles"<<endl;
				MostrarRE();
				ModificarNombreRE();	
				break;
			case 6:
				cout<<""<<endl;
				cout<<"opcion 6, salir a ArbolMenu principal"<<endl;
				ejecucion = false;	
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}

void ArbolRestaurante::BorrarPorCodigosRE() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
        return;
    }
    
    int codigo1, codigo2, codigo3;
    cout << "Ingrese el primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;

    cout << "Ingrese el tercer codigo: " << endl;
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

    while (i <= largoLista()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            if (aux == primero) {
                BorrarInicio();
            } else if (aux->siguiente == primero) {
                BorrarFinal();
            } else {
                pnodoRE temp = aux;
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                aux = aux->siguiente;
                delete temp;
            }

            cout << "nodoRE con los c?digos " << codigosBuscados << " borrado exitosamente." << endl;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
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
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolRestaurante::ComprobacionRE() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a" << endl;
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

    while (i <= largoLista()) {
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

                cout << "Codigos encontrados en la lista: " << codigosBuscados << endl;
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
        cout << "No se encontraron los c?digos en la lista." << endl;
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
                           
int ArbolRestaurante::largoLista() 
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

void ArbolRestaurante::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoRE temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoRE aux = primero; //1
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoRE temp = aux->siguiente;//2
         aux->siguiente= primero;//3
         primero->anterior=aux;//4
         delete temp;//5
      }
    }
}

void ArbolRestaurante::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoRE temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoRE aux = primero->anterior;//1
        pnodoRE temp= primero;//2
        aux->siguiente=primero->siguiente;//3
        primero=primero->siguiente; //4
        primero->anterior=aux;//5
        delete temp;//6
      }
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
        cout << "La lista est? vac?a." << endl;
        return false;
    }
    
    pnodoRE aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= largoLista()) {
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

    void InsertarInicio(string v);
    void InsertarFinal(string v);
    void InsertarPos(string v, int pos);
    bool ListaVacia() { return primero == NULL; }
    void Imprimir();
    void Borrar(string v);
    void MostrarME();
    void BorrarFinal();
    void BorrarInicio();
    void BorrarPosicion(int pos);
    int largoLista();
    void CargarDesdeArchivoME();
    void ArbolMenusME(ArbolRestaurante & ListaArbolRestaurante);
    void ComprobacionME();
    void BorrarPorCodigosME();
    void ModificarNombreME();
    void AgregarME(ArbolRestaurante & ListaArbolRestaurante);
    bool ExisteME(string codigo);
    int stringAEnteroME(const std::string &cadena);
    string EncontrarValorMayorPedido();
private:
    pnodoME primero;
};

string ArbolMenu::EncontrarValorMayorPedido() {
    if (ListaVacia()) {
        cout << "La lista de ArbolMenu esta vacia." << endl;
        return "lista vacia";
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
        return "Informacion del ArbolMenu: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n ArbolRestaurante con con consultas." << endl;
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

void ArbolMenu::AgregarME(ArbolRestaurante & ListaArbolRestaurante){
	cout<<"agregar ArbolCiudades"<<endl;
	cout<<"A continuacion muestran paises y ArbolCiudades disponibles: "<<endl;		
	ListaArbolRestaurante.MostrarRE();
	cout<<"para agregar ArbolRestaurantes, se debe de verificar la existencia del pais, ArbolCiudad y ArbolRestaurante, agregar sus codigos"<<endl;
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
    
    
	if(ListaArbolRestaurante.ExisteRE(codigosBuscados)){
		cout<<"el pais, ArbolCiudad y ArbolRestaurante existen, se procede a agregar"<<endl;
	    int codigo1a;
	    cout << "Ingrese el codigo del nuevo ArbolMenu: " << endl;
	    cin >> codigo1a;

	    std::stringstream ss1a;
	    ss1a << codigo1a;

	    string num1a = ss1.str();
		    
		string NombreNuevo;
		cout<<"digite el nombre del ArbolMenu"<<endl;
		cin >> NombreNuevo;
	
		string NuevoValor = codigosBuscados + ";" + num1a + ";" + NombreNuevo;
		InsertarFinal(NuevoValor);
	
	}else{
		cout<<"no existe, No se agrega"<<endl;
		ArbolMenusME(ListaArbolRestaurante);
	}
}

void ArbolMenu::ModificarNombreME() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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

    while (i <= largoLista()) {
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

void ArbolMenu::ArbolMenusME(ArbolRestaurante & ListaArbolRestaurante)
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolMenus"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar ArbolMenus digite 1: "<<endl;
		cout<<"ver ArbolMenus digite 2: "<<endl;
		cout<<"agregar un ArbolMenu digite 3:"<<endl;
		cout<<"borrar un ArbolMenu digite 4: "<<endl;
		cout<<"modificar un ArbolMenu digite 5"<<endl;
		cout<<"para salir digite 6: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un ArbolMenu"<<endl;
				cout<<"ArbolMenus disponibles: "<<endl;
				MostrarME();
				ComprobacionME();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los ArbolMenus"<<endl;
				cout<<"se mostraran todos los ArbolMenus a continuacion: "<<endl;
				MostrarME();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un ArbolMenu"<<endl;
				cout<<"se muestran paises, ArbolCiudades y ArbolRestaurantes disponibles"<<endl;
				MostrarME();
				AgregarME(ListaArbolRestaurante);
				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un ArbolMenu"<<endl;
				cout<<"ArbolMenus disponibles: "<<endl;
				MostrarME();
				BorrarPorCodigosME();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, modificar nombre"<<endl;
				cout<<"codigos disponibles"<<endl;
				MostrarME();
				ModificarNombreME();
				break;
			case 6: 
				cout<<""<<endl;
				cout<<"opcion 6, salir a ArbolMenu principal"<<endl;
				ejecucion = false;	
				break;		
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


void ArbolMenu::BorrarPorCodigosME() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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
    int i = 0;

    while (i <= largoLista()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            if (aux == primero) {
                BorrarInicio();
            } else if (aux->siguiente == primero) {
                BorrarFinal();
            } else {
                pnodoME temp = aux;
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                aux = aux->siguiente;
                delete temp;
            }

            cout << "nodoME con los c?digos " << codigosBuscados << " borrado exitosamente." << endl;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void ArbolMenu::ComprobacionME() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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

    while (i <= largoLista()) {
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

                cout << "Codigos encontrados en la lista: " << codigosBuscados << endl;
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
        cout << "No se encontraron los c?digos en la lista." << endl;
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
                           
int ArbolMenu::largoLista() 
{
    int cont=0;

    pnodoME aux = primero->siguiente;
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

void ArbolMenu::InsertarFinal(string v)
{
   if (ListaVacia())
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

void ArbolMenu::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoME temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoME aux = primero; //1
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoME temp = aux->siguiente;//2
         aux->siguiente= primero;//3
         primero->anterior=aux;//4
         delete temp;//5
      }
    }
}

void ArbolMenu::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoME temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoME aux = primero->anterior;//1
        pnodoME temp= primero;//2
        aux->siguiente=primero->siguiente;//3
        primero=primero->siguiente; //4
        primero->anterior=aux;//5
        delete temp;//6
      }
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
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
        return false;
    }
    
    pnodoME aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= largoLista()) {
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

    void InsertarInicio(string v);
    void InsertarFinal(string v);
    void InsertarPos(string v, int pos);
    bool ListaVacia() { return primero == NULL; }
    void Imprimir();
    void Borrar(string v);
    void MostrarPRO();
    void BorrarFinal();
    void BorrarInicio();
    void BorrarPosicion(int pos);
    int largoLista();
    void CargarDesdeArchivoPRO();
    void ArbolProductosPRO(ArbolMenu & ListaArbolMenu);
    void ComprobacionPRO();
    void BorrarPorCodigosPRO();
    void AgregarPRO(ArbolMenu & ListaArbolMenu);
    void ModificarNombrePRO();
    bool ExistePRO(string codigo);
    int stringAEnteroPRO(const std::string &cadena);
    string EncontrarValorMayorPedido();
private:
    pnodoPRO primero;
};

string ArbolProducto::EncontrarValorMayorPedido() {
    if (ListaVacia()) {
        cout << "La lista de ArbolMenu esta vacia." << endl;
        return "lista vacia";
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
        return "Informacion del ArbolProducto: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n ArbolRestaurante con con consultas." << endl;
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
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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

    while (i <= largoLista()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			cout<<"codigo encontrado"<<endl;
			string newName;
			cout<<"digite el nuevo nombre"<<endl;
			cin >> newName;
			
			int calorias,precio;
			cout<<"digite las nuevas calorias del ArbolProducto"<<endl;
			cin >> calorias;
			
			cout<<"digite el nuevo precio del ArbolProducto"<<endl;
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
        cout << "No se encontraron los codigos en la lista." << endl;
    }

}

void ArbolProducto::ArbolProductosPRO(ArbolMenu & ListaArbolMenu)
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolProductos"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar ArbolProductos digite 1: "<<endl;
		cout<<"ver ArbolProductos digite 2: "<<endl;
		cout<<"agregar un ArbolProducto digite 3:"<<endl;
		cout<<"borrar un ArbolProducto digite 4: "<<endl;
		cout<<"modificar un ArbolProducto digite 5"<<endl;
		cout<<"para salir digite 6: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un ArbolProducto"<<endl;
				cout<<"ArbolProductos disponibles: "<<endl;
				MostrarPRO();
				ComprobacionPRO();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los ArbolProductos"<<endl;
				cout<<"se mostraran todos los ArbolProductos a continuacion: "<<endl;
				MostrarPRO();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un ArbolProducto"<<endl;
				AgregarPRO(ListaArbolMenu);
				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un ArbolProducto"<<endl;
				cout<<"ArbolProductos disponibles: "<<endl;
				MostrarPRO();
				BorrarPorCodigosPRO();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, modificar nombre"<<endl;
				cout<<"opciones de moficicacion disponibles"<<endl;
				MostrarPRO();
				ModificarNombrePRO();
				break;
			case 6: 
				cout<<""<<endl;
				cout<<"opcion 6, salir a ArbolProducto principal"<<endl;
				ejecucion = false;	
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}

void ArbolProducto::AgregarPRO(ArbolMenu & ListaArbolMenu){
	cout<<"agregar ArbolProductos"<<endl;
	cout<<"A continuacion muestran paises, ArbolCiudades, ArbolRestaurantes y ArbolMenus disponibles: "<<endl;		
	ListaArbolMenu.MostrarME();
	cout<<"para agregar ArbolProductos, se debe de verificar la existencia del pais, ArbolCiudad, ArbolRestaurante y ArbolMenu, agregar sus codigos"<<endl;
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
    
    
	if(ListaArbolMenu.ExisteME(codigosBuscados)){
		cout<<"el pais, ArbolCiudad, ArbolRestaurante y ArbolMenu existen, se procede a agregar"<<endl;
	    int codigo1a;
	    cout << "Ingrese el codigo del nuevo ArbolMenu: " << endl;
	    cin >> codigo1a;

	    std::stringstream ss1a;
	    ss1a << codigo1a;

	    string num1a = ss1.str();
		    
		string NombreNuevo;
		cout<<"digite el nombre del ArbolMenu"<<endl;
		cin >> NombreNuevo;
		
		int calorias,precio;
		cout<<"digite las calorias del ArbolProducto"<<endl;
		cin >> calorias;
		
		cout<<"digite el precio del ArbolProducto"<<endl;
		cin >> precio;
		
		std::stringstream ss2a,ss2b;
		ss2a << calorias;
		ss2b << precio;
		string caloriaString =  ss2a.str();
		string precioString = ss2b.str();
	
		string NuevoValor = codigosBuscados + ";" + num1a + ";" + NombreNuevo + ";" + caloriaString + ";" + precioString;
		InsertarFinal(NuevoValor);
	
	}else{
		cout<<"no existe, No se agrega"<<endl;
		ArbolProductosPRO(ListaArbolMenu);
	}
}

void ArbolProducto::BorrarPorCodigosPRO() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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

    while (i <= largoLista()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			cout<<"codigo encontrado"<<endl;
			
			if (aux == primero) {
                BorrarInicio();
            } else if (aux->siguiente == primero) {
                BorrarFinal();
            } else {
                pnodoPRO temp = aux;
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                aux = aux->siguiente;
                delete temp;
            }
            cout<<"borrado exitoso"<<endl;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en la lista." << endl;
    }
}


void ArbolProducto::ComprobacionPRO() {
    if (ListaVacia()) {
        cout << "La lista esta vacia." << endl;
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

	while (i <= largoLista()) {
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

                cout << "Codigos encontrados en la lista: " << codigosBuscados << endl;
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
        cout << "No se encontraron los c?digos en la lista." << endl;
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
            string numero1, numero2, numero3,numero4,numero5, nombre,numero6,numero7;
            getline(iss, numero1, ';');
            getline(iss, numero2, ';');
            getline(iss, numero3, ';');
            getline(iss, numero4, ';');
            getline(iss, numero5, ';');
            getline(iss, nombre);
            getline(iss, numero6, ';');
            getline(iss, numero7, ';');

            // Verificar si NUPRORO3 es diferente de los anteriores
            if (numero4_set.find(numero4) == numero4_set.end())
            {
                numero4_set.insert(numero4);  // Agregar a conjunto de NUPRORO3
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + numero4+ ";"+ numero5+ ";" + nombre +";" + numero6 + ";" + numero7 +";" + "0";
                InsertarFinal(nuevo_valor);
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
                          
int ArbolProducto::largoLista() 
{
    int cont=0;

    pnodoPRO aux = primero->siguiente;
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

void ArbolProducto::InsertarFinal(string v)
{
   if (ListaVacia())
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
  
void ArbolProducto::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoPRO temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoPRO aux = primero; //1
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoPRO temp = aux->siguiente;//2
         aux->siguiente= primero;//3
         primero->anterior=aux;//4
         delete temp;//5
      }
    }
}

void ArbolProducto::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoPRO temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoPRO aux = primero->anterior;//1
        pnodoPRO temp= primero;//2
        aux->siguiente=primero->siguiente;//3
        primero=primero->siguiente; //4
        primero->anterior=aux;//5
        delete temp;//6
      }
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
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
        return false;
    }
    
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= largoLista()) {
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
















//clase ArbolClientes
class nodoCl {
public:
    nodoCl(const string& v) {
        valor = v;
        siguiente = NULL;
    }

    nodoCl(const string& v, nodoCl* signodoCl) {
        valor = v;
        siguiente = signodoCl;
    }

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

    void InsertarFinal(string v);
    bool ListaVacia() { return primero == NULL; }
    void MostrarCl();
    int largoLista();
    void CargarDesdeArchivoCl();
    void ConsultarClientePorCodigoCl();
    void BorrarPorCodigoCl();
    void ArbolClientesCl();
    void AgregarClienteCl();
    void ModificarNombreCL();
    bool ExisteCl(int codigo);
    string ObtenerContenidoComoString();

private:
    pnodoCl primero;
};

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

void ArbolClientes::ArbolClientesCl()
{
	bool ejecucion = true;
	cout<<"bienvenido a ArbolClientes"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar ArbolClientes digite 1: "<<endl;
		cout<<"ver ArbolClientes digite 2: "<<endl;
		cout<<"agregar un cliente digite 3:"<<endl;
		cout<<"borrar un cliente digite 4: "<<endl;
		cout<<"modificar un cliente digite 5"<<endl;
		cout<<"para salir digite 6: "<<endl;
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
				cout<<"se mostraran todos los ArbolClientes a continuacion: "<<endl;
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
				cout<<"opcion 4, borrar un cliente"<<endl;
				cout<<"ArbolClientes disponibles: "<<endl;
				MostrarCl();
				BorrarPorCodigoCl();
				MostrarCl();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, modificar un cliente"<<endl;
				cout<<"nombres disponibles"<<endl;
				MostrarCl();
				ModificarNombreCL();
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

void ArbolClientes::AgregarClienteCl()
{
    cout << "Ingrese la cedula del cliente (parte entera): ";
    int codigo;
    cin >> codigo;
    cin.ignore();  // Limpia el buffer del salto de linea

    cout << "Ingrese el nombre del cliente: ";
    string nombre;
    getline(cin, nombre);

    // Verificar si el codigo ya existe en la lista
    bool codigoExistente = false;
    pnodoCl aux = primero;
    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnLista;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnLista;

            if (codigoEnLista == codigo) {
                codigoExistente = true;
                cout << "Error: Ya existe un cliente con la misma cedula " << codigo << "." << endl;
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
        InsertarFinal(pais);
        cout << "cliente agregado exitosamente." << endl;
    }
}

void ArbolClientes::BorrarPorCodigoCl(){
	long long codigo;
	cout<<"digite el codigo a borrar: "<<endl;
	cin >> codigo;
	
    if (ListaVacia()) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    if (primero->valor.find(';') != string::npos) {
        int codigoEnLista;
        istringstream(primero->valor.substr(0, primero->valor.find(';'))) >> codigoEnLista;

        if (codigoEnLista == codigo) {
            pnodoCl temp = primero;
            primero = primero->siguiente;
            delete temp;
            cout << "Cliente con codigo " << codigo << " eliminado." << endl;
            return;
        }
    }

    pnodoCl prev = primero;
    pnodoCl curr = primero->siguiente;

    while (curr) {
        size_t pos = curr->valor.find(';');
        if (pos != string::npos) {
            int codigoEnLista;
            istringstream(curr->valor.substr(0, pos)) >> codigoEnLista;

            if (codigoEnLista == codigo) {
                prev->siguiente = curr->siguiente;
                delete curr;
                cout << "Cliente con codigo " << codigo << " eliminado." << endl;
                return;
            }
        }

        prev = curr;
        curr = curr->siguiente;
    }

    cout << "No se encontro un cliente con el codigo " << codigo << " en la lista." << endl;
}

void ArbolClientes::ConsultarClientePorCodigoCl() {
    if (ListaVacia()) {
        cout << "La lista esta vacia." << endl;
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
                    string codigoEnLista = aux->valor.substr(0, posAux);
                    
                    if (codigoEnLista == codigo) {
                        existe = true;
                        cout << "Cliente con cedula:  " << codigo << " ya existe en la lista." << endl;
                        break;
                    }
                }
                aux = aux->siguiente;
            }
            
            if (!existe) {
                InsertarFinal(codigo + ";" + nombre);
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

int ArbolClientes::largoLista(){
    int cont=0;

    pnodoCl aux= primero;
    if(ListaVacia()){
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

void ArbolClientes::InsertarFinal(string v)//76
{
   if (ListaVacia())
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

bool ArbolClientes::ExisteCl(int codigo) {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
        return false;
    }

    std::stringstream ss1;
    ss1 << codigo;
    string num1 = ss1.str();
    string codigosBuscados = num1 + ";";
    pnodoCl aux = primero;
    bool encontrado = false;

    while (aux != NULL) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
        }
        aux = aux->siguiente;
    }

    return false;
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
    bool ListaVacia() { return primero == NULL; }
    void BorrarFinal();
    void BorrarInicio();
    void MostrarCompra();
    int largoLista();
    void Paises();
    void AgregarCompra(ArbolProducto & ListaArbolProducto, string valor);
    void ConsultarPaisPorCodigo();
    void BorrarPaisPorCodigo(int codigo);
    void ModificarNombre();
    bool Existe(int codigo);
    void BorrarPaisPorSeisCodigos();
    void BorrarComprasPorInicio(string valor);
    void MostrarComprasPorInicio(string valor);

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
    if (ListaVacia()) {
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
    if (ListaVacia()) {
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
    if (ListaVacia()) {
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


void ListaCOM::AgregarCompra(ArbolProducto &ListaArbolProducto, string valor) {
    cout << "Se muestran los ArbolProductos disponibles" << endl;
    ListaArbolProducto.MostrarPRO();
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

    string codigosBuscados = num1 + ";" + num2 + ";" + num3 + ";" + num4 + ";" + num5;

    if (ListaArbolProducto.ExistePRO(codigosBuscados)) {
        cout << "ArbolProducto encontrado y agregado de manera exitosa al cliente " << endl;
        string entrada2 = valor +";"+ codigosBuscados;
        InsertarFinal(entrada2);
        MostrarCompra();
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

void ListaCOM::InsertarFinal(string v)
{
   if (ListaVacia())
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
    if (ListaVacia()){
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
    if (ListaVacia()){
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
    if (ListaVacia()) {
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
    void Agregar(ArbolProducto & ListaArbolProducto, ArbolClientes &  ListaArbolClientes, ListaCOM & ListaCompras);
    void ColaCO(ArbolProducto & ListaArbolProducto, ArbolClientes &  ListaArbolClientes,ListaCOM & ListaCompras);
    bool VerificarNumeroEnCola(string &num1);
    void MostrarCodigoEnPosicion(int posicion);
    void BorrarPorNumeroIdentificacion(ListaCOM & ListaCompras);
    void ModificarPorNumeroIdentificacion(ArbolProducto &ListaArbolProducto, ArbolClientes &ListaArbolClientes);
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

void cola::ModificarPorNumeroIdentificacion(ArbolProducto &ListaArbolProducto, ArbolClientes &ListaArbolClientes) {
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
                ListaArbolProducto.MostrarPRO();

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

void cola::Agregar(ArbolProducto &ListaArbolProducto, ArbolClientes &ListaArbolClientes, ListaCOM &ListaCompras) {
    if (fondo < 5 - 1) {
        cout << "Opciones disponibles de cliente:" << endl;
        ListaArbolClientes.MostrarCl();
        int codigo2;
        cout << "Digite el n?mero de c?dula del cliente: ";
        cin >> codigo2;

        if (ListaArbolClientes.ExisteCl(codigo2)) {
            cout << "Cliente encontrado de manera exitosa" << endl;
            std::stringstream ss10;
            ss10 << codigo2;
            string num10 = ss10.str();

            if (VerificarNumeroEnCola(num10)) {
                // El cliente ya existe en la cola, no es necesario insertarlo nuevamente.
                ListaCompras.AgregarCompra(ListaArbolProducto, num10);
            } else {
                // El cliente no est? en la cola, lo insertamos y luego agregamos la compra.
                string entrada = num10 + ";";
                int posicion = fondo + 1;  // Siguiente posici?n disponible en la cola
                insertar(entrada);  // Agregar el cliente en la siguiente posici?n
                cout << "Se procede a agregar el ArbolProducto" << endl;
                ListaCompras.AgregarCompra(ListaArbolProducto, num10);
            }

        } else {
            cout << "Cliente no encontrado" << endl;
            ColaCO(ListaArbolProducto, ListaArbolClientes, ListaCompras);
        }
    } else {
        cout << "La cola est? llena" << endl;
        ColaCO(ListaArbolProducto, ListaArbolClientes, ListaCompras);
    }
    ColaCO(ListaArbolProducto, ListaArbolClientes, ListaCompras);
}


void cola::ColaCO(ArbolProducto & ListaArbolProducto, ArbolClientes &  ListaArbolClientes,ListaCOM & ListaCompras ){

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
				Agregar(ListaArbolProducto,ListaArbolClientes,ListaCompras);
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
						ColaCO(ListaArbolProducto, ListaArbolClientes, ListaCompras);
				}
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, modificar una compra"<<endl;
				cout<<"nombres disponibles"<<endl;
				imprimir();
				ModificarPorNumeroIdentificacion(ListaArbolProducto,ListaArbolClientes);
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
	//definicion de todas las listas
	//lectura de archivos
   	ArbolPais ListaArbolPais;
   	ListaArbolPais.CargarDesdeArchivo();
   	
   	
   	ArbolCiudad ListaArbolCiudad;
   	ListaArbolCiudad.CargarDesdeArchivoCIU();
   	
   	
   	ArbolRestaurante ListaArbolRestaurante;
   	ListaArbolRestaurante.CargarDesdeArchivoRE();
   	
   	
   	ArbolMenu ListaArbolMenu;
   	ListaArbolMenu.CargarDesdeArchivoME();
   	
   	
   	ArbolProducto ListaArbolProducto;
   	ListaArbolProducto.CargarDesdeArchivoPRO();
   	
   	
   	ArbolClientes ListaArbolClientes;
   	ListaArbolClientes.CargarDesdeArchivoCl();
   	
	cola ColaCompras;
	
	
    ListaCOM ListaCompras;
    ListaCompras.MostrarCompra();

   	
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
				cout<<"opcion 1 paises "<<endl;
				ListaArbolPais.Paises();
				break;
				
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2 ArbolCiudades"<<endl;
				ListaArbolCiudad.ArbolCiudadsCIU(ListaArbolPais);
				break;
				
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3 ArbolRestaurantes"<<endl;
				ListaArbolRestaurante.ArbolRestaurantesRE(ListaArbolCiudad);
				break;
				
			case 4:
				cout<<""<<endl;
				cout<<"opcion 4 ArbolMenu"<<endl;
				ListaArbolMenu.ArbolMenusME(ListaArbolRestaurante);
				break;
					
			case 5:
				cout<<""<<endl;
				cout<<"opcion 5 ArbolProductos"<<endl;
				ListaArbolProducto.ArbolProductosPRO(ListaArbolMenu);
				break;
				
			case 6:
				cout<<""<<endl;
				cout<<"opcion 6 ArbolClientes"<<endl;
				ListaArbolClientes.ArbolClientesCl();
				break;
			case 7:
				cout<<""<<endl;
				cout<<"opcion 7 compras"<<endl;
				ColaCompras.ColaCO(ListaArbolProducto, ListaArbolClientes, ListaCompras);
				break;
			case 8: 
				cout<<""<<endl;
				cout<<"opcion 8 generar reportes"<<endl;
				
				cout<<"reportes de pais:"<<endl;
				ListaArbolPais.Mostrar();
				cout<<""<<endl;
				
				cout<<"reportes de ArbolCiudad:"<<endl;
				cout<<"paises disponibles"<<endl;
				ListaArbolPais.Mostrar();
				ListaArbolCiudad.MostrarArbolCiudadesPorPais();
				cout<<""<<endl;
				
				cout<<"reportes de ArbolRestaurantes:"<<endl;
				cout<<"paises y ArbolCiudades disponibles"<<endl;
				ListaArbolCiudad.MostrarCIU();
				ListaArbolRestaurante.MostrarArbolRestaurantesPorArbolCiudad();
				cout<<""<<endl;
				
				cout<<"reportes de ArbolClientes:"<<endl;
				ListaArbolClientes.MostrarCl();
				cout<<""<<endl;
				
				cout<<"ArbolRestaurante mas buscado:"<<endl;
				ListaArbolRestaurante.EncontrarValorMayorPedido();
				cout<<""<<endl;
				cout<<"ArbolMenu mas buscado:"<<endl;
				ListaArbolMenu.EncontrarValorMayorPedido();
				cout<<""<<endl;
				
				cout<<"ArbolProducto mas buscado:"<<endl;
				ListaArbolProducto.EncontrarValorMayorPedido();
				cout<<""<<endl;
				
				
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


	cout<<"generacion de reporte en txt"<<endl;
    ofstream archivo("reportes.txt");

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    archivo << "Reporte de paises: " << endl;
    string RepPais = ListaArbolPais.ObtenerContenidoComoString();
    archivo << RepPais <<endl;
    archivo<<""<<endl;
    
    archivo<< "Reporte de ArbolCiudades"<<endl;
    cout<<"paises disponibles"<<endl;
    ListaArbolPais.Mostrar();
    string RepCiu = ListaArbolCiudad.MostrarArbolCiudadesPorPais();
    archivo<<RepCiu<<endl;
    archivo<<""<<endl;
    
    archivo<<"Reporte de ArbolRestaurantes"<<endl;
    cout<<"paises y ArbolCiudades disponibles"<<endl;
    ListaArbolCiudad.MostrarCIU();
    string RepRes = ListaArbolRestaurante.MostrarArbolRestaurantesPorArbolCiudad();
    archivo<<RepRes<<endl;
    archivo<<""<<endl;
    
    archivo<<"Reporte de ArbolClientes"<<endl;
    string RepArbolClientes = ListaArbolClientes.ObtenerContenidoComoString();
    archivo<<RepArbolClientes<<endl;
    archivo<<""<<endl;
    
    archivo<< "Reporte de ArbolRestaurante mas buscado"<<endl;
    string RepRestMas = ListaArbolRestaurante.EncontrarValorMayorPedido();
    archivo<<RepRestMas<<endl;
    archivo<<""<<endl;
    
    archivo<<"Reporte de ArbolMenu mas buscado"<<endl;
    string RepMeMas = ListaArbolMenu.EncontrarValorMayorPedido();
    archivo<<RepMeMas<<endl;
    archivo<<""<<endl;
    
    archivo<<"Reporte de ArbolProducto mas buscado"<<endl;
    string RepProMas = ListaArbolProducto.EncontrarValorMayorPedido();
    archivo<<RepProMas<<endl;


    archivo.close();

    cout << "La informacion se ha guardado en archivo.txt." << endl;
   cin.get();
   return 0;
}
