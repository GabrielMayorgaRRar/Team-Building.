#include <stdio.h>
#include <stdlib.h>

int main()
{
    int Filas, Columnas;
    printf("Filas: ");
    scanf("%d", &Filas);
    printf("Columnas: ");
    scanf("%d", &Columnas);

    int **matriz_original = (int **)malloc(sizeof(int *) * Filas);
    int **matriz_piramide = (int **)malloc(sizeof(int *) * Filas);
    if (matriz_original == NULL)
    {
        printf("ERROR: NO SE PUDO CREAR EL ESPACIO EN LA MEMORIA");
        exit(EXIT_FAILURE);
    }
    if (matriz_piramide == NULL)
    {
        printf("ERROR: NO SE PUDO CREAR EL ESPACIO EN LA MEMORIA");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < Filas; i++)
    {
        *(matriz_original + i) = (int *)malloc(sizeof(int *) * Columnas);
        if (*(matriz_original + i) == NULL)
        {
            printf("ERROR: NO SE PUDO CREAR EL ESPACIO EN LA MEMORIA");
            exit(EXIT_FAILURE);
        }
        *(matriz_piramide + i) = (int *)malloc(sizeof(int *) * (i + 1));
        if (*(matriz_piramide + i) == NULL)
        {
            printf("ERROR: NO SE PUDO CREAR EL ESPACIO EN LA MEMORIA");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < Filas; i++)
    {
        for (int j = 0; j < Columnas; j++)
        {
            scanf("%d", (*(matriz_original + i) + j));
        }
    }

    for (int i = 0; i < Filas; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            *(*(matriz_piramide + i) + j) = *(*(matriz_original + i) + j);
        }
    }

    printf("\nMatriz Piramide\n");
    for (int i = 0; i < Filas; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            printf("%d ", *(*(matriz_piramide + i) + j));
        }
        printf("\n");
    }
}