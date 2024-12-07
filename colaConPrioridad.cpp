#include <iostream>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

// Variable global para que se use cada vez que se agregue en el listado para el id
int contador = 1;


// Estructuras

// Estructura del paciente, le añadi el id para que elimine al que corresponde
struct Paciente
{
    int id;
    string nombre;
    int edad;
    float peso, altura, IMC, A1C, factorDePosicion;
    // IMC: Índice de masa corporal, A1C prueba en porcentaje de cuanto de prioridad tiene
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


/*

Pensamientos respecto a las colas y pilas

Las colas y las pilas tienen la misma estructura pero distinta forma de recorrerlas y de
trabajar con ellas como por ejemplo, al momento de agregar se cambia la "cabeza", mientras que
en las colas se cambia el siguiente nodo. Por ello podemos utilizar esto al momento de agregar

Entonces el como cambiar las funciones permite trabajar tanto con nodo como lista según el caso
*/

// Agrega como una pila
void agregarAlInicio(Nodo** cabeza, Paciente paciente){
    Nodo* nuevoNodo = crearNodo(paciente);
    nuevoNodo->siguiente = *cabeza;
    *cabeza = nuevoNodo;
}

// Agrega como cola
void agregarAlFinal(Nodo*& cabeza, Paciente paciente){
    Nodo* nuevoNodo = crearNodo(paciente);
    // Se recorre hasta que sea nulo, ahí se agrega cuando sea nulo
    if (cabeza == nullptr)
    {
        cabeza = nuevoNodo;
    }
    else{
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
        
}


/*

Pensamientos de como trabajar y realizar la parte de escoger la prioridad

Siendo de esta forma el como se agrega en los dos casos se puede implementar
una separación de los datos mediante el como se agrega, en vez de solo consultar el while

Para trabajar el problema de los datos hay distintas formas
Habiendo distintos tipos de algoritmos de ordenamientos
El escoger en que parte se ingresa el nodo, sería el equivalente a injection sort
Entonces hay que cambiar el como se agrega para hacer la cola de prioridad

Como calcular la prioridad, tenemos variables que podemos tomar en cuenta
AC1, IMC.

IMC  x AC1 para calcular la prioridad.

Si Ac1 es bajo no debe de ser tomado tanto en cuenta
Si el IMC es bajo pero el AC1 es alto debe tomarse en cuenta ya que puede ser diabetes tipo 1

El IMC es posible el factor de riesgo de diabetes tipo 2
Entonces por ello se debe de adaptar estos factores de riesgo

Se podría hacer una múltiplicación para IMC Y AC1, pero eso no toma el factor de riesgo diabetes tipo 1

definicion de la prioridad

si a1c >= a 5.7 posibilidad de pre diabetes, factor de riesgo
si a1c <5.7 y distinto de 0
si es 0, es posible que sea que no se tienen datos, por ello se debe tomar distinto al a1c "normal"

Se recomienda tener 7% para las personas que sufren hipoglicemia (bajada de azúcar y algunas diabetes complicadas)

entonces si a1c >= 5.7
y si IMC > 25
ac1 * IMC

Supuestamente
si IMC < 18.5
De esta forma se toma como un valor cada vez mayor según el IMC más bajo, ya que son pacientes con
riesgos de diabetes tipo 1
A1c * (35.5-IMC)*2

No tomaré en cuenta la edad ya que un paciente joven y uno de tercera edad es importante en ambos casos
detectar la diabetes tipo 1 y tipo 2.

*/


// Trabajo con cola de prioridad

// Para calcular el riesgo
float calcularFactorRiesgo(Paciente& paciente) {
    if (paciente.A1C >= 5.7 && paciente.IMC >= 25) {
        return paciente.A1C * paciente.IMC;
    }
    else if (paciente.A1C >= 5.7 && paciente.IMC <= 18.5) {
        return paciente.A1C * (35.5 - paciente.IMC) * 2;
    }
    else {
        return 0; // Por ejemplo, si no se cumple ninguna condición (tiene IMC normal y azucar normal, tiene valor 0 uno de los dos)
    }
}

// Función de cola con Prioridad
void agregarConPrioridad(Nodo*& cabeza, Paciente paciente){

    Nodo* nuevoNodo = crearNodo(paciente);

    if (cabeza == nullptr || cabeza->p.factorDePosicion < paciente.factorDePosicion) {
        // Si la cola está vacía o la prioridad del nuevo paciente es mayor que la del primero
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
    }
    else{
        Nodo* actual = cabeza;
        // Recorre la lista hasta encontrar la posición adecuada
        while (actual->siguiente != nullptr && actual->siguiente->p.factorDePosicion >= paciente.factorDePosicion) {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }
}

// Trabajar con carga se refiere a trabajar con los valores del cargado de datos
void trabajar_con_carga( string nombre, string edad, string altura, string peso, string AC1, Nodo*& cabeza, Nodo*& cabezaCola, Nodo*& cabezaPrioridad){

    Paciente* pacienteIngresado = new Paciente;

    float edadIngreso = stof(edad);
    float pesoIngreso = stof(peso);
    float alturaIngreso = stof(altura);
    float AC1Ingreso = stof(AC1);


    pacienteIngresado -> nombre = nombre;
    pacienteIngresado -> edad = edadIngreso;
    pacienteIngresado -> peso = pesoIngreso;
    pacienteIngresado -> altura = alturaIngreso;
    pacienteIngresado -> A1C = AC1Ingreso;
    pacienteIngresado -> IMC = pesoIngreso/(alturaIngreso*alturaIngreso);
    pacienteIngresado -> factorDePosicion = calcularFactorRiesgo(*pacienteIngresado);


    pacienteIngresado -> id = contador;
    
    // Para tener la comparación
    agregarAlInicio(&cabeza, *pacienteIngresado);
    agregarAlFinal(cabezaCola, *pacienteIngresado);
    agregarConPrioridad(cabezaPrioridad, *pacienteIngresado);
}


// Lee el archivo y lo mete de inmediato en las colas y la pila
void cargarPacientes(const string& nombreDeArchivo, Nodo*& cabeza, Nodo*& cabezaCola, Nodo*& cabezaPrioridad) {
    ifstream file(nombreDeArchivo);
    if (!file) {
        cerr << "Error al cargar el archivo: " << nombreDeArchivo << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        string nombre, edad, altura, peso, AC1;

        getline(iss, nombre, ',');
        getline(iss, edad, ',');
        getline(iss, altura, ',');
        getline(iss, peso, ',');
        getline(iss, AC1);
        contador++;
        trabajar_con_carga(nombre, edad, altura, peso, AC1, cabeza, cabezaCola, cabezaPrioridad);
        
    }
    file.close();
}

// Funciones de listas colas, etc

// Funciona para cualquier tipo de lista, pila/cola/colaPrioridad
int contarLista(Nodo* cabeza){
    int i=0;
    while (cabeza != nullptr){
        i++;
        cabeza = cabeza->siguiente;
    }
    return i;
}

// Elimina la lista para de esta forma liberar espacio de la memoria ya que el new de crear nodo consume espacio
void destruirLista(Nodo* cabeza){
    while (cabeza != nullptr){
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
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
        std::cout << "Paciente no encontrado." << endl;
        return;
    }

    if (anterior == nullptr){
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
}

void datosGenerales(Nodo* actual){
        std::cout << "El paciente id:" << actual -> p.id << endl;
        std::cout << "El paciente " << actual -> p.nombre << " tiene su factor de prioridad de: " << actual -> p.factorDePosicion;
        std::cout << "\nEl indice de masa corporal del Paciente es: " << actual -> p.IMC << endl;
}


// Función para decirle que tiene según IMC
void IMCDatos(float IMC){
    if (IMC >=30 ){
        std::cout << "Tiene obesidad" << endl;
    }
    if (IMC >= 24.9 && IMC < 30){
        std::cout << "Tiene sobrepeso" << endl;
    }
    if (IMC >= 18.5 && IMC < 24.9){
        std::cout << "Tiene el rango normal de peso, saludable" << endl;
    }
    if (IMC < 18.5 ){
        std::cout << "Tiene peso insuficiente" << endl;
    }
}

void A1CDatos(float A1C){
    if (A1C >=6.5 ){
        std::cout << "Tiene posibilidad de diabetes" << endl;
    }
    if (A1C >= 5.7 && A1C < 6.5){
        std::cout << "Tiene posibilidad de pre diabetes" << endl;
    }
    if (A1C < 5.7 ){
        std::cout << "Tiene posibilidad de estar normal" << endl;
    }
}


// Busca un Nodo en particular según el id
void buscarNodo(Nodo** cabeza, int id){
    Nodo* actual = *cabeza;

    while (actual != nullptr){
        if (actual->p.id == id){
            std::cout << "Paciente encontrado." << endl;
            std::cout << "ID: " << actual->p.id << ", Nombre: " << actual->p.nombre << ", Edad: " << actual->p.edad << "\nPeso: " << actual->p.peso <<", Altura: " << actual->p.altura << endl;
            float IMC = (actual ->p.peso)/( actual ->p.altura * actual ->p.altura);
            std::cout << "El indice de masa corporal del Paciente es: " << IMC << endl;
            IMCDatos(IMC);
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "Paciente no encontrado." << endl;
}
// Recorre la lista y muestra los datos
void mostrarLista(Nodo* cabeza){
    Nodo* actual = cabeza;
    
    while (actual != nullptr){
        datosGenerales(actual);
        float imc= actual->p.IMC, a1c=actual->p.A1C;
        IMCDatos(imc);
        A1CDatos(a1c);
        actual = actual->siguiente;
    }
}


// Mostrar los promedios, respecto al IMC no estoy tan seguro
void mostrarPromedios(Nodo* cabeza){
    Nodo* actual = cabeza;
    float contadorDePersonas = 0, contadorDePeso = 0,contadorDeAltura = 0;
    float promedioAltura, promedioDePeso;

    while (actual != nullptr){
        contadorDePersonas ++;
        contadorDePeso = contadorDePeso + actual -> p.peso;
        contadorDeAltura = contadorDeAltura + actual -> p.altura;
        actual = actual->siguiente;
    }
    if (contadorDePersonas > 0){
        std::cout << "El promedio de altura de las personas es: "<< contadorDeAltura/contadorDePersonas << endl;
        std::cout << "El promedio del peso de las personas es: "<< contadorDePeso/contadorDePersonas << endl;
        float IMC = (contadorDePeso/contadorDePersonas)/((contadorDeAltura/contadorDePersonas)*(contadorDeAltura/contadorDePersonas));
        std::cout << "El promedio IMC de las personas es: " <<  IMC << " y la lista en general:" << endl;
        IMCDatos(IMC);
    }
}

void mostrandoDiscriminando(Nodo* cabeza, bool diabetes, bool IMC, bool bandera){
    // si bandera es verdadero ve diabetes, sino ve imc, si diabetees es verdadero ve a los diabetes, sino a los pre diabetes, en IMC verdadero ve a los sobre lo normal, falso a lo bajo normal
//    1. Ver a posibles diabeticos\n2. Ver a posibles pre diabeticos\n3. Ver a pacientes con IMC bajo\n4. Ver a pacientes con IMC alto" << endl;
    Nodo* actual = cabeza;
    // bandera true -> ve diabetes, false ve IMC
    while (actual != nullptr){
        if (bandera)
        {
            // si diabetes true = muestra a aquellos con valores sobre 6.5 en A1C
            if(diabetes && actual->p.A1C >= 6.5){
                datosGenerales(actual);
                IMCDatos(actual->p.IMC);
                A1CDatos(actual->p.A1C);
            // si diabetes false = muestra a aquellos con valores sobre 5.7 y menores a 6.5 en A1C
            }else{
                if (actual->p.A1C >= 5.7 && actual->p.A1C < 6.5){
                datosGenerales(actual);
                IMCDatos(actual->p.IMC);
                A1CDatos(actual->p.A1C);
                }
            }
        }
        else{
            // si el imc es verdadero, busca a aquellos que tienen sobrepeso
            if (IMC && actual->p.IMC >= 24.9)
            {
                datosGenerales(actual);
                IMCDatos(actual->p.IMC);
                A1CDatos(actual->p.A1C);
            }else{
                if (!IMC && actual->p.IMC < 18.5){
                    datosGenerales(actual);
                    IMCDatos(actual->p.IMC);
                    A1CDatos(actual->p.A1C);
                }

            }
            
        }
        
        actual = actual->siguiente;
    }

}



void mostrarEnEspecifico(Nodo* cabeza, Nodo* cabezaCola, Nodo* cabezaPrioridad){
    int opcion;
    std::cout << "\nIngrese su opción\n0. Salir\n1. Ver a posibles diabeticos\n2. Ver a posibles pre diabeticos\n3. Ver a pacientes con IMC bajo\n4. Ver a pacientes con IMC alto" << endl;
    cin >> opcion;
    if (opcion == 0) {
        std::cout << "\nSaliendo del menú" << endl;
    }
    // si bandera es verdadero ve diabetes, sino ve imc, si diabetees es verdadero ve a los diabetes, sino a los pre diabetes, en IMC verdadero ve a los sobre lo normal, falso a lo bajo normal

    else if (opcion == 1){
        std::cout<<"Viendo a la pila\n";
        mostrandoDiscriminando(cabeza, true, false, true);
        std::cout<<"\nViendo a la cola\n";
        mostrandoDiscriminando(cabezaCola, true, false, true);
        std::cout<<"\nViendo a la cola de prioridad";
        mostrandoDiscriminando(cabezaPrioridad, true, false, true);

    }
    else if (opcion == 2){
        std::cout<<"Viendo a la pila\n";
        mostrandoDiscriminando(cabeza, false, false, true);
        std::cout<<"\nViendo a la cola\n";
        mostrandoDiscriminando(cabezaCola, false, false, true);
        std::cout<<"\nViendo a la cola de prioridad";
        mostrandoDiscriminando(cabezaPrioridad, false, false, true);

    }
    else if (opcion == 3){
        std::cout<<"Viendo a la pila\n";
        mostrandoDiscriminando(cabeza, false, false, false);
        std::cout<<"\nViendo a la cola\n";
        mostrandoDiscriminando(cabezaCola, false, false, false);
        std::cout<<"\nViendo a la cola de prioridad";
        mostrandoDiscriminando(cabezaPrioridad, false, false, false);

    }
    else if (opcion == 4){
        std::cout<<"Viendo a la pila\n";
        mostrandoDiscriminando(cabeza, false, true, false);
        std::cout<<"\nViendo a la cola\n";
        mostrandoDiscriminando(cabezaCola, false, true, false);
        std::cout<<"\nViendo a la cola de prioridad";
        mostrandoDiscriminando(cabezaPrioridad, false, true, false);

    }
    else{
        std::cout<<"Puso valor erroneo, volviendo al menú"<<endl;
    }
}

// Crea al paciente, aqui le puse identificacion
Paciente* crearPaciente(int identificacion){
    
    string nombre;
    int edad;
    float peso, altura, A1C;

    while (true)
    {
        try
        {
            std::cout << "Ingrese al paciente" << endl;
            std::cout << "Ingrese el nombre del paciente" << endl;
            cin >> nombre;
            std::cout << "Ingrese la edad del paciente" << endl;
            cin >> edad;
            std::cout << "Ingrese el peso del paciente" << endl;
            cin >> peso;
            std::cout << "Ingrese la altura del paciente" << endl;
            cin >> altura;
            std::cout << "Ingrese el A1C del paciente" << endl;
            cin >> A1C;
            break;                
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n'<<endl;
            std::cout << "Por favor ingrese valores correspondientes" << endl;
        }
        
    }
    Paciente* pacienteIngresado = new Paciente;

    pacienteIngresado -> nombre = nombre;
    pacienteIngresado -> edad = edad;
    pacienteIngresado -> peso = peso;
    pacienteIngresado -> altura = altura;
    pacienteIngresado -> id = identificacion;
    pacienteIngresado -> IMC = peso/(altura*altura);
    pacienteIngresado -> A1C = A1C;
    pacienteIngresado -> factorDePosicion = calcularFactorRiesgo(*pacienteIngresado);

    
    return pacienteIngresado;

}

int main(){
    Nodo* cabeza = nullptr;
    Nodo* cabezaCola = nullptr;
    Nodo* cabezaPrioridad = nullptr;
    int idEliminar = 0, idBuscar = 0; // Inician en 0 por si le dan a buscar un paciente y el contador de los pacientes inicia con 1

    // Ejemplo de estructura de paciente id, nombre, edad, peso, altura
    // Struct Paciente p = {1, "Alejandro",35, 70, 1.5};
    while (true){   
    int opcion;
    std::cout << "\nIngrese su opción\n0. Salir\n1. Agregar paciente\n2. Eliminar paciente\n3. Buscar paciente\n4. Mostrar lista\n5. Mostrar Promedios\n6. Cargar Archivo" << endl;
    std::cout << "7. Contar las listas\n8. Eliminar las listas\n9.Mostrar Especificos" << endl;
    cin >> opcion;

    // Aquí tenia un switch que me daba error, increíble que funcione con un if y no con el switch
    if (opcion == 0) {
        std::cout << "\nSaliendo del menú" << endl;
        break;
    }    
    if (opcion == 1) {
        std::cout << "\nFunción de agregar" << endl;
        contador++;
        Paciente* p = crearPaciente(contador);
        agregarAlInicio(&cabeza, *p);
        agregarAlFinal(cabezaCola, *p);
        agregarConPrioridad(cabezaPrioridad, *p);
    } 
    else if (opcion == 2) {
        std::cout << "\nFunción de eliminar" << endl;
        std::cout << "Ingrese el ID del paciente a eliminar: " << endl;
        cin >> idEliminar;
        eliminarNodo(&cabeza, idEliminar);
    } 
    else if (opcion == 3) {
        std::cout << "\nFunción de buscar paciente" << endl;
        std::cout << "Ingrese el ID del paciente a buscar: " << endl;
        cin >> idBuscar;
        buscarNodo(&cabeza, idBuscar);
    } 
    else if (opcion == 4) {
        std::cout << "\nMostrando los pacientes" << endl;
        std::cout << "\nMostrando los pacientes como pila" << endl;
        mostrarLista(cabeza);
        std::cout << "\nMostrando los pacientes como cola" << endl;
        mostrarLista(cabezaCola);

        std::cout << "\nMostrando los pacientes como cola con prioridad" << endl;
        mostrarLista(cabezaPrioridad);

    }
    else if (opcion == 5) {
        std::cout << "\nMostrando los promedios" << endl;
        mostrarPromedios(cabeza);
    } 
    else if (opcion == 6) {
        std::cout << "\nCargando Lista" << endl;
        cargarPacientes("patient_list.csv", cabeza, cabezaCola, cabezaPrioridad);
    }
    else if (opcion == 7) {
        std::cout << "\nContando en las Listas" << endl;
        
        std::cout << "En la pila hay:"<< contarLista(cabeza) << endl;
        
        std::cout << "En la cola hay:"<< contarLista(cabezaCola) << endl;

        std::cout << "En la cola con prioridad hay:"<< contarLista(cabezaPrioridad)  << endl;
    }
    else if (opcion == 8) {
        std::cout << "\nEliminando Listas" << endl;
        destruirLista(cabeza);
        destruirLista(cabezaCola);
        destruirLista(cabezaPrioridad);
    }
    else if (opcion == 9) {
        mostrarEnEspecifico(cabeza,cabezaCola,cabezaPrioridad);
    } 
    else {
        std::cout << "\nIngrese un valor válido" << endl;
    }
}

destruirLista(cabeza);
destruirLista(cabezaCola);
destruirLista(cabezaPrioridad);

return 0;

}