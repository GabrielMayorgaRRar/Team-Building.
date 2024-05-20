#include "entidad.h"

int agregar_entidad(FILE *diccionarioDeDatos, TEntidad *datoEntidad)
{
    int operacionResultado = EXIT_SUCCESS;
    long posicionNuevaEntidad = CABECERA_POSICION_PRINCIPAL;
    // const long ptrNulo = SIN_DIRECCION;

    fseek(diccionarioDeDatos, CABECERA_POSICION_PRINCIPAL, SEEK_END);

    posicionNuevaEntidad = ftell(diccionarioDeDatos);
    datoEntidad->direccionArchivo = posicionNuevaEntidad;

    // Add the entity name
    fwrite(&datoEntidad->nombre, sizeof(char), NOMBRE_ENTIDAD, diccionarioDeDatos);
    // Data pointer
    fwrite(&datoEntidad->ptrDato, sizeof(long), 1, diccionarioDeDatos);
    // Attributes pointer
    fwrite(&datoEntidad->ptrAtributo, sizeof(long), 1, diccionarioDeDatos);
    // Next entity pointer
    fwrite(&datoEntidad->ptrEntidad, sizeof(long), 1, diccionarioDeDatos);

    printf("Nueva entidad \"%s\" agregada en la posicion %ld\n", datoEntidad->nombre, datoEntidad->direccionArchivo);

    return operacionResultado;
}

int eliminar_entidad(FILE *diccionarioDeDatos, long ptrEntidadActual, TEntidad *entidadTemporal)
{
    long direccionActualDireccion = SIN_DIRECCION;
    fseek(diccionarioDeDatos, ptrEntidadActual, SEEK_SET);
    fread(&direccionActualDireccion, sizeof(direccionActualDireccion), 1, diccionarioDeDatos);

    if (direccionActualDireccion == SIN_DIRECCION)
    {
        fprintf(stderr, "Error de eliminacion, entidad no encontrada\n");
        return EXIT_FAILURE;
    }
    else
    {
        char nombreEntidadActual[NOMBRE_ENTIDAD];
        long ptrSigEntidad;

        // Va a la localizacion de la entidad y lee el dato
        fseek(diccionarioDeDatos, direccionActualDireccion, SEEK_SET);
        // Lee el nombre de la entidad actual
        fread(&nombreEntidadActual, sizeof(char), NOMBRE_ENTIDAD, diccionarioDeDatos);
        ptrSigEntidad = ftell(diccionarioDeDatos) + (sizeof(long) * 2);

        // Compara los nombres de entidades para determinar si podria ser eliminada la entidad
        if (strcmp(nombreEntidadActual, entidadTemporal->nombre) == 0)
        {
            // Lee los punteros de la entidad
            fread(&entidadTemporal->ptrAtributo, sizeof(long), 1, diccionarioDeDatos);
            fread(&entidadTemporal->ptrDato, sizeof(long), 1, diccionarioDeDatos);
            fread(&entidadTemporal->ptrEntidad, sizeof(long), 1, diccionarioDeDatos);

            // Reasigna punteros
            fseek(diccionarioDeDatos, ptrEntidadActual, SEEK_SET);
            fwrite(&entidadTemporal->ptrEntidad, sizeof(long), 1, diccionarioDeDatos);
            fprintf(stdout, "Eliminacion exitosa, entidad eliminada\n");
            return EXIT_SUCCESS;
        }
        else
        {
            return eliminar_entidad(diccionarioDeDatos, ptrSigEntidad, entidadTemporal);
        }
    }
}

long valor_cabecera(FILE *diccionarioDeDatos)
{
    long cabecera;

    fseek(diccionarioDeDatos, CABECERA_POSICION_PRINCIPAL, SEEK_SET);
    fread(&cabecera, sizeof(long), 1, diccionarioDeDatos);

    return cabecera;
}

void reasignar_punteros_entidad(FILE *diccionarioDeDatos, long cabeceraActual, const char *nombreNuevaEntidad, long direccionNuevaEntidad)
{
    long valorCabecera = SIN_DIRECCION;

    fseek(diccionarioDeDatos, cabeceraActual, SEEK_SET);
    fread(&valorCabecera, sizeof(long), 1, diccionarioDeDatos);

    if (valorCabecera == SIN_DIRECCION)
    {
        // No more entities to iterate. Set the current pointer to the new entity direction.
        fseek(diccionarioDeDatos, cabeceraActual, SEEK_SET);
        fwrite(&direccionNuevaEntidad, sizeof(long), 1, diccionarioDeDatos);
    }
    else
    {
        char nombreEntidadActual[NOMBRE_ENTIDAD];
        long direccionSigEntidad;
        long ptrSigCabecera;

        // Go to the TEntidad location and read its data.
        fseek(diccionarioDeDatos, valorCabecera, SEEK_SET);
        // Read the name for the entity at the current position.
        fread(&nombreEntidadActual, sizeof(char), NOMBRE_ENTIDAD, diccionarioDeDatos);
        ptrSigCabecera = ftell(diccionarioDeDatos) + (sizeof(long) * 2);
        // Compare the TEntidad names to determine whether the current entity should be before the new one or not.
        if (strcmp(nombreEntidadActual, nombreNuevaEntidad) < 0)
        {
            // Current entity is before the new one.
            reasignar_punteros_entidad(diccionarioDeDatos, ptrSigCabecera, nombreNuevaEntidad, direccionNuevaEntidad);
        }
        else
        {
            // Reassign first pointer.
            fseek(diccionarioDeDatos, cabeceraActual, SEEK_SET);
            fwrite(&direccionNuevaEntidad, sizeof(long), 1, diccionarioDeDatos);
            // Reassign new entity pointer.
            fseek(diccionarioDeDatos, direccionNuevaEntidad + NOMBRE_ENTIDAD + (sizeof(long) * 2), SEEK_SET);
            fwrite(&valorCabecera, sizeof(long), 1, diccionarioDeDatos);
        }
    }
}

void imprimir_entidad(FILE *diccionarioDeDatos, long cabeceraActual)
{
    if (cabeceraActual == SIN_DIRECCION)
    {
        return;
    }
    else
    {
        TEntidad entidadActual;

        fseek(diccionarioDeDatos, cabeceraActual, SEEK_SET);
        fread(&entidadActual.nombre, sizeof(char), NOMBRE_ENTIDAD, diccionarioDeDatos);
        fread(&entidadActual.ptrDato, sizeof(long), 1, diccionarioDeDatos);
        fread(&entidadActual.ptrAtributo, sizeof(long), 1, diccionarioDeDatos);
        fread(&entidadActual.ptrEntidad, sizeof(long), 1, diccionarioDeDatos);

        printf("TEntidad: %s\n", entidadActual.nombre);
        imprimir_atributo(diccionarioDeDatos, entidadActual.ptrAtributo);
        imprimir_entidad(diccionarioDeDatos, entidadActual.ptrEntidad);
    }
}

int buscar_entidad(FILE *diccionarioDeDatos, long cabecera, const char *nombreEntidad)
{
    long valorCabecera;

    fseek(diccionarioDeDatos, cabecera, SEEK_SET);
    fread(&valorCabecera, sizeof(long), 1, diccionarioDeDatos);

    if (valorCabecera == SIN_DIRECCION)
    {
        fprintf(stderr, "Error de busqueda, entidad no encontrada\n");
        return EXIT_FAILURE;
    }

    char entidadActual[NOMBRE_ENTIDAD];
    fseek(diccionarioDeDatos, valorCabecera, SEEK_SET);
    fread(&entidadActual, sizeof(char), NOMBRE_ENTIDAD, diccionarioDeDatos);

    // TEntidad entidadTemporal;
    // fread(&entidadTemporal.nombre, sizeof(NOMBRE_ENTIDAD), 1, diccionarioDeDatos);
    // fread(&entidadTemporal.ptrDato, sizeof(long), 1, diccionarioDeDatos);
    // fread(&entidadTemporal.ptrAtributo, sizeof(long), 1, diccionarioDeDatos);
    // fread(&entidadTemporal.ptrEntidad, sizeof(long), 1, diccionarioDeDatos);

    if (strcmp(nombreEntidad, entidadActual) == 0)
    {
        return EXIT_SUCCESS;
    }
    long ptrSigCabecera = ftell(diccionarioDeDatos) + (sizeof(long) * 2);
    return buscar_entidad(diccionarioDeDatos, ptrSigCabecera, nombreEntidad);
}

TEntidad *crear_entidad(void)
{
    char nombreEntidad[NOMBRE_ENTIDAD];

    printf("Nombre de la nueva entidad: ");
    scanf("%[^\n]", nombreEntidad);
    getchar();

    TEntidad *nuevaEntidad = (TEntidad *)malloc(sizeof(TEntidad));
    strcpy(nuevaEntidad->nombre, nombreEntidad);
    nuevaEntidad->ptrAtributo = SIN_DIRECCION;
    nuevaEntidad->ptrDato = SIN_DIRECCION;
    nuevaEntidad->ptrEntidad = SIN_DIRECCION;
    nuevaEntidad->direccionArchivo = SIN_DIRECCION;

    return nuevaEntidad;
}

int nueva_entidad(FILE *diccionarioDeDatos, TEntidad *entidadTemporal)
{
    int operacionResultado = EXIT_SUCCESS;

    if (diccionarioDeDatos)
    {
        // TEntidad entidad;

        // snprintf(entidad.nombre, sizeof(entidad.nombre), "%s", entidadTemporal->nombre);
        if (agregar_entidad(diccionarioDeDatos, entidadTemporal) == EXIT_SUCCESS)
        {
            long cabeceraDiccionario = valor_cabecera(diccionarioDeDatos);
            reasignar_punteros_entidad(diccionarioDeDatos, CABECERA_POSICION_PRINCIPAL, entidadTemporal->nombre, entidadTemporal->direccionArchivo);
        }
        else
        {
            fprintf(stderr, "Error para crear \"%s\" entidad.\n", entidadTemporal->nombre);
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