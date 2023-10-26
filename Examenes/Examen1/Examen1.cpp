#include <iostream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>


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

typedef nodo *pnodo; 

class lista {
   public:
    lista() { primero =  NULL; }//constructor
    ~lista();//destructor
    void InsertarInicio(int v);//No retornan nada
    void InsertarFinal(int v);
    int Absoluto(int numero);
    bool ListaVacia() { return primero == NULL; } //retorna True o False
    void Mostrar();//imprimir
    int largoNumeroLista();// retorno un valor numerico
    void UNO(int num1, int num2);
    int extraerPos(int x);
    void DOS(lista & valores);
    void BorrarTodos();
    void TRES(int num1, int num2);
    void CUATRO(int num1,int num2);
    int largoNumero(int num);
    int CentroImpar(int num);
    
    void BorrarInicio();
    
   private:
    pnodo primero;
   
};

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


int lista::Absoluto(int numero) {
    if (numero < 0) {
    	int Absoluto = numero*-1;
    	return Absoluto;
	}else{
		return numero;
	}
}

int lista::CentroImpar(int num) {
    num = abs(num);
    int largoNumero = 0;
    int temp = num;

    while (temp != 0) {
        temp /= 10;
        largoNumero++;
    }

    if (largoNumero % 2 != 0) {
        int lar = (largoNumero - 1) / 2;
        int cont = largoNumero - 1;
        int centro = -1;  // Valor predeterminado en caso de que no se encuentre un centro válido

        temp = num;
        while (temp != 0) {
            int digito = temp % 10;
            if (cont == lar) {
                centro = digito;
                break;
            }
            temp /= 10;
            cont--;
        }
        return centro;
        
    } else {
        return -1;  // No hay un centro válido
    }
}

int lista::largoNumero(int num) {
    num = abs(num);
    int cont = 0;
    int temp = num;

    if (num == 0) {
        return 1;
    } else {
        while (temp != 0) {
            temp /= 10;
            cont++;
        }
        return cont;
    }
}

void lista::BorrarTodos() {
    while (!ListaVacia()) {
        BorrarInicio();
    }
}

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

int lista::largoNumeroLista(){
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

void lista::UNO(int num1, int num2){
	
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
	

	int largoNumeronum1,largoNumeronum2;
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
						Lista1Nueva.InsertarInicio(int (num1 % 10));
						Lista2Nueva.InsertarFinal(int (num2%10));
						num1 = num1 / 10;
						num2 = num2 / 10;
						contador ++;
					}
					else{
						Lista1Nueva.InsertarInicio(int (num2 % 10));
						Lista2Nueva.InsertarFinal(int (num1%10));
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
			cout<<"error, numeros largoNumero distinto a multiplo de cinco"<<endl;
		}
	}
	else{
		cout<<"error, numeros de diferente tamano"<<endl;
	}

}


void lista:: DOS(lista & valores){
	lista listaAux;
	int contador = 0;
	int listcontador = 1;
	cout<<"Lista original: "<<endl;
	valores.Mostrar();
	cout<<""<<endl;
	
	while(contador < valores.largoNumeroLista()){
		int a = valores.extraerPos(contador);
		int b = valores.extraerPos(contador+1);
		if(a < b){
			contador ++;
		}

	}
	
	contador = 0;
	while(contador < valores.largoNumeroLista()){
		int a = valores.extraerPos(contador);
		int b = valores.extraerPos(contador+1);
		
		if(a > b || contador == (valores.largoNumeroLista()-1)) {
			listaAux.InsertarFinal(valores.extraerPos(contador));
			listaAux.InsertarInicio(1);
			listaAux.InsertarInicio(0);
			listaAux.InsertarInicio(1);
			listaAux.InsertarFinal(0);
			listaAux.InsertarFinal(-1);
			listaAux.InsertarFinal(0);
			
			cout<<"lista de salida "<<listcontador<<":"<<endl;
			listcontador++;
			listaAux.Mostrar();
			cout<<""<<endl;
			listaAux.BorrarTodos();
		}
		else{
			listaAux.InsertarFinal(valores.extraerPos(contador));
		}
		contador ++;
	}
}

void lista::TRES(int num1, int num2){
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

	int largoNumeronum1,largoNumeronum2;
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
		int contador = 0;
		while(contador < contadornum1){
			Lista1Nueva.InsertarInicio(num1%10);
			Lista2Nueva.InsertarInicio(num2%10);
			num1 = num1 / 10;
			num2 = num2 / 10;
			contador ++;
		}
		
		contador = 0; 
		while(contador < contadornum1){
			if(contador % 2 == 0){
				ListaResultado.InsertarFinal(1);
				ListaResultado.InsertarFinal(0);
				ListaResultado.InsertarFinal(1);
				ListaResultado.InsertarFinal(Lista1Nueva.extraerPos(contador)-1);
				ListaResultado.InsertarFinal(Lista1Nueva.extraerPos(contador));
				ListaResultado.InsertarFinal(Lista1Nueva.extraerPos(contador)+1);
				ListaResultado.InsertarFinal(-1);
				ListaResultado.InsertarFinal(0);
				ListaResultado.InsertarFinal(-1);
				contador ++;
			}
			else{
				ListaResultado.InsertarFinal(-2);
				ListaResultado.InsertarFinal(0);
				ListaResultado.InsertarFinal(-2);
				ListaResultado.InsertarFinal(Lista2Nueva.extraerPos(contador)-1);
				ListaResultado.InsertarFinal(Lista2Nueva.extraerPos(contador));
				ListaResultado.InsertarFinal(Lista2Nueva.extraerPos(contador)+1);
				ListaResultado.InsertarFinal(2);
				ListaResultado.InsertarFinal(0);
				ListaResultado.InsertarFinal(2);
				contador ++;
			}
		}
		contador = contadornum1;
		while(contador > 0){
			if(contador % 2 == 0){
				ListaResultado.InsertarFinal(1);
				ListaResultado.InsertarFinal(0);
				ListaResultado.InsertarFinal(1);
				ListaResultado.InsertarFinal(Lista1Nueva.extraerPos(contador-1)-1);
				ListaResultado.InsertarFinal(Lista1Nueva.extraerPos(contador-1));
				ListaResultado.InsertarFinal(Lista1Nueva.extraerPos(contador-1)+1);
				ListaResultado.InsertarFinal(-1);
				ListaResultado.InsertarFinal(0);
				ListaResultado.InsertarFinal(-1);
				contador --;
			}
			else{
				ListaResultado.InsertarFinal(-2);
				ListaResultado.InsertarFinal(0);
				ListaResultado.InsertarFinal(-2);
				ListaResultado.InsertarFinal(Lista2Nueva.extraerPos(contador-1)-1);
				ListaResultado.InsertarFinal(Lista2Nueva.extraerPos(contador-1));
				ListaResultado.InsertarFinal(Lista2Nueva.extraerPos(contador-1)+1);
				ListaResultado.InsertarFinal(2);
				ListaResultado.InsertarFinal(0);
				ListaResultado.InsertarFinal(2);
				contador --;
			}
		}	
		
		cout<<"lista final: "<<endl;
		ListaResultado.Mostrar();
	}
	else{
		cout<<"error, los numeros son de diferente tamano"<<endl;
	}
}

void lista::CUATRO(int num1, int num2) {
	cout<<"Numeros: "<<num1<< " y "<<num2<<endl;
	if(num1 < 0){
		num1 = abs(num1);
	}
	if(num2<0){
		num2 = abs(num2);
	}
    lista L1; 
    lista L2; 

    int largoNumero1 = largoNumero(num1);
    int largoNumero2 = largoNumero(num2);
    
    int cen1 = CentroImpar(num1);
    int cen2 = CentroImpar(num2);
    if (largoNumero1 == largoNumero2) {
        if (largoNumero1 % 2 == 0 && largoNumero2 % 2 == 0) {
            int i = 0;
            int x = largoNumero2; 

            while (i < largoNumero1 / 2) {
                int n1 = (num1 / int(pow(10, largoNumero1 - i - 1))) % 10;
                int n2 = (num2 / int(pow(10, largoNumero1 - x))) % 10;
                int n3 = (num2 / int(pow(10, largoNumero2 - i - 1))) % 10;
                int n4 = (num1 / int(pow(10, largoNumero1 - x))) % 10;
                int n5 = (num2 / int(pow(10, largoNumero1 - i - 1))) % 10;
                int n6 = (num2 / int(pow(10, largoNumero2 - x))) % 10;
                i++;
                x--; 
                
                int resultado1 = (n1 + n2) - n3; 
                int insert1=Absoluto(resultado1);
                L1.InsertarFinal(insert1);
                
                
                int resultado2 = (n4 + n5) - n6;
				int insert2=Absoluto(resultado2);
                L1.InsertarFinal(resultado2);  
            }
            cout << "lista final: " << endl;
            L1.Mostrar();
        } else {
        	int i = 0;
            int x = largoNumero2; 

            while (i < largoNumero1 / 2) {
                int n1 = (num1 / int(pow(10, largoNumero1 - i - 1))) % 10;
                int n2 = (num2 / int(pow(10, largoNumero1 - x))) % 10;
                int n3 = (num2 / int(pow(10, largoNumero2 - i - 1))) % 10;
                int n4 = (num1 / int(pow(10, largoNumero1 - x))) % 10;
                int n5 = (num2 / int(pow(10, largoNumero1 - i - 1))) % 10;
                int n6 = (num2 / int(pow(10, largoNumero2 - x))) % 10;
                i++;
                x--; 
                
                int resultado1 = (n1 + n2) - n3; 
                int insert1 = Absoluto(resultado1);
                L2.InsertarFinal(insert1);
                
                
                int resultado2 = (n4 + n5) - n6;
                int insert2 = Absoluto(resultado2);
                L2.InsertarFinal(insert2);
        }
        
        cout << "lista final: " << endl;
        int sumCentros = cen1 * cen2;
        L2.InsertarFinal(sumCentros);
        L2.Mostrar();
        cout << "-----------------------------------------------------"<< endl;
}
    } else {
        cout << "error, numeros de diferente tamano" << endl;
    }
}

int main()
{
    lista L;
    lista valores;
	/*cout<< "*****************************"<<endl;
	cout<<"Ejercicio 1:"<<endl;
	cout<<""<<endl;
	L.UNO(61257,89102);
	cout<<""<<endl;
    cout<< "*****************************"<<endl;*/
	cout<<"Ejercicio 2:"<<endl;
	valores.InsertarFinal(1);
	valores.InsertarFinal(2);
	valores.InsertarFinal(3);
	valores.InsertarFinal(4);
	valores.InsertarFinal(5);
	valores.InsertarFinal(6);
	valores.InsertarFinal(7);
	valores.InsertarFinal(8);
	valores.InsertarFinal(9);
	valores.InsertarFinal(19);
	valores.InsertarFinal(-8);
	valores.InsertarFinal(-7);
	valores.InsertarFinal(10);
	valores.InsertarFinal(18);
	valores.InsertarFinal(27);
	valores.InsertarFinal(36);
	valores.InsertarFinal(55);
	valores.InsertarFinal(-9);


	L.DOS(valores);
	
/*	cout<<""<<endl;
    cout<< "*****************************"<<endl;
	cout<<"Ejercicio 3:"<<endl;
	L.TRES(6123452,1078952);
	cout<<""<<endl;
    cout<< "*****************************"<<endl;
	cout<<"Ejercicio 4:"<<endl;
	L.CUATRO(61389,26789);*/
   return 0;
}
