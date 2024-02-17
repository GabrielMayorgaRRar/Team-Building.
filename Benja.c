#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define ROWS 3
#define COLUMNS 4

void **crear_matriz(short filas, short columnas);
void rellena_matriz(void ***matriz, short filas, short columnas);
void copiando_matriz(void **matriz1, void ***matriz2, short filas, short columnas);
void imprime_matriz(void ***matriz, short filas, short columnas);

int main()
{
    void **matriz1 = NULL;
    void **matriz2 = NULL;
    matriz1 = crear_matriz(ROWS, COLUMNS);
    rellena_matriz(&matriz1, ROWS, COLUMNS);
    copiando_matriz(matriz1, &matriz2, ROWS, COLUMNS);
    imprime_matriz(&matriz1, ROWS, COLUMNS);
    imprime_matriz(&matriz2, ROWS, COLUMNS);

    return 0;
}

void **crear_matriz(short filas, short columnas)
{
    void **matrizAuxiliar = (void **)malloc(sizeof(void *) * filas);

    for (int i = 0; i < filas; i++)
    {
        matrizAuxiliar[i] = (short *)malloc(sizeof(short) * columnas);
        if (matrizAuxiliar[i] == NULL)
        {
            puts("ERROR. Error de memoria");
            exit(EXIT_FAILURE);
        }
    }

    return matrizAuxiliar;
}

void rellena_matriz(void ***matriz, short filas, short columnas)
{
    srand(time(NULL));
    for (short i = 0; i < filas; i++)
    {
        for (short j = 0; j < columnas; j++)
        {
            *((short *)(*matriz + i) + j) = rand() % 10;
        }
    }
}

void copiando_matriz(void **matriz1, void ***matriz2, short filas, short columnas)
{
    *matriz2 = crear_matriz(filas, columnas);

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            *((short *)(*matriz2) + i * columnas + j) = *((short *)(matriz1) + i * columnas + j);
        }
    }
}

void imprime_matriz(void ***matriz, short filas, short columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            printf("%d ", *((short *)(*matriz) + i * columnas + j));
        }
        puts("");
    }
}
