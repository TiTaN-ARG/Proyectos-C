#include <string.h>

#define TDA_COLA_IMPL_ESTATICA
#include "../TDACola/TDACola.h"

void *copiarAVector(void *vecLIzq, void *vecLDer, void *destino, const void *origen, size_t tamDato);
void *copiarDeVector(const void *vecLIzq, const void *vecLDer, void *destino, const void *origen, size_t tamDatoDestino, size_t tamDatoOrigen);
void *calcularFinDato(const void *vecLIzq, const void *vecLDer, const void *origen, size_t tamDatoOrigen);

void crearCola(Cola *pc)
{
     pc->frente = pc->fondo = pc->vCola;
     pc->tamDisponible = TAM_COLA;
}

boolean encolar(Cola *pc, const void *elem, size_t tamElem)
{
     if (tamElem + sizeof(size_t) > pc->tamDisponible)
          return FALSO;

     pc->fondo = copiarAVector(pc->vCola, pc->vCola + TAM_COLA, pc->fondo, &tamElem, sizeof(size_t));
     pc->fondo = copiarAVector(pc->vCola, pc->vCola + TAM_COLA, pc->fondo, elem, tamElem);

     pc->tamDisponible -= tamElem + sizeof(size_t);

     return VERDADERO;
}

boolean desencolar(Cola *pc, void *elem, size_t tamElem)
{
     if (pc->tamDisponible == TAM_COLA)
          return FALSO;

     size_t tamElemEncolado;

     pc->frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, &tamElemEncolado, pc->frente, sizeof(size_t), sizeof(size_t));
     pc->frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, elem, pc->frente, tamElem, tamElemEncolado);

     pc->tamDisponible += tamElemEncolado + sizeof(size_t);

     return VERDADERO;
}

boolean verFrenteDeCola(const Cola *pc, void *elem, size_t tamElem)
{
     if (pc->tamDisponible == TAM_COLA)
          return FALSO;

     size_t tamElemEncolado;

     void *frente = pc->frente;

     frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, &tamElemEncolado, frente, sizeof(size_t), sizeof(size_t));
     frente = copiarDeVector(pc->vCola, pc->vCola + TAM_COLA, elem, frente, tamElem, tamElemEncolado);

     return VERDADERO;
}

boolean ColaVacia(const Cola *pc)
{
     return pc->tamDisponible == TAM_COLA;
}

boolean ColaLlena(const Cola *pc, size_t tamElem)
{
     return tamElem + sizeof(size_t) > pc->tamDisponible;
}

void vaciarCola(Cola *pc)
{
     pc->frente = pc->fondo = pc->vCola;
     pc->tamDisponible = TAM_COLA;
}

void *copiarAVector(void *vecLIzq, void *vecLDer, void *destino, const void *origen, size_t tamDato)
{
     size_t cantACopiar = tamDato;
     size_t cantACopiar1erMC = vecLDer - destino;

     memcpy(destino, origen, cantACopiar1erMC);

     cantACopiar -= cantACopiar1erMC;

     if (cantACopiar > 0)
     {
          destino = vecLIzq;
          origen += cantACopiar1erMC;
          memcpy(destino, origen, cantACopiar);
     }

     return destino + cantACopiar;
}

void *copiarDeVector(const void *vecLIzq, const void *vecLDer, void *destino, const void *origen, size_t tamDatoDestino, size_t tamDatoOrigen)
{
     size_t cantACopiar = min(tamDatoOrigen, tamDatoDestino);
     size_t cantACopiar1erMC = vecLDer - origen;

     void *finDato = calcularFinDato(vecLIzq, vecLDer, origen, tamDatoOrigen);

     memcpy(destino, origen, cantACopiar1erMC);

     cantACopiar -= cantACopiar1erMC;

     if (cantACopiar > 0)
     {
          origen = vecLIzq;
          destino += cantACopiar1erMC;
          memcpy(destino, origen, cantACopiar);
     }

     return finDato;
}

void *calcularFinDato(const void *vecLIzq, const void *vecLDer, const void *origen, size_t tamDatoOrigen)
{
     const void *finDato = origen + tamDatoOrigen;

     if (finDato > vecLDer)
          finDato = vecLIzq + (finDato - vecLDer);

     return (void *)finDato;
}
