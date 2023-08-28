#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

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
	
	
	//leer el archivo de paises en una lista doble
	
	CargarDesdeArchivoCl();

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
        cout << "La lista está vacia." << endl;
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


int main()
{
   Clientes L1;//instancia null null valor defaul no tiene nada y evita basura
   
	L1.clientesCl();

   
   cin.get();//es pausa
   return 0;
}
