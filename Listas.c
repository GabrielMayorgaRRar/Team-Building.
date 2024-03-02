// Tiempo de Creacion: 1 hora y media.
// Creado por Gabriel Mayorga.
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int TDato;
typedef struct nod {
  TDato info;      // Cualquier tipo de info.
  struct nod *sig; // Apuntador al siguiente nodo.
} TNodo;

TNodo *crea_nodo(TDato dato);
void insercion_inicio(TDato dato, TNodo **cab);
void insercion_final(TDato dato, TNodo **cab);
void elimina_x(TNodo **cab, TDato dato);
void elimina_al_principio(TNodo **cab);
void eliminacion_al_final(TNodo **cab);
void vaciar_lista(TNodo **cab);
void impresion(TNodo *cab);

int main(void) {
  TNodo *A = NULL;
  int actions = 0, nAc = 0;
  TDato var;
  // apuntadores
  int *apuntador_actis = &actions;
  int *apuntador_nAc = &nAc;
  char Tipo_ac[50];
  char *apuntador_texto = (char *)malloc(sizeof(Tipo_ac) + 1);
  scanf("%d", apuntador_actis);
  do {
    scanf(" %[^\n]", apuntador_texto);
    if (strcmp(apuntador_texto, "push_front") == 0) {
      scanf("%d", &var);
      insercion_inicio(var, &A);

    } else if (strcmp(apuntador_texto, "pop_front") == 0) {
      elimina_al_principio(&A);

    } else if (strcmp(apuntador_texto, "push_back") == 0) {
      scanf("%d", &var);
      insercion_final(var, &A);

    } else if (strcmp(apuntador_texto, "pop_back") == 0) {
      eliminacion_al_final(&A);

    } else if (strcmp(apuntador_texto, "erase") == 0) {
      scanf("%d", &var);
      elimina_x(&A, var);

    } else if (strcmp(apuntador_texto, "clear") == 0) {
      vaciar_lista(&A);
    }
    (*apuntador_nAc)++;
  } while (*apuntador_nAc != *apuntador_actis);
  printf("\n");
  impresion(A);
  // Liberaciones de memoria
  return 0;
  free(apuntador_texto);
  free(apuntador_actis);
  free(apuntador_nAc);
  vaciar_lista(&A);
  free(A);
}

void insercion_inicio(TDato dato, TNodo **cab) {
  TNodo *aux;
  aux = crea_nodo(dato);
  if (aux) {
    aux->sig = *cab;
    *cab = aux;
  }
}

TNodo *crea_nodo(TDato dato) {
  TNodo *aux;
  aux = (TNodo *)malloc(sizeof(TNodo));
  if (aux == NULL) {
    printf("ERROR: NO SE PUDO ASIGNAR LA MEMORIA");
    exit(EXIT_FAILURE);
  } else if (aux) {
    aux->info = dato;
    aux->sig = NULL;
  }
  return aux;
}

void insercion_final(TDato dato, TNodo **cab) {
  TNodo *corre = *cab;
  if (*cab == NULL) {
    *cab = crea_nodo(dato);
  } else {
    insercion_final(dato, &((*cab)->sig));
  }
}

void elimina_x(TNodo **cab, TDato dato) {
  TNodo *aux = *cab, *ant;
  if (*cab) {
    if ((*cab)->info == dato) {
      *cab = aux->sig;
    } else {
      while (aux != NULL && aux->info != dato) {
        ant = aux;
        aux = aux->sig;
      }
      if (aux) {
        ant->sig = aux->sig;
        aux->sig = NULL;
      }
    }
  }
}

void impresion(TNodo *cab) {
    while (cab != NULL) {
        printf("%d ", cab->info);
        cab = cab->sig;
    }
}

void elimina_al_principio(TNodo **cab) {
  if (*cab != NULL) {
    return;
  }
  TNodo *tmp = *cab;
  *cab = (*cab)->sig;
  free(tmp);
}

void eliminacion_al_final(TNodo **cab) {
    TNodo *aux = *cab, *ant = NULL;

    if (*cab != NULL) {
        if ((*cab)->sig == NULL) {
            free(*cab);
            *cab = NULL;
        } else {
            while (aux->sig != NULL) {
                ant = aux;
                aux = aux->sig;
            }
            free(aux);
            if (ant != NULL) {
                ant->sig = NULL;
            } else {
                *cab = NULL; 
            }
        }
    }
}

void vaciar_lista(TNodo **cab) {
  TNodo *actual = *cab;
  TNodo *siguiente;

  while (actual != NULL) {
    siguiente = actual->sig;
    free(actual);
    actual = siguiente;
  }
  *cab = NULL;
}