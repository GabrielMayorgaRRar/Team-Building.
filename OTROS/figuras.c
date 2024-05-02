#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define FIGURES 5
#define PI 3.141596

enum figuras
{
    CIRCULO,
    TRIANGULO,
    CUADRADO
};

typedef void *TFiguras;
typedef float TDato;

typedef struct informacionBase
{
    TDato area;
    TDato perimetro;
    short tipo;
    void *informacionAdicional;
} TFigura;

typedef struct circulo
{
    TDato radio;
} TCirculo;

typedef struct triangulo
{
    TDato altura;
    TDato base;
    TDato ladoA;
    TDato ladoB;
} TTriangulo;

typedef struct cuadrado
{
    TDato lado;
} TCuadrado;

TFiguras crear_arreglo(short figuras);
void calcular_informacion(TFiguras arreglo, short figuras);
void liberar_memoria(TFiguras arreglo, short figuras);

int main()
{
    TFiguras arreglo = NULL;
    arreglo = crear_arreglo(FIGURES);
    calcular_informacion(arreglo, FIGURES);

    return 0;
}

TFiguras crear_arreglo(short figuras)
{
    TFiguras arreglo = NULL;

    arreglo = (TFiguras *)malloc(sizeof(TFigura) * figuras);
    if (arreglo = NULL)
    {
        puts("ERROR. Error de memoria");
        exit(EXIT_FAILURE);
    }

    return arreglo;
}

void calcular_informacion(TFiguras arreglo, short figuras)
{
    for (TFigura *pt = (TFigura *)arreglo; pt < (TFigura *)arreglo + figuras; pt++)
    {
        switch (pt->tipo)
        {
        case CIRCULO:
            pt->area = PI * ((TCirculo *)pt->informacionAdicional)->radio * ((TCirculo *)pt->informacionAdicional)->radio;
            pt->perimetro = 2 * PI * ((TCirculo *)pt->informacionAdicional)->radio;
            break;

        case TRIANGULO:
            pt->area = ((TTriangulo *)pt->informacionAdicional)->base * ((TTriangulo *)pt->informacionAdicional)->altura / 2;
            pt->perimetro = ((TTriangulo *)pt->informacionAdicional)->ladoA +
                            ((TTriangulo *)pt->informacionAdicional)->ladoB +
                            ((TTriangulo *)pt->informacionAdicional)->base;
            break;

        case CUADRADO:
            pt->area = ((TCuadrado *)pt->informacionAdicional)->lado * ((TCuadrado *)pt->informacionAdicional)->lado;
            pt->perimetro = 4 * ((TCuadrado *)pt->informacionAdicional)->lado;
            break;

        default:
            puts("Figura Invalida");
            break;
        }
    }
}

void liberar_memoria(TFiguras arreglo, short figuras)
{
    for (TFigura *pt = arreglo; pt < (TFigura *)arreglo; pt++)
    {
        free(pt);
    }
    free(arreglo);
}