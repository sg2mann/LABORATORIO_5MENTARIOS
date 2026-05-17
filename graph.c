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

void addNode(Graph* g, const char* label) {
    if (!g || !label) return;

}

void addEdge(Graph* g, const char* src, const char* dest, int weight) {
    if (!g || !src || !dest) return;

}

List* getEdges(Graph* g, const char* label) {
    if (!g || !label) return NULL;

    return NULL;
}

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

List* getAdjacentLabels(Graph* g, const char* label) {
    if (!g || !label) return NULL;
    return NULL; 
}

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