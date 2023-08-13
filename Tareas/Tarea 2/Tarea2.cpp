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
     void Ej5(int numero); //divide el digito en numeros individuales
     void Ej2(int numero);
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
        cout<<"proceso ok"<<::endl;
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

void Tarea::Ej2(int numero){ //sacar el promedio de un numero, despues de particionarlo
    float promedio = 0.0; //creacion de una variable para el promedio
    int contador = 0; //contador que ayuda en la formula del promedio
    int suma = 0; //almacenamiento para la suma del numero antes del promedio

    if (numero == 0){
        cout<< "el numero es cero, promedio = 0" << :: endl;
    }
    else{
        while(numero != 0){
            //sacar el digito del numero individualmente
            //almacenarlo en suma
            //confirmar que el numero es cero
            //calcular el promedio 
            int temporal = numero % 10; //se extrae el digito de manera temporal
            suma += temporal;
            contador ++;
            numero = numero /10;
        }
    }

    promedio = static_cast<float>(suma) / contador;
    cout<<""<<::endl;
    cout<<"resultado del segundo ejercicio: "<<::endl;
    cout <<"el promedio es de: " << promedio << ::endl;

}

int main(){

    Tarea mitarea; 

    mitarea.Ej5(2309);
    mitarea.Ej2(1290);
    mitarea.Ej6(2132);

    cin.get();
    return 0;
}