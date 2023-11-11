#include <iostream>

using namespace std;

int main() {
    bool ejecucion = true;  // Inicializa la variable ejecucion a true
    int opcion;

    while (ejecucion) {
        cout << "\n\n1. leer archivos" << endl;
        cout << "2. Prim" << endl;
        cout << "3. kruskal" << endl;
        cout << "4. dijkstra" << endl;
        cout << "5. puntos de articulacion" << endl;
        cout << "6. anchura" << endl;
        cout << "7. profundidad" << endl;
        cout << "8. salir" << endl;

        cin >> opcion;  // Debes leer en la variable 'opcion', no en 'ejecucion'

        switch (opcion) {  // Usa 'opcion' en lugar de 'ejecucion' en el switch
            case 1:
                cout << "leer archivos" << endl;
                break;
            case 2:
                cout << "prim" << endl;
                break;
            case 3:
                cout << "kruskal" << endl;
                break;
            case 4:
                cout << "dijkstra" << endl;
                break;
            case 5:
                cout << "puntos de articulacion" << endl;
                break;
            case 6:
                cout << "anchura" << endl;
                break;
            case 7:
                cout << "profundidad" << endl;
                break;
            case 8:
                cout << "salir" << endl;
                ejecucion = false;
                break;
            default:
                cout << "error a la hora de digitar" << endl;
                break;
        }
    }

    return 0;
}

