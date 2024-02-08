#include <stdio.h>

void main_menu();
void Geometry_2D();
void Geometry_main_menu();

int main()
{
    int resultado;
    char option;
    do
    {
        main_menu();
        printf("Opcion: ");
        scanf(" %c", &option);
        switch (option)
        {
        case 'A':

            break;
        case 'B':

            break;
        case 'C':

            break;
        case 'D':

            break;
        case 'E':

            break;
        case 'F':
            printf("\n\n");
            Geometry_2D();
            break;
        case 'G':

            break;
        case 'H':

            break;
        default:
            break;
        }
    } while (option != 'I');
    return 0;
}

void main_menu()
{
    printf("--- Menu del programa de Formulas ---\n");
    printf("(Para escojer el tipo de problema, escriba la letra correspondiente)\n");
    printf("A - Fisica\n");
    printf("B - Computacional\n");
    printf("C - Matemática\n");
    printf("D - Aritmética\n");
    printf("E - Trigonometría\n");
    printf("F - Geometría 2D\n");
    printf("G - Geometría 3D\n");
    printf("H - Factorial\n");
    printf("Elija I para salir\n");
}

void Geometry_main_menu()
{
    printf("¿De que figura quiere calcular el Perimetro?");
    printf("(Para escojer el tipo de problema, escriba la letra correspondiente)\n");
    printf("A - Trapecio\n");
    printf("B - Rombo\n");
    printf("C - Hexagono\n");
}

void Geometry_2D()
{
    char option;
    int A, B, C, D;
    Geometry_main_menu();
    printf("Opcion: ");
    scanf(" %c", &option);
    switch (option)
    {
    case 'A':
        printf("A continuacion introduzca los 4 lados del trapecio\n");
        printf("A = ");
        scanf("%d", &A);
        printf("\nB = ");
        scanf("%d", &B);
        printf("\nC = ");
        scanf("%d", &C);
        printf("\nD = ");
        scanf("%d", &D);
        int result = A + B + C + D;
        printf("El perimetro del Rombo es: ' %d '\n\n", result);
        break;
    case 'B':
        printf("A continuacion introduzca un lado del Rombo\n");
        printf("Lado = ");
        scanf("%d", &A);
        int result = A * 4;
        printf("El perimetro del Rombo es: ' %d '\n\n", result);
        break;
    case 'C':
        printf("A continuacion introduzca un lado del Hexágono\n");
        printf("Lado = ");
        scanf("%d", &A);
        int result = A * 6;
        printf("El perimetro del Hexágono es: ' %d '\n\n", result);
        break;
    default:
        break;
    }
}