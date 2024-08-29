#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;;

// Estructura del paciente, le añadi el id para que elimine al que corresponde
struct Paciente
{
    int id;
    string nombre;
    int edad;
    float peso, altura;
};
// Nodo que al final acaba siendo la pila de pacientes
struct Nodo
{
    Paciente p;
    Nodo* siguiente;
};

// Crea el nodo para añadir al paciente a su data, así separando el nodo con la estructura del paciente
Nodo* crearNodo(Paciente paciente){
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->p = paciente;
    nuevoNodo->siguiente = nullptr;
    return nuevoNodo;
}

// Agrega como una pila
void agregarAlInicio(Nodo** cabeza, Paciente paciente){
    Nodo* nuevoNodo = crearNodo(paciente);
    nuevoNodo->siguiente = *cabeza;
    *cabeza = nuevoNodo;
}

// Recorre la lista y muestra los datos
void mostrarLista(Nodo* cabeza){
    Nodo* actual = cabeza;
    while (actual != nullptr){
        cout << "ID: " << actual->p.id << ", Nombre: " << actual->p.nombre << ", Edad: " << actual->p.edad << "\nPeso: " << actual->p.peso <<", Altura: " << actual->p.altura << endl;
        actual = actual->siguiente;
    }
}

// Elimina la lista para de esta forma liberar espacio de la memoria ya que el new de crear nodo consume espacio
void destruirLista(Nodo* cabeza){
    while (cabeza != nullptr){
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Busca un Nodo en particular según el id
void buscarNodo(Nodo** cabeza, int id){
    Nodo* actual = *cabeza;

    while (actual != nullptr){
        if (actual->p.id == id){
            cout << "Paciente encontrado." << endl;
            cout << "ID: " << actual->p.id << ", Nombre: " << actual->p.nombre << ", Edad: " << actual->p.edad << "\nPeso: " << actual->p.peso <<", Altura: " << actual->p.altura << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Paciente no encontrado." << endl;
}

// Elimina el nodo según el id, no se si colocar ID o id, a veces le puse identificacion por eso
void eliminarNodo(Nodo** cabeza, int id){
    Nodo* actual = *cabeza;
    Nodo* anterior = nullptr;

    while (actual != nullptr && actual->p.id != id){
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr){
        cout << "Paciente no encontrado." << endl;
        return;
    }

    if (anterior == nullptr){
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
}

// Crea al paciente, aqui le puse identificacion
Paciente* crearPaciente(int identificacion){
    
    string nombre;
    int edad;
    float peso, altura;

    while (true)
    {
        try
        {
            cout << "Ingrese al paciente" << endl;
            cout << "Ingrese el nombre del paciente" << endl;
            cin >> nombre;
            cout << "Ingrese la edad del paciente" << endl;
            cin >> edad;
            cout << "Ingrese el peso del paciente" << endl;
            cin >> peso;
            cout << "Ingrese la altura del paciente" << endl;
            cin >> altura;
            break;                
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << '\n'<<endl;
            cout << "Por favor ingrese valores correspondientes" << endl;
        }
        
    }
    Paciente* pacienteIngresado = new Paciente;

    pacienteIngresado -> nombre = nombre;
    pacienteIngresado -> edad = edad;
    pacienteIngresado -> peso = peso;
    pacienteIngresado -> altura = altura;
    pacienteIngresado -> id = identificacion;
    
    return pacienteIngresado;

}

int main(){
    Nodo* cabeza = nullptr;
    int contador = 1;
    int idEliminar = 0, idBuscar = 0; // Inician en 0 por si le dan a buscar un paciente y el contador de los pacientes inicia con 1

    // Ejemplo de estructura de paciente id, nombre, edad, peso, altura
    // Struct Paciente p = {1, "Alejandro",35, 70, 1.5};
    while (true){   
    int opcion;
    cout << "\nIngrese su opción\n1. Agregar paciente\n2. Eliminar paciente\n3. Buscar paciente\n4. Mostrar lista\n5. Salir" << endl;
    cin >> opcion;

    // Aquí tenia un switch que me daba error, increíble que funcione con un if
    if (opcion == 1) {
        cout << "\nFunción de agregar" << endl;
        Paciente* p = crearPaciente(contador);
        agregarAlInicio(&cabeza, *p);
        contador++;
    } 
    else if (opcion == 2) {
        cout << "\nFunción de eliminar" << endl;
        cout << "Ingrese el ID del paciente a eliminar: " << endl;
        cin >> idEliminar;
        eliminarNodo(&cabeza, idEliminar);
    } 
    else if (opcion == 3) {
        cout << "\nFunción de buscar paciente" << endl;
        cout << "Ingrese el ID del paciente a buscar: " << endl;
        cin >> idBuscar;
        buscarNodo(&cabeza, idBuscar);
    } 
    else if (opcion == 4) {
        cout << "\nMostrando los pacientes" << endl;
        mostrarLista(cabeza);
    } 
    else if (opcion == 5) {
        cout << "\nSaliendo del menú" << endl;
        break;
    } 
    else {
        cout << "\nIngrese un valor válido" << endl;
    }
}

destruirLista(cabeza);

return 0;

}