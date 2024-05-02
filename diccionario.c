#include "diccionario.h"

void inicializar_diccionario(const char *nombre)
{
    printf("Diccionario de datos: %s\n", nombre);
}

short abrir_diccionario_de_datos(const char *nombre)
{
    int status = EXIT_SUCCESS;
    long header;
    FILE *ptr;
    ptr = fopen(nombre, "rb");

    if (ptr)
    {
        fread(&header, sizeof(header), 1, ptr);
        printf("Current Header: %ld\n", header);
    }
    else
    {
        fprintf(stderr, "FAILED TO OPEN THE DATA DICTIONARY");
        status = EXIT_FAILURE;
    }

    fclose(ptr);
    return EXIT_SUCCESS;
}

void initializeDataDictionary(const char *filename)
{
    long header = -1L;
    FILE *ptr = fopen(filename, "wb");
    if (ptr == NULL)
    {
        fprintf(stderr, "FAILED TO OPEN THE DATA DICTIONARY");
    }
    else
    {
        fwrite(&header, sizeof(header), 1, ptr);
    }
    fclose(ptr);
}