#ifndef FECHAS_H
#define FECHAS_H
#include "../../Comun/Defs.h"

typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

Fecha ingresarFecha();
boolean esFechaValida(const Fecha *fecha);
Fecha sumarDiasAFecha(Fecha *fecha, int dias);
Fecha restarDiasAFecha(Fecha *fecha, int dias);
int diferenciaDeDiasEntreFechas(const Fecha *f1, const Fecha *f2);
int diaDeLaSemana(const Fecha *fecha);
#endif // FECHAS_H
