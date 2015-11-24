//
//  main.c
//  Assignment 3
//
//  Created by Karl Gemayel on 10/26/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Common.h"
#include "FIFOQueue.h"

/*
 * Get the size of the largest component of a graph.
 * 
 * @param g the graph
 * @return the largest component of the graph; 0 if g is NULL
 */
size_t getSizeOfLargestComponent(Graph *g);

/*
 * Read a graph from a file.
 *
 * @param filename name of the file.
 * @return a graph pointer; NULL if filename is invalid.
 */
Graph* readGraph(const char* filename);

// print usage information
void usage(const char* progName) {
    printf("Usage: %s FILENAME\n", progName);
    printf("\tFILENAME: name of file containing graph.\n");
}

#define VERBOSE

int main(int argc, const char * argv[]) {
    
    if (argc != 2) {
        usage(argv[0]);
        return 0;
    }
    
    // read the graph
    Graph* g = readGraph(argv[1]);
    
    
    // get max component size and print it out
    size_t maxSize = getSizeOfLargestComponent(g);
    printf("%zu\n", maxSize);
    
    // free graph
    freeGraph(g);
    
    return 0;
}



Graph* readGraph(const char* filename) {
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return NULL;            // file doesn't exist
    
    unsigned numNodes = 0;
    
    fscanf(fp, "%u", &numNodes);        // read number of nodes
    
    Graph* g = makeGraph(numNodes);     // create graph
    
    unsigned u, v;
    
    // while not end-of-file
    while (fscanf(fp, "%u %u", &u, &v) != EOF) {

        // add edge to graph (both directions)
        addEdge(g, u, v);
        addEdge(g, v, u);
    }
    
    fclose(fp);
    
    return g;
}


// define colors to use with BFS
typedef enum COLOR {WHITE, GREY, BLACK} COLOR;


size_t getSizeOfLargestComponent(Graph *g) {
    
    if (g == NULL)
        return 0;
    
    // get the number of nodes in the graph
    size_t numNodes = getNumNodes(g);
    if (numNodes == 0)
        return 0;
    
    // create an array of flags, one for each node. If:
    //    - flag[i] == WHITE: node i has not be visited or inspected
    //    - flag[i] == GREY : node i has been visited, but it's neighbors not yet inspected
    //    - flag[i] == BLACK: node i has been visited, and all its neighbors have been added to the queue
    COLOR* flags = malloc(sizeof(COLOR) * numNodes);
    if (flags == NULL)
        FatalError("getSizeOfLargestComponent", "Could not allocate 'flags' array.");
    
    // set all flags to white
    for (size_t n = 0; n < numNodes; n++)
        flags[n] = WHITE;
    
    
    size_t maxComp = 0;
    size_t remainingNodes = numNodes;       // number of nodes remaining (untagged)
    
    unsigned prevStartingPoint = 0;
    
    while (remainingNodes > 0) {
    
        size_t compSize = 0;            // current component size
        
        // create an empty FIFO queue
        FIFOQueue* queue = fifo_create();
        
        unsigned u = prevStartingPoint;     // set u to be the next WHITE node
        while (flags[u] != WHITE)
            u++;
        
        prevStartingPoint = u;          // update previous starting point
        
        // NOW START BREADTH FIRST SEARCH
        
        // tag u as GREY
        flags[u] = GREY;
        
        
        // push u into queue
        unsigned a = u;
        fifo_push(queue, &a);
        
        while (fifo_size(queue) > 0) {
            
            // pop an element from the queue
            u = *((int*)fifo_pop(queue));       // first cast to int pointer, then dereference pointer
            
            // loop over all neighbors of queue
            for (unsigned neigh = neigh_first(g, u); !neigh_done(g); neigh = neigh_next(g)) {
                
                unsigned v = neigh; // copy neigh before passing reference to fifo queue
                
                // if neighbor has not been tagged (GREY) yet
                if (flags[v] == WHITE) {
                    flags[v] = GREY;             // tag v
                    fifo_push(queue, &v);        // put v in queue
                }
            }
            
            // tag u as BLACK
            flags[u] = BLACK;
            remainingNodes--;       // done with u
            compSize++;
        }
        
        // if component size is larger than max, store size
        if (compSize > maxComp) {
            maxComp = compSize;
        }
        
        // free memory
        fifo_free(queue);
    }

    // free flags array
    free(flags);
    
    return maxComp;
}




