/*
Tarea 2 estructuras de datos 
profesora: Cerdas Quesada Ivannia
asistente del curso: Madrigal Murillo Celina
estudiantes:
    -Abarca Fernando
    -Cabrera Samir
*/

#include <iostream>
using namespace std;

/* 
numero = numero entero por ejemplo 2345
num = numero particionado, como 2 o 3 o 4
*/

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
    
        
   friend class Tarea;
};

typedef nodo *pnodo; 


class Tarea{
    public: 
     Tarea() { primero = NULL; } // Constructor
     ~Tarea(); // Declaración del destructor
     bool ListaVacia() {return primero == NULL;}; //decide si la lista esta vacia
     void InsertarInicio(int num); //agrega el numero a la lista
     void Mostrar(); //muestra los numeros de la lista
     //void Ej1(int numero);
     void Ej5(int numero); 
     void Ej6(int numero);
     
   private:
    pnodo primero;

};

Tarea::~Tarea() {
    pnodo aux;

    while (primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

/*
void Tarea::Ej1(int numero){

    if(ListaVacia){
        cout<<"la lista esta vacia, por lo que no se encuentra presente"<<::enld;
    }
    else{
        int i = 1; 
        while(numero != pnodo)
        {
            pnodo -> siguiente;
            i ++;
        }
        cout<<"el numero si se encuentra en la lista"<<::endl;
    }

}
*/
void Tarea::Ej6(int numero){
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
            InsertarInicio(temporal);
            numero = numero / 10;
        }
        cout<<""<<::endl;
        cout<<"ejercicio 5:"<<::endl;
        cout<<"conteo de pares: "<<pares<<" multiplicacion de impares: "<<impares<<::endl;
    }
}
void Tarea::Ej5(int numero){ //sacar un numero por cada digito 
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
            InsertarInicio(temporal);
            //hacer el reset del numero, prepararlo para el siguiente bucle  
            numero = numero / 10; 
        }
    }
    cout<<""<<::endl;
    cout<<"resultado del primer ejercicio: "<<::endl;
    cout<<"mostar lista: "<<::endl;
    Mostrar();
    cout << "cantidad de pares: " << pares << ::endl;
}

void Tarea::InsertarInicio(int v) //uso de la funcion brindada por la profe
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

void Tarea::Mostrar()
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



int main(){

    Tarea mitarea; 

    mitarea.Ej5(2309);
    mitarea.Ej6(123456789);
    mitarea.InsertarInicio(5);
    mitarea.InsertarInicio(3);
    mitarea.InsertarInicio(4);
    mitarea.InsertarInicio(7);
    
    //mitarea.Ej1(3);


    cin.get();
    return 0;
}