//
//  main.c
//  Assignment3P1
//
//  Created by Nabil Abdurehman on 11/24/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//

#include <stdio.h>
#include "Graph.h"


// function to read in a graph
void readGraph(char const *filename);



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}




/*
 * Read in a Graph Structure from Text Representation
 *
 * @param filename name of file containing graph to be read
 */
void readGraph(char const *filename) {
    
    FILE *fp = fopen(filename, "r");
    
    int numEdges;
    double weight;
    size_t numNodes;
    unsigned fromVertex, toVertex;
    
    fscanf(fp, "%zd", &numNodes);
    fscanf(fp, "%d", &numEdges);
    
    Graph *myGraph = makeGraph(numNodes);
    
    
    // Associate with each vertex, a list of vertices it is connected to
    for (int k = 0; k < numEdges; k++) {
        
        fscanf(fp, "%zd:", &fromVertex);
        fscanf(fp, "%zd:", &toVertex);
        fscanf(fp, "%lf", &weight);
        
        addWtdEdge(myGraph, fromVertex, toVertex, weight);
        
    }
    
    
}


