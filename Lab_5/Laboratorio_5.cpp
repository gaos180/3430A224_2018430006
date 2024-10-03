#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

// Esto definio el profesor, aunque en c hay que definirlo, en c++ estan los true y false
#define TRUE 1
#define FALSE 0

using namespace std;

enum {IZQUIERDO, DERECHO};

struct Nodo {
    int dato;
    int FE;
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

/* Insertar en arbol ordenado: */
void Insertar(Arbol* a, int dat);
/* Borrar un elemento: */
void Borrar(Arbol* a, int dat);
/* Funcion de busqueda: */
bool Buscar(Arbol* a, int dat);
void PreOrden(Arbol, ofstream &fp);

// Funciones de equilibrado:
void Equilibrar(Arbol* raiz, pNodo nodo, int, int);
void RotaDerechaDerecha(Arbol* raiz, pNodo nodo);
void RotaIzquierdaIzquierda(Arbol* raiz, pNodo nodo);
void RotaDerechaIzquierda(Arbol* raiz, pNodo nodo);
void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo);

/* Funciones auxiliares: */
void Podar(Arbol* a);

void MenuPrincipal();
void GenerarGrafo(Arbol);

int main() {
    Arbol ArbolInt = NULL;
    int opcion = 0;
    int valor;
    bool flag = false; // Bandera para que se verifique si cierto número está

    // Menú
    while (opcion != 6) {
        MenuPrincipal();
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese su numero: ";
                cin >> valor;
                Insertar(&ArbolInt, valor);
                break;
            case 2:
                cout << "Ingrese su numero: ";
                cin >> valor;
                flag = Buscar(&ArbolInt, valor);
                if (flag)
                    cout<< "Se encontro el valor" << endl;
                else if (!flag)
                    cout<< "No se encontro el valor" << endl;
                break;
            case 3:
                cout << "Ingrese su numero: ";
                cin >> valor;
                flag = Buscar(&ArbolInt, valor);
                if(flag){
                    cout<< "Se encontro el valor, se eliminará" << endl;
                    Borrar(&ArbolInt, valor);
                }else if (!flag){
                    cout<< "No se encontro el valor" << endl;
                    }
                break;
            case 4:
                cout << "Ingrese su numero a modificar: ";
                cin >> valor;
                flag = Buscar(&ArbolInt, valor);
                if (flag) {
                    cout<< "Se encontro el valor" << endl;
                    Borrar(&ArbolInt, valor);
                    cout << "Ingrese el numero a actualizar: ";
                    cin >> valor;
                    Insertar(&ArbolInt, valor);
                }else if (!flag) {
                    cout<< "No se encontro el valor" << endl;
                    }
                break;
            case 5:
                GenerarGrafo(ArbolInt);
                break;
            }
        }
    

    /* Liberar memoria asociada al arbol. */
    Podar(&ArbolInt);
    return 0;
}

// genera el grafo en base al preOrden para la inyección de los datos
void GenerarGrafo(Arbol ArbolInt) {
    ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=yellow];\n";

    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
    PreOrden(ArbolInt, fp);

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void MenuPrincipal() {
    cout << "\n";
    cout << "<1> Ingresar numero\n";
    cout << "<2> Busqueda numero\n";
    cout << "<3> Eliminar numero\n";
    cout << "<4> Modificar elemento ingresado\n";
    cout << "<5> Generar Grafo\n";
    cout << "<6> Salir\n";
    cout << "\n";
}

// Libera memoria eliminando el arbol
void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = NULL;
    }
}

// Se encarga de buscar en el arbol
bool Buscar(Arbol* a, int dat){
    pNodo padre = NULL;
    pNodo actual = *a;
    if (a == nullptr){
        return false;
    }
    
    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
        
    }

    if (actual != NULL){
        if (actual ->dato == dat){
            return true;
        }
        return false;
    }

    if (padre == NULL) {
        return false;
    }
    return false;
}

// Función para borrar
void Borrar(Arbol* a, int valor) {
    if (*a == NULL) {
        return;
    }

    pNodo nodo = *a;
    pNodo padre = NULL;

    // Buscar el nodo a eliminar
    while (nodo != NULL && nodo->dato != valor) {
        padre = nodo;
        if (valor < nodo->dato) {
            nodo = nodo->izquierdo;
        } else {
            nodo = nodo->derecho;
        }
    }

    // Si el nodo no se encuentra, salir
    if (nodo == NULL) {
        return;
    }

    // Caso El nodo es una hoja, se elimina el nodo solamente
    if (nodo->izquierdo == NULL && nodo->derecho == NULL) {
        if (padre == NULL) { // Si es la raíz
            *a = NULL;
        } else if (padre->izquierdo == nodo) {
            padre->izquierdo = NULL;
        } else {
            padre->derecho = NULL;
        }
        free(nodo);
    }
    // Caso: El nodo tiene un solo hijo, como se evalua primero el otro caso
    // no da problema colocar el null || null
    else if (nodo->izquierdo == NULL || nodo->derecho == NULL) {
        pNodo hijo;
        if (nodo->izquierdo == nullptr){
            hijo = nodo->derecho;
        }else{
            hijo = nodo->izquierdo;
        }
        
        if (padre == NULL) { // Si es la raíz
            *a = hijo;
        } else if (padre->izquierdo == nodo) {
            padre->izquierdo = hijo;
        } else {
            padre->derecho = hijo;
        }
        hijo->padre = padre;
        free(nodo);
    }
    // Caso: El nodo tiene dos hijos
    else {
        // el sucesor será el más pequeño del lado derecho
        pNodo sucesor = nodo->derecho;
        while (sucesor->izquierdo != NULL) {
            sucesor = sucesor->izquierdo;
        }
        int valorSucesor = sucesor->dato;
        Borrar(a, sucesor->dato);
        nodo->dato = valorSucesor;
    }

    // Después de eliminar, equilibrar el árbol desde el nodo eliminado hasta la raíz
    if (padre != NULL) {
        if (padre->derecho == nodo) {
            Equilibrar(a, padre, DERECHO, FALSE);
        } else {
            Equilibrar(a, padre, IZQUIERDO, FALSE);
        }
    }
}


void Insertar(Arbol* a, int dat) {
    pNodo padre = NULL;
    pNodo actual = *a;

    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
        
    }

    if (actual != NULL){
        if (actual ->dato == dat){
            cout << "Ingreso un dato que ya está en el árbol" << endl;
        }
        return;
    }

    if (padre == NULL) {
        *a = new Nodo{dat, 0, NULL, NULL, NULL};
    } else if (dat < padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->izquierdo = actual;
        Equilibrar(a, padre, IZQUIERDO, TRUE);
    } else if (dat > padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->derecho = actual;
        Equilibrar(a, padre, DERECHO, TRUE);
    }
    
}


void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo){
            if (rama == IZQUIERDO){
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        }
        else{
            if (rama == IZQUIERDO){
                nodo->FE += 1;
            } 
            else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaIzquierdaDerecha(a, nodo);
            else
                RotaIzquierdaIzquierda(a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechaIzquierda(a, nodo);
            else
                RotaDerechaDerecha(a, nodo);
            salir = TRUE;
        }

        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo R = Q->derecho;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        }
        else {
            Padre->izquierdo = R;
        }
    }
    else
        *raiz = R;

    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    switch (R->FE) {
        case -1: Q->FE = 0; P->FE = 1; break;
        case 0: Q->FE = 0; P->FE = 0; break;
        case 1: Q->FE = -1; P->FE = 0; break;
    }

    R->FE = 0;
}

void RotaDerechaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo R = Q->izquierdo;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    }
    else
        *a = R;

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->FE) {
        case -1: P->FE = 0; Q->FE = 1; break;
        case 0: P->FE = 0; Q->FE = 0; break;
        case 1: P->FE = -1; Q->FE = 0; break;
    }
    R->FE = 0;
}

void RotaIzquierdaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo B = Q->derecho;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->izquierdo = B;
    Q->derecho = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void RotaDerechaDerecha(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo B = Q->izquierdo;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->derecho = B;
    Q->izquierdo = P;

    P->padre = Q;
    
    if (B){
        B->padre = P;
    } 
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void PreOrden(Arbol a, ofstream &fp) {
    if (a) {
        fp << a->dato << ";\n";
        if (a->izquierdo) {
            fp << a->dato << "->" << a->izquierdo->dato << ";\n";
            PreOrden(a->izquierdo, fp);
        }
        if (a->derecho) {
            fp << a->dato << "->" << a->derecho->dato << ";\n";
            PreOrden(a->derecho, fp);
        }
    }
}