#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "grafovr.h"

void inicializa_grafo(TGrafoVR *g, TTipoG tipo)
{
    g->tipo = tipo;
    g->num_vertices = 0;
    g->vector = NULL;
}

void libera_mem_grafo(TGrafoVR *g)
{
    for (size_t i = 0; i < g->num_vertices; i++)
    {
        TNodoRel *iterador = (g->vector + i)->cab_rel;
        while (iterador != NULL)
        {
            TNodoRel *temporal = iterador;
            iterador = iterador->sig;
            free(temporal->nom_vertice);
            free(temporal);
        }
        free((g->vector + i)->nombre);
    }
    free(g->vector);
}

bool agrega_vertice(TGrafoVR *g, char *nom_vertice)
{
    if (!existe_vertice(g, nom_vertice))
    {
        g->num_vertices++;
        g->vector = (TVerticeVR *)realloc(g->vector, sizeof(TVerticeVR) * g->num_vertices);
        assert(g->vector != NULL);
        VERTICE(g)->nombre = (char *)malloc(sizeof(char) * (strlen(nom_vertice) + 1));
        assert(VERTICE(g)->nombre != NULL);
        strcpy(VERTICE(g)->nombre, nom_vertice);
        VERTICE(g)->cab_rel = NULL;
    }

    return true;
}

bool agrega_arista(TGrafoVR *g, char *nom_vi, char *nom_vf, int peso)
{
    agrega_vertice(g, nom_vi);
    agrega_vertice(g, nom_vi);

    for (size_t i = 0; i < g->num_vertices; i++)
    {
        if (!strcmp((g->vector + i)->nombre, nom_vi))
        {
            TNodoRel *nuevoNodo = crea_nodo(nom_vf, peso);
            if ((g->vector + i)->cab_rel == NULL)
            {
                (g->vector + i)->cab_rel = nuevoNodo;
                break;
            }
            TNodoRel *iterador = (g->vector + i)->cab_rel;
            while (iterador->sig != NULL)
            {
                iterador = iterador->sig;
            }
            iterador->sig = nuevoNodo;
        }
    }

    return true;
}

bool elimina_vertice(TGrafoVR *g, char *nom_vertice)
{
    if (!existe_vertice(g, nom_vertice))
    {
        return false;
    }

    for (size_t i = 0; i < g->num_vertices; i++)
    {
        if (strcmp((g->vector + i)->nombre, nom_vertice))
        {
            elimina_arista(g, (g->vector + i)->nombre, nom_vertice);
        }
        else
        {
            g->num_vertices--;
            TNodoRel *iterador = (g->vector + i)->cab_rel;
            while (iterador != NULL)
            {
                TNodoRel *temporal = iterador;
                iterador = iterador->sig;
                free(temporal->nom_vertice);
                free(temporal);
            }
            for (size_t j = i; j < g->num_vertices; j++)
            {
                *(g->vector + j) = *(g->vector + j + 1);
            }
            free((g->vector + i)->nombre);
            g->vector = (TVerticeVR *)realloc(g->vector, sizeof(TVerticeVR) * g->num_vertices);
        }
    }

    return true;
}

bool elimina_arista(TGrafoVR *g, char *nom_vi, char *nom_vf)
{
    for (size_t i = 0; i < g->num_vertices; i++)
    {
        if (!strcmp((g->vector + i)->nombre, nom_vi))
        {
            if ((g->vector + i)->cab_rel == NULL)
            {
                continue;
            }
            if (!strcmp((g->vector + i)->cab_rel->nom_vertice, nom_vf))
            {
                TNodoRel *temporal = (g->vector + i)->cab_rel;
                (g->vector + i)->cab_rel = (g->vector + i)->cab_rel->sig;
                free(temporal->nom_vertice);
                free(temporal);
            }
            else
            {
                TNodoRel *iterador = (g->vector + i)->cab_rel;
                while (iterador->sig != NULL && strcmp(iterador->nom_vertice, nom_vf))
                {
                    iterador = iterador->sig;
                }
                if (iterador->sig != NULL)
                {
                    TNodoRel *temporal = iterador->sig;
                    iterador->sig = iterador->sig->sig;
                    free(temporal->nom_vertice);
                    free(temporal);
                    return true;
                }
            }
        }
    }

    return false;
}

void imprime_grafo(TGrafoVR g)
{
    for (size_t i = 0; i < g.num_vertices; i++)
    {
        TNodoRel *iterador = (g.vector + i)->cab_rel;
        if (iterador == NULL)
        {
            printf("%s: NULL\n", (g.vector + i)->nombre);
        }
        else
        {
            printf("%s: ", (g.vector + i)->nombre);
            while (iterador != NULL)
            {
                printf("%s ", iterador->nom_vertice);
                iterador = iterador->sig;
            }
            printf("\n");
        }
    }
}

TNodoRel *crea_nodo(const char *nom_vf, int peso)
{
    TNodoRel *nuevoNodo = (TNodoRel *)malloc(sizeof(TNodoRel));
    assert(nuevoNodo != NULL);
    nuevoNodo->nom_vertice = (char *)malloc(sizeof(char) * (strlen(nom_vf) + 1)),
    assert(nuevoNodo->nom_vertice != NULL);
    strcpy(nuevoNodo->nom_vertice, nom_vf);
    nuevoNodo->peso = peso;
    nuevoNodo->sig = NULL;

    return nuevoNodo;
}

bool existe_vertice(TGrafoVR *g, const char *nom_vertice)
{
    for (size_t i = 0; i < g->num_vertices; i++)
    {
        if (!strcmp((g->vector + i)->nombre, nom_vertice))
        {
            return true;
        }
    }

    return false;
}