#ifndef CADENA_H
#define CADENA_H

#include "../Comun/Defs.h"

typedef struct
{
     char *cursor;
     boolean finSec;
} secuenciaPalabras;

typedef struct
{
     char *ini;
     char *fin;
} palabra;

char *miStrStr(const char *cad, const char *subCad);
void normalizarCadena(const char *origen, char *destino);
void crearSecuenciaPalabras(secuenciaPalabras *sec, char *cad);
boolean leerPalabra(secuenciaPalabras *sec, palabra *pal);
boolean finSecuenciaPalabras(secuenciaPalabras *sec);
void formatearPalabra(palabra *pal);
void escribirPalabra(secuenciaPalabras *sec, palabra *pal, palabra *palDest);
void escribirCaracter(secuenciaPalabras *sec, char c);
void reposicionarSecuenciaPalabras(secuenciaPalabras *sec, int despl);
void cerrarSecuenciaPalabras(secuenciaPalabras *sec);

#endif