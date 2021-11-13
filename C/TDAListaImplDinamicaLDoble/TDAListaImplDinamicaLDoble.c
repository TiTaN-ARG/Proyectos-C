#include <string.h>

#define TDA_LISTA_IMPL_DINAMICA_LDOBLE
#include "../TDALista/TDALista.h"

void crearLista(Lista *pl)
{
     *pl = NULL;
}

int insertarEnListaOrdenada(Lista *pl, const void *elem, size_t tamElem, Cmp cmp)
{
     NodoD *act = *pl, *ant = NULL, *sig = NULL;

     if (act)
     {
          while (act->ant && cmp(elem, act->elem) < 0)
               act = act->ant;

          while (act->ant && cmp(elem, act->elem) > 0)
               act = act->sig;

          if (cmp(elem, act->elem) == 0)
               return DUPLICADO;

          if (cmp(elem, act->elem) < 0)
          {
               sig = act;
               ant = act->ant;
          }
          else
          {
               ant = act;
               sig = act->sig;
          }
     }

     NodoD *nuevo = malloc(sizeof(NodoD));
     void *elemNodo = malloc(tamElem);

     if (!nuevo || !elemNodo)
     {
          free(nuevo);
          free(elemNodo);
          return SIN_MEMORIA;
     }

     memcpy(elemNodo, elem, tamElem);
     nuevo->elem = elemNodo;
     nuevo->tamElem = tamElem;

     nuevo->ant = ant; // 1
     nuevo->sig = sig; // 2

     if (ant)
          ant->sig = nuevo; // 3

     if (sig)
          sig->ant = nuevo; // 4

     *pl = nuevo;

     return TODO_OK;
}

// int insertarActualizarEnListaOrdenada(Lista *pl, const void *elem, size_t tamElem, Cmp cmp, Actualizar actualizar)

boolean eliminarDeListaOrdenada(Lista *pl, void *elem, size_t tamElem, Cmp cmp)
{
     if (!*pl)
          return FALSO;

     NodoD *nae = *pl;

     while (nae && cmp(elem, nae->elem) < 0)
          nae = nae->ant;

     while (nae && cmp(elem, nae->elem) > 0)
          nae = nae->sig;

     if (!nae || cmp(elem, nae->elem) != 0) // no se encontro el elemento
          return FALSO;

     if (nae->ant)
          nae->ant->sig = nae->sig;

     if (nae->sig)
          nae->sig->ant = nae->ant;

     if (nae == *pl)
          *pl = nae->sig ? nae->sig : nae->ant;

     memcpy(elem, nae->elem, min(tamElem, nae->tamElem));
     free(nae->elem);
     free(nae);

     return VERDADERO;
}