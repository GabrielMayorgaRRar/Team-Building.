#include "diccionario.h"

void inicializar_diccionario(const char *nombre)
{

     long header = -1L;
    FILE *ptr = fopen(nombre, "wb");
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

    return status;
}

void initializeDataDictionary(const char *filename)
{
    
}