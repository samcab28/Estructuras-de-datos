/*
Tarea 4 estructuras de datos 
profesora: Cerdas Quesada Ivannia
asistente del curso: Madrigal Murillo Celina
estudiantes:
    -Abarca Fernando
    -Cabrera Samir
*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class nodo { // Constructores
   public:
   	
   	
nodo(int v)//3
    {
       valor = v;
       siguiente = NULL;
    }

nodo(int v, nodo  *signodo)
    {
       valor = v;
       siguiente = signodo;
    }


   private:
    int valor=0;
    nodo *siguiente;// Clase Autoreferencia
    
        
   friend class lista;
};

typedef nodo *pnodo; //Alias

//void no retorna nada
//bool retorna False o True
//int retorna entero

class lista {
   public:
    lista() { primero =  NULL; }//constructor
    ~lista();//destructor
    
    void InsertarInicio(int v);//No retornan nada
    void InsertarFinal(int v);
    void InsertarPos (int v, int pos);
    bool ListaVacia() { return primero == NULL; } //retorna True o False
    void Mostrar();//imprimir
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    void Sumanum(int num);
    int largoLista();// retorno un valor numerico
    bool ValidacionEj2(int numero);
    void Ej2(int numero);
    bool esEntero(double numero) {
    return std::abs(numero - static_cast<int>(numero)) < 1e-9;  // Pequeña tolerancia para manejar errores de precisión
}
    
   private:
    pnodo primero;
   
};

lista::~lista()
{
   pnodo aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   primero= NULL;
}

bool lista::ValidacionEj2(int numero){
   if (numero%2 == 0){
      cout<<"Error, el numero es PAR"<<::endl;
   }
   else{
      if(esEntero(numero)){
         if (numero >= 0){
            Ej2(numero);
         }
         else{
            cout<<"error, el numero NO es positivo"<<::endl;
         }
      }
      else{
         cout<<"Error, el numero NO es un numero entero"<<::endl;
      }
   }
}

void lista::Ej2(int numero){
/*
1. encontrar el centro, numero y posicion 
2. insertarlo en una lista 
3. guardar numero que este en el centro en una variable
4. hacer un while para cada posicion extraer posicion y con variable de centro
*/
   cout<<"ejercicio 2"<<::endl;
   nodo * aux; 
   int contador = 0;
   int num = 0; 
   //incertar el numero en una lista
   while (numero != 0){
      int temporal = numero % 10;
      InsertarInicio(temporal);
      numero = numero / 10;
      num ++;
      contador ++;
   }
   
   //encontrar el centro
   int centro = (contador/2) + 1;
   cout<<"Lista original"<<::endl;
   Mostrar(); 
   
   //hallar el valor del centro
   int i = 0; 
   aux = primero;
   while(i < centro-1){
      i ++;
      aux = aux->siguiente;
   }
   int ValorCentro = aux -> valor;
   
   //incertar valores que no sean en el centro
   int j = 1;
   int temp; //guarda el valor de la lista
   int nuevo; //temp + centro 
   aux = primero;
   while(num != 0){
      if(j > centro or j < centro){
         temp = aux -> valor;
         aux = aux -> siguiente;
         nuevo = temp + centro;
         InsertarPos(nuevo,j);
         borrarPosicion(j+1);
         j++;
      }
      else{
         aux = aux -> siguiente;
         j++;
      }
      num --;
   }

   cout<<"resultado"<<::endl;
   Mostrar();

}

int lista::largoLista(){
    int cont=0;

    pnodo aux= primero;
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

void lista::InsertarInicio(int v)//3 10 265
{
   if (ListaVacia())
   {
   
     primero = new nodo(v);//6
     
   }
   else
   {
     //primera forma
 //  primero=new nodo (v,primero);
    //segunda forma
    pnodo nuevo=new nodo(v);
    nuevo->siguiente=primero;
    primero=nuevo;
     
    
    
     
   }
}
 
void lista::InsertarFinal(int v)//76
{
   if (ListaVacia())
     primero = new nodo(v);
   else
      { 
      //primera forma
	    //pnodo aux = primero;
      //  while ( aux->siguiente != NULL)
      //   aux= aux->siguiente;
      //  aux->siguiente=new nodo(v);
       
       //segunda forma 
       pnodo aux = primero;
        while ( aux->siguiente != NULL)
         aux= aux->siguiente;
        pnodo nuevo=new nodo(v);
        aux->siguiente=nuevo;
      }    
}


void lista::InsertarPos(int v,int pos)
{
   if (ListaVacia())
     primero = new nodo(v);
   else{
        if(pos <=1)
		{
        	//OPcion1
          pnodo nuevo = new nodo(v);
          nuevo->siguiente= primero;
          primero= nuevo;     
          //OPcion 2
          //InsertarInicio(v);
        }      
        else{
             nodo *aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             pnodo nuevo= new nodo(v);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             
        }
        }
}
      
void lista::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        
        if (primero->siguiente == NULL) 
		{   pnodo temp=primero;
		    primero= NULL;
		    delete temp;;
            }
			 else {

                pnodo aux = primero;
                while (aux->siguiente->siguiente != NULL) {
                    aux = aux->siguiente;

                }
                
              pnodo temp = aux->siguiente;
              aux->siguiente= NULL;

                
                delete temp;
            }
        }
}

void lista::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
    
   }else{
        if (primero->siguiente == NULL) 
		{   pnodo temp=primero;
		    primero= NULL;
		    delete temp;
        } 
		else 
		{

                pnodo aux = primero;
                primero=primero->siguiente;                
                delete aux;
        }
        }
}



void lista:: borrarPosicion(int pos){
     if(ListaVacia()){
              cout << "Lista vacia" <<endl;
    }else{
         if((pos>largoLista())||(pos<0)){
        cout << "Error en posicion" << endl;
        }else{
        if(pos==1)
		{
        	pnodo temp=primero;
        	primero=primero->siguiente;
        	delete temp; //BorrarInicio();
        }
		else{
          int cont=2;
            pnodo aux=  primero;
            while(cont<pos){
             aux=aux->siguiente;
             cont++;
            }
            pnodo temp=aux->siguiente;
            aux->siguiente=aux->siguiente->siguiente;
            delete temp;
            }
        }
     }

}
 

void lista::Mostrar()
{
   nodo *aux;
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


 void lista::Sumanum(int num)//23456
{
   if (num == 0)
      cout << "Suma igual a 0";
   else
   {
   
       while (num!=0)
       {
	   
	     int temp=num%10;
		 InsertarInicio(temp);
		 num=num/10;
       }
      int suma=0;
      pnodo aux=primero; 
      while(aux !=NULL)
      {
      	suma=suma+aux->valor;
      	aux=aux->siguiente;
	  }
	  cout<<suma<<endl;
   }
	
}

int main()
{
   lista L1;//instancia null
   
    
 
   cout<< "***************************************************************************************"<<endl;

   //L1.Ej2(123);
   L1.ValidacionEj2(1234567);
   cin.get();
   return 0;
}
