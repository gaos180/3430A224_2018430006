#include <iostream>

// en caso de que se permita
#include <string>
// Funciones print creadas debido a que no quería escribir cout[...] ;
void print_char(char *charToPrint)
{
    std::cout << charToPrint << "\n";
}

void print_int(int numberToPrint)
{
    std::cout << numberToPrint << "\n";
}


// Se ha realizado en una función para la legibilidad

void even_or_odd(int number)
{
    if (number % 2 == 0){
        print_char("Es par");
    } else {
        print_char("Es impar");
    }
}

int main()
{
    int number;

    print_char("Ingrese un numero para determinar si es par o no:");
    std:: cin >> number;
    
    print_char("El número ingresado es:");
    print_int(number);

    even_or_odd(number);

    // si deja usar string sirve de la siguiente forma

    std::string word;

    print_char("Ingrese una cadena de caracteres:");
    std:: cin >> word;

    std:: cout << word;
    std:: cout << "\nEl tamaño de la pabra es de:"<< word.length();

    return 0;
}