#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TDA_COLA_IMPL_DINAMICA
#include "../TDACola/TDACola.h"

typedef struct
{
    char nombre[31];
    unsigned tiempoEnCajero;
} Cliente;

unsigned calcularTiempoArribo();
void generarCliente(Cliente *cliente);
unsigned calcularTiempoEnCajero();

int main()
{
    srand(time(NULL));

    unsigned tiempoArribo = calcularTiempoArribo();
    Cliente clienteEnCajero, cliente;
    boolean cajeroOcupado = FALSO;
    unsigned cantVecesColaVacia;
    unsigned minuto = 0;

    Cola colaCajero;
    crearCola(&colaCajero);

    while (cantVecesColaVacia < 5)
    {
        printf("Minuto %d\n", minuto);

        if (tiempoArribo == 0)
        {
            generarCliente(&cliente);

            if (!cajeroOcupado)
            {
                cajeroOcupado = VERDADERO;
                clienteEnCajero = cliente;
                printf("Llego el cliente %s e ingreso al cajero. Va a usar el cajero %d minutos.\n", cliente.nombre, cliente.tiempoEnCajero);
            }
            else
            {
                encolar(&colaCajero, &cliente, sizeof(Cliente));
                printf("Llego el cliente %s e ingreso a la cola. Va a usar el cajero %d minutos.\n", cliente.nombre, cliente.tiempoEnCajero);
            }

            tiempoArribo = calcularTiempoArribo();
        }

        if (cajeroOcupado)
        {
            clienteEnCajero.tiempoEnCajero--;

            if (clienteEnCajero.tiempoEnCajero == 0)
            {
                printf("ElCiente %s termino de usar el cajero.\n", clienteEnCajero.nombre);
                cajeroOcupado = FALSO;

                if (!ColaVacia(&colaCajero))
                {
                    desencolar(&colaCajero, &clienteEnCajero, sizeof(Cliente));
                    cajeroOcupado = VERDADERO;
                    printf("El cliente %s, que estaba en la cola, ingreso al cajero.\n", clienteEnCajero.nombre);

                    if (ColaVacia(&colaCajero))
                        cantVecesColaVacia++;
                }
            }
        }

        minuto++;
        tiempoArribo--;
    }

    return 0;
}

unsigned calcularTiempoArribo()
{
    static const unsigned ta[] = {1, 5, 9};

    return ta[rand() % 3];
}

void generarCliente(Cliente *cliente)
{
    static const char nombres[][9] = {"Juan",
                                      "Pedro",
                                      "Adrian",
                                      "Bernardo",
                                      "Carlos",
                                      "Dario",
                                      "Andrea",
                                      "Brenda",
                                      "Carla",
                                      "Daniela",
                                      "Esteban",
                                      "Fernanda",
                                      "Fernando",
                                      "Gaston",
                                      "Graciela"};

    strcpy(cliente->nombre, nombres[rand() % 15]);

    cliente->tiempoEnCajero = calcularTiempoArribo();
}

unsigned calcularTiempoEnCajero()
{
    static const unsigned tec[] = {1, 3, 5};

    return tec[rand() % 3];
}
