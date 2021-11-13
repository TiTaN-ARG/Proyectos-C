#ifndef TDAPILA_H
#define TDAPILA_H
#include <stddef.h>

#include "../Comun/Defs.h"

#ifdef TDA_PILA_IMPL_ESTATICA
#include "../TDAPilaImplEstatica/TDAPilaImplEstatica.h"
#else
#include "../TDAPilaImplDinamica/TDAPilaImplDinamica.h"
#endif // TDA_PILA_IMPL_ESTATICA

void crearPila(Pila *pp);
boolean apilar(Pila *pp, const void *elem, size_t tamElem);
boolean desapilar(Pila *pp, void *elem, size_t tamElem);
boolean verTopeDePila(const Pila *pp, void *elem, size_t tamElem);
boolean pilaVacia(const Pila *pp);
boolean pilaLlena(const Pila *pp, size_t tamElem);
void vaciarPila(Pila *pp);

#endif // TDAPILA_H
