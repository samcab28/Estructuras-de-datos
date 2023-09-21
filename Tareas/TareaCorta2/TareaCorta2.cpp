#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>
#include <set>
#include <cstdlib> 
#include <queue>
#include <stack>

using namespace std;
class ExpressionTree;

class ExpressionTree {
private:
    struct Node {
        std::string data;
        Node* left, *right;

        Node(std::string data) {
            this->data = data;
            this->left = this->right = NULL;
        };

        Node(std::string data, Node* left, Node* right) {
            this->data = data;
            this->left = left;
            this->right = right;
        };
    };

    Node* root;

public:
    ExpressionTree(std::string postfix) {
        root = construct(postfix);
    }

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    Node* construct(std::string postfix) {
        std::stack<Node*> s;

        for (int i = 0; i < postfix.length(); ++i) {
            char c = postfix[i];
            if (isOperator(c)) {
                Node* x = s.top();
                s.pop();
                Node* y = s.top();
                s.pop();
                Node* node = new Node(std::string(1, c), y, x);
                s.push(node);
            } else if (std::isdigit(c)) {
                int numStart = i;
                while (i < postfix.length() && (std::isdigit(postfix[i]) || postfix[i] == '.')) {
                    i++;
                }
                std::string numStr = postfix.substr(numStart, i - numStart);
                i--;

                s.push(new Node(numStr));
            }
        }

        return s.top();
    }

    void preOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        std::cout << root->data << " ->";
        preOrder(root->left);
        preOrder(root->right);
    }

    void inOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        inOrder(root->left);
        std::cout << root->data << " -> ";
        inOrder(root->right);
    }

    void postOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        std::cout << root->data << " -> ";
    }

	void muestraAcostado(int nivel, Node* root)
	{
	    if (root == NULL)
	    {
	        return;
	    }
	
	    muestraAcostado(nivel + 1, root->right);
	
	    for (int i = 0; i < nivel; i++)
	    {
	        cout << "  ";
	    }
	
	    cout << root->data << endl;
	
	    muestraAcostado(nivel + 1, root->left);
	}

	void muestraAcostado(){
		 muestraAcostado(0, root);
		 std::cout << std::endl;
    }
	
    void preOrden() {
        preOrder(root);
        std::cout << std::endl;
    }

    void inOrden() {
        inOrder(root);
        std::cout << std::endl;
    }

    void postOrden() {
        postOrder(root);
        std::cout << std::endl;
    }
};

class Nodo
{
public:
    string dato;  
    Nodo* izquierdoPtr;
    Nodo* derechoPtr;
};


class Arbol
{
private:
    Nodo* raizPtr;
    bool esVacio();
    void gotoxy(int x,int y);

public:
    Arbol();
    ~Arbol();
    Nodo*& regresaRaiz();
    void insertarNodo(string valor, Nodo*& nodoPtr);
    void muestraAcostado(int nivel, Nodo* nodoPtr);
    void inOrden(Nodo * nodoPtr);
    void preOrden(Nodo * nodoPtr);
    void postOrden(Nodo * nodoPtr);
    void establecerRaiz(string valor);


};

void Arbol::inOrden(Nodo * nodoPtr){
    if(nodoPtr == NULL){
        return;
    }

    inOrden(nodoPtr -> izquierdoPtr);
    cout<<nodoPtr -> dato <<" -> ";
    inOrden(nodoPtr -> derechoPtr);
}

void Arbol::preOrden(Nodo * nodoPtr){
    if(nodoPtr == NULL){
        return;
    }

    cout<<nodoPtr -> dato<< " -> ";
    preOrden(nodoPtr->izquierdoPtr);
    preOrden(nodoPtr->derechoPtr);
}

void Arbol::postOrden(Nodo * nodoPtr){
    if(nodoPtr == NULL){
        return;
    }

    postOrden(nodoPtr -> izquierdoPtr);
    postOrden(nodoPtr -> derechoPtr);
    cout<< nodoPtr -> dato << " -> ";
}


void Arbol::establecerRaiz(string valor)
{
    if (raizPtr == NULL)
    {
        raizPtr = new Nodo();
        raizPtr->dato = valor;
        raizPtr->izquierdoPtr = NULL;
        raizPtr->derechoPtr = NULL;
    }
    else
    {
        raizPtr->dato = valor;
    }
}


Arbol::Arbol()
{
    raizPtr = NULL;
}

Arbol::~Arbol()
{
    //podarArbol(raizPtr);
}

Nodo*& Arbol::regresaRaiz()
{
    return raizPtr;
}

void Arbol::insertarNodo(string valor, Nodo*& nodoPtr)
{
    if (nodoPtr == NULL)
    {
        nodoPtr = new Nodo();
        nodoPtr->dato = valor;
        nodoPtr->izquierdoPtr = NULL;
        nodoPtr->derechoPtr = NULL;
    }
    else if (valor < nodoPtr->dato)
    {
        insertarNodo(valor, nodoPtr->izquierdoPtr);
    }
    else if (valor > nodoPtr->dato)
    {
        insertarNodo(valor, nodoPtr->derechoPtr);
    }
}



void Arbol::muestraAcostado(int nivel, Nodo* nodoPtr)
{
    if (nodoPtr == NULL)
    {
        return;
    }

    muestraAcostado(nivel + 1, nodoPtr->derechoPtr);

    for (int i = 0; i < nivel; i++)
    {
        cout << "  ";
    }

    cout << nodoPtr->dato << endl;

    muestraAcostado(nivel + 1, nodoPtr->izquierdoPtr);
}

class nodoOP {
    private:
    string valor;
    int prioridad;
    nodoOP *siguiente;

    friend class tabla;

    public:
    // constructor
    nodoOP(string v, int prior) {
        valor = v;
        prioridad = prior;
        siguiente = NULL;
    }

    nodoOP(string v, int prior, nodoOP *sigNodo) {
        valor = v;
        prioridad = prior;
        siguiente = sigNodo;
    }
};

typedef nodoOP *pnodoOP;

class tabla {
    private:
    pnodoOP primero;
    public:
    tabla() { // constructor
        primero = NULL;
    }

    ~tabla() { // destructor
        pnodoOP aux;
        while(primero) {
            aux = primero;
            primero = primero->siguiente;
            delete aux;
        }
        primero = NULL;
    }

    bool listaVacia() {
        return primero == NULL;
    }

    void insertarFinal(string v, int prior) {
        if (listaVacia())
            primero = new nodoOP(v,prior);
        else {
            pnodoOP aux = primero;
            while (aux->siguiente != NULL)
                aux = aux->siguiente;
                aux->siguiente=new nodoOP(v, prior);
        }
    }

    void mostrar() {
        nodoOP *aux;
        if (primero== NULL)
            cout << "No hay elementos";  
        else {
		  aux = primero;
	       while(aux) {
    	    cout << aux->valor << ":" << aux->prioridad <<" -> ";
    	    aux = aux->siguiente;
    	   }
    	cout << endl;
        }
    }

    void crearTablaFuera() {
        insertarFinal("+", 1);
        insertarFinal("-", 1);
        insertarFinal("*", 2);
        insertarFinal("/", 2);
        insertarFinal("(", 5);
        insertarFinal(")", 10);
        insertarFinal("^", 4);
    }

    void crearTablaDentro() {
        insertarFinal("+", 1);
        insertarFinal("-", 1);
        insertarFinal("*", 2);
        insertarFinal("/", 2);
        insertarFinal("(", 0);
        insertarFinal(")", 10);
        insertarFinal("^", 3);
    }

    int buscarOP(string op) {
        nodoOP* aux = primero;
        while ((aux->valor != op) && (aux->siguiente!=NULL)) {
            aux = aux->siguiente;
        }

        return aux->prioridad;
    }
};

class nodo {
    private:
        string valor;
        nodo* siguiente;

        friend class lista;
        friend class pila;

    public:
        nodo() {
            valor = "";
            siguiente = NULL;
        }
        nodo(string v) {
            valor = v;
            siguiente = NULL;
        }

        nodo(string v, nodo* sigNodo) {
            valor = v;
            siguiente = sigNodo;
        }
};

typedef nodo *pnodo;

class lista {
    private:    
        pnodo primero;
        friend class ExpressionTree;
    public:
        lista() {
            primero = NULL;
        }

        ~lista() {
            pnodo aux;
            while (primero) {
                aux = primero;
                primero = primero->siguiente;
                delete aux;
            }
            primero = NULL;
        }

        bool listaVacia() {
            return primero == NULL;
        }

        void insertarFinal(string valor);
        void mostrar();
        void crearCola(pnodo Cola[]);
        void mostrarExpresion(pnodo primerl);
        void mostrar(pnodo primerl);
        void crearPostfijo(pnodo primerl, int contador);
        string guardar();
};

class pila {
    private:    
        pnodo tope;
        friend class lista;
    public:
        pila() {
            tope = NULL;
        }

        ~pila() {
            pnodo aux;
            while (tope) {
                aux = tope;
                tope = tope->siguiente;
                delete aux;
            }
            tope = NULL;
        }

        bool pilaVacia() {
            return tope == NULL;
        }

        void push(string valor);
        void pop();
        void mostrar();

};

void pila::push(string v) {
        if (pilaVacia())
            tope = new nodo(v);
        else
            tope = new nodo(v, tope);
}

void pila::pop() {
    if (pilaVacia()) {
            cout << "La pila no tiene elementos" << endl;
    } else {
        if (tope->siguiente==NULL) {
            pnodo temp = tope;
            tope = NULL;
            delete temp;
        } else {
            pnodo aux = tope;
            tope=tope->siguiente;
            delete aux;
        }
    }
}

void pila::mostrar() {
    nodo *aux;
    if (tope== NULL)
        cout << "No hay elementos";  
    else {
        aux = tope;
        while(aux) {
            cout << aux->valor << " -> ";
    	    aux = aux->siguiente;
        }
    	cout << endl;
    }
}

void lista::crearCola(pnodo Cola[]) {
    for (int i = 1; i <= 5; i++) {
        string str;
        ifstream archivo;
        pnodo aux;
        aux = Cola[i - 1];
        std::stringstream ss1;
        ss1 << i;
        string num1 = ss1.str();
        archivo.open(("Archivos/Arch" + num1 + ".txt").c_str()); // Convertir a const char* con c_str()
        while (archivo >> str) {
            while (aux->siguiente != NULL) {
                aux = aux->siguiente;
            }
            aux->siguiente = new nodo(str);
        }
        aux->siguiente->siguiente = new nodo(")");
        archivo.close();
        str = "";
    }
}


void lista::mostrarExpresion(pnodo primerl) {
    pnodo aux;
    aux = primerl->siguiente;
    if (aux==NULL) {
        cout << "No hay elementos";
    } else {
        while (aux->siguiente!=NULL) {
            cout << aux->valor;
            aux = aux->siguiente;
        }
        cout << endl;
    }
}

void lista::mostrar() {
    nodo *aux;

    aux = primero;
    while(aux) {
    cout << aux->valor << " -> ";
    aux = aux->siguiente;
    }
    cout << endl;
}

string lista::guardar() {
    nodo *aux;
    string x;
    aux = primero;
    while (aux) {
        x += aux->valor + " "; // Concatena el valor actual a la cadena x
        aux = aux->siguiente;
    }
    //cout << x << endl; // Imprime la cadena x
    return x; // Devuelve la cadena x
}


void lista::insertarFinal(string v) {
    if (listaVacia())
        primero = new nodo(v);
    else {
        pnodo aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
            aux->siguiente=new nodo(v);
    }
}

void lista::crearPostfijo(pnodo primerl,int contador) {
    tabla TablaDentro, TablaFuera;
    TablaDentro.crearTablaDentro();
    TablaFuera.crearTablaFuera();
    nodo* aux;
    lista postfijo;
    aux = primerl->siguiente;
    lista* listaAux;
    pila pilaOperadores;
    Arbol miArbol;
    Nodo* raizArbolPtr = NULL;
    
	ofstream archivo("reportes.txt", std::ios::app); // Abre el archivo en modo de apéndice
	
	if (!archivo.is_open()) {
	    cerr << "No se pudo abrir el archivo." << endl;
	    return; 
	}

	archivo<<""<<endl;
	archivo<<""<<endl;
	archivo << "Reporte de archivo: "<<contador <<endl;
    while (aux->siguiente != NULL) {
        if (aux->valor == "+" || aux->valor == "-" || aux->valor == "*" || aux->valor == "/" || aux->valor == "^" || aux->valor == "(" || aux->valor == ")") {
            if (aux->valor == "(") {
                pilaOperadores.push(aux->valor);
            } else if (aux->valor == ")") {
                while (!pilaOperadores.pilaVacia() && pilaOperadores.tope->valor != "(") {
                    postfijo.insertarFinal(pilaOperadores.tope->valor);
                    miArbol.insertarNodo(pilaOperadores.tope->valor, raizArbolPtr);
                    pilaOperadores.pop();
                }
                pilaOperadores.pop();
            } else {
                int priorFuera = TablaFuera.buscarOP(aux->valor);
                
                cout << "afuera pila operadores: " << aux->valor << endl;
                archivo << "afuera pila operadores: "<<aux->valor <<endl;
                int priorDentro = TablaDentro.buscarOP(pilaOperadores.pilaVacia() ? "" : pilaOperadores.tope->valor);
                cout << "adentro pila numeros: " << aux->valor << endl;
                archivo << "adentro pila operadores: "<<aux->valor <<endl;

                if (priorFuera > priorDentro) {
                    pilaOperadores.push(aux->valor);
                    cout << "push a expresion: " << aux->valor << endl;
                } else {
                    while (!pilaOperadores.pilaVacia() && TablaDentro.buscarOP(pilaOperadores.tope->valor) >= priorFuera) {
                        postfijo.insertarFinal(pilaOperadores.tope->valor);
                        miArbol.insertarNodo(pilaOperadores.tope->valor, raizArbolPtr);
                        cout << "evalua " << pilaOperadores.tope->valor << endl;
                        pilaOperadores.pop();
                    }
                    pilaOperadores.push(aux->valor);
                }
            }
        } else {
            postfijo.insertarFinal(aux->valor);
            miArbol.insertarNodo(aux->valor, raizArbolPtr);
            cout << "Numero: " << aux->valor << endl;
        }
        aux = aux->siguiente;
    }

    while (!pilaOperadores.pilaVacia()) {
        postfijo.insertarFinal(pilaOperadores.tope->valor);
        miArbol.insertarNodo(pilaOperadores.tope->valor, raizArbolPtr);
        pilaOperadores.pop();
    }
    aux = postfijo.primero;
	cout<<""<<endl;
    pila PilaResultado;
    while (aux) {
        if (aux->valor == "+" || aux->valor == "-" || aux->valor == "*" || aux->valor == "/" || aux->valor == "^") {
            string op = aux->valor;
            float num2;
            std::stringstream(PilaResultado.tope->valor) >> num2;
            PilaResultado.pop();
            float num1;
            std::stringstream(PilaResultado.tope->valor) >> num1;
            PilaResultado.pop();

            std::stringstream ss;
            if (op == "+") {
                ss << num1 + num2;
            } else if (op == "-") {
                ss << num1 - num2;
            } else if (op == "*") {
                ss << num1 * num2;
            } else if (op == "/") {
                if (num2 == 0) {
                    cout << "No se puede dividir entre 0" << endl;
                    return;
                }
                ss << num1 / num2;
            } else if (op == "^") {
                ss << pow(num1, num2);
            }

            PilaResultado.push(ss.str());
            cout << "Resultado parcial: " << PilaResultado.tope->valor << endl; // Imprimir el resultado parcial
        } else {
            PilaResultado.push(aux->valor);
        }
        aux = aux->siguiente;
    }
    cout<<""<<endl;
    cout<<"resultado final: "<< PilaResultado.tope->valor<<endl;

	string postfixExpression = postfijo.guardar();
    cout << "" << endl;

    ExpressionTree tree(postfixExpression);
    
    cout<<"muestra de arbol"<<endl;
    cout<<""<<endl;
    tree.muestraAcostado();
    cout<<""<<endl;
    cout << "InOrden: ";
    tree.inOrden();
    cout << endl;

    cout << "PreOrden: ";
    tree.preOrden();
    cout << endl;

    cout << "PostOrden: ";
    tree.postOrden();
    cout << endl;
}












int main() {
    const char* nombreArchivo = "reportes.txt";

    if (std::remove(nombreArchivo) == 0) {
        //std::cout << "El archivo \"" << nombreArchivo << "\" ha sido borrado exitosamente." << std::endl;
    } else {
        //std::cerr << "Error al borrar el archivo \"" << nombreArchivo << "\"." << std::endl;
    }
    lista Lista;
    pnodo primerol1 = new nodo();
    pnodo primerol2 = new nodo();
    pnodo primerol3 = new nodo();
    pnodo primerol4 = new nodo();
    pnodo primerol5 = new nodo();
    
    pnodo Cola[5] = {primerol1,primerol2,primerol3,primerol4,primerol5};

    Lista.crearCola(Cola);

	
	for(int i =0; i<5; i++){
		if(i==0){
		}
		else{
			cout<<""<<endl;
			cout<<""<<endl;
			cout<<""<<endl;
			cout<<""<<endl;	
		}
		cout<<"---------------------------------------------------------------------------------"<<endl;
		cout<<"informacion de archivo: "<<i+1<<endl;
		cout<<""<<endl;
		cout<<"expresion: "<<endl;
		Lista.mostrarExpresion(Cola[i]);
		cout<<""<<endl;
		cout<<"analisis de postfijo:"<<endl;
		Lista.crearPostfijo(Cola[i], i+1);
	}

    return 0;
}
