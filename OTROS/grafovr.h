#ifndef GRAFO_VR_H
#define GRAFO_VR_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    DIRIGIDO,
    NO_DIRIGIDO
} TTipoG;

typedef struct vertice_vr {
    char *nombre;
    struct nodo_rel *cab_rel;
} TVerticeVR;

typedef struct nodo_rel {
    char *nom_vertice;
    int peso;
    struct nodo_rel *sig;
} TNodoRel;

typedef struct grafo_vr {
    TTipoG tipo;
    size_t num_vertices;
    TVerticeVR *vector;
} TGrafoVR;

void inicializa_grafo(TGrafoVR *g, TTipoG tipo);
void libera_mem_grafo(TGrafoVR *g);
bool agrega_vertice(TGrafoVR *g, char *nom_vertice);
bool agrega_arista(TGrafoVR *g, char *nom_vi, char *nom_vf, int peso);
bool elimina_vertice(TGrafoVR *g, char *nom_vertice);
bool elimina_arista(TGrafoVR *g, char *nom_vi, char *nom_vf);
void imprime_grafo(TGrafoVR g);

#endif