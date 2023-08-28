#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class pila {
private:
    stack<string> Pila;

public:
    bool pilaVacia() { return Pila.empty(); }
    void push(string v);
    void imprimir();
    void compararOperadoresCiclo();
};

void pila::push(string v) {
    Pila.push(v);
}

void pila::imprimir() {
    stack<string> temp = Pila;

    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }

    cout << endl;
}

void pila::compararOperadoresCiclo() {
    stack<string> nuevaPila;

    while (!Pila.empty()) {
        string operadorActual = Pila.top();
        Pila.pop();

        if (!nuevaPila.empty() && (operadorActual == "+" || operadorActual == "-")) {
            while (!nuevaPila.empty() && (nuevaPila.top() == "*" || nuevaPila.top() == "/" || nuevaPila.top() == "^")) {
                Pila.push(nuevaPila.top());
                nuevaPila.pop();
            }
        }

        nuevaPila.push(operadorActual);
    }

    while (!nuevaPila.empty()) {
        Pila.push(nuevaPila.top());
        nuevaPila.pop();
    }
}

int main() {
    pila pila;
    pila.push("(");
    pila.push("^");
    pila.push("-");
    pila.push("+");
    pila.push("/");
    pila.push("*");
    pila.push("(");
    pila.push("-");
    pila.push(")");
    pila.push(")");

    cout << "Pila original: ";
    pila.imprimir();

    pila.compararOperadoresCiclo();

    cout << "Resultado después de la comparación: ";
    pila.imprimir();

    cin.get();
    return 0;
}

