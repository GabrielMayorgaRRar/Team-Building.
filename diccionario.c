#include "diccionario.h"

void inicializar_diccionario(const char *nombre)
{
    printf("Diccionario de datos: %s\n", nombre);
}

short abrir_diccionario_de_datos(const char *nombre)
{
    FILE *ptr;
    ptr = fopen(nombre, "wb");
    fclose(ptr);
    
    return EXIT_SUCCESS;
}
