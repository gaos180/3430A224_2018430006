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

void mostrar(paciente p){
    paciente *pt = &p;

    cout << "\nPaciente: " << pt->nombre ;
    printf("\n\tEdad: %d\n\tPeso:%.2f\n\tAltura: %.2f", pt->edad, pt->peso, pt->altura);
}


int main(){

    paciente arreglo[3];

    struct paciente p = {"Alejandro",35, 70, 1.5};
    struct paciente *pt = &p;

    struct paciente p2 = {"Alexandra", 26, 50, 1.5};
    struct paciente *pt2 = &p2;

    struct paciente p3 = {"Kathya", 26, 60, 1.6};
    struct paciente *pt3 = &p3;

    arreglo[0] = p;
    arreglo[1] = p2;
    arreglo[2] = p3;

    for (int i = 0; i < 3; i++)
    {
        mostrar(arreglo[i]);
    }
    
    //printf("La información del paciente es: \n\tNombre: %s.\n\tEdad: %d\n\tHabitación: %d", pt->name, pt->age, pt->room);

    return 0;
}