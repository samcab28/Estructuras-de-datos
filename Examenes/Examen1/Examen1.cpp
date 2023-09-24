#include <iostream>
#include <cstdlib>
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
    
    void valores(int num1, int num2);
    int extraerPos(int x);
    
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

int lista::extraerPos(int x)
{
    if (ListaVacia()) {
        cout << "Lista vacía" << endl;
    } else {
        if (x < 0) {
            cout << "Posición inválida" << endl;
        } else {
            int cont = 0;
            pnodo aux = primero;

            while (aux) {
                if (cont == x) {
                    return aux -> valor;
                }
                aux = aux->siguiente;
                cont++;
            }

            if (cont <= x) {
                
            }
        }
    }
}


void lista::valores(int num1, int num2){
	
	lista Lista1Nueva;
	lista Lista2Nueva;
	lista ListaResultado;
	
	cout<<"Numeros: "<<num1<< " y "<<num2<<endl;
	if(num1 < 0){
		num1 = abs(num1);
	}
	if(num2<0){
		num2 = abs(num2);
	}
	

	int largonum1,largonum2;
	int pruebanum1 = num1;
	int pruebanum2 = num2;
	int contadornum1 =0;
	int contadornum2 =0;
	
	while(pruebanum1 != 0){
		pruebanum1 = pruebanum1 / 10;
		contadornum1 ++;
	}
	
	
	while(pruebanum2 != 0){
		pruebanum2 = pruebanum2 / 10;
		contadornum2 ++;
	}
		
	if(contadornum1 == contadornum2){
		if(contadornum1 % 5 == 0 && contadornum2 % 5 ==0){
			if(contadornum1 % 10 == 5 && contadornum2 % 10 == 5){
				int contador = 0;
				
				while(contador < contadornum1){
					if(contador % 2 == 0){
						Lista1Nueva.InsertarFinal(int (num2 % 10));
						Lista2Nueva.InsertarInicio(int (num1 % 10));
						num1 = num1 / 10;
						num2 = num2 / 10;
						contador ++;
					}
					else{
						Lista1Nueva.InsertarFinal(int (num1 % 10));
						Lista2Nueva.InsertarInicio(int (num2 % 10));
						num1 = num1 / 10;
						num2 = num2 / 10;
						contador ++;
					}
				}
				
				cout<<"lista 1 nueva: "<<endl;
				Lista1Nueva.Mostrar();
				cout<<"lista 2 nueva: "<<endl;
				Lista2Nueva.Mostrar();
				
				contador =  0;
				while(contador < contadornum1){
					
					int a = Lista1Nueva.extraerPos(contador);
					int b = Lista2Nueva.extraerPos(contador);
					int c = a + b;
					ListaResultado.InsertarFinal(c);
					contador ++;
				}
				
				cout<<"resultado: "<<endl;
				ListaResultado.Mostrar();
				
			}
			else{
				cout<<"error los numeros tienen una longitud par"<<endl;
			}
		}
		else{
			cout<<"error, numeros largo distinto a multiplo de cinco"<<endl;
		}
	}
	else{
		cout<<"error, numeros de diferente tamano"<<endl;
	}

}

int main()
{
   lista L1;//instancia null
   
	L1.valores(-12344,-67905);
 
   cout<< "***************************************************************************************"<<endl;

   cin.get();
   return 0;
}
