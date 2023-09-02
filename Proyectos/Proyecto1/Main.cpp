#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <set>

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

    friend class PyC;
};

typedef nodo* pnodo;

class PyC {
public:
    PyC() { primero = NULL; }
    ~PyC();

    void InsertarFinal(string v);
    bool ListaVacia() { return primero == NULL; }
    void BorrarFinal();
    void BorrarInicio();
    void Mostrar();
    int largoLista();
    void Paises();
    void CargarDesdeArchivo();
    void AgregarPais();
    void ConsultarPaisPorCodigo();
    void BorrarPaisPorCodigo(int codigo);
    void ModificarNombre();
    bool Existe(int codigo);

private:
    pnodo primero;
};


void PyC::ModificarNombre() {
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

    cout << "No se encontró un país con el código proporcionado." << endl;
}


void PyC::ConsultarPaisPorCodigo() {
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

void PyC::BorrarPaisPorCodigo(int codigo) {
    if (ListaVacia()) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    pnodo aux = primero;
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

void PyC::AgregarPais()
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

void PyC::CargarDesdeArchivo()
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


void PyC::Paises()
{
	bool ejecucion = true;
	cout<<""<<endl;
	cout<<"bienvenido a paises"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"consultar pais digite 1: "<<endl;
		cout<<"ver paises digite 2: "<<endl;
		cout<<"agregar un pais digite 3:"<<endl;
		cout<<"borrar un pais digite 4: "<<endl;
		cout<<"modificar nombre digite 5: "<<endl;
		cout<<"salir digite 6: "<<endl;
		
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
				cout<<"opcion 4, borrar un pais"<<endl;
				cout<<"paises disponibles: "<<endl;
				Mostrar();
				cout<<"registrar codigo: "<<endl;
				int codigo;
				cin >> codigo;
				BorrarPaisPorCodigo(codigo);
				break;		
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5 modoficar nombre"<<endl;
				cout<<"paises disponibles: "<<endl;
				Mostrar();
				ModificarNombre();
				break;
			case 6:
				cout<<""<<endl;
				cout<<"opcion 6, salir a menu principal"<<endl;
				ejecucion = false;	
				break;			
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


PyC::~PyC()
{
   pnodo aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   primero=NULL;
}

int PyC::largoLista(){
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

void PyC::InsertarFinal(string v)
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

     
void PyC::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL)//solo un nodo
		 {
        	pnodo temp=primero;
            primero= NULL;
            delete temp;
            } 
			else 
			{

                pnodo aux = primero;
                while (aux->siguiente->siguiente != NULL) 
                {
                    aux = aux->siguiente;
                }
                
              pnodo temp = aux->siguiente;
              aux->siguiente= NULL;
                      
                delete temp;
            }
        }
}

void PyC::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) {
            pnodo temp=primero;
            primero= NULL;
            delete temp;
            } 
			else
			{

                pnodo aux = primero;
                primero=primero->siguiente;   
				primero->anterior=NULL;            
                delete aux;
            }
        }
}

void PyC::Mostrar()
{
   nodo *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}


bool PyC::Existe(int codigo){
    if (ListaVacia()) {
        cout << "La lista esta vacia." << endl;
        return false;
    }

    pnodo aux = primero;
    bool encontrado = false;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnLista;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnLista;

            if (codigoEnLista == codigo) {
                encontrado = true;
                if (aux == primero) {
                    return true;
                }
                else if (aux->siguiente == NULL) {
                    return true;
                }
                else {
                    aux->anterior->siguiente = aux->siguiente;
                    aux->siguiente->anterior = aux->anterior;
                    delete aux;
                }
                //cout << "Pais con codigo " << codigo << " borrado exitosamente." << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontro un pais con el codigo " << codigo << " en la lista." << endl;
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

    friend class Ciudad;
};
typedef nodoCIU *pnodoCIU;

class Ciudad {
public:
    Ciudad() { primero = NULL; }
    ~Ciudad();

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
    void CiudadsCIU(PyC ListaPyC);
    void ComprobacionCIU();
    void BorrarPorCodigosCIU();
    void AgregarCIU(PyC ListaPyC);
private:
    pnodoCIU primero;
    //friend class PyC;
};


void Ciudad::AgregarCIU(PyC ListaPyC){
	int NumPais;
	cout<<"agregar ciudades"<<endl;
	cout<<"A continuacion se muestran los paises disponibles: "<<endl;		
	ListaPyC.Mostrar();
	cout<<"para agregar ciudades, se debe de verificar la existencia del pais, digite el numero de pais"<<endl;
	cin>>NumPais;
	if(ListaPyC.Existe(NumPais) == true){
		cout<<"el pais si existe, se procede a agregar"<<endl;
		string NombreNuevo;
		cout<<"digite el nombre de la ciudad"<<endl;
		cin >> NombreNuevo;
		
	    std::stringstream ss1;
	    ss1 << NumPais;
	    string num1 = ss1.str();
	    
		string NuevoValor = num1+ ";" + NombreNuevo;
		InsertarFinal(NuevoValor);
	}
	else{
		cout<<"el pais no existe, No se agrega"<<endl;
	}
}

void Ciudad::CiudadsCIU(PyC ListaPyC)
{
	bool ejecucion = true;
	cout<<"bienvenido a Ciudades"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"para consultar Ciudades digite 1: "<<endl;
		cout<<"para ver todos los Ciudades digite 2: "<<endl;
		cout<<"para agregar un Ciudad digite 3:"<<endl;
		cout<<"para borrar un Ciudad digite 4: "<<endl;
		cout<<"para salir digite 5: "<<endl;
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
				AgregarCIU(ListaPyC);

				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un Ciudad"<<endl;
				cout<<"Ciudads disponibles: "<<endl;
				MostrarCIU();
				BorrarPorCodigosCIU();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a menu principal"<<endl;
				ejecucion = false;	
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


void Ciudad::BorrarPorCodigosCIU() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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

    while (aux) {
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

            cout << "nodoCIU con los c?digos " << codigosBuscados << " borrado exitosamente." << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void Ciudad::ComprobacionCIU() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
        return;
    }

    int codigo1, codigo2;
    cout << "Ingrese primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;


    std::stringstream ss1, ss2, ss3;
    ss1 << codigo1;
    ss2 << codigo2;


    string num1 = ss1.str();
    string num2 = ss2.str();
 

    string codigosBuscados = num1 + ";" + num2;
    pnodoCIU aux = primero;
    bool encontrado = false;

    while (aux) {
        // Buscar el patr?n de c?digos (123;456;789) en el valor del nodoCIU
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            // Extraer el nombre del nodoCIU (parte despu?s del ?ltimo punto y coma)
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);

            cout << "C?digos encontrados en la lista: " << codigosBuscados << endl;
            cout << "Nombre asociado: " << nombre << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void Ciudad::CargarDesdeArchivoCIU() {
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
                
Ciudad::~Ciudad()
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
                           //  aux
int Ciudad::largoLista() //3-4-5    cont=0 1 2 3
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

void Ciudad::InsertarInicio(string v)
{
  
   if (ListaVacia())
   {
     primero = new nodoCIU(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoCIU nuevo=new nodoCIU (v);//1
     nuevo->siguiente=primero;//2
     nuevo->anterior= primero->anterior;//3
     primero->anterior->siguiente=nuevo;//4
     nuevo->siguiente->anterior=nuevo;//5
     primero= nuevo;//6
   }
}
 
void Ciudad::InsertarFinal(string v)
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
     /*nuevo->siguiente=primero->anterior->siguiente;opcion para intruccion 3*/
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}


void Ciudad::InsertarPos(string v,int pos)
{
   if (ListaVacia())
   {
     primero = new nodoCIU(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   } 
   {
      if(pos <=1)
        InsertarInicio(v);    
       else
       {
        if (pos==largoLista())
          InsertarFinal(v);
        else
        {     
             pnodoCIU aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoCIU nuevo= new nodoCIU(v);//1
             nuevo->siguiente=aux->siguiente;//2
             aux->siguiente=nuevo;//3
             aux->siguiente->anterior=aux;//4 o puede nuevo->anterio=aux
             nuevo->siguiente->anterior=nuevo;  //5                         
        }
       }
   }
}   

void Ciudad::BorrarFinal()
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

void Ciudad::BorrarInicio()
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

void Ciudad:: BorrarPosicion(int pos)
{
    
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos==1))
      
   {
   	BorrarInicio();
   	
   }
        
   else
   {
    if(pos>largoLista()||(pos<=0))
    {
       cout << "Error en posicion" << endl;
	}
        
    else
    {
       int cont=2;
       pnodoCIU aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoCIU temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       aux->siguiente->anterior=aux;
       delete temp;
     }
    }
  }
}

void Ciudad::MostrarCIU()
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









//clase clientes
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

    friend class Clientes;
};

typedef nodoCl* pnodoCl;

class Clientes {
public:
    Clientes() { primero = NULL; }
    ~Clientes();

    void InsertarInicio(string v);
    void InsertarFinal(string v);
    void InsertarPos(string v, int pos);
    bool ListaVacia() { return primero == NULL; }
    void MostrarCl();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    int largoLista();
    void CargarDesdeArchivoCl();
    void ConsultarClientePorCodigoCl();
    void BorrarPorCodigoCl();
    void clientesCl();
    void AgregarClienteCl();

private:
    pnodoCl primero;
};


void Clientes::clientesCl()
{
	bool ejecucion = true;
	cout<<"bienvenido a Clientes"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"para consultar Clientes digite 1: "<<endl;
		cout<<"para ver todos los clientes digite 2: "<<endl;
		cout<<"para agregar un cliente digite 3:"<<endl;
		cout<<"para borrar un cliente digite 4: "<<endl;
		cout<<"para salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un cliente"<<endl;
				cout<<"clientes disponibles: "<<endl;
				MostrarCl();
				ConsultarClientePorCodigoCl();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los clientes"<<endl;
				cout<<"se mostraran todos los clientes a continuacion: "<<endl;
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
				cout<<"clientes disponibles: "<<endl;
				MostrarCl();
				BorrarPorCodigoCl();
				MostrarCl();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a menu principal"<<endl;
				ejecucion = false;	
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}

void Clientes::AgregarClienteCl()
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

void Clientes::BorrarPorCodigoCl(){
	int codigo;
	cout<<"digite el codigo a borrar: "<<endl;
	cin >> codigo;
	
    if (ListaVacia()) {
        cout << "La lista est? vacia." << endl;
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

void Clientes::ConsultarClientePorCodigoCl() {
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

void Clientes::CargarDesdeArchivoCl()
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

Clientes::~Clientes() {
    nodoCl* aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

int Clientes::largoLista(){
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

void Clientes::InsertarInicio(string v)//6
{
   if (ListaVacia())
   {
   
     primero = new nodoCl(v);//6
     
   }
   else
   {
    pnodoCl nuevo=new nodoCl(v);//1
    nuevo->siguiente=primero;//2
    primero=nuevo;

   }
}
 
void Clientes::InsertarFinal(string v)//76
{
   if (ListaVacia())
     primero = new nodoCl(v);
   else
      { 
      //primera forma
	    //pnodoCl aux = primero;
      //  while ( aux->siguiente != NULL)
      //   aux= aux->siguiente;
      //  aux->siguiente=new nodoCl(v);
       
       //segunda forma 
       pnodoCl aux = primero;
        while ( aux->siguiente != NULL)
         aux= aux->siguiente;
        pnodoCl nuevo=new nodoCl(v);
        aux->siguiente=nuevo;
      }    
}

void Clientes::InsertarPos(string v,int pos)
{
   if (ListaVacia())
     primero = new nodoCl(v);
   else{
        if(pos <=1)
		{
        	//OPcion1
          pnodoCl nuevo = new nodoCl(v);
          nuevo->siguiente= primero;
          primero= nuevo;     
          //OPcion 2
          //InsertarInicio(v);
        }      
        else{
             nodoCl *aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodoCl nuevo= new nodoCl(v);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             
        }
        }
}
      
void Clientes::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        
        if (primero->siguiente == NULL) 
		{   pnodoCl temp=primero;
		    primero= NULL;
		    delete temp;;
            }
			 else {

                pnodoCl aux = primero;
                while (aux->siguiente->siguiente != NULL) {
                    aux = aux->siguiente;

                }
                
              pnodoCl temp = aux->siguiente;
              aux->siguiente= NULL;

                
                delete temp;
            }
        }
}

void Clientes::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) 
		{   pnodoCl temp=primero;
		    primero= NULL;
		    delete temp;
        } 
		else 
		{

                pnodoCl aux = primero;
                primero=primero->siguiente;                
                delete aux;
        }
        }
}

void Clientes:: borrarPosicion(int pos){
     if(ListaVacia()){
              cout << "Lista vacia" <<endl;
    }else{
         if((pos>largoLista())||(pos<0)){
        cout << "Error en posicion" << endl;
        }else{
        if(pos==1)
		{
        	pnodoCl temp=primero;
        	primero=primero->siguiente;
        	delete temp; //BorrarInicio();
        }
		else{
          int cont=2;
            pnodoCl aux=  primero;
            while(cont<pos){
             aux=aux->siguiente;
             cont++;
            }
            pnodoCl temp=aux->siguiente;
            aux->siguiente=aux->siguiente->siguiente;
            delete temp;
            }
        }
     }

}
 
void Clientes::MostrarCl()

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










//clase restaurante
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

    friend class Restaurante;
};
typedef nodoRE *pnodoRE;

class Restaurante {
public:
    Restaurante() { primero = NULL; }
    ~Restaurante();

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
    void restaurantesRE(Ciudad ListaCiudad);
    void ComprobacionRE();
    void BorrarPorCodigosRE();
    //void agregar restaurantes(Ciudad listaCIUDAD);
private:
    pnodoRE primero;
};


void Restaurante::restaurantesRE(Ciudad listaCIUDAD)
{
	bool ejecucion = true;
	cout<<"bienvenido a restaurantes"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"para consultar restaurantes digite 1: "<<endl;
		cout<<"para ver todos los restaurantes digite 2: "<<endl;
		cout<<"para agregar un restaurante digite 3:"<<endl;
		cout<<"para borrar un restaurante digite 4: "<<endl;
		cout<<"para salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un restaurante"<<endl;
				cout<<"restaurantes disponibles: "<<endl;
				MostrarRE();
				ComprobacionRE();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los restaurantes"<<endl;
				cout<<"se mostraran todos los restaurantes a continuacion: "<<endl;
				MostrarRE();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un restaurante"<<endl;

				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un restaurante"<<endl;
				cout<<"restaurantes disponibles: "<<endl;
				MostrarRE();
				BorrarPorCodigosRE();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a menu principal"<<endl;
				ejecucion = false;	
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


void Restaurante::BorrarPorCodigosRE() {
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

    while (aux) {
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
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void Restaurante::ComprobacionRE() {
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

    while (aux) {
        // Buscar el patr?n de c?digos (123;456;789) en el valor del nodoRE
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            // Extraer el nombre del nodoRE (parte despu?s del ?ltimo punto y coma)
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);

            cout << "C?digos encontrados en la lista: " << codigosBuscados << endl;
            cout << "Nombre asociado: " << nombre << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void Restaurante::CargarDesdeArchivoRE() {
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
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + nombre;
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
                
Restaurante::~Restaurante()
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
                           //  aux
int Restaurante::largoLista() //3-4-5    cont=0 1 2 3
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

void Restaurante::InsertarInicio(string v)
{
  
   if (ListaVacia())
   {
     primero = new nodoRE(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoRE nuevo=new nodoRE (v);//1
     nuevo->siguiente=primero;//2
     nuevo->anterior= primero->anterior;//3
     primero->anterior->siguiente=nuevo;//4
     nuevo->siguiente->anterior=nuevo;//5
     primero= nuevo;//6
   }
}
 
void Restaurante::InsertarFinal(string v)
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


void Restaurante::InsertarPos(string v,int pos)
{
   if (ListaVacia())
   {
     primero = new nodoRE(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   } 
   else
   {
      if(pos <=1)
        InsertarInicio(v);    
       else
       {
        if (pos==largoLista())
          InsertarFinal(v);
        else
        {     
             pnodoRE aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoRE nuevo= new nodoRE(v);//1
             nuevo->siguiente=aux->siguiente;//2
             aux->siguiente=nuevo;//3
             aux->siguiente->anterior=aux;//4 o puede nuevo->anterio=aux
             nuevo->siguiente->anterior=nuevo;  //5                         
        }
       }
   }
}   

void Restaurante::BorrarFinal()
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

void Restaurante::BorrarInicio()
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

void Restaurante:: BorrarPosicion(int pos)
{
    
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos==1))
      
   {
   	BorrarInicio();
   	
   }
        
   else
   {
    if(pos>largoLista()||(pos<=0))
    {
       cout << "Error en posicion" << endl;
	}
        
    else
    {
       int cont=2;
       pnodoRE aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoRE temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       aux->siguiente->anterior=aux;
       delete temp;
     }
    }
  }
}

void Restaurante::MostrarRE()
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










//clase menu
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

    friend class Menu;
};
typedef nodoME *pnodoME;

class Menu {
public:
    Menu() { primero = NULL; }
    ~Menu();

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
    void MenusME();
    void ComprobacionME();
    void BorrarPorCodigosME();
private:
    pnodoME primero;
};


void Menu::MenusME()
{
	bool ejecucion = true;
	cout<<"bienvenido a Menus"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"para consultar Menus digite 1: "<<endl;
		cout<<"para ver todos los Menus digite 2: "<<endl;
		cout<<"para agregar un Menu digite 3:"<<endl;
		cout<<"para borrar un Menu digite 4: "<<endl;
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

				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un Menu"<<endl;
				cout<<"Menus disponibles: "<<endl;
				MostrarME();
				BorrarPorCodigosME();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a menu principal"<<endl;
				ejecucion = false;	
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


void Menu::BorrarPorCodigosME() {
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

    while (aux) {
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
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void Menu::ComprobacionME() {
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

    while (aux) {
        // Buscar el patr?n de c?digos (123;456;789) en el valor del nodoME
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            // Extraer el nombre del nodoME (parte despu?s del ?ltimo punto y coma)
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);

            cout << "C?digos encontrados en la lista: " << codigosBuscados << endl;
            cout << "Nombre asociado: " << nombre << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void Menu::CargarDesdeArchivoME() {
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
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + numero4+ ";" + nombre;
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
                
Menu::~Menu()
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
                           //  aux
int Menu::largoLista() //3-4-5    cont=0 1 2 3
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

void Menu::InsertarInicio(string v)
{
  
   if (ListaVacia())
   {
     primero = new nodoME(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoME nuevo=new nodoME (v);//1
     nuevo->siguiente=primero;//2
     nuevo->anterior= primero->anterior;//3
     primero->anterior->siguiente=nuevo;//4
     nuevo->siguiente->anterior=nuevo;//5
     primero= nuevo;//6
   }
}
 
void Menu::InsertarFinal(string v)
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


void Menu::InsertarPos(string v,int pos)
{
   if (ListaVacia())
   {
     primero = new nodoME(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   } 
   else
   {
      if(pos <=1)
        InsertarInicio(v);    
       else
       {
        if (pos==largoLista())
          InsertarFinal(v);
        else
        {     
             pnodoME aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoME nuevo= new nodoME(v);//1
             nuevo->siguiente=aux->siguiente;//2
             aux->siguiente=nuevo;//3
             aux->siguiente->anterior=aux;//4 o puede nuevo->anterio=aux
             nuevo->siguiente->anterior=nuevo;  //5                         
        }
       }
   }
}   

void Menu::BorrarFinal()
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

void Menu::BorrarInicio()
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

void Menu:: BorrarPosicion(int pos)
{
    
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos==1))
      
   {
   	BorrarInicio();
   	
   }
        
   else
   {
    if(pos>largoLista()||(pos<=0))
    {
       cout << "Error en posicion" << endl;
	}
        
    else
    {
       int cont=2;
       pnodoME aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoME temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       aux->siguiente->anterior=aux;
       delete temp;
     }
    }
  }
}

void Menu::MostrarME()
{
   pnodoME aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     //EXTRA
     cout<<endl;
    /* cout<< "primero";
     cout<<endl;
     cout<<aux->siguiente->valor<<"->";
     cout<<endl;
     cout<< "ultimo";
     cout<<endl;
     cout<<primero->anterior->valor<<"->";*/
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

    friend class producto;
};
typedef nodoPRO *pnodoPRO;

class producto {
public:
    producto() { primero = NULL; }
    ~producto();

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
    void productosPRO();
    void ComprobacionPRO();
    void BorrarPorCodigosPRO();
private:
    pnodoPRO primero;
};


void producto::productosPRO()
{
	bool ejecucion = true;
	cout<<"bienvenido a productos"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"para consultar productos digite 1: "<<endl;
		cout<<"para ver todos los productos digite 2: "<<endl;
		cout<<"para agregar un producto digite 3:"<<endl;
		cout<<"para borrar un producto digite 4: "<<endl;
		cout<<"para salir digite 5: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un producto"<<endl;
				cout<<"productos disponibles: "<<endl;
				MostrarPRO();
				ComprobacionPRO();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los productos"<<endl;
				cout<<"se mostraran todos los productos a continuacion: "<<endl;
				MostrarPRO();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un producto"<<endl;

				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un producto"<<endl;
				cout<<"productos disponibles: "<<endl;
				MostrarPRO();
				BorrarPorCodigosPRO();
				break;	
			case 5: 
				cout<<""<<endl;
				cout<<"opcion 5, salir a producto principal"<<endl;
				ejecucion = false;	
				break;
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


void producto::BorrarPorCodigosPRO() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
        return;
    }
    
    int codigo1, codigo2, codigo3,codigo4, codigo5;
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
    ss4 << codigo5;

    string num1 = ss1.str();
    string num2 = ss2.str();
    string num3 = ss3.str();
    string num4 = ss4.str();
    string num5 = ss5.str();

    string codigosBuscados = num1 + ";" + num2 + ";" + num3 + ";" + num4 + ";" + num5;
    pnodoPRO aux = primero;
    bool encontrado = false;

    while (aux) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

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

            cout << "nodoPRO con los c?digos " << codigosBuscados << " borrado exitosamente." << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void producto::ComprobacionPRO() {
    if (ListaVacia()) {
        cout << "La lista est? vac?a." << endl;
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

    while (aux) {
        // Buscar el patr?n de c?digos (123;456;789) en el valor del nodoPRO
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            // Extraer el nombre del nodoPRO (parte despu?s del ?ltimo punto y coma)
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);

            cout << "C?digos encontrados en la lista: " << codigosBuscados << endl;
            cout << "Nombre asociado: " << nombre << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en la lista." << endl;
    }
}


void producto::CargarDesdeArchivoPRO() {
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
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + numero4+ ";"+ numero5+ ";" + nombre +";" + numero6 + ";" + numero7;
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
                
producto::~producto()
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
                           //  aux
int producto::largoLista() //3-4-5    cont=0 1 2 3
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

void producto::InsertarInicio(string v)
{
  
   if (ListaVacia())
   {
     primero = new nodoPRO(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoPRO nuevo=new nodoPRO (v);//1
     nuevo->siguiente=primero;//2
     nuevo->anterior= primero->anterior;//3
     primero->anterior->siguiente=nuevo;//4
     nuevo->siguiente->anterior=nuevo;//5
     primero= nuevo;//6
   }
}
 
void producto::InsertarFinal(string v)
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
     /*nuevo->siguiente=primero->anterior->siguiente;opcion para intruccion 3*/
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}


void producto::InsertarPos(string v,int pos)
{
   if (ListaVacia())
   {
     primero = new nodoPRO(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   } 
   else
   {
      if(pos <=1)
        InsertarInicio(v);    
       else
       {
        if (pos==largoLista())
          InsertarFinal(v);
        else
        {     
             pnodoPRO aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoPRO nuevo= new nodoPRO(v);//1
             nuevo->siguiente=aux->siguiente;//2
             aux->siguiente=nuevo;//3
             aux->siguiente->anterior=aux;//4 o puede nuevo->anterio=aux
             nuevo->siguiente->anterior=nuevo;  //5                         
        }
       }
   }
}   

void producto::BorrarFinal()
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

void producto::BorrarInicio()
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

void producto:: BorrarPosicion(int pos)
{
    
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos==1))
      
   {
   	BorrarInicio();
   	
   }
        
   else
   {
    if(pos>largoLista()||(pos<=0))
    {
       cout << "Error en posicion" << endl;
	}
        
    else
    {
       int cont=2;
       pnodoPRO aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoPRO temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       aux->siguiente->anterior=aux;
       delete temp;
     }
    }
  }
}

void producto::MostrarPRO()
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





	
int main()
{
	//definicion de todas las listas
	//lectura de archivos
   	PyC ListaPyC;
   	ListaPyC.CargarDesdeArchivo();
   	
   	
   	Ciudad ListaCiudad;
   	ListaCiudad.CargarDesdeArchivoCIU();
   	
   	
   	Restaurante ListaRestaurante;
   	ListaRestaurante.CargarDesdeArchivoRE();
   	
   	
   	Menu ListaMenu;
   	ListaMenu.CargarDesdeArchivoME();
   	
   	
   	producto ListaProducto;
   	ListaProducto.CargarDesdeArchivoPRO();
   	
   	
   	Clientes ListaClientes;
   	ListaClientes.CargarDesdeArchivoCl();
   	
   	
   	
	bool ejecucion = true;
	
	while(ejecucion)
	{
		int MenuPrincipal;
		cout<<""<<endl;
		cout<<"Bienvenido"<<endl;
		cout<<"para Pais, digite 1"<<endl;
		cout<<"para ciudad, digite 2"<<endl;
		cout<<"para restaurantes, digite 3"<<endl;
		cout<<"para menu, digite 4"<<endl;
		cout<<"para productos, digite 5"<<endl;
		cout<<"para clientes, digite 6"<<endl;
		cout<<"para salir, digite 7"<<endl;
		
		cin >> MenuPrincipal;
		
		switch(MenuPrincipal)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1 paises "<<endl;
				ListaPyC.Paises();
				break;
				
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2 ciudades"<<endl;
				ListaCiudad.CiudadsCIU(ListaPyC);
				break;
				
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3 restaurantes"<<endl;
				ListaRestaurante.restaurantesRE(ListaCiudad);
				break;
				
			case 4:
				cout<<""<<endl;
				cout<<"opcion 4 menu"<<endl;
				ListaMenu.MenusME();
				break;
					
			case 5:
				cout<<""<<endl;
				cout<<"opcion 5 productos"<<endl;
				ListaProducto.productosPRO();
				break;
				
			case 6:
				cout<<""<<endl;
				cout<<"opcion 6 clientes"<<endl;
				ListaClientes.clientesCl();
				break;
			case 7:
				cout<<""<<endl;
				cout<<"opcion 7 salir"<<endl;
				exit(0);
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
