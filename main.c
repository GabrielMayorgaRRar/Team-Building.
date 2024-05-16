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
        if (abrir_diccionario_de_datos(nombreDiccionario) == EXIT_SUCCESS)
        {
            puts("El diccionario de datos fue abierto");
        }
        break;
    case ABRIR_DICCIONARIO:
        leer_nombre("Ingresa el nombre del ciccionario: ", nombreDiccionario, MAX_LINE);
        if (abrir_diccionario_de_datos(nombreDiccionario) == EXIT_SUCCESS)
        {
            puts("El diccionario de datos fue abierto");
        }
        break;
    case CERRAR_PROGRAMA:
        puts("Saliendo...");
        break;
    default:
        puts("Opcion no valida");
        break;
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
    while ((caracter = getchar()) != EOF && caracter != caracter)
    {
    }
}

int searchDataEntity(FILE *dataDictionary, long header, const char *entityName)
{
    long headerValue;
    fseek(dataDictionary, header, SEEK_SET);
    fread(&headerValue, sizeof(headerValue), 1, dataDictionary);
    if (headerValue == -1)
        return EXIT_FAILURE;
    char currentEntity[50];
    long nextHeaderPointer;
    fseek(dataDictionary, headerValue,SEEK_SET);
    fread(&currentEntity, 50, 1, dataDictionary);

    }