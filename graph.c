#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"
#include "map.h"

/* =========================================
 *         ESTRUCTURAS INTERNAS
 * ========================================= */

struct Graph {
    Map* adjacencyMap; 
};

int is_equal_string(void *key1, void *key2) {
    return strcmp((char*)key1, (char*)key2) == 0;
}

/* =========================================
 *         IMPLEMENTACIÓN
 * ========================================= */

// CREAR GRAFO
Graph* createGraph() 
{
    Graph * g = (Graph *) malloc(sizeof(Graph));

    if (g == NULL)
    {
        return NULL;
    }

    g->adjacencyMap = map_create(is_equal_string);
    return g;
}

// AGREGRAR NODOS
void addNode(Graph* g, const char* label) 
{
    if (!g || !label) return;

    if (map_search(g->adjacencyMap, (void*)label) != NULL)
    {
        return;
    }

    char* labelCopia = (char *) malloc(strlen(label) + 1);
    if (labelCopia == NULL)
    {
        return;
    }

    strcpy(labelCopia, label);

    List * nueva = list_create();
    map_insert(g->adjacencyMap, labelCopia, nueva);
}

// AGREGAR ARCOS
void addEdge(Graph* g, const char* src, const char* dest, int weight) 
{
    if (!g || !src || !dest) return;

    MapPair * par = map_search(g->adjacencyMap, (void*)src);

    if (par == NULL)
    {
        return;
    }

    Edge * nuevoArco = (Edge *) malloc(sizeof(Edge));
    if (nuevoArco == NULL)
    {
        return;
    }

    nuevoArco->weight = weight;
    nuevoArco->target = (char *) malloc(strlen(dest) + 1);
    if (nuevoArco->target == NULL)
    {
        free(nuevoArco);
        return;
    }

    strcpy(nuevoArco->target, dest);

    List* listaArcos = (List *) par->value;
    list_pushBack(listaArcos, nuevoArco);
}

// OBTENER ARCOS
List* getEdges(Graph* g, const char* label) 
{
    if (!g || !label) return NULL;

    MapPair * par = map_search(g->adjacencyMap, (void *) label);

    if (par == NULL)
    {
        return NULL;
    }
    
    return (List *) par->value;
}

// OBTENER PESO DE UN ARCO
int getWeight(Graph* g, const char* label1, const char* label2) 
{
    if (!g || !label1 || !label2) return -1;

    MapPair * par = map_search(g->adjacencyMap, (void *)label1);

    if (par == NULL) 
    {
        return -1;
    }
    
    Edge * aux = list_first(par->value);
    
    while (aux != NULL) 
    {
        if (strcmp(aux->target, label2) == 0) 
        {
            return aux->weight;
        }
        aux = (Edge *) list_next(par->value); 
    }
    return -1;
}

// OBTENER ETIQUETA DE LOS NODOS ADYACENTES
List* getAdjacentLabels(Graph* g, const char* label) 
{
    if (!g || !label) return NULL;

    List * arcos = getEdges(g, label);
    if (arcos == NULL)
    {
        return NULL;
    }

    List * nodosAdy = list_create();
    Edge * arcoActual = (Edge *) list_first(arcos);

    while (arcoActual != NULL)
    {
        list_pushBack(nodosAdy, arcoActual->target);
        arcoActual = (Edge *) list_next(arcos);
    }

    return nodosAdy;
}

// ELIMINAR EL GRAFO
void destroyGraph(Graph* g) 
{
    if (!g) return;

    MapPair* pair = map_first(g->adjacencyMap);
    while (pair != NULL) 
    {
        char* label = (char*)pair->key;
        List* edgesList = (List*)pair->value;

        Edge* e = (Edge*)list_first(edgesList);
        while (e != NULL) 
        {
            free(e->target);
            free(e);
            e = (Edge*)list_next(edgesList);
        }
        
        list_clean(edgesList);
        free(edgesList);

        free(label);

        pair = map_next(g->adjacencyMap);
    }
    map_clean(g->adjacencyMap);
    free(g->adjacencyMap);
    free(g);
}