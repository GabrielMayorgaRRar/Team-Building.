#include <stdio.h>
#include <math.h>

#define MAXLINE 30

void menu();
void decimal_binario();
void punto_fijo(int *numero, int potencia);
void hexadecimal_decimal();
void octal_binario();

int main()
{
    int opcion;
    menu();
    scanf("%d", &opcion);
    fflush(stdin);
    switch (opcion)
    {
    case 1:
        decimal_binario();
        break;
    case 2:
        hexadecimal_decimal();
        break;
    case 3:
        octal_binario();
        break;
    default:
        puts("Opcion invalida");
        break;
    }

    return 0;
}

void menu()
{
    puts("Selecciona el tipo de conversion a realizar:");
    puts("\t1. Decimal a binario:");
    puts("\t2. Hexadecimal a decimal:");
    puts("\t3. Octal a binario:");
}

void decimal_binario()
{
    int numero;
    char resultado[MAXLINE];

    printf("Ingresa el numero a convertir: ");
    scanf("%d", &numero);

    punto_fijo(&numero, 1);
}

void punto_fijo(int *numero, int potencia)
{
    if (potencia > *numero)
    {
        return;
    }
    punto_fijo(numero, potencia * 2);
    if (*numero >= potencia)
    {
        *numero -= potencia;
        printf("1");
    }
    else
    {
        printf("0");
    }
}

void hexadecimal_decimal()
{
    int hexadecimal;
    printf("Ingresa el numero a convertir:");
    scanf("%x", &hexadecimal);
    printf("%d", hexadecimal);
}

void octal_binario()
{
    int octal, binario;
    printf("Ingresa el numero octal:");
    scanf("%o", &octal);
    while (octal > 0)
    {
        /* code */
    }
    
}