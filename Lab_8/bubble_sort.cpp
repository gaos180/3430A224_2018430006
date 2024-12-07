#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

void burbuja_menor(int* arr, int size) {
    // Repetir con I desde 2 hasta N
    for (int i = 1; i < size; ++i) {
        // Repetir con J desde N hasta I
        for (int j = size-1; j >= i; --j) {
            // Si A[J-1] > A[J] entonces
            if (arr[j - 1] > arr[j]) {
                // Hacer AUX <- A[J-1]
                int aux = arr[j - 1];
                // Hacer A[J-1] <- A[J]
                arr[j - 1] = arr[j];
                // Hacer A[J] <- AUX
                arr[j] = aux;
            }
        }
    }
}

void llenarArreglo(int* arr, int size) {
    // Llenar el arreglo con numeros aleatorios entre 1 y 100
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100 + 1; // Genera un numero entre 1 y 100
    }
}

void mostrarArreglo(int* arr, int size) {
    // Mostrar los valores del arreglo
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}


int main() {
    const int SIZE = 10; // Tamano del arreglo
    int arr[SIZE];

    // Inicializa la semilla para numeros aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // ------------------------------------------

    // Llamar a la funcion para llenar el arreglo
    llenarArreglo(arr, SIZE);

    std::cout << "Arreglo de numeros enteros:\n";
    // Llamar a la funcion para mostrar el arreglo
    mostrarArreglo(arr, SIZE);
    
    // Llamar a la funcion Burbuja Menor
    burbuja_menor(arr, SIZE);

    std::cout << "Post Metodo Burbuja_Menor:\n";
    // Llamar a la funcion para mostrar el arreglo
    mostrarArreglo(arr, SIZE);

    return 0;
}