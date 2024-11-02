#include <stdlib.h>
#include <iostream>

// para randoms
#include <cstdlib>
#include <ctime>


/*
Nombre: Gabriel Rojas
Este código está hecho según lo que creo que es los hash

Implementar algoritmos:
hash:

*Reasignacion Prueba Lineal (L).
*Reasignacion Prueba Cuadratica (C).
*Reasignacion Doble Direccion Hash (D).

Búsqueda correspondiente a las reasignaciones adecuadas


complilar:
g++ -o lab9 lab_9.cpp 

./lab9 n opc

*/

using namespace std;

int generate_random(int n){
    return rand() % n;
}

int hashNumero(int, int); // funcion para que funcione llamar hash

// función para realizar la vista de los elementos
void print_array(int array[], int n){
    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " | ";
    }
    cout << endl;
}

// Si no encuentra Soluciona la colisión: 


// Siguiente k a k (k+1)%n 
void reasignacionHashLineal(int arrayHash[], int numero, int posicion, int n){

    cout << "Hubo colisión en: " << posicion << ", entro a la reasignación lineal" << endl;
    
    while (true)
    {
        // revisa la posición siguiente, va iterando usando k
        if ( arrayHash[ ( posicion + 1 )% n] == -1)
        {
            cout << "Fue reasignado en " << ( posicion + 1 )% n << endl;
            arrayHash[ ( posicion + 1 )% n] = numero;
            break; // lo guardo
        }else{
            posicion ++;
        }
        
    }
    
}

// busqueda( arrayHash, numero a buscar, posicion hash, n del arreglo)
void busquedaLineal(int arrayHash[], int numero, int posicion, int n){
    
    // esto es únicamente si se mantiene las normas aleatorias, sino se tiene que sacar
    if (numero > n)
    {
        cout << "Es un número mayor de los posibles" << endl;
        return; // tiene un return para evitar que se recorra
    }

    if (arrayHash[posicion] == numero)
        cout << "Se encontro el número en la posicion:" << posicion << endl;
    else{
        cout << "Se busca el numero: " << numero << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "Hubo colisión en: " << posicion << ", entro a la reasignación lineal" << endl;
            if (arrayHash[( posicion + i + 1 )% n] == numero)
            {
                cout << "Fue encontrado en " << ( posicion + i + 1 )% n << endl;
                return;
            }
        }
        cout << "No se encuentra el número" << endl;
    }
    
    
}


// (D + i²) % n +1 
void reasignacionHashCuadratico(int arrayHash[], int numero, int posicion, int n){
    int i = 1;

    cout << "Hubo colisión en: " << posicion << ", entro a la reasignación cuadrática" << endl;


    while (true)
    {
        // revisa la posición + i², va iterando usando k
        if ( arrayHash[ ( posicion + i*i )% n] == -1)
        {
            cout << "Fue reasignado en " << ( posicion + i*i )% n << endl;
            arrayHash[ ( posicion + i*i )% n] = numero;
            break; // lo guardo se rompe el ciclo
        }else{
            i ++;
        }
        
    }

}

// función hecha para comprobar si entro en todos los elementos de un array
bool compruebaArrayVisitados(int array[], int n){
    for (int i = 0; i < n; i++)
    {
        if (array[i] ==-1)
        {
            return false;
        }
        
    }
    return true;
    
}

void busquedaCuadratica(int arrayHash[], int numero, int posicion, int n){
    int arrayVisitados[n];
    for (int i = 0; i < n; i++)
    {
        arrayVisitados[i] = -1;
    }
    
    int i = 1;
    if (numero > n)
    {
        cout << "Es un número mayor de los posibles" << endl;
        return; // tiene un return para evitar que se recorra
    }

    if (arrayHash[posicion] == numero)
        cout << "Se encontro el número en la posicion:" << posicion << endl;
    else{
        cout << "Se busca el numero: " << numero << endl;

        while (true)
        {
            cout << "Hubo colisión en: " << posicion << ", entro a la reasignación cuadratica" << endl;
            if (arrayHash[( posicion + i*i )% n] == numero)
            {
                cout << "Fue encontrado en " << ( posicion + i*i )% n << endl;
                return;
            }
            arrayVisitados[( posicion + i*i )% n] = 1;
            
            // si todos están visitados, no está el número
            if (compruebaArrayVisitados)
            {
                cout << "No se encuentra el número" << endl;
                break;
            }
            
            i++;
        }
        
        /* Por si acaso mantengo este
        for (int i = 1; i <= n; i++)
        {
            cout << "Hubo colisión en: " << posicion << ", entro a la reasignación cuadratica" << endl;
            if (arrayHash[( posicion + i*i )% n] == numero)
            {
                cout << "Fue encontrado en " << ( posicion + i*i )% n << endl;
                return;
            }
        }
        cout << "No se encuentra el número" << endl;
        */
    }

}


// no solucionado aún
// Problema del doble hash == solo revisa 2n al hacer doble hash
// por ejemplo 25, 43, ,56, 35, 54, 13, 80, 104, || estos siguientes numeros escogidos: 23, 33, dará error
// dara error porque en ningún momento visitará el lugar libre al ir de 2 en 2. Solución propuesta, que sea de 3 en 3
// al ser impar hará que se vaya rotando si da la vuelta completa
// ( (D +1)% n + 1) % n
void reasignacionHashDD(int arrayHash[], int numero, int posicion, int n){
    //int D = hashNumero(hashNumero(posicion, n), n); // da error porque el doble hash es par y avanza de 2 en 2
    
    // ya tiene un hash la posición, entonces aquí tiene dos
    int D = ((((posicion + 1) % n) + 1 ) % n)+1 %n ;
    cout << "Hubo colisión en: " << posicion << ", entro a la reasignación doble Hash" << endl;

    
    while (true)
    {
        // revisa la posición + i², va iterando usando k
        if ( arrayHash[D] == -1)
        {
            cout << "Fue reasignado en " << D << endl;
            arrayHash[D] = numero;
            break; // lo guardo se rompe el ciclo
        }else{
            D = ((D + 1) % n + 1) % n;
            //D = hashNumero(hashNumero(D, n), n);
        }
    }

}

void busquedaHashDD(int arrayHash[], int numero, int posicion, int n){
    int D = ((posicion + 1 % n) + 1 ) % n;

    if (numero > n)
    {
        cout << "Es un número mayor de los posibles" << endl;
        return; // tiene un return para evitar que se recorra
    }

    if (arrayHash[posicion] == numero)
        cout << "Se encontro el número en la posicion:" << posicion << endl;
    else{
        cout << "Se busca el numero: " << numero << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "Hubo colisión en: " << posicion << ", entro a la reasignación DobleHash" << endl;
            if (arrayHash[D] == numero)
            {
                cout << "Fue encontrado en " << D << endl;
                return;
            }
        }
        cout << "No se encuentra el número" << endl;
    }

}


int hashNumero(int numero, int n){
    return (numero % n ) +1;
}

// para usar el switch tanto en trabajar como para buscar, usando un booleano
void trabajoHash(char opc, int array[], int arrayHash[], int n, bool flag){
    int k;
    int numeroBuscado = 0;


    switch (opc) {
        case 'L':
            // Lógica para la opción 'L'

            cout << "Opción L seleccionada para colisiones" << endl;
            if (flag)
            {

                for (int i = 0; i < n; i++)
                {   
                    k = hashNumero(array[i], n);
                    cout << "K:" << k << endl;
                    if (arrayHash[k] != -1)
                        reasignacionHashLineal(arrayHash, array[i], i, n);
                    else
                        arrayHash[k] = array[i];
                }

            }else{
                cout << "Ingrese su número a buscar:" << endl;
                cin >> numeroBuscado;
                k = hashNumero(numeroBuscado, n);
                busquedaLineal(arrayHash, numeroBuscado, k, n);
            }
            break;
            

        case 'C':
            // Lógica para la opción 'C'

            cout << "Opción C seleccionada para colisiones" << endl;

            if (flag)
            {
                for (int i = 0; i < n; i++)
                {   
                    k = hashNumero(array[i], n);
                    cout << "K:" << k << endl;
                    if (arrayHash[k] != -1)
                        reasignacionHashCuadratico(arrayHash, array[i], i, n);
                    else
                        arrayHash[k] = array[i];
                    
                }

            }else{
                cout << "Ingrese su número a buscar:" << endl;
                cin >> numeroBuscado;
                k = hashNumero(numeroBuscado, n);
                busquedaCuadratica(arrayHash, numeroBuscado, k, n);
            }
            
            
            break;
        
        case 'D':
            // Lógica para la opción 'D'

            cout << "Opción D seleccionada para colisiones" << endl;
            if (flag)
            {
                for (int i = 0; i < n; i++)
                {   
                    k = hashNumero(array[i], n);
                    cout << "K:" << k << endl;
                    if (arrayHash[k] != -1)
                        reasignacionHashDD(arrayHash, array[i], i, n);
                    else
                        arrayHash[k] = array[i];
                    
                }

            }else{
                cout << "Ingrese su número a buscar:" << endl;
                cin >> numeroBuscado;
                k = hashNumero(numeroBuscado, n);
                busquedaHashDD(arrayHash, numeroBuscado, k, n);
            }
            
            
            break;

        default:
            cout << "Opción inválida" << endl;
            break;
    }


}


int main(int argc, char **argv) {
    srand(time(NULL)); // genera la semilla para los números aleatorios

    // número de elementos.
    int n, opcionBuscar;

    // opción de como se examina el hash 
    char opc;


    // valida cantidad de parámetros mínimos.
    if (argc < 3) {
        cout << "Uso: \n./Lab_8 n Hash {L|C|D}\n";
        return -1;
    }
    
    // convierte string a entero.
    n = atoi(argv[1]);

    // hace la opción en mayúscula
    opc = toupper(*argv[2]);

    // ver si coloco un número negativo de matriz
    if (! (n > 0))
        return -1;

    cout << "La opción es: " << opc << endl;

    // definiendo los arrays
    int array[n], arrayHash[n];
    
    for (int i = 0; i < n; i++)
    {
       array[i] = generate_random(n);
       arrayHash[i] = -1; // representando un valor que nulo
    }
    
    /*
    array = [random1, ... , randomN]
    arrayHash = [-1, ... , n veces -1]
    Esto esta hecho así para que se pueda ver si hay un valor ya en una posición en el arrayHash
    Y así resolver las colisiones
    */
    
    cout << "El array es:" << endl;
    print_array(array, n);

    // booleano true: reasignar, false buscar
    trabajoHash(opc, array, arrayHash, n, true);

    cout << "El array con Hash quedo:" << endl;
    print_array(arrayHash, n);

    while (true)
    {
        cout << "Desea buscar un numero: \n[0]No\n[1]Si:" << endl;
        cin >> opcionBuscar;
        if (opcionBuscar == 0)
        {
            break;
        }else if (opcionBuscar == 1)
        {
            trabajoHash(opc, array, arrayHash, n, false);
        }else{
            cout << "Ingrese una opción válida" << endl;
        }
        
        
    }

    return 0;
}
