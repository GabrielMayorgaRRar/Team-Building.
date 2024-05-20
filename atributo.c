#include "atributo.h"

int nuevo_atributp(FILE *diccionarioDeDatos, TAtributo *atributoTemporal)
{
    int operacionResultado = EXIT_SUCCESS;

    if (diccionarioDeDatos)
    {
        if (agregar_atributo(diccionarioDeDatos, atributoTemporal) == EXIT_SUCCESS)
        {
            long cabeceraDiccionario = valor_cabecera(diccionarioDeDatos);
            reasignar_punteros_atributo(diccionarioDeDatos, CABECERA_POSICION_PRINCIPAL, atributoTemporal);
        }
        else
        {
            fprintf(stderr, "Error para crear \"%s\" entidad.\n", atributoTemporal->nombre);
            operacionResultado = EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "Error para abrir el diccionario de datos.\n");
        operacionResultado = EXIT_FAILURE;
    }

    return operacionResultado;
}

int agregar_atributo(FILE *diccionarioDeDatos, TAtributo *datoAtributo)
{
    int operacionResultado = EXIT_SUCCESS;
    long posicionNuevoAtributo = CABECERA_POSICION_PRINCIPAL;

    fseek(diccionarioDeDatos, CABECERA_POSICION_PRINCIPAL, SEEK_END);

    posicionNuevoAtributo = ftell(diccionarioDeDatos);
    datoAtributo->direccionArchivo = posicionNuevoAtributo;

    // Agrega el nombre del atributp
    fwrite(&datoAtributo->nombre, sizeof(char), NOMBRE_ATRIBUTO, diccionarioDeDatos);
    // Agrega el tipo del atributo
    fwrite(&datoAtributo->tipo, sizeof(TipoAtributo), 1, diccionarioDeDatos);
    // Agrega el tamaño del atributo
    fwrite(&datoAtributo->largo, sizeof(int), 1, diccionarioDeDatos);
    // Agrega la direccion del siguiente atributo
    fwrite(&datoAtributo->ptrSigAtributo, sizeof(long), 1, diccionarioDeDatos);

    printf("Nuevo atributo \"%s\" agregado en la posicion %li\n", datoAtributo->nombre, datoAtributo->direccionArchivo);

    return operacionResultado;
}

void reasignar_punteros_atributo(FILE *diccionarioDeDatos, long ptrAtributoActual, TAtributo *atributoNuevo)
{
    long direccionAtributoActual = SIN_DIRECCION;

    fseek(diccionarioDeDatos, ptrAtributoActual, SEEK_SET);
    fread(&direccionAtributoActual, sizeof(long), 1, diccionarioDeDatos);

    if (direccionAtributoActual == SIN_DIRECCION)
    {
        fseek(diccionarioDeDatos, ptrAtributoActual, SEEK_SET);
        fwrite(&atributoNuevo->direccionArchivo, sizeof(long), 1, diccionarioDeDatos);
    }
    else
    {
        char nombreAtributoActual[NOMBRE_ATRIBUTO];
        long direccionSigAtributo;
        long ptrSigAtributo;

        //
        fseek(diccionarioDeDatos, direccionAtributoActual, SEEK_SET);
        //
        fread(&nombreAtributoActual, sizeof(char), NOMBRE_ATRIBUTO, diccionarioDeDatos);
        ptrSigAtributo = ftell(diccionarioDeDatos) + sizeof(TipoAtributo) + sizeof(int);
        //
        if (strcmp(nombreAtributoActual, atributoNuevo->nombre) < 0)
        {
            reasignar_punteros_atributo(diccionarioDeDatos, ptrSigAtributo, atributoNuevo);
        }
        else
        {
            fseek(diccionarioDeDatos, ptrAtributoActual, SEEK_SET);
            fwrite(&atributoNuevo->direccionArchivo, sizeof(long), 1, diccionarioDeDatos);
            //
            fseek(diccionarioDeDatos, atributoNuevo->direccionArchivo + NOMBRE_ATRIBUTO + sizeof(TipoAtributo) + sizeof(int), SEEK_SET);
            fwrite(&direccionAtributoActual, sizeof(long), 1, diccionarioDeDatos);
        }
    }
}

TAtributo *crear_atributo(const char *nombreAtributo)
{
    TAtributo *atributoNuevo = (TAtributo *)malloc(sizeof(TAtributo));
    assert(atributoNuevo != NULL);

    strcpy(atributoNuevo->nombre, nombreAtributo);
    atributoNuevo->direccionArchivo = SIN_DIRECCION;
    atributoNuevo->tipo = CADENA;
    atributoNuevo->largo = 5;

    return atributoNuevo;
}

void imprimir_atributo(FILE *diccionarioDeDatos, long cabeceraActual)
{
    if (cabeceraActual == SIN_DIRECCION)
    {
        return;
    }
    else
    {
        TAtributo atributoActual;

        fseek(diccionarioDeDatos, cabeceraActual, SEEK_SET);
        fread(&atributoActual.nombre, sizeof(char), NOMBRE_ATRIBUTO, diccionarioDeDatos);
        fread(&atributoActual.tipo, sizeof(TipoAtributo), 1, diccionarioDeDatos);
        fread(&atributoActual.largo, sizeof(int), 1, diccionarioDeDatos);
        fread(&atributoActual.ptrSigAtributo, sizeof(long), 1, diccionarioDeDatos);

        printf("\tTAtributo: %s | Tipo: %i | Largo: %i\n", atributoActual.nombre, (int)atributoActual.tipo, atributoActual.largo);
        imprimir_atributo(diccionarioDeDatos, atributoActual.ptrSigAtributo);
    }
}
