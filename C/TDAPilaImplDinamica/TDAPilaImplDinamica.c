#define TDA_PILA_IMPL_DINAMICA

#include <stdlib.h>
#include <string.h>

#include "../TDAPila/TDAPila.h"

void crearPila(Pila *pp)
{
     *pp = NULL;
}

boolean apilar(Pila *pp, const void *elem, size_t tamElem)
{
     Nodo *nue = (Nodo *)malloc(sizeof(Nodo));
     void *elemNodo = malloc(tamElem);

     if (!nue || elemNodo)
     {
          free(nue);
          free(elemNodo);
          return FALSO;
     }

     memcpy(elemNodo, elem, tamElem);

     nue->elem = elemNodo;
     nue->tamElem = tamElem;

     nue->sig = *pp; // 1
     *pp = nue;      // 2

     return VERDADERO;
}

boolean desapilar(Pila *pp, void *elem, size_t tamElem)
{
     if (!*pp)
          return FALSO;

     Nodo *nae = *pp; // 1
     *pp = mae->sig;  // 2

     memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

     free(nae->elem);
     free(nae);

     return VERDADERO;
}

boolean verTopeDePila(const Pila *pp, void *elem, size_t tamElem)
{
     if (!*pp)
          return FALSO;

     Nodo *tope = *pp; // 1

     memcpy(elem, tope->elem, min(tamElem, tope->tamElem));

     return VERDADERO;
}

boolean pilaVacia(const Pila *pp)
{
     return !*pp; // *PP == NULL
}

boolean pilaLlena(const Pila *pp, size_t tamElem)
{
     void *nue = malloc(sizeof(Nodo));
     void *elemNodo = malloc(tamElem);

     free(nue);
     free(elemNodo);

     return !nue || !elemNodo;
}

void vaciarPila(Pila *pp)
{
     Nodo *nae;

     while (*pp)
     {
          nae = *pp;      // 1
          *pp = nae->sig; // 2
          free(nae->elem);
          free(nae);
     }
}