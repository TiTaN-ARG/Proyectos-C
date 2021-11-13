#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Vectores.c"

typedef struct
{
    int DNI;
    char Apellido[51];
    char Nombre[51];
    float sueldo;
} Empleado;

int cmpEmpl(const void *pv1, const void *pv2);
int cmpEmplApeYNom(const void *pv1, const void *pv2);
void mostrarEmpl(const void *pve);

int main()
{
    Vector vec;

    crearVector(&vec, sizeof(Empleado));

    Empleado empleados[7] =
        {
            {22333444,
             "Perez",
             "Juan",
             56000},

            {21323744,
             "Perez",
             "Antonio",
             66000},

            {22333555,
             "Rodriguez",
             "Pedro",
             60000},

            {21423955,
             "Alvarez",
             "Fabricio",
             50000},

            {11253565,
             "Carmona",
             "Jorge",
             80000},

            {33153185,
             "Brandan",
             "Juan",
             90000},

            {22373885,
             "Darias",
             "Dario",
             75000},
        };

    for (int i = 1; i < 7; i++)
        insertarEnVectorAlFinal(&vec, &empleados[i]);

    mostrarVector(&vec, mostrarEmpl);

    puts("--------------------------------------------------------\n");

    time_t tIni = time(NULL);

    ordenarVectorAscSeleccion(&vec, cmpEmpl);

    time_t tFin = time(NULL);

    mostrarVector(&vec, mostrarEmpl);

    printf("El ordenamiento demoro %ld segundos.", (long)tFin - tIni);

    return 0;
}

int cmpEmpl(const void *pv1, const void *pv2)
{
    Empleado *emp1 = (Empleado *)pv1;
    Empleado *emp2 = (Empleado *)pv2;

    return emp1->DNI - emp2->DNI;
}

int cmpEmplApeYNom(const void *pv1, const void *pv2)
{
    Empleado *emp1 = (Empleado *)pv1;
    Empleado *emp2 = (Empleado *)pv2;

    int comp = strcmp(emp1->Apellido, emp2->Apellido);
    if (comp == 0)
        comp = strcmp(emp1->Nombre, emp2->Nombre);

    return comp;
}

void mostrarEmpl(const void *pve)
{
    Empleado *empl = (Empleado *)pve;

    printf("(DNI: %d, Apellido: %s, Nombre: %s, Suledo: %.2f)\n", empl->DNI, empl->Apellido, empl->Nombre, empl->sueldo);
}