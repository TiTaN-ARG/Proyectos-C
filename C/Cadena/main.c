#include <stdio.h>
#include <stdlib.h>

#include "Cadena.c"

int main()
{
     char cadena[] = "hola lalala!";
     char subCad[] = "lala";

     char *encontrada = miStrStr(cadena, subCad);

     if (encontrada) // encontrada != FALSO
          printf("La subcadena es: %s\n", subCad);
     else
          printf("La subcadena %s no fue encontrada\n", subCad);

     char cadANorm[] = ".-'+esTO&/&eS&/&uN'$&-$t.TituLo&=.#";
     char cadNorm[20];

     normalizarCadena(cadANorm, cadNorm);

     printf("Cadena a normalizar:\n%s\n"), cadANorm;
     printf("Cadena normalizada:\n%s\n"), cadNorm;

     return 0;
}
