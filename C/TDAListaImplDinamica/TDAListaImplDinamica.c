#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"

#include <string.h>

void crearLista(Lista *pl)
{
     *pl = NULL;
}

int insertarEnListaOrdenada(Lista *pl, const void *elem, size_t tamElem, Cmp cmp)
{
     while (*pl && cmp(elem, (*pl)->elem) > 0)
          pl = &(*pl)->sig;

     if (*pl && cmp(elem, (*pl)->elem) == 0)
          return DUPLICADO;

     Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
     void *elemNodo = malloc(tamElem);

     if (!nuevo || !elemNodo)
     {
          free(nuevo);
          free(elemNodo);
          return SIN_MEMORIA;
     }

     nuevo->elem = elemNodo;
     memcpy(nuevo->elem, elem, tamElem);
     nuevo->tamElem = tamElem;

     nuevo->sig = *pl;
     *pl = nuevo;

     return TODO_OK;
}

int insertarActualizarEnListaOrdenada(Lista *pl, const void *elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
     while (*pl && cmp(elem, (*pl)->elem) > 0)
          pl = &(*pl)->sig;

     if (*pl && cmp(elem, (*pl)->elem) == 0)
     {
          actualizar((*pl)->elem, elem);
          return ACTUALIZADO;
     }

     Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
     void *elemNodo = malloc(tamElem);

     if (!nuevo || !elemNodo)
     {
          free(nuevo);
          free(elemNodo);
          return SIN_MEMORIA;
     }

     nuevo->elem = elemNodo;
     memcpy(nuevo->elem, elem, tamElem);
     nuevo->tamElem = tamElem;

     nuevo->sig = *pl;
     *pl = nuevo;

     return TODO_OK;
}

boolean eliminarDeListaOrdenada(Lista *pl, void *elem, size_t tamElem, Cmp cmp)
{
     while (*pl && cmp(elem, (*pl)->elem) > 0)
          pl = &(*pl)->sig;

     if (!*pl || cmp(elem, (*pl)->elem) < 0)
          return FALSO;

     Nodo *nae = *pl;  // 1
     *pl = (*pl)->sig; // 2

     memcpy(elem, nae->elem, min(tamElem, nae->tamElem));

     free(nae->elem);
     free(nae);

     return VERDADERO;
}

void ordenarLista(Lista *pl, Cmp cmp)
{
     Nodo *nodo;
     Lista lOrd = NULL;
     Lista *plOrd;

     while (*pl)
     {
          nodo = *pl;
          *pl = nodo->sig;
          plOrd = &lOrd;

          while (*plOrd && cmp(nodo->elem, (*plOrd)->elem) > 0)
               plOrd = &(*plOrd)->sig;

          nodo->sig = *plOrd;
          *plOrd = nodo;
     }

     *pl = lOrd;
}

int eliminarDuplicadosDeListaOrdenada(Lista *pl, Cmp cmp, Actualizar actualizar)
{
     int cantElim = 0;
     Lista *plDup = pl;
     Nodo *nae;

     while (*pl)
     {
          plDup = &(*pl)->sig;
          while (*plDup && cmp((*pl)->elem, (*plDup)->elem) == 0)
          {
               actualizar((*pl)->elem, (*plDup)->elem);
               nae = *plDup;
               *plDup = nae->sig;
               free(nae->elem);
               free(nae);
               cantElim++;
          }

          pl = &(*pl)->sig;
     }

     return cantElim;
}