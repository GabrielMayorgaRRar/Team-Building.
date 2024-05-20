#include "main.h"

int main(void)
{
    short opcionActual = SIN_SELECCION;
    do
    {
        mostrar_menu();
        opcionActual = entrada_de_usuario();
        system("clear");
        procesar_opcion_seleccionada((OpcionMenu)opcionActual);
    } while (opcionActual != CERRAR_PROGRAMA);

    return EXIT_SUCCESS;
}

void mostrar_menu(void)
{
    puts("----------Diccionario de Datos----------");
    printf("%i) Crear un nuevo diccionario\n", NUEVO_DICCIONARIO);
    printf("%i) Abrir un diccionario existente\n", ABRIR_DICCIONARIO);
    printf("%i) Salir\n", CERRAR_PROGRAMA);
}

short entrada_de_usuario(void)
{
    short opcion_seleccionada;
    printf("Por favor selecciona una opcion: ");
    scanf("%hi", &opcion_seleccionada);
    limpiar_buffer();

    return opcion_seleccionada;
}

void procesar_opcion_seleccionada(OpcionMenu opcionSeleccionada)
{
    char nombreDiccionario[MAX_LINE];

    switch (opcionSeleccionada)
    {
    case NUEVO_DICCIONARIO:
        leer_nombre("Ingresa el nombre del diccionario: ", nombreDiccionario, MAX_LINE);
        inicializar_diccionario(nombreDiccionario);
        break;
    case ABRIR_DICCIONARIO:
        leer_nombre("Ingresa el nombre del diccionario: ", nombreDiccionario, MAX_LINE);
        break;
    case CERRAR_PROGRAMA:
        puts("Saliendo...");
        break;
    default:
        puts("Opcion no valida, intenta de nuevo");
        break;
    }

    if (opcionSeleccionada != CERRAR_PROGRAMA && abrir_diccionario_de_datos(nombreDiccionario) == EXIT_SUCCESS)
    {
        if (opcionSeleccionada == NUEVO_DICCIONARIO)
        {
            puts("El diccionario de datos ha sido creado");
        }
        puts("El diccionario de datos ha sido abierto");
        short operacionRealizar = SIN_SELECCION;
        do
        {
            mostrar_submenu();
            operacionRealizar = entrada_de_usuario();
            system("clear");
            operar_diccionario((OpcionSubmenu)operacionRealizar, nombreDiccionario);
        } while (operacionRealizar != REGRESAR);
        // pasar entidad por referencia, para saber si existe y de existir agregar atributos
    }
}

void leer_nombre(const char *prompt, char *buffer, size_t tamanio)
{
    if (prompt != NULL)
    {
        printf("%s", prompt);
    }
    if (fgets(buffer, tamanio, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

void limpiar_buffer(void)
{
    char caracter;
    while ((caracter = getchar()) != EOF && caracter != '\n')
    {
    }
}

void mostrar_submenu(void)
{
    puts("----------Operacion a realizar----------");
    printf("%i) Imprimir diccionario de datos\n", IMPRIMIR_DICCIONARIO);
    printf("%i) Nueva entidad\n", NUEVA_ENTIDAD);
    printf("%i) Eliminar entidad\n", ELIMINAR_ENTIDAD);
    printf("%i) Modificar entidad\n", MODIFICAR_ENTIDAD);
    printf("%i) Nuevo atributo\n", NUEVO_ATRIBUTO);
    printf("%i) Eliminar atributo\n", ELIMINAR_ATRIBUTO);
    printf("%i) Modificar atributo\n", MODIFICAR_ATRIBUTO);
    printf("%i) Regresar\n", REGRESAR);
}
