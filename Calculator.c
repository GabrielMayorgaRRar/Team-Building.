#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.1416

void main_menu();
void Geometry_2D();
void Geometry_main_menu();
void Geometry_3D();
void Geometry_main_menu_2();
void factorial();
void Arithmetic();
void menu_ari();
long long int operation_facto(int x);

int main()
{
    bool bandera = false;
    int resultado;
    char option, decision;
    main_menu();
    do
    {
        if (bandera == true)
        {

            printf("¿Quieres hacer otra operación? \n(Y -> Yes) (N -> No)\n");
            scanf(" %c", &decision);
            if (decision == 'N')
            {
                option = 'I';
            }
            else if (decision == 'Y')
            {
                main_menu();
            }
        }
        bandera = true;
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
            Arithmetic();
            break;
        case 'E':

            break;
        case 'F':
            printf("\n\n");
            Geometry_2D();
            break;
        case 'G':
            printf("\n\n");
            Geometry_3D();
            break;
        case 'H':
            factorial();
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
    int A, B, C, D, result;
    Geometry_main_menu();
    printf("Opcion: ");
    scanf(" %c", &option);
    switch (option)
    {
    case 'A':
        printf("A continuacion introduzca los 4 lados del trapecio\n");
        printf("A = ");
        scanf("%d", &A);
        printf("B = ");
        scanf("%d", &B);
        printf("C = ");
        scanf("%d", &C);
        printf("D = ");
        scanf("%d", &D);
        result = A + B + C + D;
        printf("El perimetro del Rombo es: ' %d '\n\n", result);
        break;
    case 'B':
        printf("A continuacion introduzca un lado del Rombo\n");
        printf("Lado = ");
        scanf("%d", &A);
        result = A * 4;
        printf("El perimetro del Rombo es: ' %d '\n\n", result);
        break;
    case 'C':
        printf("A continuacion introduzca un lado del Hexágono\n");
        printf("Lado = ");
        scanf("%d", &A);
        result = A * 6;
        printf("El perimetro del Hexágono es: ' %d '\n\n", result);
        break;
    default:
        break;
    }
}

void Geometry_3D()
{
    char option;
    float A, B, C, D;
    float result2;
    Geometry_main_menu_2();
    printf("Opcion: ");
    scanf(" %c", &option);
    switch (option)
    {
    case 'A':
        printf("A continuacion introduzca el valor del radio de la Esfera:\n");
        printf("Radio = ");
        scanf("%f", &A);
        result2 = (A*A*A) * 3.1416 * (4.0/3.0);
        printf("El Volumen de la Esfera es: ' %f '\n\n", result2);
        break;
    case 'B':
        printf("A continuacion introduzca el valor del radio de la base\n y despues la altura del Cono:\n");
        printf("Radio = ");
        scanf("%f", &A);
        printf("Altura = ");
        scanf("%f", &B);
        result2 = (1.0 / 3.0) * 3.14159 * (A * A) * B;
        printf("El Volumen del Cono es: ' %0.3f '\n\n", result2);
        break;
    case 'C':
        printf("A continuacion introduzca el valor del la longitud de un lado de la base\n y despues la altura de la piramide:\n");
        printf("Longitud = ");
        scanf("%f", &A);
        printf("Altura = ");
        scanf("%f", &B);
        result2 = (1.0 / 3.0) * (A * A) * B;
        printf("El Volumen del piramide es: ' %0.3f '\n\n", result2);
        break;
    default:
        break;
    }
}

void Geometry_main_menu_2()
{
    printf("¿De que figura quiere calcular el Volumen?");
    printf("(Para escojer el tipo de problema, escriba la letra correspondiente)\n");
    printf("A - Esfera\n");
    printf("B - Cono\n");
    printf("C - Pirámide Cuadrada\n");
}

long long int operation_facto(int x){
  if (x==1)
    return 1;
  return x*operation_facto(x-1);
}

void factorial(){
    int Number;
    printf("Acontinuacion introduzca el numero del que quiere el factorial: ");
    scanf("%d", &Number);
    long long int result = operation_facto(Number);
    printf("El factorial de ' %d ' es ' %lld '\n", Number, result);
}

void Arithmetic(){
    menu_ari(); // Ahora menu_ari() está declarado antes de su uso
    char option;
    double numero, raiz, result;
    printf("Opcion: ");
    scanf(" %c", &option);
    switch (option)
    {
    case 'A':
        printf("Ingrese el numero: ");
        scanf("%lf", &numero);
        result = sqrt(numero);
        printf("La raiz cuadrada de %.2lf es %.2lf\n", numero, result);
        break;
    case 'B':
        
        printf("Ingrese el numero a elevar al cuadrado ");
        scanf("%lf", &numero);
        result = numero*numero;
        printf("La potencia cuadrada de %.2lf es %.2lf\n", numero, result);
        break;
    default:
        break;
    }
}

void menu_ari(){
    printf("¿Que operacion quiere hacer?");
    printf("(Para escojer el tipo de problema, escriba la letra correspondiente)\n");
    printf("A - Raíz cuadradada de un número\n");
    printf("B - Potencia cuadrada de un número.\n");
}