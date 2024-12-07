#include <stdlib.h>
#include <iostream>

// para randoms
#include <cstdlib>
#include <ctime>

// para tiempo usando chrono
#include <chrono>

/*
Implementar algoritmos:

Quicksort

*/


using namespace std;

// retorna un valor aleatorio del tamaño del arreglo
int generate_random(int n){
    return rand() % n;
}

void selectionSort(int array[], int n){

    int minor, K;

    for (int i = 0; i < n; i++)
    {
        minor = array[i];
        K = i;
        for (int j = i; j < n; j++)
        {

            if (array[j] < minor)
            {

                minor = array[j];
                K = j;

            }
            
        }

        array[K] = array[i];
        array[i] = minor;

    }
}

void reduce(int inicio, int fin, int posicion, int array[]){
    bool band;
    int izq, der, aux;

    izq = inicio;
    der = fin;
    posicion = inicio;
    band = true;

    while (band)
    {

        while ( (array[posicion] <= array[der]) && (posicion != der) )
        {
            der--;
        }
        if (posicion == der)
        {
            band = false;
        }else{
            aux = array[posicion];
            array[posicion] = array[der];
            array[der] = aux;
            posicion = der;

            while ( (array[posicion] >= array[izq]) && (posicion != izq) )
            {
                izq++;
            }
            if (posicion == izq)
            {
                band = false;
            }else
            {

                aux = array[posicion];
                array[posicion] = array[izq];
                array[izq] = aux;
                posicion = izq;
                
            }

        }
        
    }

}

void quickSort(int array[], int n){

    int tope, inicio, fin, pos;
    tope = 1;

    int pilamenor[tope], pilamayor[tope];

    pilamenor[tope] = 0;
    pilamayor[tope] = n-1;

    while (tope > 0)
    {
        inicio = pilamenor[tope];
        fin = pilamayor[tope];
        tope--;
        pos = inicio;
        reduce(inicio, fin, pos, array);

        if (inicio < (pos - 1 ))
        {
            tope++;
            pilamenor[tope] = inicio;
            pilamayor[tope] = pos - 1;

        }
        if (fin > (pos + 1))
        {
            tope++;
            pilamenor[tope] = pos + 1;
            pilamayor[tope] = fin;
            
        }
    }
}

// función para realizar la vista de los elementos
void print_array(int array[], int n){
    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " | ";
    }
    cout << endl;
}


int main(int argc, char **argv) {
    srand(time(NULL)); // genera la semilla para los números aleatorios

    // número de elementos.
    int n;
    // opción de como se colocan los nodos
    int opc;
    int ver;


    // valida cantidad de parámetros mínimos.
    if (argc < 3) {
        cout << "Uso: \n./Lab_8 n Ver arreglo( [1]Si || [0] No )\n";
        return -1;
    }
    
    // convierte string a entero.
    n = atoi(argv[1]);
    ver = atoi(argv[2]);

    if (! (n > 0))
        return -1;

    int arrayQuick[n], arraySelection[n];

    for (int i = 0; i < n; i++)
    {
       arrayQuick[i] = generate_random(n);
       arraySelection[i] = generate_random(n);
    }
    

    cout << "Entro tamaño :" << n << " | " << ver << endl;

    cout << "Realizando QuickSort" << endl;


    if (ver == 1){
        cout << "Sin ordenar" << endl;
        print_array(arrayQuick, n);
        }
    auto start = chrono::system_clock::now();
    
    // zona de evaluación del algoritmo

    //selectionSort(arraySelection, n);
    quickSort(arrayQuick, n);

    auto end = chrono::system_clock::now();
    
    if (ver == 1){
        cout << "Ordenado" << endl;
        print_array(arrayQuick, n);
        }
    chrono::duration<double, milli> duration = end - start;

    cout << duration.count() << " ms haciendo QuickSort" << endl;

    //----------- SelectionSort --------------------------------
    cout << "Realizando SelectionSort" << endl;
    if (ver == 1){
        cout << "Sin ordenar" << endl;
        print_array(arraySelection, n);
        }
    auto start2 = chrono::system_clock::now();
    
    // zona de evaluación del algoritmo

    selectionSort(arraySelection, n);
    //quickSort(arraySelection, n);

    auto end2 = chrono::system_clock::now();
    
    if (ver == 1){
        cout << "Ordenado" << endl;
        print_array(arraySelection, n);
    }
    chrono::duration<double, milli> duration2 = end2 - start2;

    cout << duration2.count() << " ms haciendo SelectionSort" << endl;

    
    return 0;
}