//
//  Graph.c
//  Assignment 3
//
//  Created by Karl Gemayel on 10/26/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#include "Graph.h"
#include <stdlib.h>

// adjacency list element
typedef struct ALElement {
    
    unsigned from;
    unsigned to;
    
    double weight; // weight of the edge connecting "from" and "to"
    
    struct ALElement *next;
    
} ALElement;


typedef struct Graph {
    
    size_t numNodes;
    
    ALElement** adjList;     // adjacency list
    
    ALElement* iter;        // used by iterator
    
} Graph;



/*
 * Read in a Graph Structure from Text Representation
 *
 * @param filename name of file containing graph to be read
 */
Graph *readGraph(char const *filename) {
    
    FILE *fp = fopen(filename, "r");
    
    float weight;
    size_t numberOfNodes;
    unsigned fromVertex, toVertex;
    
    fscanf(fp, "%zu", &numberOfNodes);
    //    printf("Number of nodes is %zu\n", numNodes);
    
    
    Graph *myGraph = makeGraph(numberOfNodes);
    
    // Associate with each vertex, a list of vertices it is connected to
    for (size_t k = 0; k < numberOfNodes; k++) {
        
        fscanf(fp, "%u:", &fromVertex);
        fscanf(fp, "%u:", &toVertex);
        fscanf(fp, "%f", &weight);
        
        addWtdEdge(myGraph, fromVertex, toVertex, weight);
        
    }
    
    return myGraph;
}





Graph* makeGraph(size_t numNodes) {
    Graph *g = (Graph*) malloc(sizeof(Graph));
    
    g->numNodes = numNodes;
    
    g->adjList = (ALElement **) malloc(sizeof(ALElement*) * numNodes);
    for (size_t i = 0; i < numNodes; i++) {
        g->adjList[i] = NULL;
    }
    
    g->iter = NULL;
    
    return g;
}

void freeGraph(Graph *g) {
    
    // free the graph, one step at a time
    for (size_t n = 0; n < g->numNodes; n++) {
        ALElement* p = g->adjList[n];
        
        while (p != NULL) {
            ALElement* temp = p;
            p = p->next;
            free(temp);
        }
            
        
    }
    
    free(g->adjList);
    free(g);
}

void addEdge(Graph *g, unsigned from, unsigned to) {
    
    ALElement* e = malloc(sizeof(ALElement));
    e->from = from;
    e->to = to;
    e->next = NULL;
    
    if (g->adjList[from] == NULL)
        g->adjList[from] = e;
    else {
        ALElement *p = g->adjList[from];
        
        // add to front of list
        e->next = p;
        g->adjList[from] = e;
    }
}





void addWtdEdge(Graph* g, unsigned from, unsigned to, float wt) {
    
    ALElement* e = malloc(sizeof(ALElement));
    e->from = from;
    e->to = to;
    e->next = NULL;
    e->weight = wt;
    
    if (g->adjList[from] == NULL)
        g->adjList[from] = e;
    else {
        ALElement *p = g->adjList[from];
        
        // add to front of list
        e->next = p;
        g->adjList[from] = e;
    }
    
}




/*
 * Print array of metadata
 */
void print_graph(Graph* myGraph) {
    
    size_t num_nodes = getNumNodes(myGraph);
    printf("Number of Nodes is: %zu\n", num_nodes);
    
    for (unsigned k = 0; k < num_nodes; k++) {
        
        for (unsigned vert = neigh_first(myGraph, k); !neigh_done(myGraph); vert = neigh_next(myGraph)) {
            
            double currWeight = getWeight(myGraph);
            printf("Edge from %u to %u with weight: %f\n", k, vert, currWeight);
            
        }
    }
    
}




// iterator methods
unsigned neigh_first (Graph *g, unsigned from) {
    
    if (from >= g->numNodes)
        return INT_FAST32_MAX;
    
    g->iter = NULL;                 // reset iterator
    
    if (g->adjList[from] == NULL)
        return INT_FAST32_MAX;
    
    g->iter = g->adjList[from];
    
    return g->iter->to;
    
}

unsigned neigh_next (Graph *g) {
    
    if (g->iter == NULL)
        return INT_FAST32_MAX;
    
    g->iter = g->iter->next;        // next element
    
    if (g->iter == NULL)
        return INT_FAST32_MAX;
    
    return g->iter->to;
    
}

int neigh_done (Graph *g) {
    return (g->iter == NULL);
}



size_t getNumNodes(Graph *g) {
    return g->numNodes;
}


double getWeight(Graph *g) {
    return g->iter->weight;
}



