	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <cctype>
	#include <set>
	#include <string> 
	#include <cstdlib> 
	
	using namespace std;
	
	class nodoAd {
	public:
	    nodoAd(const string& v) {
	        valor = v;
	        siguiente = NULL;
	        numCompras = 0; // Inicialmente, el administrador no tiene compras.
	    }
	
	    nodoAd(const string& v, nodoAd* signodoAd) {
	        valor = v;
	        siguiente = signodoAd;
	    }
	
	    int numCompras; // Agrega un campo para el n?mero de compras.
	
	private:
	    string valor;
	    nodoAd* siguiente;
	
	    friend class administrador;
	};
	
	
	typedef nodoAd* pnodoAd;
	
	class administrador {
	public:
	    administrador() { primero = NULL; }
	    ~administrador();
	
	    void agregarNodo(string v);
	    bool ArbolVacio() { return primero == NULL; }
	    void MostrarAd();
	    int cantNodos();
	    void CargarDesdeArchivoAd();
	    string ConsultarAdministradorPorCodigoAd(string codigo);
	    void administradorAd();
	    void AgregarAdministradorAd(string codigo, string nombre);
	    void ModificarNombre(string codigo, string nombre);
	    bool ExisteAd(string codigo);
	    string ObtenerContenidoComoString();
	    void agregarComprar(string code);
	    int stringAEnteroAd(const std::string &cadena);
	    string muestraCompradores();
	    string ObtenerContenidoAdministradors();
	    void BorrarPorCodigoAd(string codigo);
	    string intToString(int numero);
	
	private:
	    pnodoAd primero;
	};
	
	string administrador ::intToString(int numero) {
    if (numero == 0) {
        return "0";
    }

    std::string resultado = "";
    bool esNegativo = false;

    if (numero < 0) {
        esNegativo = true;
        numero = -numero;
    }

    while (numero > 0) {
        char digito = '0' + (numero % 10); // Obtén el dígito de la unidad
        resultado = digito + resultado;     // Agrega el dígito al principio de la cadena
        numero /= 10;                       // Elimina el dígito de la derecha
    }

    if (esNegativo) {
        resultado = "-" + resultado;  // Agrega el signo negativo si era un número negativo
    }

    return resultado;
}

	
	void administrador::BorrarPorCodigoAd(string codigo2){
	long long codigo = stringAEnteroAd(codigo2);

	
    if (ArbolVacio()) {
        return;
    }

    if (primero->valor.find(';') != string::npos) {
        int codigoArbol;
        istringstream(primero->valor.substr(0, primero->valor.find(';'))) >> codigoArbol;

        if (codigoArbol == codigo) {
            pnodoAd temp = primero;
            primero = primero->siguiente;
            delete temp;
            cout << "Administrador con codigo " << codigo << " eliminado." << endl;
            return;
        }
    }

    pnodoAd prev = primero;
    pnodoAd curr = primero->siguiente;

    while (curr) {
        size_t pos = curr->valor.find(';');
        if (pos != string::npos) {
            int codigoArbol;
            istringstream(curr->valor.substr(0, pos)) >> codigoArbol;

            if (codigoArbol == codigo) {
                prev->siguiente = curr->siguiente;
                delete curr;
                cout << "Administrador con codigo " << codigo << " eliminado." << endl;
                return;
            }
        }

        prev = curr;
        curr = curr->siguiente;
    }

    cout << "No se encontro un administrador con el codigo " << codigo << " en la lista." << endl;
}
	
	
	string administrador::ObtenerContenidoAdministradors() {
	    stringstream ss;
	    pnodoAd aux = primero;
	
	    while (aux) {
	        ss << aux->valor << " (" << aux->numCompras << " compras)" << " -> ";
	        aux = aux->siguiente;
	    }
	
	    return ss.str();
	}
	
	
	int administrador::stringAEnteroAd(const std::string &cadena) {
	    int resultado = 0;
	    int multiplicador = 1;
	
	    // Comprueba si la cadena representa un n?mero negativo
	    size_t indice = 0;
	    if (cadena[0] == '-') {
	        multiplicador = -1;
	        indice = 1; // Saltar el signo negativo
	    }
	
	    // Recorre la cadena y construye el n?mero entero
	    for (; indice < cadena.length(); ++indice) {
	        char digito = cadena[indice];
	        if (isdigit(digito)) {
	            int valorDigito = digito - '0';
	            resultado = resultado * 10 + valorDigito;
	        } else {
	            // Manejo de error si la cadena contiene caracteres no num?ricos
	            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
	            return 0;
	        }
	    }
	
	    return resultado * multiplicador;
	}
	
	string administrador::ObtenerContenidoComoString() {
	        std::stringstream ss;
	        nodoAd* aux;
		   if (primero== NULL)
		       cout << "No hay elementos AQUI";  
		   else
		   {
		   		aux = primero;
				while(aux) 
				{
				    ss << aux->valor << "-> ";
				    aux = aux->siguiente;
				}
				cout << endl;
		   }
	        return ss.str();
	}
	
	void administrador::ModificarNombre(string codigo2, string nombre2) {
	    int code = stringAEnteroAd(codigo2);

	    string newName = nombre2;

	    pnodoAd aux = primero;
	
	    while (aux) {
	        size_t pos = aux->valor.find(';');
	        if (pos != string::npos) {
	            int codigoEnArbol;
	            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;
	
	            if (codigoEnArbol == code) {
				    std::stringstream sscode;
				    sscode << code;
				
				    string num1 = sscode.str();          	
	            	
	                aux->valor = num1 + ";" + newName + ";" + "0";
	                cout << "Nombre del pais modificado exitosamente." << endl;
	                return;
	            }
	        }
	        aux = aux->siguiente;
	    }
	
	    cout << "No se encontr? un pa?s con el c?digo proporcionado." << endl;
	}
	

	void administrador::AgregarAdministradorAd(string codigo2, string nombre) {
	    /*cout << "Ingrese la c?dula del administrador (parte entera): ";
	    int codigo;
	    cin >> codigo;
	    cin.ignore();  // Limpia el buffer del salto de l?nea
	
	    cout << "Ingrese el nombre del administrador: ";
	    string nombre;
	    getline(cin, nombre);*/
		int codigo = stringAEnteroAd(codigo2);
	    // Verificar si el c?digo ya existe en la lista
	    bool codigoExistente = false;
	    pnodoAd aux = primero;
	    while (aux) {
	        size_t pos = aux->valor.find(';');
	        if (pos != string::npos) {
	            int codigoEnArbol;
	            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;
				
	            if (codigoEnArbol == codigo) {
	                codigoExistente = true;
	                cout << "Error: Ya existe un administrador con la misma c?dula " << codigo << "." << endl;
	                break;
	            }
	        }
	        aux = aux->siguiente;
	    }
	
	    if (!codigoExistente) {
	        // Usar ostringstream para convertir el entero a cadena
	        ostringstream ss;
	        ss << codigo;
	        string codigoStr = ss.str();
	
	        string pais = codigo2 + ";" + nombre+";"+"0";
	        agregarNodo(pais);
	        cout << "Administrador agregado exitosamente." << endl;
	    }
	}
	
	
	string administrador::ConsultarAdministradorPorCodigoAd(string codigo2) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return ""; 
    }
    int codigo = stringAEnteroAd(codigo2);
    pnodoAd aux = primero;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == codigo) {
                return aux->valor; 
            }
        }
        aux = aux->siguiente;
    }

    
    return "No se encontró un administrador con el código " + codigo2;
}

	
	void administrador::CargarDesdeArchivoAd()
	{
	    ifstream archivo("Administradores.txt");
	    if (!archivo.is_open()) {
	        cout << "No se pudo abrir el archivo." << endl;
	        return;
	    }
	
	    string linea;
	    while (getline(archivo, linea)) {
	        size_t pos = linea.find(';');
	        if (pos != string::npos) {
	            string codigo = linea.substr(0, pos);
	            string nombre = linea.substr(pos + 1);
	            
	            bool existe = false;
	            pnodoAd aux = primero;
	            
	            while (aux) {
	                size_t posAux = aux->valor.find(';');
	                if (posAux != string::npos) {
	                    string codigoEnArbol = aux->valor.substr(0, posAux);
	                    
	                    if (codigoEnArbol == codigo) {
	                        existe = true;
	                        cout << "Administrador con cedula:  " << codigo << " ya existe en el arbol." << endl;
	                        break;
	                    }
	                }
	                aux = aux->siguiente;
	            }
	            
	            if (!existe) {
	                agregarNodo(codigo + ";" + nombre + ";" + "0");
	                cout << "Administrador con cedula: " << codigo << " agregado exitosamente." << endl;
	            }
	        }
	    }
	
	    archivo.close();
	}
	
	administrador::~administrador() {
	    nodoAd* aux;
	
	    while (primero) {
	        aux = primero;
	        primero = primero->siguiente;
	        delete aux;
	    }
	    primero = NULL;
	}
	
	int administrador::cantNodos(){
	    int cont=0;
	
	    pnodoAd aux= primero;
	    if(ArbolVacio()){
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
	
	void administrador::agregarNodo(string v)//76
	{
	   if (ArbolVacio())
	     primero = new nodoAd(v);
	   else
	      { 
	       pnodoAd aux = primero;
	        while ( aux->siguiente != NULL)
	         aux= aux->siguiente;
	        pnodoAd nuevo=new nodoAd(v);
	        aux->siguiente=nuevo;
	      }    
	}
	     
	void administrador::MostrarAd()
	
	{
	   nodoAd *aux;
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
	
	bool administrador::ExisteAd(string codigo) {
	    if (ArbolVacio()) {
	        cout << "El arbol esta vacio" << endl;
	        return false;
	    }
	    
	    pnodoAd aux = primero;
	    bool encontrado = false;
	    int i = 0;
	
	    while (i < cantNodos()) {
	        if (aux->valor.find(codigo) != string::npos) {
	            encontrado = true;
	            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
	            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
	            return true;
	            break;
	        }
	        aux = aux->siguiente;
	        i ++;
	    }
	
	    if (!encontrado) {
	        return false;
	    }
	}
	
	void administrador::agregarComprar(string code) {
	    string codigosBuscados = code;
	    pnodoAd aux = primero;
	    bool encontrado = false;
	    int i = 0;
	
		while (i <= cantNodos()) {
	        if (aux->valor.find(codigosBuscados) != string::npos) {
	            encontrado = true;
	            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
	            if (posicionUltimoPuntoComa != string::npos) {
	                size_t posicionNumero = posicionUltimoPuntoComa + 1;
	                std::string numeroStr = aux->valor.substr(posicionNumero);
	                int numero = stringAEnteroAd(numeroStr);
	                numero++;
	                
					std::stringstream ss1;
	    			ss1 << numero;
	
					string num1 = ss1.str();
	    
	    
	                
	                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
	                aux->valor = nuevoValor;
	            } else {
	                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
	            }
	            break;
	        }
	        aux = aux->siguiente;
	        i++;
	    }
	
	    if (!encontrado) {
	        cout << "No se encontraron los c?digos en el arbol." << endl;
	    }
	}
	
	string administrador::muestraCompradores() {
	    string compradores = "";
	    pnodoAd aux = primero;
	
	    while (aux) {
	        size_t pos = aux->valor.find(';');
	        if (pos != string::npos) {
	            int codigoEnArbol;
	            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;
	
	            size_t lastPos = aux->valor.find_last_of(';');
	            if (lastPos != string::npos) {
	                string nombre = aux->valor.substr(lastPos + 1);
	                if (codigoEnArbol % 10 != 0) {
	                    stringstream ss;
	                    ss << codigoEnArbol;
	                    compradores += ss.str() + ";" + nombre + "\n";
	                }
	            }
	        }
	        aux = aux->siguiente;
	    }
	
	    return compradores;
	}
	
	

	
	class nodoCl {
	public:
	    nodoCl(const string& v) {
	        valor = v;
	        siguiente = NULL;
	        numCompras = 0; // Inicialmente, el cliente no tiene compras.
	    }
	
	    nodoCl(const string& v, nodoCl* signodoCl) {
	        valor = v;
	        siguiente = signodoCl;
	    }
	
	    int numCompras; // Agrega un campo para el n?mero de compras.
	
	private:
	    string valor;
	    nodoCl* siguiente;
	
	    friend class cliente;
	};
	
	
	typedef nodoCl* pnodoCl;
	
	class cliente {
	public:
	    cliente() { primero = NULL; }
	    ~cliente();
	
	    void agregarNodo(string v);
	    bool ArbolVacio() { return primero == NULL; }
	    void MostrarCl();
	    int cantNodos();
	    void CargarDesdeArchivoCl();
	    string ConsultarClientePorCodigoCl(string codigo);
	    void clienteCl();
	    void AgregarClienteCl(string codigo, string nombre);
	    void ModificarNombreCL(string codigo, string nombre);
	    bool ExisteCl(string codigo);
	    string ObtenerContenidoComoString();
	    void agregarComprar(string code);
	    int stringAEnteroCl(const std::string &cadena);
	    string muestraCompradores();
	    string ObtenerContenidoClientes();
	    void BorrarPorCodigoCl(string codigo);
	    string intToString(int numero);
	
	private:
	    pnodoCl primero;
	};
	
	string cliente ::intToString(int numero) {
    if (numero == 0) {
        return "0";
    }

    std::string resultado = "";
    bool esNegativo = false;

    if (numero < 0) {
        esNegativo = true;
        numero = -numero;
    }

    while (numero > 0) {
        char digito = '0' + (numero % 10); // Obtén el dígito de la unidad
        resultado = digito + resultado;     // Agrega el dígito al principio de la cadena
        numero /= 10;                       // Elimina el dígito de la derecha
    }

    if (esNegativo) {
        resultado = "-" + resultado;  // Agrega el signo negativo si era un número negativo
    }

    return resultado;
}

	
	void cliente::BorrarPorCodigoCl(string codigo2){
	long long codigo = stringAEnteroCl(codigo2);

	
    if (ArbolVacio()) {
        return;
    }

    if (primero->valor.find(';') != string::npos) {
        int codigoArbol;
        istringstream(primero->valor.substr(0, primero->valor.find(';'))) >> codigoArbol;

        if (codigoArbol == codigo) {
            pnodoCl temp = primero;
            primero = primero->siguiente;
            delete temp;
            cout << "Cliente con codigo " << codigo << " eliminado." << endl;
            return;
        }
    }

    pnodoCl prev = primero;
    pnodoCl curr = primero->siguiente;

    while (curr) {
        size_t pos = curr->valor.find(';');
        if (pos != string::npos) {
            int codigoArbol;
            istringstream(curr->valor.substr(0, pos)) >> codigoArbol;

            if (codigoArbol == codigo) {
                prev->siguiente = curr->siguiente;
                delete curr;
                cout << "Cliente con codigo " << codigo << " eliminado." << endl;
                return;
            }
        }

        prev = curr;
        curr = curr->siguiente;
    }

    cout << "No se encontro un cliente con el codigo " << codigo << " en la lista." << endl;
}
	
	
	string cliente::ObtenerContenidoClientes() {
	    stringstream ss;
	    pnodoCl aux = primero;
	
	    while (aux) {
	        ss << aux->valor << " (" << aux->numCompras << " compras)" << " -> ";
	        aux = aux->siguiente;
	    }
	
	    return ss.str();
	}
	
	
	int cliente::stringAEnteroCl(const std::string &cadena) {
	    int resultado = 0;
	    int multiplicador = 1;
	
	    // Comprueba si la cadena representa un n?mero negativo
	    size_t indice = 0;
	    if (cadena[0] == '-') {
	        multiplicador = -1;
	        indice = 1; // Saltar el signo negativo
	    }
	
	    // Recorre la cadena y construye el n?mero entero
	    for (; indice < cadena.length(); ++indice) {
	        char digito = cadena[indice];
	        if (isdigit(digito)) {
	            int valorDigito = digito - '0';
	            resultado = resultado * 10 + valorDigito;
	        } else {
	            // Manejo de error si la cadena contiene caracteres no num?ricos
	            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
	            return 0;
	        }
	    }
	
	    return resultado * multiplicador;
	}
	
	string cliente::ObtenerContenidoComoString() {
	        std::stringstream ss;
	        nodoCl* aux;
		   if (primero== NULL)
		       cout << "No hay elementos AQUI";  
		   else
		   {
		   		aux = primero;
				while(aux) 
				{
				    ss << aux->valor << "-> ";
				    aux = aux->siguiente;
				}
				cout << endl;
		   }
	        return ss.str();
	}
	
	void cliente::ModificarNombreCL(string codigo2, string nombre2) {
	    int code = stringAEnteroCl(codigo2);

	    string newName = nombre2;

	    pnodoCl aux = primero;
	
	    while (aux) {
	        size_t pos = aux->valor.find(';');
	        if (pos != string::npos) {
	            int codigoEnArbol;
	            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;
	
	            if (codigoEnArbol == code) {
				    std::stringstream sscode;
				    sscode << code;
				
				    string num1 = sscode.str();          	
	            	
	                aux->valor = num1 + ";" + newName + ";" + "0";
	                cout << "Nombre del pais modificado exitosamente." << endl;
	                return;
	            }
	        }
	        aux = aux->siguiente;
	    }
	
	    cout << "No se encontr? un pa?s con el c?digo proporcionado." << endl;
	}
	

	void cliente::AgregarClienteCl(string codigo2, string nombre) {
	    /*cout << "Ingrese la c?dula del cliente (parte entera): ";
	    int codigo;
	    cin >> codigo;
	    cin.ignore();  // Limpia el buffer del salto de l?nea
	
	    cout << "Ingrese el nombre del cliente: ";
	    string nombre;
	    getline(cin, nombre);*/
		int codigo = stringAEnteroCl(codigo2);
	    // Verificar si el c?digo ya existe en la lista
	    bool codigoExistente = false;
	    pnodoCl aux = primero;
	    while (aux) {
	        size_t pos = aux->valor.find(';');
	        if (pos != string::npos) {
	            int codigoEnArbol;
	            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;
				
	            if (codigoEnArbol == codigo) {
	                codigoExistente = true;
	                cout << "Error: Ya existe un cliente con la misma c?dula " << codigo << "." << endl;
	                break;
	            }
	        }
	        aux = aux->siguiente;
	    }
	
	    if (!codigoExistente) {
	        // Usar ostringstream para convertir el entero a cadena
	        ostringstream ss;
	        ss << codigo;
	        string codigoStr = ss.str();
	
	        string pais = codigo2 + ";" + nombre+";"+"0";
	        agregarNodo(pais);
	        cout << "Cliente agregado exitosamente." << endl;
	    }
	}
	
	
	string cliente::ConsultarClientePorCodigoCl(string codigo2) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return ""; 
    }
    int codigo = stringAEnteroCl(codigo2);
    pnodoCl aux = primero;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == codigo) {
                return aux->valor; 
            }
        }
        aux = aux->siguiente;
    }

    
    return "No se encontró un cliente con el código " + codigo2;
}

	
	void cliente::CargarDesdeArchivoCl()
	{
	    ifstream archivo("Clientes.txt");
	    if (!archivo.is_open()) {
	        cout << "No se pudo abrir el archivo." << endl;
	        return;
	    }
	
	    string linea;
	    while (getline(archivo, linea)) {
	        size_t pos = linea.find(';');
	        if (pos != string::npos) {
	            string codigo = linea.substr(0, pos);
	            string nombre = linea.substr(pos + 1);
	            
	            bool existe = false;
	            pnodoCl aux = primero;
	            
	            while (aux) {
	                size_t posAux = aux->valor.find(';');
	                if (posAux != string::npos) {
	                    string codigoEnArbol = aux->valor.substr(0, posAux);
	                    
	                    if (codigoEnArbol == codigo) {
	                        existe = true;
	                        cout << "Cliente con cedula:  " << codigo << " ya existe en el arbol." << endl;
	                        break;
	                    }
	                }
	                aux = aux->siguiente;
	            }
	            
	            if (!existe) {
	                agregarNodo(codigo + ";" + nombre + ";" + "0");
	                cout << "Cliente con cedula: " << codigo << " agregado exitosamente." << endl;
	            }
	        }
	    }
	
	    archivo.close();
	}
	
	cliente::~cliente() {
	    nodoCl* aux;
	
	    while (primero) {
	        aux = primero;
	        primero = primero->siguiente;
	        delete aux;
	    }
	    primero = NULL;
	}
	
	int cliente::cantNodos(){
	    int cont=0;
	
	    pnodoCl aux= primero;
	    if(ArbolVacio()){
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
	
	void cliente::agregarNodo(string v)//76
	{
	   if (ArbolVacio())
	     primero = new nodoCl(v);
	   else
	      { 
	       pnodoCl aux = primero;
	        while ( aux->siguiente != NULL)
	         aux= aux->siguiente;
	        pnodoCl nuevo=new nodoCl(v);
	        aux->siguiente=nuevo;
	      }    
	}
	     
	void cliente::MostrarCl()
	
	{
	   nodoCl *aux;
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
	
	bool cliente::ExisteCl(string codigo) {
	    if (ArbolVacio()) {
	        cout << "El arbol esta vacio" << endl;
	        return false;
	    }
	    
	    pnodoCl aux = primero;
	    bool encontrado = false;
	    int i = 0;
	
	    while (i < cantNodos()) {
	        if (aux->valor.find(codigo) != string::npos) {
	            encontrado = true;
	            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
	            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
	            return true;
	            break;
	        }
	        aux = aux->siguiente;
	        i ++;
	    }
	
	    if (!encontrado) {
	        return false;
	    }
	}
	
	void cliente::agregarComprar(string code) {
	    string codigosBuscados = code;
	    pnodoCl aux = primero;
	    bool encontrado = false;
	    int i = 0;
	
		while (i <= cantNodos()) {
	        if (aux->valor.find(codigosBuscados) != string::npos) {
	            encontrado = true;
	            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
	            if (posicionUltimoPuntoComa != string::npos) {
	                size_t posicionNumero = posicionUltimoPuntoComa + 1;
	                std::string numeroStr = aux->valor.substr(posicionNumero);
	                int numero = stringAEnteroCl(numeroStr);
	                numero++;
	                
					std::stringstream ss1;
	    			ss1 << numero;
	
					string num1 = ss1.str();
	    
	    
	                
	                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
	                aux->valor = nuevoValor;
	            } else {
	                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
	            }
	            break;
	        }
	        aux = aux->siguiente;
	        i++;
	    }
	
	    if (!encontrado) {
	        cout << "No se encontraron los c?digos en el arbol." << endl;
	    }
	}
	
	string cliente::muestraCompradores() {
	    string compradores = "";
	    pnodoCl aux = primero;
	
	    while (aux) {
	        size_t pos = aux->valor.find(';');
	        if (pos != string::npos) {
	            int codigoEnArbol;
	            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;
	
	            size_t lastPos = aux->valor.find_last_of(';');
	            if (lastPos != string::npos) {
	                string nombre = aux->valor.substr(lastPos + 1);
	                if (codigoEnArbol % 10 != 0) {
	                    stringstream ss;
	                    ss << codigoEnArbol;
	                    compradores += ss.str() + ";" + nombre + "\n";
	                }
	            }
	        }
	        aux = aux->siguiente;
	    }
	
	    return compradores;
	}
	



class nodo {
public:
    nodo(string v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodo(string v, nodo* signodo)
    {
        valor = v;
        siguiente = signodo;
    }

private:
    string valor;
    nodo* siguiente;
    nodo* anterior;

    friend class ArbolPais;
};

typedef nodo* pnodo;

class ArbolPais {
public:
    ArbolPais() { primero = NULL; }
    ~ArbolPais();

    void agregarNodo(string v);
    bool ArbolVacio() { return primero == NULL; }
    void Mostrar();
    int cantNodos();
    void Paises();
    void CargarDesdeArchivo();
    void AgregarPais(string codigo, string nombre);
   	string ConsultarPaisPorCodigo(string codigo);
    void ModificarNombre(string codigo, string nombre);
    bool Existe(int codigo);
    string ObtenerContenidoComoString();
    int stringAEnteroCl(const std::string &cadena);
    void BorrarPorCodigo(string codigo2);

private:
    pnodo primero;
};

void ArbolPais::BorrarPorCodigo(string codigo2){
	long long codigo = stringAEnteroCl(codigo2);

	
    if (ArbolVacio()) {
        return;
    }

    if (primero->valor.find(';') != string::npos) {
        int codigoArbol;
        istringstream(primero->valor.substr(0, primero->valor.find(';'))) >> codigoArbol;

        if (codigoArbol == codigo) {
            pnodo temp = primero;
            primero = primero->siguiente;
            delete temp;
            cout << "Cliente con codigo " << codigo << " eliminado." << endl;
            return;
        }
    }

    pnodo prev = primero;
    pnodo curr = primero->siguiente;

    while (curr) {
        size_t pos = curr->valor.find(';');
        if (pos != string::npos) {
            int codigoArbol;
            istringstream(curr->valor.substr(0, pos)) >> codigoArbol;

            if (codigoArbol == codigo) {
                prev->siguiente = curr->siguiente;
                delete curr;
                cout << "Cliente con codigo " << codigo << " eliminado." << endl;
                return;
            }
        }

        prev = curr;
        curr = curr->siguiente;
    }

    cout << "No se encontro un cliente con el codigo " << codigo << " en la lista." << endl;
}

int ArbolPais::stringAEnteroCl(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

string ArbolPais::ObtenerContenidoComoString() {
        std::stringstream ss;
        nodo* aux = primero;
        
        while (aux) {
            ss << aux->valor << "-> ";
            aux = aux->siguiente;
        }
        
        return ss.str();
}

void ArbolPais::ModificarNombre(string codigo2, string nombre2) {
	
    int code = stringAEnteroCl(codigo2);

    string newName = nombre2;

    pnodo aux = primero;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == code) {
			    std::stringstream sscode;
			    sscode << code;
			
			    string num1 = sscode.str();          	
            	
                aux->valor = num1 + ";" + newName;
                cout << "Nombre del pais modificado exitosamente." << endl;
                return;
            }
        }
        aux = aux->siguiente;
    }

    cout << "No se encontr? un pa?s con el c?digo proporcionado." << endl;
}

string ArbolPais::ConsultarPaisPorCodigo(string codigo2) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return "";
    }


	int codigo = stringAEnteroCl(codigo2);
    pnodo aux = primero;
    bool encontrado = false;

    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == codigo) {
                encontrado = true;
                return aux->valor;
                break;
                
            }
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontro un pais con el codigo " << codigo << " en el arbol." << endl;
        return "";
    }
}

void ArbolPais::AgregarPais(string codigo2, string nombre)
{
	int codigo = stringAEnteroCl(codigo2);

    bool codigoExistente = false;
    pnodo aux = primero;
    while (aux) {
        size_t pos = aux->valor.find(';');
        if (pos != string::npos) {
            int codigoEnArbol;
            istringstream(aux->valor.substr(0, pos)) >> codigoEnArbol;

            if (codigoEnArbol == codigo) {
                codigoExistente = true;
                cout << "Error: Ya existe un pais con el codigo " << codigo << "." << endl;
                break;
            }
        }
        aux = aux->siguiente;
    }

    if (!codigoExistente) {
        // Usar ostringstream para convertir el entero a cadena
        ostringstream ss;
        ss << codigo;
        string codigoStr = ss.str();

        string pais = codigoStr + ";" + nombre;
        agregarNodo(pais);
        cout << "Pais agregado exitosamente." << endl;
    }
}

void ArbolPais::CargarDesdeArchivo()
{
    ifstream archivo("Paises.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(';');
        if (pos != string::npos) {
            string codigo = linea.substr(0, pos);
            string nombre = linea.substr(pos + 1);
            
            bool existe = false;
            pnodo aux = primero;
            
            while (aux) {
                size_t posAux = aux->valor.find(';');
                if (posAux != string::npos) {
                    string codigoEnArbol = aux->valor.substr(0, posAux);
                    
                    if (codigoEnArbol == codigo) {
                        existe = true;
                        cout << "Pais con codigo " << codigo << " ya existe en el arbol." << endl;
                        break;
                    }
                }
                aux = aux->siguiente;
            }
            
            if (!existe) {
                agregarNodo(codigo + ";" + nombre);
            }
        }
    }

    archivo.close();
}

ArbolPais::~ArbolPais()
{
   pnodo aux;
   
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   primero=NULL;
}

int ArbolPais::cantNodos(){
    int cont=0;

    pnodo aux;
    aux = primero;
    if(ArbolVacio()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
    
}

void ArbolPais::agregarNodo(string v)
{
   if (ArbolVacio())
   {
   
     primero = new nodo(v);
       
   }
   else
     { pnodo aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodo(v);
        aux->siguiente->anterior=aux;       
      }    
}
   

void ArbolPais::Mostrar()
{
   nodo *aux;
   
   aux = primero;
   while(aux) {
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

bool ArbolPais::Existe(int codigo) {
    if (ArbolVacio()) {
        cout << "El arbol ABB esta vacio" << endl;
        return false;
    }

    std::stringstream ss1;
    ss1 << codigo;
    string num1 = ss1.str();
    string codigosBuscados = num1 + ";";
    pnodo aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        return false;
    }
}


	





// CIUDADES
class nodoCIU {
public:
    nodoCIU(const string &v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoCIU(const string &v, nodoCIU *signodoCIU)
    {
        valor = v;
        siguiente = signodoCIU;
    }

private:
    string valor;
    nodoCIU *siguiente;
    nodoCIU *anterior;

    friend class ArbolCiudad;
};
typedef nodoCIU *pnodoCIU;

class ArbolCiudad {
public:
    ArbolCiudad() { primero = NULL; }
    ~ArbolCiudad();

    void agregarNodoIn(string v);
    void agregarNodo(string v);
    void InsertarPos(string v, int pos);
    bool ArbolVacio() { return primero == NULL; }
    void Imprimir();
    void MostrarCIU();
    int cantNodos();
    void CargarDesdeArchivoCIU();
    string ComprobacionCIU(string pais, string ciudad);
    void AgregarCIU(ArbolPais & arbolPais, string pais, string ciudad, string nombre);
    void ModificarNombreCIU(string pais, string ciudad, string nombre);
    bool ExisteCIU(string codigo);
    string MostrarArbolCiudadesPorPais();
    string GuardarArbolCiudades();
    string ObtenerContenidoComoString();
    int stringAEnteroCl(const std::string &cadena);
    void BorrarPorCodigosCIU(string pais, string ciudad);
    void BorrarFinal();
    void BorrarInicio();
private:
    pnodoCIU primero;
};

int ArbolCiudad::stringAEnteroCl(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolCiudad::BorrarPorCodigosCIU(string pais, string ciudad) {
    if (ArbolVacio()) {
        cout << "La lista esta vac?a." << endl;
        return;
    }
    
    int codigo1 =stringAEnteroCl(pais);
    int codigo2 = stringAEnteroCl(ciudad);
    
    std::stringstream ss1, ss2;
    ss1 << codigo1;
    ss2 << codigo2;

    string num1 = ss1.str();
    string num2 = ss2.str();
 

    string codigosBuscados = num1 + ";" + num2;
    pnodoCIU aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            if (aux == primero) {
                BorrarInicio();
            } else if (aux->siguiente == primero) {
                BorrarFinal();
            } else {
                pnodoCIU temp = aux;
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                aux = aux->siguiente;
                delete temp;
            }

            cout << "nodoCIU con los codigos " << codigosBuscados << " borrado exitosamente." << endl;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        cout << "No se encontraron los codigos en la lista." << endl;
    }
}

void ArbolCiudad::BorrarFinal()
{
    if (ArbolVacio())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoCIU temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoCIU aux = primero; //1
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoCIU temp = aux->siguiente;//2
         aux->siguiente= primero;//3
         primero->anterior=aux;//4
         delete temp;//5
      }
    }
}

void ArbolCiudad::BorrarInicio()
{
    if (ArbolVacio())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoCIU temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoCIU aux = primero->anterior;//1
        pnodoCIU temp= primero;//2
        aux->siguiente=primero->siguiente;//3
        primero=primero->siguiente; //4
        primero->anterior=aux;//5
        delete temp;//6
      }
    }
}


string ArbolCiudad::ObtenerContenidoComoString() {
    if (ArbolVacio()) {
        return "Arbol vacio";
    }

    std::stringstream ss;
    pnodoCIU aux = primero;

    do {
        ss << aux->valor << " -> ";
        aux = aux->siguiente;
    } while (aux != primero);

    return ss.str();
}

string ArbolCiudad::GuardarArbolCiudades() {
    string memoria;

    if (ArbolVacio()) {
        cout << "El arbol de Ciudades esta vacio." << endl;
        return "Arbol vacio";
    }

    pnodoCIU aux = primero;
    int i = 0;

    while (i < cantNodos()) {
        memoria += aux->valor + "->";
        aux = aux->siguiente;
        i++;
    }
    
    // Agregar el ?ltimo elemento (para que no quede un "; //" extra al final)
    memoria += aux->valor;

    return memoria;
}


string ArbolCiudad::MostrarArbolCiudadesPorPais() {
	cout<<"digite el codigo de pais a buscar"<<endl;
	string codigoPais;
	cin >> codigoPais;
	string memoria;
    if (ArbolVacio()) {
        cout << "El arbol de Ciudades esta vacio." << endl;
        return "Arbol vacio";
    }

    pnodoCIU aux = primero;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigoPais) != string::npos) {
            cout << aux->valor << endl;
            memoria += aux -> valor + "; // ";
        }
        aux = aux->siguiente;
        i++;
    }
    
    return memoria;
}


void ArbolCiudad::ModificarNombreCIU(string pais, string ciudad, string nombre) {
    if (ArbolVacio()) {
        cout << "El arbol AVL esta vacio" << endl;
        return;
    }

    int codigo1 = stringAEnteroCl(pais);
    int codigo2 = stringAEnteroCl(ciudad);

    std::stringstream ss1, ss2;
    ss1 << codigo1;
    ss2 << codigo2;

    string num1 = ss1.str();
    string num2 = ss2.str();

    string codigosBuscados = num1 + ";" + num2;
    pnodoCIU aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			string newName = nombre;
			
			string modificar = codigosBuscados + ";" + newName;
			aux -> valor = modificar;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol" << endl;
    }

}

void ArbolCiudad::AgregarCIU(ArbolPais & arbolPais, string pais, string ciudad, string nombre){
	int NumPais = stringAEnteroCl(pais);
	if(arbolPais.Existe(NumPais)){
		int codigoArbolCiudad = stringAEnteroCl(ciudad);
		
	    std::stringstream ss1,ss2;
	    ss1 << NumPais;
	    ss2 << codigoArbolCiudad;
	    string num1 = ss1.str();
	    string num2 = ss2.str();
	    
		string NombreNuevo = nombre;
	
		string NuevoValor = num1 + ";" + num2 + ";" + NombreNuevo;
		agregarNodo(NuevoValor);
	
	}else{
		cout<<"el pais no existe, No se agrega"<<endl;
	}
}


string ArbolCiudad::ComprobacionCIU(string pais, string ciudad) {
    if (ArbolVacio()) {
        cout << "El arbol AVL esta vacio" << endl;
        return "";
    }

    int codigo1 = stringAEnteroCl(pais);
    int codigo2 = stringAEnteroCl(ciudad);

    std::stringstream ss1, ss2;
    ss1 << codigo1;
    ss2 << codigo2;

    string num1 = ss1.str();
    string num2 = ss2.str();

    string codigosBuscados = num1 + ";" + num2;
    pnodoCIU aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;

            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
			return aux->valor;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol." << endl;
        return "";
    }
}


void ArbolCiudad::CargarDesdeArchivoCIU() {
    set<string> numero2_set;  

    ifstream archivo("Ciudades.txt");
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
                agregarNodo(nuevo_valor);
            }
            else
            {
                cout << "Advertencia: NUMERO debe ser diferente a los otros NUMERO anteriores." << endl;
            }
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
                
ArbolCiudad::~ArbolCiudad()
{
   pnodoCIU aux;
   pnodoCIU temp;
   
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
                        
int ArbolCiudad::cantNodos() 
{
    int cont=0;

    pnodoCIU aux = primero->siguiente;
    if(ArbolVacio())
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

void ArbolCiudad::agregarNodo(string v)
{
   if (ArbolVacio())
     {
     primero = new nodoCIU(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoCIU nuevo = new nodoCIU(v);//1
     nuevo->anterior = primero->anterior;//2
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}
 
void ArbolCiudad::MostrarCIU()
{
   pnodoCIU aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;
} 

bool ArbolCiudad::ExisteCIU(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoCIU aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        return false;
    }
}












//clase ArbolRestaurante
class nodoRE {
public:
    nodoRE(const string &v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoRE(const string &v, nodoRE *signodoRE)
    {
        valor = v;
        siguiente = signodoRE;
    }

private:
    string valor;
    nodoRE *siguiente;
    nodoRE *anterior;

    friend class ArbolRestaurante;
};
typedef nodoRE *pnodoRE;

class ArbolRestaurante {
public:
    ArbolRestaurante() { primero = NULL; }
    ~ArbolRestaurante();

    void agregarNodoIn(string v);
    void agregarNodo(string v);
    void InsertarPos(string v, int pos);
    bool ArbolVacio() { return primero == NULL; }
    void Imprimir();
    void MostrarRE();
    int cantNodos();
    void CargarDesdeArchivoRE();
    string ComprobacionRE(string pais, string ciudad, string nombre);
    void ModificarNombreRE(string pais, string ciudad, string restaurante, string nombre);
    void agregarRE(ArbolCiudad & arbolCiudad, string pais, string ciudad, string restaurante, string nombre);
    bool ExisteRE(string codigo);
    string MostrarArbolRestaurantesPorArbolCiudad();
    int stringAEnteroRE(const std::string &cadena);
    string EncontrarValorMayorPedido();
    string GuardarInformacionRestaurantes();
    string ObtenerContenidoComoString();
    int stringAEnteroCl(const std::string &cadena);
    void BorrarPorCodigosRE(string pais, string ciudad, string restaurante);
    void BorrarFinal();
    void BorrarInicio();
    
private:
    pnodoRE primero;
};

int ArbolRestaurante::stringAEnteroCl(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolRestaurante::BorrarPorCodigosRE(string pais, string ciudad, string restaurante) {
    if (ArbolVacio()) {
        cout << "arbol vacio" << endl;
        return;
    }

    string codigosBuscados = pais + ";" + ciudad + ";" + restaurante;
    pnodoRE aux = primero;
    pnodoRE nodoAEliminar = NULL;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            nodoAEliminar = aux;
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (encontrado) {
        if (nodoAEliminar == primero) {
            BorrarInicio();
        } else if (nodoAEliminar->siguiente == primero) {
            BorrarFinal();
        } else {
            nodoAEliminar->anterior->siguiente = nodoAEliminar->siguiente;
            nodoAEliminar->siguiente->anterior = nodoAEliminar->anterior;
            delete nodoAEliminar;
        }

        cout << "nodoRE con los c?digos " << codigosBuscados << " borrado exitosamente." << endl;
    } else {
        cout << "No encontrado" << endl;
    }
}


void ArbolRestaurante::BorrarFinal()
{
    if (ArbolVacio())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoRE temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoRE aux = primero; //1
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoRE temp = aux->siguiente;//2
         aux->siguiente= primero;//3
         primero->anterior=aux;//4
         delete temp;//5
      }
    }
}

void ArbolRestaurante::BorrarInicio()
{
    if (ArbolVacio())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoRE temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoRE aux = primero->anterior;//1
        pnodoRE temp= primero;//2
        aux->siguiente=primero->siguiente;//3
        primero=primero->siguiente; //4
        primero->anterior=aux;//5
        delete temp;//6
      }
    }
}


string ArbolRestaurante::ObtenerContenidoComoString() {
    if (ArbolVacio()) {
        return "Arbol vacio";
    }

    std::stringstream ss;
    pnodoRE aux = primero;

    do {
        ss << aux->valor << " -> ";
        aux = aux->siguiente;
    } while (aux != primero);

    return ss.str();
}

string ArbolRestaurante::GuardarInformacionRestaurantes() {
    string memoria;

    if (ArbolVacio()) {
        cout << "El árbol de Restaurantes está vacío." << endl;
        return "Árbol vacío";
    }

    pnodoRE aux = primero;
    int i = 0;

    while (i < cantNodos()) {
        memoria += aux->valor + "->";
        aux = aux->siguiente;
        i++;
    }

    // Agregar el último elemento (para que no quede un "; //" extra al final)
    memoria += aux->valor;

    return memoria;
}

string ArbolRestaurante::EncontrarValorMayorPedido() {
    if (ArbolVacio()) {
        cout << "El arbol de Restaurantes esta vacio." << endl;
        return "lista vacia";
    }

    pnodoRE aux = primero;
    int valorMayor = -1;  
    pnodoRE nodoMayor = NULL;  

    while (aux->siguiente != primero) {
        size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
        string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
        int numeroPedido = stringAEnteroRE(pedidoStr);

        if (numeroPedido > valorMayor) {
            valorMayor = numeroPedido;
            nodoMayor = aux;
        }

        aux = aux->siguiente;
    }

    // Comprobar el ?ltimo nodo tambi?n
    size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
    string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
    int numeroPedido = stringAEnteroRE(pedidoStr);

    if (numeroPedido > valorMayor) {
        valorMayor = numeroPedido;
        nodoMayor = aux;
    }

    if (nodoMayor != NULL) {
        cout << "Informacion del Restaurante: " << nodoMayor->valor << endl;
        return "Informacion del Restaurante: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n Restaurante con con consultas." << endl;
    }
}

string ArbolRestaurante::MostrarArbolRestaurantesPorArbolCiudad() {
    cout << "Digite el codigo de pais: ";
    string codigoPais;
    cin >> codigoPais;

    cout << "Digite el codigo de Ciudad: ";
    string codigoArbolCiudad;
    cin >> codigoArbolCiudad;

    string codigosBuscados = codigoPais + ";" + codigoArbolCiudad;
    
    string memoria;
    if (ArbolVacio()) {
        cout << "El arbol de Restaurantes esta vacio." << endl;
        return "arbol vacia";
    }

    pnodoRE aux = primero;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
        	memoria += aux -> valor + "; // ";
            cout << aux->valor << endl;
        }
        aux = aux->siguiente;
        i++;
    }
    return memoria;
}

void ArbolRestaurante::agregarRE(ArbolCiudad & arbolCiudad, string pais, string ciudad, string restaurante, string nombre){
    int codigo11 = stringAEnteroCl(pais);
    int codigo21 = stringAEnteroCl(ciudad);
    

    std::stringstream ss1, ss2;
    ss1 << codigo11;
    ss2 << codigo21;

    string num1 = ss1.str();
    string num2 = ss2.str();

    string codigosBuscados = num1 + ";" + num2;
    
    
	if(arbolCiudad.ExisteCIU(codigosBuscados)){
		string NombreNuevo = nombre;
	
		string NuevoValor = codigosBuscados + ";" + restaurante + ";" + NombreNuevo +";" +"0";
		agregarNodo(NuevoValor);
	
	}else{
		cout<<"el pais no existe, No se agrega"<<endl;
	}
}

void ArbolRestaurante::ModificarNombreRE(string pais, string ciudad, string restaurante, string nombre) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    string codigosBuscados = pais +";" + ciudad +";" + restaurante; 
    pnodoRE aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			string modificar = codigosBuscados + ";" + nombre + ";" + "0";
			aux -> valor = modificar;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol." << endl;
    }

}

int ArbolRestaurante::stringAEnteroRE(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

string ArbolRestaurante::ComprobacionRE(string pais, string ciudad, string nombre) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return "";
    }


    string codigosBuscados = pais + ";" + ciudad + ";" + nombre;
    pnodoRE aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroRE(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;
				return aux->valor;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
        return "";
    }
}

void ArbolRestaurante::CargarDesdeArchivoRE() {
    set<string> numero3_set;  

    ifstream archivo("Restaurantes.txt");
    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            istringstream iss(linea);
            string numero1, numero2, numero3, nombre;
            getline(iss, numero1, ';');
            getline(iss, numero2, ';');
            getline(iss, numero3, ';');
            getline(iss, nombre);

            // Verificar si NUMERO3 es diferente de los anteriores
            if (numero3_set.find(numero3) == numero3_set.end())
            {
                numero3_set.insert(numero3);  // Agregar a conjunto de NUMERO3
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + nombre + +";"+"0";
                agregarNodo(nuevo_valor);
            }
            else
            {
                cout << "Advertencia: NUMERO3 debe ser diferente a los otros NUMERO3 anteriores." << endl;
            }
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
                
ArbolRestaurante::~ArbolRestaurante()
{
   pnodoRE aux;
   pnodoRE temp;
   
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
                           
int ArbolRestaurante::cantNodos() 
{
    int cont=0;

    pnodoRE aux = primero->siguiente;
    if(ArbolVacio())
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
 
void ArbolRestaurante::agregarNodo(string v)
{
   if (ArbolVacio())
     {
     primero = new nodoRE(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoRE nuevo = new nodoRE(v);//1
     nuevo->anterior = primero->anterior;//2
     /*nuevo->siguiente=primero->anterior->siguiente;opcion para intruccion 3*/
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}


void ArbolRestaurante::MostrarRE()
{
   pnodoRE aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;

} 

bool ArbolRestaurante::ExisteRE(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoRE aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        return false;
    }
}















//clase ArbolMenu
class nodoME {
public:
    nodoME(const string &v)
    {
        valor = v;
        siguiente = NULL;
        anterior = NULL;
    }

    nodoME(const string &v, nodoME *signodoME)
    {
        valor = v;
        siguiente = signodoME;
    }

private:
    string valor;
    nodoME *siguiente;
    nodoME *anterior;

    friend class ArbolMenu;
};
typedef nodoME *pnodoME;

class ArbolMenu {
public:
    ArbolMenu() { primero = NULL; }
    ~ArbolMenu();

    void agregarNodoIn(string v);
    void agregarNodo(string v);
    void InsertarPos(string v, int pos);
    bool ArbolVacio() { return primero == NULL; }
    void Imprimir();
    void MostrarME();
    int cantNodos();
    void CargarDesdeArchivoME();
    void ArbolMenusME(ArbolRestaurante & arbolRestaurante);
    string ComprobacionME(string pais, string ciudad, string restaurante, string menu);
    void ModificarNombreME(string pais, string ciudad, string restaurante, string menu, string nombre);
    void AgregarME(ArbolRestaurante & arbolRestaurante, string pais, string ciudad, string restaurante, string menu, string nombre);
    bool ExisteME(string codigo);
    int stringAEnteroME(const std::string &cadena);
    string EncontrarValorMayorPedido();
    string MostrarMESTR();
    string ObtenerContenidoComoString();
    int stringAEnteroCl(const std::string &cadena);
    void BorrarPorCodigosRE(string pais, string ciudad, string restaurante,string menu);
    void BorrarInicio();
    void BorrarFinal();
private:
    pnodoME primero;
};


int ArbolMenu::stringAEnteroCl(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolMenu::BorrarPorCodigosRE(string pais, string ciudad, string restaurante,string menu) {
    if (ArbolVacio()) {
        cout << "arbol vacio" << endl;
        return;
    }

    string codigosBuscados = pais + ";" + ciudad + ";" + restaurante +";" + menu;
    pnodoME aux = primero;
    pnodoME nodoAEliminar = NULL;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            nodoAEliminar = aux;
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (encontrado) {
        if (nodoAEliminar == primero) {
            BorrarInicio();
        } else if (nodoAEliminar->siguiente == primero) {
            BorrarFinal();
        } else {
            nodoAEliminar->anterior->siguiente = nodoAEliminar->siguiente;
            nodoAEliminar->siguiente->anterior = nodoAEliminar->anterior;
            delete nodoAEliminar;
        }

        cout << "nodoRE con los c?digos " << codigosBuscados << " borrado exitosamente." << endl;
    } else {
        cout << "No encontrado" << endl;
    }
}


void ArbolMenu::BorrarFinal()
{
    if (ArbolVacio())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero)
      {
        pnodoME temp= primero;
        primero= NULL;
        delete temp;
      }
      else 
      {
         pnodoME aux = primero; //1
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         pnodoME temp = aux->siguiente;//2
         aux->siguiente= primero;//3
         primero->anterior=aux;//4
         delete temp;//5
      }
    }
}

void ArbolMenu::BorrarInicio()
{
    if (ArbolVacio())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
        pnodoME temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        pnodoME aux = primero->anterior;//1
        pnodoME temp= primero;//2
        aux->siguiente=primero->siguiente;//3
        primero=primero->siguiente; //4
        primero->anterior=aux;//5
        delete temp;//6
      }
    }
}


string ArbolMenu::ComprobacionME(string pais, string ciudad, string restaurante, string menu) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return "";
    }


    string codigosBuscados = pais + ";" + ciudad + ";" + restaurante +";" + menu;
    pnodoME aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroCl(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;
				return aux->valor;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
        return "";
    }
}

std::string ArbolMenu::MostrarMESTR() {
    pnodoME aux = primero;
    std::stringstream ss;

    while (aux->siguiente != primero) {
        ss << aux->valor << " -> ";
        aux = aux->siguiente;
    }

    ss << aux->valor << " -> ";
    
    return ss.str();
}

string ArbolMenu::ObtenerContenidoComoString() {
    if (ArbolVacio()) {
        return "Arbol vacio";
    }

    std::stringstream ss;
    pnodoME aux = primero;

    do {
        ss << aux->valor << " -> ";
        aux = aux->siguiente;
    } while (aux != primero);

    return ss.str();
}

string ArbolMenu::EncontrarValorMayorPedido() {
    if (ArbolVacio()) {
        cout << "El arbol de Menu esta vacio." << endl;
        return "Arbol vacio";
    }

    pnodoME aux = primero;
    int valorMayor = -1;  // Inicializamos con un valor menor al m?nimo posible
    pnodoME nodoMayor = NULL;  // Nodo correspondiente al valor m?s alto

    while (aux->siguiente != primero) {
        size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
        string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
        int numeroPedido = stringAEnteroME(pedidoStr);

        if (numeroPedido > valorMayor) {
            valorMayor = numeroPedido;
            nodoMayor = aux;
        }

        aux = aux->siguiente;
    }

    // Comprobar el ?ltimo nodo tambi?n
    size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
    string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
    int numeroPedido = stringAEnteroME(pedidoStr);

    if (numeroPedido > valorMayor) {
        valorMayor = numeroPedido;
        nodoMayor = aux;
    }

    if (nodoMayor != NULL) {
        cout << "Informacion del m: " << nodoMayor->valor << endl;
        return "Informacion del Menu: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n Restaurante con con consultas." << endl;
    }
}

int ArbolMenu::stringAEnteroME(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolMenu::AgregarME(ArbolRestaurante & arbolRestaurante, string pais, string ciudad, string restaurante, string menu, string nombre){


    string codigosBuscados = pais + ";" + ciudad + ";" + restaurante;
    
    
	if(arbolRestaurante.ExisteRE(codigosBuscados)){
		string NuevoValor = codigosBuscados + ";"+ menu +";" + nombre +";" + "0";
		agregarNodo(NuevoValor);
	
	}else{
		cout<<"no existe, No se agrega"<<endl;
	}
}

void ArbolMenu::ModificarNombreME(string pais, string ciudad, string restaurante, string menu, string nombre) {
    string codigosBuscados = pais + ";" + ciudad + ";" + restaurante + ";" + menu;
    pnodoME aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
			string modificar = codigosBuscados + ";" + nombre + ";" + "0";
			aux -> valor = modificar;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol" << endl;
    }

} 


void ArbolMenu::CargarDesdeArchivoME() {
    set<string> numero4_set;  

    ifstream archivo("Menu.txt");
    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            istringstream iss(linea);
            string numero1, numero2, numero3,numero4, nombre;
            getline(iss, numero1, ';');
            getline(iss, numero2, ';');
            getline(iss, numero3, ';');
            getline(iss, numero4, ';');
            getline(iss, nombre);

            // Verificar si NUMERO3 es diferente de los anteriores
            if (numero4_set.find(numero4) == numero4_set.end())
            {
                numero4_set.insert(numero4);  // Agregar a conjunto de NUMERO3
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + numero4+ ";" + nombre + ";" + "0";
                agregarNodo(nuevo_valor);
            }
            else
            {
                cout << "Advertencia: NUMERO3 debe ser diferente a los otros NUMERO3 anteriores." << endl;
            }
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
                
ArbolMenu::~ArbolMenu()
{
   pnodoME aux;
   pnodoME temp;
   
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
                           
int ArbolMenu::cantNodos() 
{
    int cont=0;

    pnodoME aux = primero->siguiente;
    if(ArbolVacio())
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

void ArbolMenu::agregarNodo(string v)
{
   if (ArbolVacio())
     {
     primero = new nodoME(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoME nuevo = new nodoME(v);//1
     nuevo->anterior = primero->anterior;//2
     /*nuevo->siguiente=primero->anterior->siguiente;opcion para intruccion 3*/
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}

void ArbolMenu::MostrarME()
{
   pnodoME aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
}   

bool ArbolMenu::ExisteME(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoME aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        return false;
    }
}


   


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

    friend class ArbolProducto;
};
typedef nodoPRO *pnodoPRO;

class ArbolProducto {
public:
    ArbolProducto() { primero = NULL; }
    ~ArbolProducto();

    void agregarNodoIn(string v);
    void agregarNodo(string v);
    void InsertarPos(string v, int pos);
    bool ArbolVacio() { return primero == NULL; }
    void Imprimir();
    void MostrarPRO();
    int cantNodos();
    void CargarDesdeArchivoPRO();
    string ComprobacionPRO(string pais, string ciudad, string restaurante, string menu, string producto);
    void AgregarPRO(ArbolMenu & arbolMenu, string pais, string ciudad, string restaurante, string menu, string producto, string nombre, string calorias, string precio);
    void ModificarNombrePRO(string pais, string ciudad, string restaurante, string menu, string producto, string nombre, string calorias, string precio, string cantidad);
    bool ExistePRO(string codigo);
    int stringAEnteroPRO(const std::string &cadena);
    string EncontrarValorMayorPedido();
    string muestraCantidad(string codigo);
    bool ModificarCantidadPro(string codigosBuscados, int resta);
    string getPrecio(string codigosBuscados);
    string getCantProd(string codigosBuscados);
    string MostrarPROSTR();
    string ObtenerContenidoComoString();
    void BorrarPorCodigosRE(string pais, string ciudad, string restaurante,string menu,string producto);
    void BorrarFinal();
    void BorrarInicio();
private:
    pnodoPRO primero;
};


string ArbolProducto::ObtenerContenidoComoString() {
    if (ArbolVacio()) {
        return "Arbol vacio";
    }

    std::stringstream ss;
    pnodoPRO aux = primero;

    do {
        ss << aux->valor << " -> ";
        aux = aux->siguiente;
    } while (aux != primero);

    return ss.str();
}


void ArbolProducto::BorrarFinal()
{
    if (ArbolVacio())
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

void ArbolProducto::BorrarInicio()
{
    if (ArbolVacio())
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


void ArbolProducto::BorrarPorCodigosRE(string pais, string ciudad, string restaurante,string menu,string producto) {
    if (ArbolVacio()) {
        cout << "arbol vacio" << endl;
        return;
    }

    string codigosBuscados = pais + ";" + ciudad + ";" + restaurante +";" + menu +";" + producto;
    pnodoPRO aux = primero;
    pnodoPRO nodoAEliminar = NULL;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            nodoAEliminar = aux;
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (encontrado) {
        if (nodoAEliminar == primero) {
            BorrarInicio();
        } else if (nodoAEliminar->siguiente == primero) {
            BorrarFinal();
        } else {
            nodoAEliminar->anterior->siguiente = nodoAEliminar->siguiente;
            nodoAEliminar->siguiente->anterior = nodoAEliminar->anterior;
            delete nodoAEliminar;
        }

        cout << "nodoRE con los c?digos " << codigosBuscados << " borrado exitosamente." << endl;
    } else {
        cout << "No encontrado" << endl;
    }
}

std::string ArbolProducto::MostrarPROSTR() {
    pnodoPRO aux = primero;
    std::stringstream ss;

    while (aux->siguiente != primero) {
        ss << aux->valor << " -> ";
        aux = aux->siguiente;
    }
    
    ss << aux->valor << " -> ";
    ss << std::endl;

    return ss.str();
}


string ArbolProducto::EncontrarValorMayorPedido() {
    if (ArbolVacio()) {
        cout << "El arbol de Menu esta vacio." << endl;
        return "arbol vacio";
    }

    pnodoPRO aux = primero;
    int valorMayor = -1;  // Inicializamos con un valor menor al m?nimo posible
    pnodoPRO nodoMayor = NULL;  // Nodo correspondiente al valor m?s alto

    while (aux->siguiente != primero) {
        size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
        string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
        int numeroPedido = stringAEnteroPRO(pedidoStr);

        if (numeroPedido > valorMayor) {
            valorMayor = numeroPedido;
            nodoMayor = aux;
        }

        aux = aux->siguiente;
    }

    // Comprobar el ?ltimo nodo tambi?n
    size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
    string pedidoStr = aux->valor.substr(posicionUltimoPuntoComa + 1);
    int numeroPedido = stringAEnteroPRO(pedidoStr);

    if (numeroPedido > valorMayor) {
        valorMayor = numeroPedido;
        nodoMayor = aux;
    }

    if (nodoMayor != NULL) {
        cout << "Informacion del m: " << nodoMayor->valor << endl;
        return "Informacion del Producto: " + nodoMayor->valor;
    } else {
        cout << "No se encontr? ning?n Restaurante con con consultas." << endl;
    }
}

int ArbolProducto::stringAEnteroPRO(const std::string &cadena) {
    int resultado = 0;
    int multiplicador = 1;

    // Comprueba si la cadena representa un n?mero negativo
    size_t indice = 0;
    if (cadena[0] == '-') {
        multiplicador = -1;
        indice = 1; // Saltar el signo negativo
    }

    // Recorre la cadena y construye el n?mero entero
    for (; indice < cadena.length(); ++indice) {
        char digito = cadena[indice];
        if (isdigit(digito)) {
            int valorDigito = digito - '0';
            resultado = resultado * 10 + valorDigito;
        } else {
            // Manejo de error si la cadena contiene caracteres no num?ricos
            std::cerr << "Error: La cadena contiene caracteres no num?ricos." << std::endl;
            return 0;
        }
    }

    return resultado * multiplicador;
}

void ArbolProducto::ModificarNombrePRO(string pais, string ciudad, string restaurante, string menu, string producto, string nombre, string calorias, string precio, string cantidad){
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return;
    }

    string codigosBuscados = pais+ ";" + ciudad + ";" + restaurante + ";" + menu + ";" + producto;
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
 
			string modificar = codigosBuscados + ";" + nombre + ";" + calorias + ";" + precio + ";" + cantidad;
			aux -> valor = modificar;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (encontrado == false) {
        cout << "No se encontraron los codigos en el arbol." << endl;
    }

}

void ArbolProducto::AgregarPRO(ArbolMenu & arbolMenu, string pais, string ciudad, string restaurante, string menu, string producto, string nombre, string calorias, string precio){

    string codigosBuscados = pais+ ";" + ciudad + ";" + restaurante + ";" + menu;
    
	if(arbolMenu.ExisteME(codigosBuscados)){
	
		string NuevoValor = codigosBuscados + ";" + producto + ";" + nombre + ";" + calorias + ";" + precio + ";" + "20" + ";" + "0";
		agregarNodo(NuevoValor);
	
	}else{
		cout<<"no existe, No se agrega"<<endl;
	}
}


string ArbolProducto::ComprobacionPRO(string pais, string ciudad, string restaurante, string menu, string producto) {
    if (ArbolVacio()) {
        cout << "El arbol está vacío" << endl;
        return "";
    }

    string codigosBuscados = pais + ";" + ciudad + ";" + restaurante + ";" + menu + ";" + producto;
    pnodoPRO aux = primero;
    bool encontrado = false;

    while (aux != NULL) {
        size_t found = aux->valor.find(codigosBuscados);
        if (found != string::npos) {
            encontrado = true;
            size_t lastSemicolon = aux->valor.find_last_of(';');
            if (lastSemicolon != string::npos) {
                size_t numberStart = lastSemicolon + 1;
                string numeroStr = aux->valor.substr(numberStart);
                int numero = stringAEnteroPRO(numeroStr);
                numero++;

                std::stringstream ss1;
                ss1 << numero;
                string num1 = ss1.str();

                string nuevoValor = aux->valor.substr(0, numberStart) + num1;
                aux->valor = nuevoValor;
                return aux->valor;
            } else {
                cout << "No se encontró el último punto y coma en el valor." << endl;
            }
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron los códigos en el árbol." << endl;
    }

    return "";
}


void ArbolProducto::CargarDesdeArchivoPRO() {
    set<string> numero4_set;  

    ifstream archivo("Productos.txt");
    if (archivo.is_open())
    {
        string linea;
        while (getline(archivo, linea))
        {
            istringstream iss(linea);
            string numero1, numero2, numero3, numero4, numero5, nombre, numero6, numero7, numero8;
            getline(iss, numero1, ';');
            getline(iss, numero2, ';');
            getline(iss, numero3, ';');
            getline(iss, numero4, ';');
            getline(iss, numero5, ';');
            getline(iss, nombre, ';');
            getline(iss, numero6, ';');
            getline(iss, numero7, ';');
            getline(iss, numero8);

            // Verificar si NUPRORO3 es diferente de los anteriores
            if (numero4_set.find(numero4) == numero4_set.end())
            {
                numero4_set.insert(numero4);  // Agregar a conjunto de NUPRORO3
                string nuevo_valor = numero1 + ";" + numero2 + ";" + numero3 + ";" + numero4 + ";" + numero5 + ";" + nombre + ";" + numero6 + ";" + numero7 + ";" + numero8;
                agregarNodo(nuevo_valor + ";0");
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

                
ArbolProducto::~ArbolProducto()
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
                          
int ArbolProducto::cantNodos() 
{
    int cont=0;

    pnodoPRO aux = primero->siguiente;
    if(ArbolVacio())
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

void ArbolProducto::agregarNodo(string v)
{
   if (ArbolVacio())
     {
     primero = new nodoPRO(v);
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   { 
     pnodoPRO nuevo = new nodoPRO(v);//1
     nuevo->anterior = primero->anterior;//2
	 nuevo->siguiente=primero;// coloca alguna de la dos 3
     primero->anterior->siguiente=nuevo;//4
     primero->anterior=nuevo;//5
    }    
}
  
void ArbolProducto::MostrarPRO()
{
   pnodoPRO aux=primero;
   while(aux->siguiente!=primero)
     {
                                
      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;
}

bool ArbolProducto::ExistePRO(string codigo) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return false;
    }
    
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

    while (i <= cantNodos()) {
        if (aux->valor.find(codigo) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            string nombre = aux->valor.substr(posicionUltimoPuntoComa + 1);
            return true;
            break;
        }
        aux = aux->siguiente;
        i ++;
    }

    if (!encontrado) {
        return false;
    }
}

string ArbolProducto::muestraCantidad(string codigosBuscados) {
    if (ArbolVacio()) {
        cout << "El arbol esta vacio" << endl;
        return "ARBOL VACIO";
    }
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

	while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroPRO(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;
			    std::string cadena = aux -> valor ;
			    std::istringstream stream(cadena);
			    std::string dato;
				int j = 0;
				while (std::getline(stream, dato, ';')) {
						        if (!dato.empty()) {
									if(j==8){
										return dato;
									}
						            j++;
						        }
						    }
				            break;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        return "no se encontro codigo en el arbol";
    }
}

bool ArbolProducto::ModificarCantidadPro(string codigosBuscados, int resta){
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;
	string nuevo;
	while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroPRO(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;
			    std::string cadena = aux -> valor ;
			    std::istringstream stream(cadena);
			    std::string dato;
				int j = 0;
				string producto, caloria, precio, busquedas, StrnuevaCantidad ;
				while (std::getline(stream, dato, ';')) {
						        if (!dato.empty()) {
						        	
						        	if(j == 5){
						        		producto = dato;
									}
						        	if(j == 6){
						        		caloria = dato;
									}
						        	if(j == 7){
						        		precio = dato;
									}
									if(j==8){
										int valor = stringAEnteroPRO(dato);
										cout<<"cantidad: "<<valor<<endl;
										cout<<"a restar: "<<resta<<endl;
										if(resta > valor){
											cout<<"error la cantidad de compra es mayor que la disponible"<<endl;
											return false;
										}
										int nuevaCantidad = valor - resta;
										std::stringstream ss1;
										ss1 << nuevaCantidad;
										StrnuevaCantidad = ss1.str();
									}
									if(j==9){
										busquedas = dato;
									}
						            j++;
						        }
						    }
						    nuevo = codigosBuscados + ";" + producto + ";" + caloria + ";" + precio + ";" + StrnuevaCantidad + ";" + busquedas;
						    cout<<nuevo<<endl;
						    aux -> valor = nuevo;
						    return true;
				            break;	            
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
                return false;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
        return false;
    }
}

string ArbolProducto::getPrecio(string codigosBuscados){
    pnodoPRO aux = primero;
    bool encontrado = false;
    int i = 0;

	while (i <= cantNodos()) {
        if (aux->valor.find(codigosBuscados) != string::npos) {
            encontrado = true;
            size_t posicionUltimoPuntoComa = aux->valor.find_last_of(';');
            if (posicionUltimoPuntoComa != string::npos) {
                size_t posicionNumero = posicionUltimoPuntoComa + 1;
                std::string numeroStr = aux->valor.substr(posicionNumero);
                int numero = stringAEnteroPRO(numeroStr);
                numero++;
                
				std::stringstream ss1;
    			ss1 << numero;

				string num1 = ss1.str();
    
    
                
                string nuevoValor = aux->valor.substr(0, posicionNumero) + num1;
                aux->valor = nuevoValor;

                cout << "Codigos encontrados en el arbol: " << codigosBuscados << endl;
                cout << "Nuevo valor asociado: " << nuevoValor << endl;
			    std::string cadena = aux -> valor ;
			    std::istringstream stream(cadena);
			    std::string dato;
				int j = 0;
				while (std::getline(stream, dato, ';')) {
						        if (!dato.empty()) {
						        	
						        	if(j == 5){
						     		cout<<"pruducto: "<<dato<<endl;
									}
						        	if(j == 6){
						        		cout<<"calorias: "<<dato<<endl;
									}
						        	if(j == 7){
						        		cout<<"precio: "<<dato<<endl;
						        		return dato;
									}
									if(j==8){
										cout<<"cantidad de productos: "<<dato<<endl;
									}
									if(j==9){
										cout<<"cantidad de busquedas: "<<dato<<endl;
									}
						            j++;
						        }
						    }
				            break;
            } else {
                cout << "No se encontr? el ?ltimo punto y coma en el valor." << endl;
            }
            break;
        }
        aux = aux->siguiente;
        i++;
    }

    if (!encontrado) {
        cout << "No se encontraron los c?digos en el arbol." << endl;
    }
}








	
	int main(){
		//clientes ok 
		cliente ac;
		ArbolPais ap;
		administrador ad;
		ArbolCiudad aCiu;
		ArbolRestaurante are;
		ArbolMenu ame;
		ArbolProducto apro;
		
		ap.CargarDesdeArchivo();
		
		ac.CargarDesdeArchivoCl();
		
		ad.CargarDesdeArchivoAd();
		
		aCiu.CargarDesdeArchivoCIU();
		
		are.CargarDesdeArchivoRE();
				
		ame.CargarDesdeArchivoME();
		
		apro.CargarDesdeArchivoPRO();
		
		/*
		//clientes
		ac.MostrarCl();
		if(ac.ExisteCl("23242")){
			cout<<"si esta en la lista"<<endl;
		}
		else{
			cout<<"no esta en la lista"<<endl;
		}
		ac.AgregarClienteCl("12345","Samir Cabrera");
		ac.MostrarCl();
		cout<<ac.ConsultarClientePorCodigoCl("12345")<<endl;
		ac.BorrarPorCodigoCl("eqweq");
		cout<<ac.ObtenerContenidoComoString()<<endl;
		ac.ModificarNombreCL("12345","pamela");
		cout<<ac.ObtenerContenidoComoString()<<endl;
		
		
		//paises
		cout<<ap.ObtenerContenidoComoString()<<endl;
		ap.AgregarPais("12345","Samir Cabrera");
		cout<<ap.ConsultarPaisPorCodigo("12345")<<endl;
		ap.BorrarPorCodigo("1");
		cout<<ap.ObtenerContenidoComoString()<<endl;
		ap.ModificarNombre("2", "pamela");
		cout<<ap.ObtenerContenidoComoString()<<endl;
		
		
		
	
		//administradores
		cout<<ad.ObtenerContenidoComoString()<<endl;
		ad.AgregarAdministradorAd("123456","juanfrancisco");
		ad.ModificarNombre("657","Mario");
		cout<<ad.ObtenerContenidoComoString()<<endl;
		cout<<ad.ConsultarAdministradorPorCodigoAd("123456")<<endl;
		ad.BorrarPorCodigoAd("657");
		cout<<ad.ObtenerContenidoComoString()<<endl;
		
		
	
		//ciudades
		cout<<aCiu.ObtenerContenidoComoString()<<endl;
		aCiu.AgregarCIU(ap, "1", "34", "tokyo");
		cout<<aCiu.ObtenerContenidoComoString()<<endl;
		cout<<aCiu.ComprobacionCIU("1","34")<<endl;
		aCiu.ModificarNombreCIU("1","34","perez zeledon");
		aCiu.BorrarPorCodigosCIU("3","89");
		cout<<aCiu.ObtenerContenidoComoString()<<endl;
		
		//restaurantes
		cout<<are.ObtenerContenidoComoString()<<endl;
		are.agregarRE(aCiu,"2","35","777","emilio");
		are.ModificarNombreRE("1","22","125","munchu");
		cout<<are.ObtenerContenidoComoString()<<endl;
		cout<<are.ComprobacionRE("1","22","125")<<endl;
		are.BorrarPorCodigosRE("1","22","125");
		cout<<are.ObtenerContenidoComoString()<<endl;*/
		
		//menu
		/*cout<<ame.ObtenerContenidoComoString()<<endl;
		ame.AgregarME(are,"1","19","112","345","Pizza");
		cout<<ame.ObtenerContenidoComoString()<<endl;
		ame.AgregarME(are,"1","19","112","345","teta");
		cout<<ame.ObtenerContenidoComoString()<<endl;
		cout<<ame.ComprobacionME("1","19","112","345")<<endl;
		ame.BorrarPorCodigosRE("2","35","130","246");
		cout<<ame.ObtenerContenidoComoString()<<endl;*/

		//producto
		cout<<apro.ObtenerContenidoComoString()<<endl;
		apro.AgregarPRO(ame, "1","19","112","227","777","pingavenosa", "1300","2500");
		cout<<apro.ObtenerContenidoComoString()<<endl;
		cout<<apro.ComprobacionPRO("1","19","112","227","777")<<endl;
		cout<<apro.ComprobacionPRO("1","19","112","227","777")<<endl;
		cout<<apro.ComprobacionPRO("1","19","112","227","777")<<endl;
		apro.ModificarNombrePRO("1","19","112","227","777","la hello kity", "5400","7500","30");
		cout<<apro.ObtenerContenidoComoString()<<endl;
		apro.BorrarPorCodigosRE("1","19","112","227","777");
		cout<<apro.ObtenerContenidoComoString()<<endl;

		
		
		return 0;
	}
	
	
	/*
	clientes: 
	-agregar ||
	-modificar ||
	-eliminar ||
	-consultar ||
	
	paises:
	-agregar ||
	-modificar ||
	-eliminar ||
	-consultar ||
	
	admin
	-agregar ||
	-modificar ||
	-eliminar ||
	-consultar ||
	
	ciudad
	-agregar ||
	-modificar ||
	-eliminar ||
	-consultar ||
	
	restaurante
	-agregar ||
	-modificar ||
	-eliminar ||
	-consultar ||
	
	menu
	-agregar ||
	-modificar ||
	-eliminar ||
	-consultar ||
	
	producto
	-agregar ||
	-modificar ||
	-eliminar 
	-consultar ||
	
	
	*/
	




	
