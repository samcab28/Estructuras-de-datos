#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <set>

using namespace std;

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
	
	
	//leer el archivo de paises en una lista doble
	
	CargarDesdeArchivoPRO();

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
        cout << "La lista está vacía." << endl;
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

            cout << "nodoPRO con los códigos " << codigosBuscados << " borrado exitosamente." << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los códigos en la lista." << endl;
    }
}


void producto::ComprobacionPRO() {
    if (ListaVacia()) {
        cout << "La lista está vacía." << endl;
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
        // Buscar el patrón de códigos (123;456;789) en el valor del nodoPRO
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            // Extraer el nombre del nodoPRO (parte después del último punto y coma)
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);

            cout << "Códigos encontrados en la lista: " << codigosBuscados << endl;
            cout << "Nombre asociado: " << nombre << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los códigos en la lista." << endl;
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


int main(){
	producto listaproducto;
	listaproducto.productosPRO();
	return 0;
}

