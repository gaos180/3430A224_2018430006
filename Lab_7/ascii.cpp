#include <iostream>

int main() {
    const int size = 6; // Tamano del arreglo (letras A a F)
    char letters[size]; // Declaracion del arreglo de caracteres

    // Llenar el arreglo con letras de 'A' a 'F'
    for (int i = 0; i < size; ++i) {
        //letters[i] = 'A' + i; // Asignar valores ASCII de 'A' a 'F'
        letters[i] = 97 + i; // Asignar valores ASCII de 'a' a 'f'
        //letters[i] = 65 + i; // Asignar valores ASCII de 'A' a 'F'
    }

    // Imprimir los valores y sus correspondientes códigos ASCII
    std::cout << "Letras y sus códigos ASCII:" << std::endl;
    for (int i = 0; i < size; ++i) {
        //std::cout << letters[i] << " : " << static_cast<int>(letters[i]) << std::endl;
        std::cout << letters[i] << std::endl;
    }

    return 0;
}