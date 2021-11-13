#ifndef TDALISTA_H
#define TDALISTA_H

#ifdef TDA_LISTA_IMPL_ESTATICA
#include "../TDAListaImplEstatica/TDAListaImplEstatica.h"
#endif

#ifdef TDA_LISTA_IMPL_DINAMICA
#include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#endif

#ifdef TDA_LISTA_IMPL_DINAMICA_LDOBLE
#include "../TDAListaImplDinamicaLDoble/TDAListaImplDinamicaLDoble.h"
#endif

#include "../Comun/Defs.h"

void crearLista(Lista *pl);
int insertarEnListaOrdenada(Lista *pl, const void *elem, size_t tamElem, Cmp cmp);
int insertarActualizarEnListaOrdenada(Lista *pl, const void *elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int insertarEnListaEnPosicion(Lista *pl, const void *elem, size_t tamElem, int pos);
int insertarEnListaAlFinal(Lista *pl, const void *elem, size_t tamElem);
int insertarEnListaAlInicio(Lista *pl, const void *elem, size_t tamElem);
boolean eliminarDeListaEnPosicion(Lista *pl, int pos);
boolean eliminarDeListaAlInicio(Lista *pl, void *elem, size_t tamElem);
boolean eliminarDeListaAlFinal(Lista *pl, void *elem, size_t tamElem);
boolean eliminarDeListaOrdenada(Lista *pl, void *elem, size_t tamElem, Cmp cmp);
boolean eliminarDeListaDesordenada(Lista *pl, void *elem, size_t tamElem, Cmp cmp);
int eliminarDuplicadosDeListaOrdenada(Lista *pl, Cmp cmp, Actualizar actualizar);
int eliminarDuplicadosDeListaDesordenada(Lista *pl, Cmp cmp, Actualizar actualizar);
boolean buscarEnListaOrdenada(const Lista *pl, void *elem, size_t tamElem, Cmp cmp);
boolean buscarEnListaDesordenada(const Lista *pl, void *elem, size_t tamElem, Cmp cmp);
void vaciarLista(Lista *pl);
boolean listaVacia(const Lista *pl);
boolean listaLlena(const Lista *pl, size_t tamElem);
void mostrarLista(const Lista *pl, Mostrar mostrar);
void ordenarLista(Lista *pl, Cmp cmp);

#endif // TDALISTA_H
