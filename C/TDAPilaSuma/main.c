#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TDA_PILA_IMPL_ESTATICA

#include "../TDAPila/TDAPila.h"

#define aBin(c) ((c) - '0')
#define aChar(d) ((d) + '0')

boolean sumar(const char *num1S, const char *num2S);
boolean cargarPila(const int *vec, Pila *pp, int cantCeros);
void cargarVector(Pila *pp, char *vec);

int main(int argc, char *argv[])
{
     int ret = sumar(argv[1], argv[2]);

     return ret;
}

boolean sumar(const char *num1S, const char *num2S)
{
     Pila pNum1, pNum2, pSuma;

     crearPila(&pNum1);
     crearPila(&pNum2);
     crearPila(&pSuma);

     boolean pudoCargar;

     int cantCeros = strlen(num1S) - strlen(num2S);

     pudoCargar = cargarPila(num1S, &pNum1, (cantCeros < 0) ? -cantCeros : 0);

     if (!pudoCargar)
          return FALSO;

     pudoCargar = cargarPila(num2S, &pNum2, (cantCeros < 0) ? cantCeros : 0);

     if (!pudoCargar)
          return FALSO;

     int acarreo = 0, digS, cantDigS = 0;
     char digNum1C, digNum2C, digSC;

     while (!pilaVacia(&pNum1) && pudoCargar)
     {
          desapilar(&pNum1, &digNum1C, sizeof(char));
          desapilar(&pNum1, &digNum2C, sizeof(char));

          digS = aBin(digNum1C) + aBin(digNum2C) + acarreo;

          acarreo = digS / 10;

          digSC = aChar(digS % 10);

          pudoCargar = apilar(&pSuma, &digSC, sizeof(char));
          cantDigS++;
     }

     if (pudoCargar && acarreo == 1)
     {
          char acarreoC = '1';
          pudoCargar = apilar(&pSuma, &acarreoC, sizeof(char));
          cantDigS++;
     }

     if (pudoCargar)
     {
          char *sumaS = (char *)malloc(cantDigS);

          if (!sumaS)
               return FALSO;

          cargarVector(&pSuma, sumaS);

          puts(sumaS);

          free(sumaS);
     }

     return pudoCargar;
}

boolean cargarPila(const int *vec, Pila *pp, int cantCeros)
{
     char cero = '0';
     boolean pudoApilar = VERDADERO;

     for (int i = 1; i <= cantCeros && pudoApilar; i++)
          pudoApilar = apilar(pp, &cero, sizeof(char));

     const char *act = vec;

     while (*act && pudoApilar)
     {
          pudoApilar = apilar(pp, act, sizeof(char));
          act++;
     }

     return pudoApilar;
}

void cargarVector(Pila *pp, char *vec)
{
     char *act = vec;

     while (!pilaVacia(pp))
     {
          desapilar(pp, act, sizeof(char));
          act++;
     }

     *act = '\0';
}
