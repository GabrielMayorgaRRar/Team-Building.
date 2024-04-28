#include <ctype.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo
{
  char Info[10000];
  struct nodo *Next;
} TNodo;

typedef struct
{
  char Left[10000];
  char Right[10000];
} TPrcc;

typedef struct nodD
{
  char Magic_t;
  TNodo *Info;
  struct nodD *Next;
  struct nodD *After;
} TNodoMagic;

typedef struct
{
  char Magic_t;
  char Info[100];
} TGramaticc;

typedef struct
{
  char *Magic_t;
  char *noMagic_t;
  int n_Magic_T;
  int no_Magic_T;
} TMagic;

TNodoMagic *crea_nodoD(char Magic_t);

TNodo *crea_nodo(char cad[]);

int leer_gramatica(char *nom_arch, TPrcc *produc);

void crear_magic_prod(TPrcc **arr, int n);

void llenar_arreglo(TPrcc *arr, int n, char *nom_arch);

void magic_no_magic(TPrcc *arr, TMagic *gram, int n);

void Proceso_1(TPrcc *arr, TNodoMagic **cbs, int n);

void Proceso_2(TNodoMagic **cbs, TGramaticc **cab);

void Proceso_3(TNodoMagic **cbs, TGramaticc **cab);

void Proceso_4(char rest[]);

void imprimir_Gramatic_Magic(TPrcc *arr, int n);

void rellenar_magi(TNodoMagic **cbs, TGramaticc **cab, int *i);

void producciones_unidas(TNodoMagic *cab);

void imprimir_Gramatic_Magic_Magic_t_no_Magic_t(TMagic *gram);

void agregar_magic_e_imprimir(char rest[]);

int main()
{
  int tam, tam2;
  TPrcc *arr;
  TMagic gram;
  TGramaticc *cab2 = NULL;
  TNodoMagic *cab = NULL;
  char nom_arch[50], rest[100];

  strcpy(nom_arch, "gramatica.txt");
  tam = leer_gramatica(nom_arch, arr);

  if (tam != 0)
  {
    crear_magic_prod(&arr, tam);
    if (arr != NULL)
    {
      llenar_arreglo(arr, tam, nom_arch);
      printf("Producciones de la gramática:\n");
      imprimir_Gramatic_Magic(arr, tam);
      magic_no_magic(arr, &gram, tam);

      printf("\nInformación sobre Terminales y no Terminales:\n");
      imprimir_Gramatic_Magic_Magic_t_no_Magic_t(&gram);
      printf("\n");

      printf("\nPaso 1 -- Juntar producciones:\n");
      Proceso_1(arr, &cab, tam);
      printf("Producciones combinadas:\n");
      producciones_unidas(cab);
      printf("\n");

      printf("\nPaso 2 -- Reducciones:\n");
      rellenar_magi(&cab, &cab2, &tam2);
      printf("Producciones reducidas:\n");
      Proceso_2(&cab, &cab2);
      printf("\n");

      printf("\nPaso 3 -- Sustituciones:\n");
      printf("Producciones sustituidas:\n");
      Proceso_3(&cab, &cab2);
      printf("\n");

      printf("\nPaso 4 -- Expresión regular:\n");
      printf("Expresión regular resultante:\n");
      strcpy(rest, cab2->Info);
      agregar_magic_e_imprimir(rest);

      free(arr);
    }
  }
}

int leer_gramatica(char *nom_arch, TPrcc *produc)
{
  FILE *arch;
  char *aux;
  arch = fopen(nom_arch, "r");
  if (arch == NULL)
  {
    printf("ERROR: ARCHIVO NO ENCONTRADO\n");
    return 0;
  }
  aux = (char *)malloc(sizeof(char) * 500);
  if (aux == NULL)
  {
    printf("ERROR: AL ASIGNAR MEMORIA\n");
    fclose(arch);
    return 0;
  }

  int i = 0;
  while (fgets(aux, 500, arch) != NULL)
  {
    if (*aux != '\n' && *aux != ' ')
    {
      i++;
    }
  }
  free(aux);
  fclose(arch);
  return i;
}

void crear_magic_prod(TPrcc **arr, int n)
{
  *arr = (TPrcc *)malloc(n * sizeof(TPrcc));
  if (*arr == NULL)
  {
    printf("ERROR: ERROR AL ASIGNAR MEMORIA\n");
  }
}

void llenar_arreglo(TPrcc *arr, int n, char *nom_arch)
{
  FILE *arch;
  char *aux = (char *)malloc(sizeof(char) * 100);
  int i = 0;
  if (aux != NULL)
  {
    arch = fopen(nom_arch, "r");
    if (arch != NULL)
    {
      while (fgets(aux, 100, arch) != NULL)
      {
        if (*aux != '\n' && *aux != ' ')
        {
          strcpy((arr + i)->Left, strtok(aux, "- >"));
          strcpy((arr + i)->Right, strtok(NULL, "- > \n"));
          i++;
        }
      }
      fclose(arch);
      free(aux);
    }
    else
    {
      printf("ERROR: ARCHIVO NO ENCONTRADO\n");
    }
  }
}

void imprimir_Gramatic_Magic(TPrcc *arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%-3s->   %-3s\n", (arr + i)->Left, (arr + i)->Right);
  }
  printf("\n");
}

void magic_no_magic(TPrcc *arr, TMagic *gram, int n)
{
  int i, j;
  gram->Magic_t = (char *)malloc(sizeof(char));
  gram->noMagic_t = (char *)malloc(sizeof(char));
  gram->n_Magic_T = 0;
  gram->no_Magic_T = 0;
  for (i = 0; i < n; i++)
  {
    if (strchr(gram->noMagic_t, (arr + i)->Left[0]) == NULL)
    {
      gram->noMagic_t = (char *)realloc(gram->noMagic_t,
                                        (gram->no_Magic_T + 2) * sizeof(char));
      gram->noMagic_t[gram->no_Magic_T++] = (arr + i)->Left[0];
    }
    for (j = 0; j < strlen(arr[i].Right); j++)
    {
      if (!isspace((arr + i)->Right[j]))
      {
        if (!isupper((arr + i)->Right[j]))
        {
          if (strchr(gram->Magic_t, (arr + i)->Right[j]) == NULL)
          {
            gram->Magic_t = (char *)realloc(
                gram->Magic_t, (gram->n_Magic_T + 2) * sizeof(char));
            gram->Magic_t[gram->n_Magic_T++] = (arr + i)->Right[j];
          }
        }
        else
        {
          if (strchr(gram->noMagic_t, (arr + i)->Right[j]) == NULL)
          {
            gram->noMagic_t = (char *)realloc(
                gram->noMagic_t, (gram->no_Magic_T + 2) * sizeof(char));
            gram->noMagic_t[gram->no_Magic_T++] = (arr + i)->Right[j];
          }
          else
          {
            if (strchr(gram->noMagic_t, (arr + i)->Right[j]) == NULL)
            {
              gram->noMagic_t = (char *)realloc(
                  gram->noMagic_t, (gram->no_Magic_T + 2) * sizeof(char));
              gram->noMagic_t[gram->no_Magic_T++] = (arr + i)->Right[j];
            }
          }
        }
      }
    }
    gram->Magic_t =
        (char *)realloc(gram->Magic_t, (gram->n_Magic_T + 1) * sizeof(char));
    gram->noMagic_t =
        (char *)realloc(gram->noMagic_t, (gram->no_Magic_T + 1) * sizeof(char));
    gram->Magic_t[gram->n_Magic_T] = '\0';
    gram->noMagic_t[gram->no_Magic_T] = '\0';
  }
}

void imprimir_Gramatic_Magic_Magic_t_no_Magic_t(TMagic *gram)
{
  printf("Terminales: \n");
  for (int i = 0; i < gram->n_Magic_T; i++)
  {
    printf("%c ", gram->Magic_t[i]);
  }
  printf("\n\n");
  printf("No Terminales: \n");
  for (int i = 0; i < gram->no_Magic_T; i++)
  {
    printf("%c ", gram->noMagic_t[i]);
  }
  printf("\n");
}

TNodoMagic *crea_nodoD(char Magic_t)
{
  TNodoMagic *auxD;
  auxD = (TNodoMagic *)malloc(sizeof(TNodoMagic));
  if (auxD != NULL)
  {
    auxD->Magic_t = Magic_t;
    auxD->Next = NULL;
    auxD->After = NULL;
    auxD->Info = NULL;
  }
  return auxD;
}

TNodo *crea_nodo(char cad[])
{
  TNodo *aux;
  aux = (TNodo *)malloc(sizeof(TNodo));
  if (aux != NULL)
  {
    strcpy(aux->Info, cad);
    aux->Next = NULL;
  }
  return aux;
}

void rellenar_magi(TNodoMagic **cbs, TGramaticc **cab, int *i)
{
  bool ban2 = false;
  int cont = 0;
  TNodo *aux;
  TNodoMagic *auxD, *auxD2;
  TGramaticc *auxDG;
  char temp[10];
  for (auxD = *cbs; auxD != NULL; auxD = auxD->Next)
  {
    cont++;
  }
  *cab = (TGramaticc *)malloc(cont * sizeof(TGramaticc) * cont);
  cont = 0;
  for (auxD = *cbs; auxD != NULL; auxD = auxD->Next)
  {
    ban2 = false;
    auxDG = (*cab + cont);
    auxDG->Magic_t = auxD->Magic_t;
    for (aux = auxD->Info; aux != NULL; aux = aux->Next)
    {
      if (ban2)
      {
        strcat(auxDG->Info, "|");
        ban2 = false;
      }
      strcpy(temp, aux->Info);
      strcat(auxDG->Info, temp);
      ban2 = true;
    }
    cont++;
  }
  *i = cont;
}

void agregar_magic_e_imprimir(char rest[])
{
  int log, comp = 0;
  int comp_p = 1, aux;
  int comp_c = 0;
  int cont, cont2 = 0;
  log = strlen(rest);
  int i, y, j = 0;
  char result[10000];
  char aux2[10000];
  for (i = 0; i < log; i++)
  {
    result[j] = rest[i];
    if (rest[i] == '|')
    {
      comp = i;
      j++;
      result[j] = '\'';
    }
    j++;
  }
  result[j] = '\0';
  rest = result;
  cont = j;
  j = 0;
  for (i = 0; i < log; i++)
  {
    result[j] = rest[i];
    if (rest[i] == '|')
    {
      cont += 1;
      comp = i;
      y = comp;
      while (y != 0 && comp_c != 1)
      {
        if (rest[y] == ')')
        {
          comp_p += 1;
        }
        if (rest[y] == '(' && comp_p != 0)
        {
          comp_p -= 1;
        }
        if (rest[y] == '(' && comp_p == 0 && comp_c != 1)
        {
          strcpy(aux2, result);
          for (aux = y + 1; aux < comp - 1; aux++)
          {
            result[aux + 1] = aux2[aux];
          }
          result[y + 1] = '\'';
          comp_c = 1;
        }
        y -= 1;
      }
    }
    j++;
  }
  result[cont + cont2] = '\0';
  rest = result;
  Proceso_4(rest);
}

void producciones_unidas(TNodoMagic *cab)
{
  TNodoMagic *auxD;
  TNodo *aux;
  for (auxD = cab; auxD != NULL; auxD = auxD->Next)
  {
    printf("%c: ", auxD->Magic_t);
    for (aux = auxD->Info; aux->Next != NULL; aux = aux->Next)
    {
      printf("%s | ", aux->Info);
    }
    printf("%s\n", aux->Info);
  }
}
void Proceso_1(TPrcc *arr, TNodoMagic **cbs, int n)
{
  TNodoMagic *auxD, *cmpD;
  TNodo *aux;
  for (int i = 0; i < n; i++)
  {
    cmpD = NULL;
    for (auxD = *cbs; auxD != NULL; auxD = auxD->Next)
    {
      if (auxD->Magic_t == (arr + i)->Left[0])
      {
        cmpD = auxD;
        break;
      }
    }
    if (cmpD == NULL)
    {
      cmpD = crea_nodoD((arr + i)->Left[0]);
      if (*cbs == NULL)
      {
        *cbs = cmpD;
      }
      else
      {
        TNodoMagic *lastD = *cbs;
        while (lastD->Next != NULL)
        {
          lastD = lastD->Next;
        }
        lastD->Next = cmpD;
        cmpD->After = lastD;
      }
    }
    aux = crea_nodo((arr + i)->Right);
    if (cmpD->Info == NULL)
    {
      cmpD->Info = aux;
    }
    else
    {
      TNodo *last = cmpD->Info;
      while (last->Next != NULL)
      {
        last = last->Next;
      }
      last->Next = aux;
    }
  }
}

void Proceso_2(TNodoMagic **cbs, TGramaticc **cab)
{
  bool ban = false, ban2;
  int cont = 0, cont2 = 0, pos;
  TNodo *aux;
  TNodoMagic *auxD, *auxD2;
  TGramaticc *auxDG;
  char *aux2, *temp2;
  char xi, ai[10000], wi[10000], temp[10000], parte1[10000], parte2[10000], auxd[10000];
  ai[0] = '\0';
  wi[0] = '\0';
  for (auxD = *cbs; auxD->Next != NULL; auxD = auxD->Next)
  {
    ban2 = false;
    printf("\ni = %d", cont + 1);
    xi = auxD->Magic_t;
    auxDG = (*cab + cont);
    printf("   %c = %s\n", auxDG->Magic_t, auxDG->Info);
    strcpy(auxd, auxDG->Info);
    temp2 = strtok(auxd, "({|}})");
    while (temp2 != NULL)
    {
      aux2 = strchr(temp2, xi);
      if (aux2 != NULL)
      {
        if (ban2)
        {
          strcat(ai, " | ");
          ban2 = false;
        }
        pos = aux2 - temp2;
        strncat(ai, temp2, pos);
        ban = true;
        ban2 = true;
      }
      temp2 = strtok(NULL, "({|}})");
    }
    ban2 = false;
    strcpy(auxd, auxDG->Info);
    if (ban == true && ai[0] != '\0')
    {
      temp2 = strtok(auxd, "({|}})");
      while (temp2 != NULL)
      {
        aux2 = strchr(temp2, xi);
        if (aux2 == NULL)
        {
          if (ban2)
          {
            strcat(wi, "|");
            ban2 = false;
          }
          strcat(wi, temp2);
          ban = true;
          ban2 = true;
        }
        temp2 = strtok(NULL, "({|}})");
      }
    }
    if (ai[0] != '\0' && wi[0] != '\0')
    {
      strcpy(auxDG->Info, "{");
      strcat(auxDG->Info, ai);
      strcat(auxDG->Info, "}");
      strcat(auxDG->Info, "(");
      strcat(auxDG->Info, wi);
      strcat(auxDG->Info, ")");
    }
    printf("x: %c | a: %s | w: (%s)\n", xi, ai, wi);
    printf("\n");
    if (ai[0] == '\0')
    {
      printf("No reduce: %c = %s\n", auxDG->Magic_t, auxDG->Info);
      printf("\n");
    }
    else
    {
      printf("Reduce: %c = %s\n", auxDG->Magic_t, auxDG->Info);
      printf("\n");
    }
    cont2 = cont;
    for (auxD2 = auxD->Next; auxD2 != NULL; auxD2 = auxD2->Next)
    {
      cont2 = cont2 + 1;
      aux2 = strchr((*cab + cont2)->Info, xi);
      if (aux2 == NULL)
      {
        printf("No sustituye en %c\n", auxD2->Magic_t);
        printf("\n");
      }
      else
      {
        printf("Sustituye en %c\n", auxD2->Magic_t);
        printf("\n");
        pos = aux2 - (*cab + cont2)->Info;
        strncpy(parte1, (*cab + cont2)->Info, pos);
        parte1[pos] = '\0';
        strcpy(parte2, (*cab + cont2)->Info + pos + 1);
        sprintf((*cab + cont2)->Info, "%s%s%s", parte1, auxDG->Info, parte2);
        printf("%c: %s\n", auxD2->Magic_t, (*cab + cont2)->Info);
        printf("\n");
      }
    }
    ai[0] = '\0';
    wi[0] = '\0';
    cont++;
  }
}

void Proceso_3(TNodoMagic **cbs, TGramaticc **cab)
{
  bool ban = false, ban2;
  int cont = 0, cont2 = 0, pos;
  TNodo *aux;
  TNodoMagic *auxD, *auxD2, *auxD3;
  TGramaticc *auxDG;
  char *aux2, *temp2;
  char xi, ai[10000], wi[10000], temp[10000], parte1[10000], parte2[10000], auxd[10000];
  ai[0] = '\0';
  wi[0] = '\0';
  for (auxD = *cbs; auxD->Next != NULL; auxD = auxD->Next)
  {
    cont++;
  }
  auxD3 = *cbs;
  for (; auxD->After != auxD3->After; auxD = auxD->After)
  {
    ban2 = false;
    printf("\ni = %d", cont + 1);
    xi = auxD->Magic_t;
    auxDG = (*cab + cont);
    printf("   %c = %s\n", auxDG->Magic_t, auxDG->Info);
    strcpy(auxd, auxDG->Info);
    temp2 = strtok(auxd, "({|}})");
    while (temp2 != NULL)
    {
      aux2 = strchr(temp2, xi);
      if (aux2 != NULL)
      {
        if (ban2)
        {
          strcat(ai, " | ");
          ban2 = false;
        }
        pos = aux2 - temp2;
        strncat(ai, temp2, pos);
        ban = true;
        ban2 = true;
      }
      temp2 = strtok(NULL, "({|}})");
    }
    ban2 = false;
    strcpy(auxd, auxDG->Info);
    if (ban == true && ai[0] != '\0')
    {
      temp2 = strtok(auxd, "({|}})");
      while (temp2 != NULL)
      {
        aux2 = strchr(temp2, xi);
        if (aux2 == NULL)
        {
          if (ban2)
          {
            strcat(wi, "|");
            ban2 = false;
          }
          strcat(wi, temp2);
          ban = true;
          ban2 = true;
        }
        temp2 = strtok(NULL, "({|}})");
      }
    }
    if (ai[0] != '\0' && wi[0] != '\0')
    {
      strcpy(auxDG->Info, "{");
      strcat(auxDG->Info, ai);
      strcat(auxDG->Info, "}");
      strcat(auxDG->Info, "(");
      strcat(auxDG->Info, wi);
      strcat(auxDG->Info, ")");
    }
    printf("x: %c | a: %s | w: (%s)\n", xi, ai, wi);
    if (ai[0] == '\0')
    {
      printf("No reduce: %c = %s\n", auxDG->Magic_t, auxDG->Info);
    }
    else
    {
      printf("Reduce: %c = %s\n", auxDG->Magic_t, auxDG->Info);
    }
    cont2 = cont;
    for (auxD2 = auxD; auxD2->After != auxD3->After; auxD2 = auxD2->After)
    {
      cont2 = cont2 - 1;
      aux2 = strchr((*cab + cont2)->Info, xi);
      if (aux2 == NULL)
      {
        printf("No sustituye en %c\n", (*cab + cont2)->Magic_t);
      }
      else
      {
        printf("Sustituye en %c\n", (*cab + cont2)->Magic_t);
        pos = aux2 - (*cab + cont2)->Info;
        strncpy(parte1, (*cab + cont2)->Info, pos);
        parte1[pos] = '\0';
        strcpy(parte2, (*cab + cont2)->Info + pos + 1);
        sprintf((*cab + cont2)->Info, "%s(%s)%s", parte1, auxDG->Info, parte2);
        printf("%c: %s\n", (*cab + cont2)->Magic_t, (*cab + cont2)->Info);
      }
    }
    ai[0] = '\0';
    wi[0] = '\0';
    cont--;
  }
}

void Proceso_4(char rest[])
{
  int log, log2, comp = 0;
  int i, j = 0;
  char result[10000];
  char auxc;
  log = strlen(rest);
  for (i = 0; i < log; i++)
  {
    if (rest[i] == '(' || rest[i] == ')')
    {
    }
    else if (rest[i] == '{')
    {
      rest[j++] = '(';
    }
    else if (rest[i] == '}')
    {
      rest[j++] = ')';
      rest[j++] = '*';
      i += 1;
    }
    else
    {
      rest[j++] = rest[i];
    }
  }
  rest[j] = '\0';
  log2 = strlen(rest);
  j = 0;
  for (i = 0; i < log2; i++)
  {
    auxc = rest[i];
    if (rest[i + 1] == '(' && rest[i + 2] == auxc)
    {
      i += 1;
      comp = 1;
    }
    result[j] = rest[i];
    if (comp == 1)
    {
      if (rest[i] == '*')
      {
        result[j] = '+';
        comp = 0;
      }
    }
    j += 1;
  }
  result[j] = '\0';
  printf("\n");
  printf("ER: %s\n", result);
}