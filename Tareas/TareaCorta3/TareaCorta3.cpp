//tarea corta 3

#include <iostream>
using namespace std; 

int main(){
	
	bool programa = true;
	
	while(programa){
		cout<<"\n1 para buscar"<<endl;
		cout<<"2 para eliminar"<<endl;
		cout<<"3 para insertar"<<endl;
		cout<<"4 para purgar"<<endl;
		cout<<"5 para reindexar"<<endl;
		cout<<"6 para imprimir"<<endl;
		cout<<"7 para cache"<<endl;
		cout<<"8 para salir"<<endl;
		cout<<"\n digite la opcion: "<<endl;
		int x;
		cin >> x;
		switch(x){
			case 1:
				cout<<"1. buscar"<<endl;
				break;
			case 2: 
				cout<<"2. eliminar"<<endl;
				break;
			case 3: 
				cout<<"3. insertar"<<endl;
				break;
			case 4: 
				cout<<"4. purgar"<<endl;
				break;
			case 5: 
				cout<<"5. reindexar"<<endl;
				break;
			case 6: 
				cout<<"6. imprimir"<<endl;
				break;
			case 7: 
				cout<<"7. cache"<<endl;
			case 8:
				cout<<"salir"<<endl;
				programa = false;
				break;
			default:
				cout<<"error a la hora de digitar"<<endl;
				break;
		}
		
	}
	
	
	return 0;
}
