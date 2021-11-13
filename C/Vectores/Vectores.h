#ifndef VECTORES_H
#define VECTORES_H

#include "../Comun/Defs.h"

#define CAP 10000

#define TODO_OK 0
#define VEC_LLENO 1
#define DUPLICADO 2

typedef struct
{
    char v[CAP];
    int ce;
    int tamElem;
} Vector;

void crearVector(Vector *vec, int tamElem);
int insertarEnVectorOrdAscConDup(Vector *vec, int elem);
int insertarEnVectorOrdAscSinDup(Vector *vec, int elem);
int insertarEnVectorOrdDesConDup(Vector *vec, int elem);
int insertarEnVectorOrdDesSinDup(Vector *vec, int elem);
int insertarEnVectorEnPos(Vector *vec, int elem);
int insertarEnVectorAlInicio(Vector *vec, int elem);
int insertarEnVectorAlFinal(Vector *vec, int elem);
boolean eliminarDeVectorOrdAsc(Vector *vec, int elem);
boolean eliminarDeVectorOrdDes(Vector *vec, int elem);
boolean eliminarDeVectorDesord(Vector *vec, int elem);
boolean eliminarDeVectorDePos(Vector *vec, int elem);
boolean eliminarDeVectorPrimero(Vector *vec);
boolean eliminarDeVectorUltimo(Vector *vec);
boolean buscarEnVector(const Vector *vec, int elem);
void ordenarVectorAscBurbujeo(Vector *vec);
void ordenarVectorDesBurbujeo(Vector *vec, int tamElem);
void ordenarVectorAscSeleccion(Vector *vec);
void ordenarVectorDesSeleccion(Vector *vec, int tamElem);
void ordenarVectorAscInsercion(Vector *vec);
void ordenarVectorDesInsercion(Vector *vec);
void mostrarVector(const Vector *vec, Mostrar mostrar);
int eliminarDuplicadosDeVectorOrd(Vector *vec);
int eliminarDuplicadosDeVectorDesord(Vector *vec);
void intercambiar(void *v1, void *v2, int tamElem);
void buscarMenor(void *inicio, void *fin, int tamElem);

#endif // VECTORES_H
