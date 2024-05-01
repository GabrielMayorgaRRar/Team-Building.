#ifndef MAIN_H
#define MAIN_H

#define MAX_LINE 50

#include <stdio.h>
#include <stdlib.h>
#include "diccionario.h"

typedef enum
{
    SIN_SELECCION,
    NUEVO_DICCIONARIO,
    ABRIR_DICCIONARIO,
    CERRAR_PROGRAMA
} OpcionMenu;

void mostrar_menu(void);
short entrada_de_usuario(void);
void procesar_opcion_seleccionada(OpcionMenu opcionSeleccionada);
void leer_nombre(const char *prompt, char *buffer, size_t tamanio);
void limpiar_buffer(void);

#endif