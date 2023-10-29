#include <iostream>
#include <string>
#include <sstream>

class FilaCL {
public:
    FilaCL() { primero = NULL; }
    ~FilaCL();

    void InsertarFinal(const std::string& v);
    bool ListaVacia() { return primero == NULL; }
    std::string ObtenerContenido() const;
    void BorrarComprasPorInicio(const std::string& valor);

private:
    struct nodoFilaCl {
        std::string valor;
        nodoFilaCl* siguiente;

        nodoFilaCl(const std::string& v) : valor(v), siguiente(NULL) {}
    };

    nodoFilaCl* primero;
};

FilaCL::~FilaCL() {
    while (primero) {
        nodoFilaCl* aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
}

void FilaCL::InsertarFinal(const std::string& v) {
    // Verificar si el valor ya existe en la fila
    nodoFilaCl* aux = primero;
    while (aux) {
        if (aux->valor == v) {
            // El valor ya existe, no lo agregamos de nuevo
            return;
        }
        aux = aux->siguiente;
    }

    // Si llegamos aquí, el valor no existe en la fila, lo agregamos
    if (ListaVacia())
        primero = new nodoFilaCl(v);
    else {
        aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = new nodoFilaCl(v);
    }
}


std::string FilaCL::ObtenerContenido() const {
    std::string contenido;
    nodoFilaCl* aux = primero;
    while (aux) {
        contenido += aux->valor;
        if (aux->siguiente != NULL)
            contenido += " -> ";
        aux = aux->siguiente;
    }
    return contenido;
}

void FilaCL::BorrarComprasPorInicio(const std::string& valor) {
    while (primero && primero->valor.find(valor) == 0) {
        nodoFilaCl* temp = primero;
        primero = primero->siguiente;
        delete temp;
    }

    if (!primero)
        return;

    nodoFilaCl* aux = primero;
    while (aux->siguiente) {
        if (aux->siguiente->valor.find(valor) == 0) {
            nodoFilaCl* temp = aux->siguiente;
            aux->siguiente = temp->siguiente;
            delete temp;
        } else {
            aux = aux->siguiente;
        }
    }
}

int main() {
    FilaCL l;
    l.InsertarFinal("1");
    l.InsertarFinal("2");
    l.InsertarFinal("2");
    l.InsertarFinal("2");
    l.InsertarFinal("2");
    l.InsertarFinal("2");
    l.InsertarFinal("2");
    l.InsertarFinal("2");
    l.InsertarFinal("3");
    l.InsertarFinal("4");
    l.InsertarFinal("5");
    l.InsertarFinal("6");
    l.InsertarFinal("7");

    std::cout << l.ObtenerContenido() << std::endl;

    l.BorrarComprasPorInicio("3");
    std::cout << l.ObtenerContenido() << std::endl;

    return 0;
}

