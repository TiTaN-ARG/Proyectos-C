#define TDA_PILA_IMPL_ESTATICA

#include "../TDAPila/TDAPila.h"
#include <string.h>

#define espacioLibre(pp) (TAM_PILA - (pp)->tope)

void crearPila(Pila *pp)
{
     pp->tope = 0;
}

boolean apilar(Pila *pp, const void *elem, size_t tamElem)
{
     if (tamElem + sizeof(size_t) > espacioLibre(pp))
          return FALSO;

     memcpy(pp->vPila + pp->tope, elem, tamElem);
     pp->tope += tamElem;

     *(size_t *)(pp->vPila + pp->tope) = tamElem;
     pp->tope += sizeof(size_t);

     return VERDADERO;
}

boolean desapilar(Pila *pp, void *elem, size_t tamElem)
{
     if (pp->tope == 0) // Vacia
          return FALSO;

     pp->tope -= sizeof(size_t);
     size_t tamElemApilado = *(size_t *)(pp->vPila + pp->tope);

     pp->tope -= tamElemApilado;
     memcpy(elem, pp->vPila + pp->tope, min(tamElem, tamElemApilado));

     return VERDADERO;
}

boolean verTopeDePila(const Pila *pp, void *elem, size_t tamElem)
{
     if (pp->tope == 0) // Vacia
          return FALSO;

     unsigned tope = pp->tope;

     tope -= sizeof(size_t);
     size_t tamElemApilado = *(size_t *)(pp->vPila + tope);

     tope -= tamElemApilado;
     memcpy(elem, pp->vPila + tope, min(tamElem, tamElemApilado));

     return VERDADERO;
}

boolean pilaVacia(const Pila *pp)
{
     return pp->tope == 0;
}

boolean pilaLlena(const Pila *pp, size_t tamElem)
{
     return tamElem + sizeof(size_t) > espacioLibre(pp);
}

void vaciarPila(Pila *pp)
{
     pp->tope = 0;
}