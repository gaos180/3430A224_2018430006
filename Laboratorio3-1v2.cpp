#include <iostream>
#include <string>

// Nombre: Gabriel Rojas

using namespace std;

// Nodo
struct Nodo
{
    int dato, tope, maximo;
    Nodo* siguiente;
};

// Creacion del nodo
Nodo* crearNodo(int dato){
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = nullptr;
    return nuevoNodo;
}

// Si la pila está vacia retorna verdadero
bool pila_vacia(Nodo* cabeza){
    if (cabeza == nullptr)
    {
        return true;
    }
    return false;
}

// Ver si la pila esta llena
// Se hace primero el analizar si es null, para que se devuelva de inmediato y no de error
bool pila_llena(Nodo* cabeza){
    if (cabeza == nullptr)
    {
        return false;
    }
    
    if (cabeza->tope == cabeza->maximo)
    {
        return true;
    }else
    {
    return false;
    }
}

// Push->agregar, defino el tope de forma manual cuando es nulo
void push(Nodo*& cabeza, int dato, int maximo){
    Nodo* nuevoNodo = crearNodo(dato);
    nuevoNodo->siguiente = cabeza;

    if (cabeza==nullptr)
    {
        nuevoNodo->tope = 1;
    }else{
        nuevoNodo->tope = cabeza->tope +1;
    }
    
    cabeza = nuevoNodo;
    cabeza->maximo = maximo;
}

// Eliminar el ultimo ingresado
void pop(Nodo*& cabeza){
    if (pila_vacia(cabeza))
    {
        cout << "No se puede ya que la pila esta vacia" << endl;
        return;
    }else{
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        cout << "Se elimino el último" << endl;
    }
}

// Destruir la pila, limpieza de memoria
void destruirPila(Nodo* cabeza){
    while (cabeza != nullptr){
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Mostrar datos
void mostrar(Nodo* cabeza){
    Nodo* actual = cabeza;
    if (cabeza == nullptr)
    {
        cout<< "Está vacia la pila" << endl;
        return;
    }
    
    while (actual != nullptr)
    {
        cout << actual->dato << endl;
        actual = actual->siguiente;
    }
    
}

// Main principal
int main(){
    Nodo* pila = nullptr;
    int maximo, opc;
    
    cout << "Ingrese el valor del máximo de la pila" << endl;
    cin >> maximo;
    
    while (true)
    {
        cout <<"Ingrese su opción:\n0. Salir\n1. Ingresar numero/push\n2. Eliminar ultimo de la pila/pop\n3. Mostrar pila" << endl;
        cin >> opc;
        if (opc == 0)
        {
            break;
        }else if (opc == 1)
        {
            if (pila_llena(pila))
            {
                cout<< "No se puede añadir ya está llena" << endl;
            }else
            {
                cout<< "Ingrese el número a añadir en la pila" << endl;
                cin >> opc;
                push(pila, opc, maximo);
            }
            
            
        }else if (opc == 2)
        {
            pop(pila);
        }else if (opc == 3)
        {
            cout<< "Mostrando pila" << endl;
            mostrar(pila);
        }else{
            cout<<"Ingrese una opción válida"<<endl;
        }
        
    }
        
    destruirPila(pila);
    
    return 0;
}

