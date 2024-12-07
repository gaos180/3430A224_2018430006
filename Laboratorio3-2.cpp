#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

// Nombre: Gabriel Rojas

struct Dato
{
    int numero;
    string empresa;
};

// Estructura hecha ya que daba error devolver dos valores en una función
struct FilaYColumna
{
    int fila;
    int columna;
};


// Nodo
struct Nodo
{
    Dato dato;
    int indice, maximo;
    Nodo* siguiente;
};

// Matriz
struct Matriz
{
    int indice, maximo;
    Nodo* n;
    Matriz* siguiente;
};

Matriz* crearNodoMatriz(Nodo*& nodo){
    Matriz* nuevaMatriz = new Matriz;
    nuevaMatriz->n = nodo;
    nuevaMatriz->siguiente = nullptr;
    return nuevaMatriz;
}

// Creacion del nodo
Nodo* crearNodo(Dato dato){
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

bool matriz_llena(Matriz* cabeza){
    if (cabeza == nullptr)
    {
        return false;
    }
    
    if (cabeza->indice == cabeza->maximo)
    {
        return true;
    }else
    {
    return false;
    }
}

// Ver si la pila esta llena
// Se hace primero el analizar si es null, para que se devuelva de inmediato y no de error
bool pila_llena(Nodo* cabeza){
    if (cabeza == nullptr)
    {
        return false;
    }
    
    if (cabeza->indice == cabeza->maximo)
    {
        return true;
    }else
    {
    return false;
    }
}

// Push->agregar, defino el indice de forma manual cuando es nulo
void push(Nodo*& cabeza, Dato dato, int maximo){
    Nodo* nuevoNodo = crearNodo(dato);
    nuevoNodo->siguiente = cabeza;

    if (cabeza==nullptr)
    {
        nuevoNodo->indice = 1;
    }else{
        nuevoNodo->indice = cabeza->indice +1;
    }
    
    cabeza = nuevoNodo;
    cabeza->maximo = maximo;
}

// Push como el otro pero en matriz en vez en nodo
void push_Matriz(Matriz*& cabeza, Nodo*& nodo, int maximo){
    Matriz* nuevoNodo = crearNodoMatriz(nodo);
    nuevoNodo->siguiente = cabeza;

    if (cabeza==nullptr)
    {
        nuevoNodo->indice = 1;
    }else{
        nuevoNodo->indice = cabeza->indice +1;
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

// retorna información el pop (no elimina el ultimo no más sino que envia información del eliminado)
Dato pop_con_dato(Nodo*& cabeza){
    if (pila_vacia(cabeza))
    {
        Dato temporal;
        temporal.numero =-1;
        cout << "No se puede ya que la pila esta vacia" << endl;
        return temporal;
    }else{
        Nodo* temp = cabeza;
        Dato temp_data = cabeza->dato;
        cabeza = cabeza->siguiente;
        delete temp;
        return temp_data;
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
        cout<< "Está vacia la lista" << endl;
        return;
    }
    
    while (actual != nullptr)
    {
        cout << actual->dato.numero << endl;
        actual = actual->siguiente;
    }
    
}

// de esta forma se clona la matriz y hay diferente memoria
Nodo* clonarPila(Nodo* cabeza) {
    
    if (cabeza == nullptr)
    {
        return nullptr;
    }
    
    Nodo* nuevaCabeza = nullptr;
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    // va creando un nuevo nodo mientras va recorriendo
    while(actual !=nullptr)
    {
        Nodo* nuevoNodo = crearNodo(actual->dato);
        nuevoNodo->indice = actual->indice;
        nuevoNodo->maximo = actual->maximo;
        if (nuevaCabeza == nullptr)
        {
            nuevaCabeza = nuevoNodo;
        }
        else 
        {
            anterior->siguiente = nuevoNodo;
        }
        anterior = nuevoNodo;
        actual = actual->siguiente;
    }
    return nuevaCabeza;
}


// función para ver la matriz según su indice/fila y columna
void mostrarIndiceMatriz(Matriz* cabeza){
    Matriz* actual = cabeza;
    if (cabeza == nullptr)
    {
        cout<< "Está vacia la lista" << endl;
        return;
    }
    while (actual != nullptr)
    {
        Nodo* actualNodo = actual->n;
        cout << "[" << actual->indice << "]";
        while (actualNodo != nullptr)
        {
            cout << actualNodo->indice;
            actualNodo = actualNodo->siguiente;
            
        }
        cout << endl;
        actual = actual->siguiente;
    }
}

// Muestra los datos en la matriz
void mostrarDatoMatriz(Matriz* cabeza){
    Matriz* actual = cabeza;
    if (cabeza == nullptr)
    {
        cout<< "Está vacia la matriz" << endl;
        return;
    }
    while (actual != nullptr)
    {
        Nodo* actualNodo = actual->n;
        cout << "[" << actual->indice << "]";
        while (actualNodo != nullptr)
        {
            cout << "|" << actualNodo->dato.numero << "/" << actualNodo->dato.empresa << "|";
            actualNodo = actualNodo->siguiente;
            
        }
        cout << endl;
        actual = actual->siguiente;
    }
}


/* Analisis de lo que hay que hacer
Hay que tener dos listas, y una "pila"

Las dos listas son para hacer una matriz de nxm

Se debe hacer un método de trabajar con la matriz

habrá una "pila" que pase de un lado a otro

hay distintas formas de realizar esto, una estructura de matriz
dos listas, vectores, etc.

*/

// Número aleatorio
int numeroAleatorio(int rango){
    int numero;
    numero = rand()%rango + 1;
    return numero;
}

/*
Se requiere que se analice columna, de columna en columna, por lo que no se debe revisar
un nodo distinto que el de la columna matriz

la fila con el mismo indice, entonces es dependiente del indice de fila y columna donde editar

entonces se analizan las filas con el mismo indice de columna

se recorre la matriz y se analizan los nodos que tengan ese mismo indice de columna
¿Es el indice de la fila necesario?

hay que hacer un buscador para saber donde está el contenedor que se quiere obtener, en que fila y posición

*/

FilaYColumna buscadorMatriz(Matriz* cabeza, string nombreDeEmpresa, int numeroDeEmpresa){
    // matriz es fila, nodo es columna, actual recorre las filas y actualNodo recorre las columnas
    FilaYColumna encontrado;
    Matriz* actual = cabeza;
    
    // definiendo el caso en que no encuentre nada
    encontrado.columna=-1;
    encontrado.fila=-1;
    
    if (cabeza == nullptr)
    {
        cout<< "Está vacia la matriz" << endl;
        
        return encontrado;
    }

    while (actual != nullptr)
    {
        Nodo* actualNodo = actual->n;
        while (actualNodo != nullptr)
        {
            if (actualNodo->dato.numero == numeroDeEmpresa && actualNodo->dato.empresa == nombreDeEmpresa)
            {
                encontrado.columna= actualNodo->indice;
                encontrado.fila=actual->indice;
                return encontrado;
            }
            
            actualNodo = actualNodo->siguiente;
            
        }
        actual = actual->siguiente;
    }
    // no se encontró
    return encontrado;
}

// hecho pensando que se editara uno en particular
void editarMatriz(Matriz* cabeza,int indiceFila, int indiceColumna, Dato datoIngresado){

    // matriz es fila, nodo es columna

    Matriz* actual = cabeza;
    if (cabeza == nullptr)
    {
        cout<< "Está vacia la matriz" << endl;
        return;
    }

    while (actual != nullptr)
    {
        Nodo* actualNodo = actual->n;
        //cout << "[" << actual->indice << "]";
        while (actualNodo != nullptr)
        {
            // Aqui se debe de modificar el numero y el dato de la empresa
            //cout << "|" << actualNodo->dato.numero << "/" << actualNodo->dato.empresa << "|";
            if (actual->indice == indiceFila && actualNodo->indice == indiceColumna)
            {
                actualNodo->dato = datoIngresado;
            }
            
            /*if (actualNodo->dato.numero == 0 && actualNodo->dato.numero !=0)
            {
                cout;
            }*/
            
            actualNodo = actualNodo->siguiente;
            
        }
        //cout << endl;
        actual = actual->siguiente;
    }
    return;
}

// agrega mientras haya 0
void agregarEnMatriz(Matriz* cabeza, int indiceColumna, Dato datoIngresado){

    // matriz es fila, nodo es columna
    Nodo* temporal = nullptr;

    Matriz* actual = cabeza;
    if (cabeza == nullptr)
    {
        cout<< "Está vacia la matriz" << endl;
        return;
    }

    while (actual != nullptr)
    {
        Nodo* actualNodo = actual->n;
        //cout << "[" << actual->indice << "]";
        while (actualNodo != nullptr)
        {
            // Aqui se debe de modificar el numero y el dato de la empresa
            //cout << "|" << actualNodo->dato.numero << "/" << actualNodo->dato.empresa << "|";
            if (actualNodo->indice == indiceColumna && actualNodo->dato.numero == 0)
            {
                // así este nodo temporal va cambiando mientras esté disponible y cambia el último disponible
                temporal = actualNodo;
            }
            actualNodo = actualNodo->siguiente;
            
        }
        //cout << endl;
        actual = actual->siguiente;
        
    }
    if (temporal != nullptr)
    {
        temporal->dato = datoIngresado;
    }
    else if (temporal == nullptr && indiceColumna <= cabeza->maximo)
    {
        return agregarEnMatriz(cabeza, indiceColumna+1, datoIngresado);
    }
    else
    {
        cout << "No se puede añadir aqui" << endl;
        return;
    }
}

// Buscando en la matriz
Nodo* buscarYGuardar(Matriz* cabeza, string nombreDeEmpresa, int numeroDeEmpresa, int columna){
    Nodo* pilaSobre = nullptr;
    Matriz* actual = cabeza;
    
    if (cabeza == nullptr)
    {
        cout<< "Está vacia la matriz" << endl;
        
        return pilaSobre;
    }

    while (actual != nullptr)
    {
        Nodo* actualNodo = actual->n;
        while (actualNodo != nullptr)
        {
            // si encuentra el nodo que se busca devuelve la pila de objetos que tenia encima
            if (actualNodo->dato.numero == numeroDeEmpresa && actualNodo->dato.empresa == nombreDeEmpresa)
            {
                return pilaSobre;
            }
            if (actualNodo->indice == columna)
            {
                push(pilaSobre, actualNodo->dato, actual->maximo);
            }
            
            
            actualNodo = actualNodo->siguiente;
            
        }
        actual = actual->siguiente;
    }
    // no se encontró
    return pilaSobre;
}




// se encarga de buscar y borrar donde estaba ese contenedor
void buscarYSacarContenedor(Matriz* cabeza){
    Nodo* pilaEncima = nullptr;
    Nodo* pilaEncimaInversa = nullptr;
    string empresaContenedor;
    int numeroContenedor;
    
    Dato eliminar;
    eliminar.empresa = "emp0";
    eliminar.numero = 0;

    FilaYColumna buscado;

    cout << "Ingrese la empresa que buscar" << endl;
    cin >> empresaContenedor;
    cout << "Ingrese el numero del contenedor que buscar:" << endl;
    cin >> numeroContenedor;
    buscado = buscadorMatriz(cabeza, empresaContenedor, numeroContenedor);

    if (buscado.fila <=0)
    {
        cout << "No se encontro" << endl;
        return;
    }else
    {
        // se encuentra el dato
        cout << "Se encontro en:"<< buscado.fila <<"," << buscado.columna << endl;
        // se guardan todos los datos que estaban encima
        pilaEncimaInversa = buscarYGuardar(cabeza, empresaContenedor, numeroContenedor, buscado.columna);

        while (!pila_vacia(pilaEncimaInversa))
        {
            Dato datoQueEstabaEncimaInversa;
            datoQueEstabaEncimaInversa = pop_con_dato(pilaEncimaInversa);
            push(pilaEncima, datoQueEstabaEncimaInversa, cabeza->maximo);
        }
        
        
        int iteradorFilas = cabeza->maximo;
        
        while (!pila_vacia(pilaEncima))
        {
            Dato datoQueEstabaEncima;
            editarMatriz(cabeza, iteradorFilas, buscado.columna, eliminar);
            iteradorFilas= iteradorFilas - 1;
            cout << "Editando Matriz" << endl;
            datoQueEstabaEncima = pop_con_dato(pilaEncima);
            int filaAgregar =(buscado.columna +1 % cabeza->maximo);
            cout << filaAgregar << datoQueEstabaEncima.empresa << datoQueEstabaEncima.numero << endl;
            agregarEnMatriz(cabeza, filaAgregar, datoQueEstabaEncima);
            mostrarDatoMatriz(cabeza);
        }
    }
    cout<< "Quitando último contenedor" <<endl;
    editarMatriz(cabeza, buscado.fila, buscado.columna, eliminar);
    mostrarDatoMatriz(cabeza);

    return;
    
    
}

// Main principal
int main(){
    srand(time(NULL));
    Nodo* pila = nullptr;
    Nodo* pilaDatosAleatorios = nullptr;

    Matriz* matriz = nullptr;
    int maximoColumnas, numeroDeEmpresa, maximoFilas, maximoAleatorio, indice_fila, indice_columna;
    Dato dato_a_colocar, opc;

    string nombresEmpresas[3];
    nombresEmpresas[0] = "emp1";
    nombresEmpresas[1] = "emp2";
    nombresEmpresas[2] = "emp3";


    cout <<"Ingrese la cantidad maxima de columnas" << endl;
    cin >> maximoFilas;
    //push(pila, opc, maximo);

    cout <<"Ingrese la cantidad maxima de filas" << endl;
    cin >> maximoColumnas;

    maximoAleatorio = 4;


    while(!pila_llena(pilaDatosAleatorios))
    {
    opc.numero = numeroAleatorio(3);
    opc.empresa = nombresEmpresas[(numeroAleatorio(3)-1)];
    push(pilaDatosAleatorios, opc, maximoAleatorio);
    }

    while(!pila_llena(pila))
    {
    opc.numero = 0;
    opc.empresa = "emp0";
    push(pila, opc, maximoFilas);
    }
    
    while(!matriz_llena(matriz))
    {
        // se necesita clonar cada pila para que tenga dirección de memoria distinta cada nodo
        Nodo* pilaClonada = clonarPila(pila);
        push_Matriz(matriz, pilaClonada, maximoColumnas);
    }

    cout << "Mostrando pila" << endl;
    mostrar(pila);
    
  
    cout << "Mostrando matriz segun indice" << endl;
    mostrarIndiceMatriz(matriz);    

    cout << "Mostrando matriz segun dato en la fila" << endl;
    mostrarDatoMatriz(matriz);    

    cout << "Editando Matriz" << endl;

    // dato para probar, banana en referencia a los minions
    dato_a_colocar.empresa = "banana";
    dato_a_colocar.numero = 180;

    agregarEnMatriz(matriz, 1, dato_a_colocar);
    agregarEnMatriz(matriz, 1, dato_a_colocar);

    while (!pila_vacia(pilaDatosAleatorios))
    {
        cout << "Editando Matriz" << endl;
        Dato datoAleatorio;
        datoAleatorio = pop_con_dato(pilaDatosAleatorios);
        agregarEnMatriz(matriz, numeroAleatorio(maximoColumnas), datoAleatorio);
    }

    cout << "Mostrando matriz segun dato en la fila" << endl;
    mostrarDatoMatriz(matriz);
    
    FilaYColumna buscado;
    
    buscado = buscadorMatriz(matriz, "banana", 180);
    cout<< "Se halló en la fila: "<< buscado.fila << " y en la columna: "<< buscado.columna << endl;

    buscarYSacarContenedor(matriz);

    destruirPila(pila);
    
    return 0;
}
