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

    struct paciente p2 = {"Alexandra", 26, 50, 1.5};
    struct paciente *pt2 = &p2;

    struct paciente p3 = {"Kathya", 26, 60, 1.6};
    struct paciente *pt3 = &p3;

    //printf("La información del paciente es: \n\tNombre: %s.\n\tEdad: %d\n\tHabitación: %d", pt->name, pt->age, pt->room);

    cout << "\nPaciente: " << pt->nombre ;
    printf("\n\tEdad: %d\n\tPeso:%.2f\n\tAltura: %.2f", pt->edad, pt->peso, pt->altura);
    cout << "\nPaciente: " << pt2->nombre ;
    printf("\n\tEdad: %d\n\tPeso:%.2f\n\tAltura: %.2f", pt2->edad, pt2->peso, pt2->altura);
    cout << "\nPaciente: " << pt3->nombre ;
    printf("\n\tEdad: %d\n\tPeso:%.2f\n\tAltura: %.2f", pt3->edad, pt3->peso, pt3->altura);

    return 0;
}