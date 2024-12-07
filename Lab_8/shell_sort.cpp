#include <iostream>

void shellSort(int A[], int N) {
    int INT = N + 1; // Inicializa INTERVALO
    while (INT > 1) {
        INT = INT / 2; // Divide INTTRVALO entre 2
        bool BAND = true; // Bandera para el bucle

        while (BAND) {
            BAND = false; // Reinicia la bandera
            int I = 0; // Inicializa I

            while ((I + INT) < N) { // Comprueba el limite
                if (A[I] > A[I + INT]) { // Comparacion
                    // Intercambia los elementos
                    int AUX = A[I];
                    A[I] = A[I + INT];
                    A[I + INT] = AUX;
                    BAND = true; // Marca que hubo un intercambio
                }
                I++; // Incrementa I
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
    const int SIZE_tmp = 10; // Tamano predefinido del arreglo
    int arr[SIZE_tmp];

    int SIZE;
    std::cout << "Tamano del arreglo (n<10): ";
    std::cin >> SIZE;

    // Inicializa la semilla para numeros aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // ------------------------------------------

    // Llamar a la funcion para llenar el arreglo
    llenarArreglo(arr, SIZE);

    std::cout << "Arreglo de numeros enteros:\n";
    // Llamar a la funcion para mostrar el arreglo
    mostrarArreglo(arr, SIZE);
    
    // Llamar a la funcion Burbuja Menor
    shellSort(arr, SIZE);

    std::cout << "Post Metodo Burbuja_Menor:\n";
    // Llamar a la funcion para mostrar el arreglo
    mostrarArreglo(arr, SIZE);

    return 0;
}