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
    void CargarDesdeArchivo(const string &nombreArchivo);
    
   private:
    pnodo primero;
  
};

    
void listaD::CargarDesdeArchivo(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
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
	
	/*
	//menu opcional
	cout<<"bienvenido a paises"<<endl;
	cout<<"para consultar pais digite 1, para ver todos los paises digite 2"<<endl;
	cout<<"para agregar un pais digite 3 y para borrar un pais digite 4"<<endl;
	int x;
	
	cin >> x;
	
	
	switch(x)
	{
		case 1: 
			cout<<"opcion 1"<<endl;
			cout<<"en caso de consultar pais por digito, digite 1 y por nombre 2"<<endl;
			int x2;
			cin >> x2;
			
			switch(x2){
				case 1:
					cout<<"consulta de pais por digito, ingrese el digito"<<endl;
					int NumPais;
					cin >> NumPais; 
					cout<<"se consultara el pais de digito: "<<NumPais<<endl;
					break;
				case 2:
					cout<<"consulta de pais por nombre, ingrese el nombre del pais"<<endl;
					string NombrePais;
					cin >> NombrePais;
					cout<<"se consultara el pais de nombre: "<<NombrePais<<endl;
					break;
			}
			break;
		case 2:
			cout<<"opcion 2"<<endl;
			break;		
		case 3:
			cout<<"opcion 3"<<endl;
			break;			
		case 4: 
			cout<<"opcion 4"<<endl;
			break;		
		default:
			cout<<"error opcion incorrecta"<<endl;
			break;			
	}*/
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
   
    Lista.InsertarInicio("a");
    Lista.Mostrar();
	Lista.Paises();
	Lista.CargarDesdeArchivo("paises.txt");
  
   cin.get();
   return 0;
}
