#include <iostream>
#include <random>
using namespace std;

class nodo { // Constructores
   public:
   	
   	
nodo(int v)//6  nodo(string)  nodo(int x
    {
       valor = v;
       siguiente = NULL;
    }

nodo(int v, nodo  *signodo)    // nodo(nodo *signodo,int v)
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
    void Ej1(int numero);
    void Ej2(int numero,int posicion);
    void Ej3();
    void Ej4();
    void Ej5(int numero); 
    void Ej6(int numero);
    int* ConvertirAArray(int* array, int maxSize) {
        int index = 0;
        nodo* aux = primero;
        while (aux && index < maxSize) {
            array[index] = aux->valor;
            aux = aux->siguiente;
            index++;
        }
        return array;
    }
    
    
   private:
    pnodo primero;
   
};

lista::~lista()
{
   nodo *aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   primero= NULL;
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

void lista::Ej1(int numero){
   nodo * aux;
   cout<<::endl;
   cout<<"ejercicio 1:"<<::endl;

   if (ListaVacia()){
      cout<<"la lista esta vacia, numero NO esta presente"<<::endl;
   }
   else{
      int contador = 1;
      int valor = 0;
      aux = primero;
      while(contador <= largoLista()){
         if (numero == aux -> valor){
            cout<<"el numero("<<numero<<") SI esta en la lista, en la posicion: "<<contador<<::endl;
            valor ++;
            break;
         }
         else{
            aux = aux -> siguiente;
            contador ++;
         }   
      }
      if (valor ==0){
         cout<<"el numero ("<<numero<<") NO se encontraba en la lista"<<::endl;
      }
   }
} 

void lista::Ej2(int numero, int posicion){
   nodo * aux;
   aux = primero;

   cout<<::endl;
   cout<<"ejercicio 2:"<<::endl;

   if (ListaVacia()){
      cout<<"la lista esta vacia, numero NO esta presente"<<::endl;
   }
   else{
      if(posicion <= largoLista()){
         int contador = 1; 
         while(contador != posicion){
            aux = aux -> siguiente;
            contador ++;
         }
         if(numero == aux -> valor){
            cout<<"el numero seleccionado ("<<numero<<"), en la posicion determinada ("<<numero<<") SI es el mismo"<<::endl;
         }
         else{
            cout<<"el numero seleccionado ("<<numero<<"), en la posicion determinada ("<<posicion<<") NO es el mismo"<<::endl;
         }
      }
      else{
         cout<<"error, no se puede busca el numero ya que no es una posicion de la lista"<<::endl;
      }
   }
}

void lista::Ej3(){
   lista lista1;
   lista lista2;
   lista lista3;
   int contador1 = 0;
   int contador2 = 0;
 
   while (contador1 <= 20){
      int minNum = 1;
      int maxNum = 100;
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(minNum, maxNum);
      int randomNumber = dis(gen);
      lista1.InsertarInicio(randomNumber);
      contador1 ++;
   }
   while (contador2 <= 20){
      int minNum = 1;
      int maxNum = 100;
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(minNum, maxNum);
      int randomNumber = dis(gen);
      lista2.InsertarInicio(randomNumber);
      contador2 ++;
   }
   cout<<::endl;
   cout<<"ejercicio 3:"<<::endl;
   cout<<"lista 1:"<<::endl;
   lista1.Mostrar();
   cout<<"lista 2:"<<::endl;
   lista2.Mostrar();

   const int maxSize = 20;
   int array[maxSize];
   int resultado[maxSize];

   for(int i = 0; i <= maxSize; ++i){
      resultado[i] = lista1.ConvertirAArray(array,maxSize)[i] + lista2.ConvertirAArray(array,maxSize)[i];
   }
   cout<<"suma de listas: "<<::endl;
   for (int i = 0; i <= maxSize; ++i) {
      lista3.InsertarFinal(resultado[i]);
   }
   lista3.Mostrar();
}

void lista::Ej4(){
   lista lista1;
   lista lista2;
   lista lista3;

   int minNumNumero = 1;
   int maxNumNumero = 25;
   int minNum = 1;
   int maxNum = 4;
   int contador1 = 0;
   int contador2 = 0;
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dis1(minNumNumero, maxNumNumero);
   std::uniform_int_distribution<> dis2(minNumNumero, maxNumNumero);
   int randomNumber1 = dis1(gen);
   int randomNumber2 = dis2(gen);

   int mayor, menor;

   while(randomNumber1==randomNumber2){
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis1(minNumNumero, maxNumNumero);
      std::uniform_int_distribution<> dis2(minNumNumero, maxNumNumero);
      int randomNumber1 = dis1(gen);
      int randomNumber2 = dis2(gen);
   }

   if (randomNumber1 > randomNumber2){
      mayor = randomNumber1;
      menor = randomNumber2;
   }
   else{
      mayor = randomNumber2;
      menor = randomNumber1;
   }

   //crear lista mayor
   while (contador1 <= mayor){
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(minNum, maxNum);
      int randomNumber = dis(gen);
      lista1.InsertarInicio(randomNumber);
      contador1 ++;
   }  

   //crear lista menor
   while (contador2 <= menor){
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(minNum, maxNum);
      int randomNumber = dis(gen);
      lista2.InsertarInicio(randomNumber);
      contador2 ++;
   }  

   cout<<::endl;
   cout<<"ejercicio 4:"<<::endl;
   cout<<"lista 1:"<<::endl;
   lista1.Mostrar();
   cout<<"lista 2:"<<::endl;
   lista2.Mostrar();

   while(lista2.largoLista()+1 != lista1.largoLista()){
      lista2.InsertarFinal(0);
   }
   int resultado[mayor];
   int array1[mayor];
   int array2[mayor];

   for(int i = 0; i <=mayor; ++i){
      resultado[i] = lista1.ConvertirAArray(array1,mayor)[i] + lista2.ConvertirAArray(array2,mayor)[i];
   }
   cout<<"suma de listas: "<<::endl;
   for (int i = 0; i <=mayor; ++i) {
      lista3.InsertarFinal(resultado[i]);
   }
   lista3.Mostrar();  

}
void lista::Ej5(int numero){
   cout<<""<<::endl;
   cout<<"ejercicio 5:"<<::endl;
   lista lista1; //sacar un numero por cada digito 
    int pares = 0; //variable que muestra la cantidad de pares que se encuentren
    if (numero ==0){
        cout<<"el numero es cero"<<::endl;
    }
    else{
        while(numero !=0){
            //sacar el digito del numero individualmente
            //contar el numero en pares
            //enviar el numero a la lista 
            int temporal = numero % 10; //se extrae el digito
            if (temporal % 2 == 0){ //confirmacion de par
                pares ++; //deteccion de numero par 
            }
            //hacer la llamada al envio de la lista
            lista1.InsertarInicio(temporal);
            //hacer el reset del numero, prepararlo para el siguiente bucle  
            numero = numero / 10; 
        }
    }
    cout<<"mostar lista: "<<::endl;
    lista1.Mostrar();
    cout << "cantidad de pares: " << pares << ::endl;
}

void lista::Ej6(int numero){
   cout<<::endl;
   lista lista3;
   cout<<"ejercicio 6:"<<::endl;
    int pares = 0;
    int impares = 1; 

    if(numero == 0){
        cout<<"el numero es cero"<<::endl;
    }
    else{
        while(numero != 0){
            int temporal = numero % 10;
            if (temporal % 2 == 0){
                pares += temporal;
            }
            else{
                impares *= temporal;
            }
            lista3.InsertarInicio(temporal);
            numero = numero / 10;
        }
        cout<<"lista: "<<::endl;
        lista3.Mostrar();
        cout<<"conteo de pares: "<<pares<<" y multiplicacion de impares: "<<impares<<::endl;
    }
}
void lista::InsertarInicio(int v)//6
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
    pnodo nuevo=new nodo(v);//1
    nuevo->siguiente=primero;//2
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
   lista L1;//instancia null null valor defaul no tiene nada y evita basura
   cout<< "***************************************************************************************"<<endl;
   L1.InsertarInicio(6);
   L1.InsertarInicio(7);
   L1.InsertarInicio(10);
   L1.InsertarInicio(1265);
   L1.InsertarFinal(176);
   L1.InsertarFinal(24);
   L1.InsertarPos(1479,1);
   cout<<"lista de ejemplo para Ej1 y Ej2: "<<::endl;
   L1.Mostrar();
   L1.Ej1(16);
   L1.Ej2(7,3);
   L1.Ej3();
   L1.Ej4();
   L1.Ej5(2309);
   L1.Ej6(123456789);

   cin.get();//es pausa
   return 0;
}
