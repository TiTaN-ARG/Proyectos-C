#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Fechas.h"

int ingresarEnteroPositivo(const char *mensaje);
boolean continuar(const char *mensaje);

int main()
{
    //-------Programa para Validar la Fecha---------

    do
    {
        Fecha fecha = ingresaFecha();

        int cantDias = ingresarEnteroPositivo("Ingresa los dias a sumar");

        Fecha suma = sumarDiasAFecha(&fecha, cantDias);

        printf("La suma es %02d/%02d/%4d \n", suma.dia, suma.mes, suma.anio);

        Fecha f2 = ingresarFecha();

        int dif = diferenciaDeDiasEntreFechas(&fecha, &f2);

        printf("La diferencia entre las fechas es: %d\n", dif);
    } while (continuar("�Queres realizar otra suma?"));

    return 0;

    //--------Fin del Programa--------
}

int ingresarEnteroPositivo(const char *mensaje)
{
    int valor;
    printf("%s ---->", mensaje);
    fflush(stdin);
    scanf("%d", &valor);

    while (valor < 1)
    {
        printf("El valor ingresado no es valido. Ingrese un valor entero Positivo\n");
        fflush(stdin);
        scanf("%d\n", &valor);
    }
    return valor;
}

boolean continuar(const char *mensaje)
{
    char cont;
    printf("%s (s/n) ---->", mensaje);
    fflush(stdin);
    scanf("%c\n", &cont);
    cont = tolower(cont);

    while (cont != 's' && cont != 'n')
    {
        printf("Opcion incorrecta. Ingresar s o n \n");
        scanf("%c\n", &cont);
        fflush(stdin);
        cont = tolower(cont);
    }

    return cont == 's';
}
