#include <stdio.h>
#include "Fechas.h"
#include "../../Comun/Defs.h"

int cantDiasMes(int, int);
boolean esBisiesto(int anio);
int cantDiasAnio(int anio);

boolean esFechaValida(const Fecha *f)
{
    return f->anio > 1600 &&
           f->mes >= 1 && f->mes <= 12 &&
           f->dia >= 1 && f->dia <= cantDiasMes(f->mes, f->anio);
}

int cantDiasMes(int mes, int anio)
{
    static const int cdm[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && esBisiesto(anio))
        return 29;

    return cdm[mes];
}

boolean esBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

//------Tarea------

Fecha sumarDiasAFecha(Fecha *f, int dias)
{
    int dReal;

    f->dia += dias;

    while (f->dia > (dReal - cantDiasMes(f->mes, f->anio)))
    {
        f->mes++;
        f->dia -= dReal;

        if (f->mes > 12)
        {
            f->anio++;
            f->mes = 1;
        }
    }

    return *f;
}

Fecha restarDiasAFecha(Fecha *f, int dias)
{
    int dReal;

    f->dia -= dias;

    while (f->dia < 1)
    {

        f->mes--;
        dReal = cantDiasMes(f->mes, f->anio);
        f->dia += dReal;

        if (f->mes < 1)
        {
            f->anio--;
            f->mes = 12;
        }
    }

    return *f;
}

Fecha ingresarFecha(Fecha *f)
{
    printf("Ingresa el Dia\n");
    fflush(stdin);
    scanf("%d", &f->dia);

    printf("Ingresa el Mes\n");
    fflush(stdin);
    scanf("%d", &f->mes);

    printf("Ingresa el Anio\n");
    fflush(stdin);
    scanf("%d", &f->anio);

    return *f;
}

int diferenciaDeDiasEntreFechas(const Fecha *f1, const Fecha *f2)
{
    int dif = diaDelAnio(f2) - diaDelAnio(f1);
    int anioAct = f1->anio;

    while (anioAct < f2->anio)
    {
        dif += cantDiasAnio(anioAct);
        anioAct++;
    }
    return dif;
}

int diaDelAnio(const Fecha *f)
{
    int diaA = f->dia;
    int mesAct = 1;

    while (mesAct < f->mes)
    {
        diaA += cantDiasMes(mesAct, f->anio);
        mesAct++;
    }
    return diaA;
}

int cantDiasAnio(int anio)
{
    return esBisiesto(anio) ? 366 : 365;
}
