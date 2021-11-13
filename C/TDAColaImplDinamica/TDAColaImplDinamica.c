#include <stdlib.h>
#include <string.h>

#define TDA_COLA_IMPL_DINAMICA
#include "../TDACola/TDACola.h"

void crearCola(Cola *pc)
{
     pc->frente = pc->fondo = NULL;
}

boolean encolar(Cola *pc, const void *elem, size_t tamElem)
{
     Nodo *nue = malloc(sizeof(Nodo));
     void *elemNodo = malloc(tamElem);

     if (!nue || !elemNodo)
     {
          free(nue);
          free(elemNodo);
          return FALSO;
     }

     memcpy(elemNodo, elem, tamElem);
     nue->elem = elemNodo;
     nue->tamElem = tamElem;
     nue->sig = NULL;

     if (pc->fondo)
          pc->fondo->sig = nue; // 1
     else
          pc->frente = nue; // 3

     pc->fondo = nue; // 2

     return VERDADERO;
}

boolean desencolar(Cola *pc, void *elem, size_t tamElem)
{
     if (!pc->frente)
          return FALSO;

     Nodo *nae = pc->frente; // 1
     pc->frente = nae->sig;  // 2

     if (!pc->frente)
          pc->fondo = NULL;

     memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

     free(nae->elem);
     free(nae);

     return VERDADERO;
}

boolean verFrenteDeCola(const Cola *pc, void *elem, size_t tamElem)
{
     Nodo *frente = pc->frente; // 1

     if (!frente)
          return FALSO;

     memcpy(elem, frente->elem, min(tamElem, frente->tamElem));

     return VERDADERO;
}

boolean ColaVacia(const Cola *pc)
{
     return !pc->frente;
}

boolean ColaLlena(const Cola *pc, size_t tamElem)
{
     void *nue = malloc(sizeof(Nodo));
     void *elemNodo = malloc(tamElem);

     free(nue);
     free(elemNodo);

     return !nue || !elemNodo;
}

void vaciarCola(Cola *pc)
{
     Nodo *nae;

     while (pc->frente)
     {
          nae = pc->frente;      // 1
          pc->frente = nae->sig; // 2
          free(nae->elem);
          free(nae);
     }

     pc->fondo = NULL;
}