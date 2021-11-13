#include <stdio.h>
#include <memory.h>

#include "Vectores.h"

void crearVector(Vector *vec, int tamElem)
{
    vec->ce = 0;
    vec->tamElem = tamElem;
}

int insertarEnVectorOrdAscConDup(Vector *vec, int *elem)
{
    if (vec->ce == CAP)
        return VEC_LLENO;

    int posAct;

    for (posAct = vec->ce - 1; posAct >= 0 && elem < vec->v[posAct]; posAct--)
    {
        vec->v[posAct + 1] = vec->v[posAct];
    }

    vec->v[posAct + 1] = elem;
    vec->ce++;

    return TODO_OK;
}

int insertarEnVectorOrdAscSinDup(Vector *vec, int elem)
{
    if (vec->ce == CAP)
        return VEC_LLENO;

    int posAct;

    while (posAct < vec->ce && elem > vec->v[posAct])
        posAct++;

    if (vec->ce > 0 && elem == vec->v[posAct])
        return DUPLICADO;

    int posIns = posAct;

    for (posAct = vec->ce - 1; posAct >= posIns; posAct--)
    {
        vec->v[posAct + 1] = vec->v[posAct];
    }

    vec->v[posAct + 1] = elem;
    vec->ce++;

    return TODO_OK;
}

int insertarEnVectorOrdDesConDup(Vector *vec, int elem)
{
    if (vec->ce == CAP)
        return VEC_LLENO;

    int posAct;

    for (posAct = vec->ce - 1; posAct >= 0 && elem < vec->v[posAct]; posAct--)
    {
        vec->v[posAct + 1] = vec->v[posAct];
    }

    vec->v[posAct + 1] = elem;
    vec->ce++;

    return TODO_OK;
}

int insertarEnVectorAlFinal(Vector *vec, const void *elem)
{
    if (CAP - vec->ce * vec->tamElem < vec->tamElem)
        return VEC_LLENO;

    memcpy(vec->v + vec->ce * vec->tamElem, elem, vec->tamElem);

    vec->ce++;

    return TODO_OK;
}

void mostrarVector(const Vector *vec, Mostrar mostrar)
{
    if (vec->ce == 0)
    {
        puts("El vector esta vacio.\n");
        return;
    }

    const void *ult = vec->v + (vec->ce - 1) * vec->tamElem;

    for (const void *i = vec->v; i <= ult; i += vec->tamElem)
        mostrar(i);

    putchar('\n');
}

boolean buscarEnVector(const Vector *vec, int elem)
{
    int posAct = 0;

    while (posAct < vec->ce && elem > vec->v[posAct])
        posAct++;

    return posAct < vec->ce && elem == vec->v[posAct];
}

boolean eliminarDeVectorOrdAsc(Vector *vec, int elem)
{
    int posElem = buscarEnVector(vec, elem);

    if (posElem == -1)
        return FALSO;

    for (int posAct = posElem; posAct < vec->ce - 1; posAct++)
        vec->v[posAct] = vec->v[posAct + 1];

    vec->ce--;

    return VERDADERO;
}

void ordenarVectorAscBurbujeo(Vector *vec)
{
    boolean huboIntercambio = VERDADERO;
    int i = 1;

    while (i < vec->ce && huboIntercambio)
    {
        huboIntercambio = FALSO;

        for (int j = 0; j < vec->ce - i; j++)
        {
            if (vec->v[j] > vec->v[j + 1])
            {
                intercambiar(&vec->v[j], &vec->v[j + 1]);
                huboIntercambio = VERDADERO;
            }
        }

        i++;
    }
    puts("Vector Ordenado de menor a mayor Satisfactoriamente\n");
}

void ordenarVectorDesBurbujeo(Vector *vec, int tamElem)
{
    boolean huboIntercambio = VERDADERO;
    int i = 1;

    while (i < vec->ce && huboIntercambio)
    {
        huboIntercambio = FALSO;

        for (int j = 0; j < vec->ce - i; j++)
        {
            if (vec->v[j] < vec->v[j + 1])
            {
                intercambiar(&vec->v[j], &vec->v[j + 1], tamElem);
                huboIntercambio = VERDADERO;
            }
        }

        i++;
    }
    puts("Vector Ordenado de mayor a menor Satisfactoriamente\n");
}

void ordenarVectorAscSeleccion(Vector *vec, Cmp cmp)
{
    void *m;
    void *ult = vec->v + (vec->ce - 1) * vec->tamElem;

    for (void *i = vec->v; i < ult; i += vec->tamElem)
    {
        m = buscarMenor(i, ult, vec->tamElem, cmp);

        if (m != i)
            intercambiar(m, i, vec->tamElem);
    }
    puts("Vector Ordenado de mayor a menor Satisfactoriamente\n");
}

void ordenarVectorDesSeleccion(Vector *vec, int tamElem)
{
    void *m;
    void *ult = vec->v + (vec->ce - 1) * vec->tamElem;

    for (void *i = vec->v; i > ult; i += vec->tamElem)
    {
        m = buscarMenor(i, ult, vec->tamElem);

        if (m != i)
            intercambiar(m, i, vec->tamElem);
    }
    puts("Vector Ordenado de mayor a menor Satisfactoriamente\n");
}

void ordenarVectorAscInsercion(Vector *vec)
{
    int elem;

    for (int i = 0; i <= vec->ce; i++)
    {
        int j;
        elem = vec->v[i];

        for (j = i - 1; j >= 0 && elem < vec->v[j]; j--)
            vec->v[j + 1] = vec->v[j];

        if (i != j + 1)
            vec->v[j + 1] = elem;
    }
    puts("Vector Ordenado de menor a mayor Satisfactoriamente\n");
}

void buscarMenor(void *inicio, void *fin, int tamElem, Cmp cmp)
{
    void *m = inicio;

    for (void *j = inicio + tamElem; j <= fin; j += tamElem)
    {
        if (cmp(j, m) < 0)
            m = j;
    }

    return m;
}

void intercambiar(void *v1, void *v2, int tamElem)
{
    char aux[tamElem];
    memcpy(aux, v1, tamElem);
    memcpy(v1, v2, tamElem);
    memcpy(v2, aux, tamElem);
}
