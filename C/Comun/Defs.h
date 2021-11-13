#ifndef DEFS_H
#define DEFS_H

typedef enum
{
    VERDADERO = 1,
    FALSO = 0
} boolean;

#define TODO_OK 0
#define DUPLICADO 1
#define SIN_MEMORIA 2
#define ACTUALIZADO 3

#define min(x, y) ((x) < (y) ? (x) : (y))

typedef int (*Cmp)(const void *, const void *);
typedef void (*Actualizar)(void *, const void *);
typedef void (*Mostrar)(const void *);

#endif // DEFS_H
