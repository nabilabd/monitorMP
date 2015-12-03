//
//  main.c
//  Assignment3P1
//
//  Created by Nabil Abdurehman on 11/24/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//

#include "BellmanFord.h"
#include "Common.h"

// function to read in a graph
Graph *readGraph(char const *filename);



int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (argc != 2) {
        Warning("main", "missing argument: filename of graph");
    }
    
    
    char const *graph_file = argv[1];
    printf(&graph_file[0]);
    printf("\n\n");
    
    Graph* graph = readGraph(graph_file);
    freeGraph(graph);
    
    printf("Hello, World!\n");
    return 0;
}




/*
 * Read in a Graph Structure from Text Representation
 *
 * @param filename name of file containing graph to be read
 */
Graph *readGraph(char const *filename) {
    
    FILE *fp = fopen(filename, "r");
    
    float weight;
    size_t numNodes;
    unsigned fromVertex, toVertex;
    
    fscanf(fp, "%zu", &numNodes);
    printf("Number of nodes is %zu\n", numNodes);
    printf("Working here.\n");
    
    
    Graph *myGraph = makeGraph(numNodes);
    printf("Working so far.\n");
    
    // Associate with each vertex, a list of vertices it is connected to
    for (size_t k = 0; k < numNodes; k++) {
        
        fscanf(fp, "%u:", &fromVertex);
        fscanf(fp, "%u:", &toVertex);
        fscanf(fp, "%f", &weight);
        
        addWtdEdge(myGraph, fromVertex, toVertex, weight);
        
    }
    
    return myGraph;
}


