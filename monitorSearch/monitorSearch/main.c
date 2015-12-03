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
    
    if (argc < 2) {
        Warning("main", "missing argument: filename of graph");
    } else if (argc > 2) {
        Warning("main", "too many arguments; only using the second one");
    }
    
    char const *graph_file = argv[1];

    Graph* graph = readGraph(graph_file);
    size_t graphSize = getNumNodes(graph);
    print_graph(graph);
    
    
    MetaNode** myArray = make_array( graphSize );
    InitializeSingleSource(myArray, graphSize, 5);
    
    
    double mindist = bellmanFord(graph, 0, 3, graphSize, myArray);
    printf("Bellman-Ford min distance is: %f\n", mindist);
    
    
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


