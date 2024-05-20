#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*TODO
deuelve nombre entidad, posicion archivo y apuntadores, para reutilizarlos como cabecera*/
/*PREGUNTAR PORQUE ATRIBUTO DESEA AGREGAR, EL TIPO Y SU TAMAÑO EN CADENAS*/

#define CABECERA_POSICION_PRINCIPAL 0L
#define NOMBRE_ATRIBUTO 50
#define SIN_DIRECCION -1L

typedef enum tipoAtributo
{
    CARACTER,
    ENTERO,
    CADENA
} TipoAtributo;

typedef struct atributo
{
    long direccionArchivo;
    char nombre[NOMBRE_ATRIBUTO];
    TipoAtributo tipo;
    int largo;
    long ptrSigAtributo;
} TAtributo;

int nuevo_atributp(FILE *diccionarioDeDatos, TAtributo *atributoTemporal);
int agregar_atributo(FILE *diccionarioDeDatos, TAtributo *datoAtributo);
int eliminar_atributo(FILE *diccionarioDeDatos, long ptratributoActual, const char *nombreatributo);
long valor_cabecera(FILE *diccionarioDeDatos);
void reasignar_punteros_atributo(FILE *diccionarioDeDatos, long ptrAtributoActual, TAtributo *atributoNuevo);
void imprimir_atributo(FILE *diccionarioDeDatos, long cabeceraActual);
int buscar_atributo(FILE *diccionarioDeDatos, long cabecera, const char *nombreatributo);

TAtributo *crear_atributo(const char *nombreAtributo);

#endif