#include "diccionario.h"
#include "entidad.h"

void inicializar_diccionario(const char *nombreArchivo)
{
    long cabecera = SIN_DIRECCION;
    FILE *archivo = fopen(nombreArchivo, "wb");

    if (archivo == NULL)
    {
        fprintf(stderr, "Error al crear el diccionario de datos.\n");
    }

    if (fwrite(&cabecera, sizeof(cabecera), 1, archivo) != 1)
    {
        fprintf(stderr, "Error al inicializar el diccionario de datos.\n");
    }

    fclose(archivo);
}

int abrir_diccionario_de_datos(const char *nombreArchivo)
{
    int resultadoOperacion = EXIT_SUCCESS;
    long cabecera;
    FILE *archivo = fopen(nombreArchivo, "rb");

    if (archivo)
    {
        if (fread(&cabecera, sizeof(cabecera), 1, archivo) != 1)
        {
            fprintf(stderr, "Error para leer datos.\n");
            resultadoOperacion = EXIT_FAILURE;
        }
        else
        {
            printf("El valor de la cabecera es: %ld\n", cabecera);
        }
        fclose(archivo);
    }
    else
    {
        fprintf(stderr, "Error para abrir el diccionario de datos.\n");
        resultadoOperacion = EXIT_FAILURE;
    }

    return resultadoOperacion;
}

void imprimir_diccionario_de_datos(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "rb");

    if (archivo)
    {
        // TEntidad entidadDato;
        printf("Nombre del diccionario: %s\n", nombreArchivo);
        long primerEntidad;
        fread(&primerEntidad, sizeof(long), 1, archivo);
        imprimir_entidad(archivo, primerEntidad);
        fclose(archivo);
    }
    else
    {
        fprintf(stderr, "Error al abrir el diccionario de datos.\n");
    }
}

void operar_diccionario(OpcionSubmenu opcionSeleccionada, const char *nombreDiccionario)
{
    FILE *ptrDiccionario = fopen(nombreDiccionario, "r+b");
    char nombreEntidad[NOMBRE_ENTIDAD];

    // factorizar
    TEntidad entidadTemporal;
    entidadTemporal.ptrDato = SIN_DIRECCION;
    entidadTemporal.ptrAtributo = SIN_DIRECCION;
    entidadTemporal.ptrEntidad = SIN_DIRECCION;

    switch (opcionSeleccionada)
    {
    case IMPRIMIR_DICCIONARIO:
        imprimir_diccionario_de_datos(nombreDiccionario);
        break;
    case NUEVA_ENTIDAD:
        printf("Ingresa el nombre de la nueva entidad: ");
        scanf("%[^\n]%*c", entidadTemporal.nombre);
        nueva_entidad(ptrDiccionario, &entidadTemporal);
        break;
    case ELIMINAR_ENTIDAD:
        printf("Ingresa el nombre de la entidad a eliminar: ");
        scanf("%[^\n]%*c", entidadTemporal.nombre);
        eliminar_entidad(ptrDiccionario, CABECERA_POSICION_PRINCIPAL, &entidadTemporal);
        break;
    case MODIFICAR_ENTIDAD:
        printf("Ingresa el nombre de la entidad a modificar: ");
        scanf("%[^\n]%*c", entidadTemporal.nombre);
        if (eliminar_entidad(ptrDiccionario, CABECERA_POSICION_PRINCIPAL, &entidadTemporal) != EXIT_FAILURE)
        {
            printf("Ingresa el nombre de la nueva entidad: ");
            scanf("%[^\n]%*c", entidadTemporal.nombre);
            nueva_entidad(ptrDiccionario, &entidadTemporal);
        }
        /* que es modificar, que se le modifica
        DAR DE BAJA Y DAR DE ALTA O SOLO CAMBIAR EL NOMBRE DE IDENTIDAD*/
        break;
    case NUEVO_ATRIBUTO:
        printf("Ingresa el nombre de la entidad: ");
        scanf("%[^\n]%*c", entidadTemporal.nombre);
        if (buscar_entidad(ptrDiccionario, CABECERA_POSICION_PRINCIPAL, entidadTemporal.nombre) == EXIT_SUCCESS)
        {
            TAtributo atributoTemporal;
            atributoTemporal.ptrSigAtributo = SIN_DIRECCION;
            printf("Ingresa el tipo del nuevo atributo: ");
            int tipo;
            scanf("%i%*c", &tipo);
            atributoTemporal.tipo = tipo;
            switch (atributoTemporal.tipo)
            {
            case CARACTER:
                atributoTemporal.largo = sizeof(char);
                break;
            case ENTERO:
                atributoTemporal.largo = sizeof(int);
                break;
            case CADENA:
                atributoTemporal.largo = sizeof(NOMBRE_ATRIBUTO);
                break;
            default:
                puts("ERROR.");
                exit(EXIT_FAILURE);
                break;
            }
            printf("Ingresa el nombre del nuevo atributo: ");
            scanf("%[^\n]%*c", atributoTemporal.nombre);
            agregar_atributo(ptrDiccionario, &atributoTemporal);
            eliminar_entidad(ptrDiccionario, CABECERA_POSICION_PRINCIPAL, &entidadTemporal);
            entidadTemporal.ptrAtributo = atributoTemporal.direccionArchivo;
            nueva_entidad(ptrDiccionario, &entidadTemporal);
        }
        break;
    case ELIMINAR_ATRIBUTO:
        /* code */
        break;
    case MODIFICAR_ATRIBUTO:
        /* como se modifica un atributo */
        break;
    case REGRESAR:
        break;
    default:
        puts("Opcion no valida, intenta de nuevo");
        /*Preguntar como esta organizado cada dato y como es que se conectan los atributos y entidades
        POR LOS 3 APUNTADORES QUE POSEEE
        LOS DATOS QUEDAN VACIOS*/
        break;
    }

    fclose(ptrDiccionario);
}
