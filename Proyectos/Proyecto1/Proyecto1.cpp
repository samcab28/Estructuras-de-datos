#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;



class nodo {
   public:
    nodo(string v)
    {
       valor = v;
       siguiente = NULL;
       anterior =NULL;
    }

nodo(string v, nodo * signodo)
    {
       valor = v;
       siguiente = signodo;
    }

   private:
    string valor;
    nodo *siguiente;
    nodo *anterior;
    
        
   friend class listaD;
};

typedef nodo *pnodo;

class listaD {
   public:
    listaD() { primero =  NULL; }
    ~listaD();
    
    void InsertarInicio(string v);
    void InsertarFinal(string v);
    void InsertarPos (string v, int pos);
    bool ListaVacia() { return primero == NULL; } 
    void BorrarFinal();
    void BorrarInicio();
    void BorrarPosicion(int pos);
    void Mostrar();
    int largoLista();
    void Paises();
    void CargarDesdeArchivo();
    void AgregarPais();
    void ConsultarPaisPorCodigo();
    void BorrarPaisPorCodigo(int codigo);
   private:
    pnodo primero;
  
};


void listaD::BorrarPaisPorCodigo(int codigo) {
    if (ListaVacia()) {
        cout << "La lista está vacía." << endl;
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
                } else if (aux->siguiente == NULL) {
                    BorrarFinal();
                } else {
                    aux->anterior->siguiente = aux->siguiente;
                    aux->siguiente->anterior = aux->anterior;
                    delete aux;
                }
                cout << "País con código " << codigo << " borrado exitosamente." << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontró un país con el código " << codigo << " en la lista." << endl;
    }
}


void listaD::ConsultarPaisPorCodigo()
{
            cout << "Ingrese el código del país que desea consultar: ";
            int codigo;
            cin >> codigo;

            pnodo aux = primero; // Get the first node of the list
            int posicion = 1;
            bool encontrado = false;

            while (aux) {
                size_t pos = aux->valor.find(';');
                if (pos != string::npos) {
                    int codigoEnLista;
                    istringstream(aux->valor.substr(0, pos)) >> codigoEnLista;

                    if (codigoEnLista == codigo) {
                        encontrado = true;
                        cout << "Código de país: " << codigoEnLista << endl;
                        cout << "Nombre de país: " << aux->valor.substr(pos + 1) << endl;
                        cout << "Posición en la lista: " << posicion << endl;
                        break;
                    }
                }
                aux = aux->siguiente;
                posicion++;
    }

    if (!encontrado) {
        cout << "País no encontrado para el código " << codigo << endl;
    }
}

void listaD::AgregarPais()
{
    cout << "Ingrese el código del país (parte entera): ";
    int codigo;
    cin >> codigo;
    cin.ignore();  // Limpia el buffer del salto de línea

    cout << "Ingrese el nombre del país: ";
    string nombre;
    getline(cin, nombre);

    // Usar ostringstream para convertir el entero a cadena
    ostringstream ss;
    ss << codigo;
    string codigoStr = ss.str();

    string pais = codigoStr + ";" + nombre;
    InsertarFinal(pais);
    cout << "País agregado exitosamente." << endl;
}
    
void listaD::CargarDesdeArchivo()
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
            InsertarFinal(codigo + ";" + nombre);
        }
    }

    archivo.close();
}


void listaD::Paises()
{
	
	listaD paises;
	
	//leer el archivo de paises en una lista doble
	
	paises.CargarDesdeArchivo();

	bool ejecucion = true;
	cout<<"bienvenido a paises"<<endl;
	
	while(ejecucion){
		cout<<""<<endl;
		cout<<"para consultar pais digite 1: "<<endl;
		cout<<"para ver todos los paises digite 2: "<<endl;
		cout<<"para agregar un pais digite 3:"<<endl;
		cout<<"para borrar un pais digite 4: "<<endl;
		int x;
		
		cin >> x;
		
		
		switch(x)
		{
			case 1:
				cout<<""<<endl;
				cout<<"opcion 1, consultar un pais"<<endl;
				cout<<"paises disponibles: "<<endl;
				paises.Mostrar();
				paises.ConsultarPaisPorCodigo();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los paises"<<endl;
				cout<<"se mostraran todos los paises a continuacion: "<<endl;
				paises.Mostrar();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un pais"<<endl;
				paises.AgregarPais();
				paises.Mostrar();
				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un pais"<<endl;
				cout<<"paises disponibles: "<<endl;
				paises.Mostrar();
				cout<<"registrar codigo: "<<endl;
				int codigo;
				cin >> codigo;
				paises.BorrarPaisPorCodigo(codigo);
				break;		
			default:
				cout<<""<<endl;
				cout<<"error opcion incorrecta"<<endl;
				break;			
		}
	}

}


listaD::~listaD()
{
   pnodo aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   primero=NULL;
}

int listaD::largoLista(){
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

void listaD::InsertarInicio(string v)
{
   if (ListaVacia())
   {
   
     primero = new nodo(v);
     primero->anterior=NULL;     
   }
   else
   {
     primero=new nodo (v,primero);
     primero->siguiente->anterior=primero;
   }
}
//Otra forma ultimas dos lineas
// pnodo nuevo=new nodo(v);
//nuevo->siguiente=primero;
//primero->anterior=nuevo;
//primero=nuevo;
 
void listaD::InsertarFinal(string v)
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
//Otra forma cambia las ultimas dos instrucciones
//pnodo nuevo= new nodo(v);
//nuevo->anterior=aux;
//aux->siguiente=nuevo;


void listaD::InsertarPos(string v,int pos)
{
   if (ListaVacia())
    {
   
     primero = new nodo(v);
     primero->anterior=NULL;     
   }
   else{
        if(pos <=1)
          InsertarInicio(v);    
        else
        {
             pnodo aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodo nuevo= new nodo(v);
             nuevo->siguiente=aux->siguiente;
			 nuevo->anterior=aux;
			   nuevo->siguiente->anterior=nuevo;
			   aux->siguiente=nuevo;                      
        }
        }
}
      
void listaD::BorrarFinal()
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

void listaD::BorrarInicio()
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



void listaD:: BorrarPosicion(int pos)
{
     if(ListaVacia())
     {
              cout << "Lista vacia" <<endl;
     }
     else
     {
        if((pos>largoLista())||(pos<0))//no validas
        {
        cout << "Error en posicion" << endl;
        }
        else
        {
        if(pos==1)
           BorrarInicio();
        else
        {
          if (pos == largoLista())   
             BorrarFinal();
          else
          {   
            int cont=2;
            pnodo aux=  primero;
            while(cont<pos)
            {
             aux=aux->siguiente;
             cont++;
            }
            pnodo temp=aux->siguiente;
            aux->siguiente=aux->siguiente->siguiente;
            aux->siguiente->anterior=aux;
            delete temp;
          }//else
        }//else
      }//else
    }//else
}
 

void listaD::Mostrar()
{
   nodo *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}


int main()
{
   listaD Lista;
   
	Lista.Paises();
	//Lista.CargarDesdeArchivo();
	//Lista.Mostrar();
  
   cin.get();
   return 0;
}
