#include <iostream>

// En caso de que se permita 
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
    std:: cout << "El número: " << number;
    if (number % 2 == 0){
        print_char(" es par\n");
    } else {
        print_char(" es impar\n");
    }
}

void even_or_odd_1_10(){
    for (int i = 1; i <= 10; i++)
    {   
        even_or_odd(i);
    }
    
}

void working_with_word(){
   // si deja usar string sirve de la siguiente forma

    std::string word;

    print_char("Ingrese una cadena de caracteres:");
    std:: cin >> word;

    std:: cout << word;
    std:: cout << "\nEl tamaño de la pabra es de:"<< word.length();

 
}

int main()
{
    int number;

    print_char("Ingrese un numero para determinar si es par o no:");
    std:: cin >> number;
    
    print_char("El número ingresado es:");
    print_int(number);

    even_or_odd(number);
    
    even_or_odd_1_10();

    // Otras formas:
    /*
    print_char("El número 1 es impar");
    print_char("El número 2 es par");
    print_char("El número 3 es impar");
    print_char("El número 4 es par");
    print_char("El número 5 es impar");
    print_char("El número 6 es par");
    print_char("El número 7 es impar");
    print_char("El número 8 es par");
    print_char("El número 9 es impar");
    print_char("El número 10 es par");
    */
   // o de la siguiente forma:
   /*
    even_or_odd(1);
    even_or_odd(2);
    even_or_odd(3);
    even_or_odd(4);
    even_or_odd(5);
    even_or_odd(6);
    even_or_odd(7);
    even_or_odd(8);
    even_or_odd(9);
    even_or_odd(10);
   
   */

    working_with_word();   
    return 0;
}