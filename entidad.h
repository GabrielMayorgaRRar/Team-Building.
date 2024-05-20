#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "atributo.h"

#define CABECERA_POSICION_PRINCIPAL 0L
#define NOMBRE_ENTIDAD 50
#define SIN_DIRECCION -1L

typedef struct datoEntidad
{
    long direccionArchivo;       // almacena direccion en append, sirve para la reasignacion de apuntadores
    char nombre[NOMBRE_ENTIDAD];
    long ptrDato;
    long ptrAtributo;
    long ptrEntidad;
    // pasar 2 parametros o 1 solo (entidad por referencia)
    // variable NULLPTR
} TEntidad;

int agregar_entidad(FILE *diccionarioDeDatos, TEntidad *datoEntidad);
int eliminar_entidad(FILE *diccionarioDeDatos, long ptrEntidadActual, TEntidad *entidadTemporal);
long valor_cabecera(FILE *diccionarioDeDatos);
void reasignar_punteros_entidad(FILE *diccionarioDeDatos, long cabeceraActual, const char *nombreNuevaEntidad, long direccionNuevaEntidad);
void imprimir_entidad(FILE *diccionarioDeDatos, long cabeceraActual);
int buscar_entidad(FILE *diccionarioDeDatos, long cabecera, const char *nombreEntidad);

/*Funciones Adicionales*/
TEntidad *crear_entidad(void);
int nueva_entidad(FILE *diccionarioDeDatos, TEntidad *entidadTemporal);

#endif