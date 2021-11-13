#ifndef TDACOLA_H
#define TDACOLA_H

#ifdef TDA_COLA_IMPL_ESTATICA
#include "../TDAColaImplEstatica/TDAColaImplEstatica.h"
#endif
#include "../TDAColaImplDinamica/TDAColaImplDinamica.h"

#include "../Comun/Defs.h"

void crearCola(Cola *pc);
boolean encolar(Cola *pc, const void *elem, size_t tamElem);
boolean desencolar(Cola *pc, void *elem, size_t tamElem);
boolean verFrenteDeCola(const Cola *pc, void *elem, size_t tamElem);
boolean ColaVacia(const Cola *pc);
boolean ColaLlena(const Cola *pc, size_t tamElem);
void vaciarCola(Cola *pc);

#endif // TDACOLA_H
