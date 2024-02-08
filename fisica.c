#include <stdio.h>

void menu();
void distancia();
void aceleracion();
void fuerza();
void celcius_farenheit();

int main()
{
    int opcion;
    menu();
    scanf("%i", &opcion);
    fflush(stdin);

    return 0;
}

void menu()
{
    puts("Selecciona el tipo de problema a resolver:");
    puts("\t1. Distancia");
    puts("\t2. Aceleracion");
    puts("\t3. Fuerza");
    puts("\t4. Conversion de grados Celsius a Farhrenheit");
}

void distancia(void)
{
    double tiempo, velocidad, distancia;
    printf("Tiempo y velocidad: ");
    scanf("%lf %lf", &tiempo, &velocidad);
    distancia = tiempo * velocidad;
    printf("%lf", distancia);
}

void aceleracion(void)
{
    double velocidadInicial, velocidadFinal, tiempo, aceleracion;
    printf("Velocidad inicial, final y tiempo: ");
    scanf("%lf %lf %lf", &velocidadInicial, &velocidadFinal, &tiempo);
    aceleracion = (velocidadFinal - velocidadInicial) / tiempo;
    printf("%.2lf", aceleracion);
}

void fuerza(void)
{
    double fuerza, masa, aceleracion;
    printf("Masa y aceleracion: ");
    scanf("%lf %lf", &masa, &aceleracion);
    fuerza = masa * aceleracion;
    printf("%.2lf", fuerza);
}

void celcius_farenheit(void)
{
    double gradosCelsius, gradosFarhrenheit;
    printf("Grados Celsius:");
    scanf("%lf", &gradosCelsius);
    gradosFarhrenheit = (gradosCelsius * 9.0 / 5.0) + 32.0;
    printf("%.2lf", gradosFarhrenheit);
}