#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;;

struct paciente
{
    /* datos */
    string nombre;
    int edad;
    float peso, altura;
};



int main(){

    // se crea un numero y un puntero, para detectar un puntero se hace con el *
    struct paciente p = {"Alejandro",35, 70, 1.5};
    struct paciente *pt = &p;

    //printf("La información del paciente es: \n\tNombre: %s.\n\tEdad: %d\n\tHabitación: %d", pt->name, pt->age, pt->room);

    cout << "Paciente: " << pt->nombre ;
    printf("\n\tEdad: %d\n\tPeso:%.2f\n\tAltura: %.2f", pt->edad, pt->peso, pt->altura);

    return 0;
}