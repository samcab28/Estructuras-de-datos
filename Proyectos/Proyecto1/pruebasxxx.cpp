#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <set>

using namespace std;

class nodoCI {
public:
    nodoCI(const string &v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoCI(const string &v, nodoCI *signodoCI)
    {
        valor = v;
        siguiente = signodoCI;
    }

private:
    string valor;
    nodoCI *siguiente;
    nodoCI *anterior;

    friend class Ciudad;
};
typedef nodoCI *pnodoCI;

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
    void MostrarCI();
    void BorrarFinal();
    void BorrarInicio();
    void BorrarPosicion(int pos);
    int largoLista();
    void CargarDesdeArchivoCI();
    void CiudadsCI();
    void ComprobacionCI();
    void BorrarPorCodigosCI();
private:
    pnodoCI primero;
};


void Ciudad::CiudadsCI()
{
	
	
	//leer el archivo de paises en una lista doble
	
	CargarDesdeArchivoCI();

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
				MostrarCI();
				ComprobacionCI();
				break;
			case 2:
				cout<<""<<endl;
				cout<<"opcion 2, ver todos los Ciudads"<<endl;
				cout<<"se mostraran todos los Ciudads a continuacion: "<<endl;
				MostrarCI();
				break;		
			case 3:
				cout<<""<<endl;
				cout<<"opcion 3, agregar un Ciudad"<<endl;

				break;			
			case 4: 
				cout<<""<<endl;
				cout<<"opcion 4, borrar un Ciudad"<<endl;
				cout<<"Ciudads disponibles: "<<endl;
				MostrarCI();
				BorrarPorCodigosCI();
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


void Ciudad::BorrarPorCodigosCI() {
    if (ListaVacia()) {
        cout << "La lista está vacía." << endl;
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
    pnodoCI aux = primero;
    bool encontrado = false;

    while (aux) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            if (aux == primero) {
                BorrarInicio();
            } else if (aux->siguiente == primero) {
                BorrarFinal();
            } else {
                pnodoCI temp = aux;
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                aux = aux->siguiente;
                delete temp;
            }

            cout << "nodoCI con los códigos " << codigosBuscados << " borrado exitosamente." << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los códigos en la lista." << endl;
    }
}


void Ciudad::ComprobacionCI() {
    if (ListaVacia()) {
        cout << "La lista está vacía." << endl;
        return;
    }

    int codigo1, codigo2;
    cout << "Ingrese el primer codigo: " << endl;
    cin >> codigo1;

    cout << "Ingrese el segundo codigo: " << endl;
    cin >> codigo2;


    std::stringstream ss1, ss2, ss3;
    ss1 << codigo1;
    ss2 << codigo2;


    string num1 = ss1.str();
    string num2 = ss2.str();
 

    string codigosBuscados = num1 + ";" + num2;
    pnodoCI aux = primero;
    bool encontrado = false;

    while (aux) {
        // Buscar el patrón de códigos (123;456;789) en el valor del nodoCI
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            // Extraer el nombre del nodoCI (parte después del último punto y coma)
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


void Ciudad::CargarDesdeArchivoCI() {
    set<string> numero2_set;  

    ifstream archivo("CiudadEs.txt");
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
   pnodoCI aux;
   pnodoCI temp;
   
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

    pnodoCI aux = primero->siguiente;
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
     primero = new nodoCI(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     pnodoCI nuevo=new nodoCI (v);//1
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
     primero = new nodoCI(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoCI nuevo = new nodoCI(v);//1
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
     primero = new nodoCI(v);
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
             pnodoCI aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
                   i++;
                   aux=aux->siguiente;
             }
             pnodoCI nuevo= new nodoCI(v);//1
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
        pnodoCI temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoCI aux = primero; //1
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoCI temp = aux->siguiente;//2
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
        pnodoCI temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoCI aux = primero->anterior;//1
        pnodoCI temp= primero;//2
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
       pnodoCI aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       pnodoCI temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       aux->siguiente->anterior=aux;
       delete temp;
     }
    }
  }
}

void Ciudad::MostrarCI()
{
   pnodoCI aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;

} 


int main(){
	Ciudad lista;
	lista.CiudadsCI();
	return 0;
}


