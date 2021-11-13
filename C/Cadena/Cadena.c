#include "Cadena.h"
#include <stddef.h>
#include <ctype.h>

#define esLetra(c) ((c) >= 'A' && (c) <= 'Z' || (c) >= 'a' && (c) <= 'z')

char *miStrStr(const char *cad, const char *subCad)
{
     char *i = (char *)cad;
     char *j;
     char *encontrada;

     while (*i) // *i != '\0'
     {
          while (*i && *i != *subCad)
               i++;

          if (*i)
          {
               encontrada = i;
               i++;
               j = (char *)subCad + 1;
               while (*i && *j && *i == *j)
               {
                    i++;
                    j++;
               }

               if (!*j)
                    return encontrada;
               else
                    i = encontrada + 1;
          }
     }

     return FALSO;
}

void normalizarCadena(const char *origen, char *destino)
{
     secuenciaPalabras secLect;
     crearSecuenciaPalabras(&secLect, (char *)origen);

     secuenciaPalabras secEscr;
     crearSecuenciaPalabras(&secEscr, destino);

     palabra pal, palDest;
     leerPalabra(&secLect, &pal);
     while (!finSecuenciaPalabras(&secLect))
     {
          escribirPalabra(&secEscr, &pal, &palDest);
          formatearPalabra(&palDest);
          escribirCaracter(&secEscr, ' ');
          leerPalabra(&secLect, &pal);
     }

     reposicionarSecuenciaPalabras(&secEscr, -1);
     cerrarSecuenciaPalabras(&secEscr);
}

void crearSecuenciaPalabras(secuenciaPalabras *sec, char *cad)
{
     sec->cursor = cad;
     sec->finSec = FALSO;
}

boolean leerPalabra(secuenciaPalabras *sec, palabra *pal)
{
     char *act = sec->cursor;
     while (*act && !esLetra(*act))
          act++;

     if (!*act) //*act = \0
     {
          sec->finSec = VERDADERO;
          return FALSO;
     }

     pal->ini = act;

     while (*act && esLetra(*act))
          act++;

     pal->fin = act - 1;

     return VERDADERO;
}

boolean finSecuenciaPalabras(secuenciaPalabras *sec)
{
     return !*(sec->cursor);
}

void formatearPalabra(palabra *pal)
{
     *(pal->ini) = toupper(*pal->ini);

     for (char *act = pal->ini + 1; act <= pal->fin; act++)
          *act = tolower(*act);
}

void escribirPalabra(secuenciaPalabras *sec, palabra *pal, palabra *palDest)
{
     char *dest = sec->cursor;

     palDest->ini = dest;

     for (char *orig = pal->ini; orig <= pal->fin; orig++, dest++)
          *dest = *orig;

     palDest->fin = dest - 1;

     sec->cursor = dest;
}

void escribirCaracter(secuenciaPalabras *sec, char c)
{
     *(sec->cursor) = c;
     sec->cursor++;
}

void reposicionarSecuenciaPalabras(secuenciaPalabras *sec, int despl)
{
     sec->cursor += despl;
}

void cerrarSecuenciaPalabras(secuenciaPalabras *sec)
{
     *sec->cursor = '\0';
}