//
//  main.c
//  Assignment3P1
//
//  Created by Nabil Abdurehman on 11/24/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//

#include "BellmanFord.h"
#include "Common.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (argc < 2) {
        Warning("main", "missing argument: filename of graph");
    } else if (argc > 2) {
        Warning("main", "too many arguments; only using the second one");
    }
    
    char const *graph_file = argv[1];
    size_t numberOfEdges = strtol(argv[2], NULL, 10);

    Graph* graph = readGraph(graph_file);
    size_t graphSize = getNumNodes(graph);
    print_graph(graph);
    
    
    MetaNode** myArray = make_array( graphSize );
    InitializeSingleSource(myArray, graphSize, 5);
    
    
    double mindist = bellmanFord(graph, 5, 3, graphSize, myArray);
    printf("Bellman-Ford min distance is: %f\n\n", mindist);
    
    MetaNode** myArray2 = make_array( graphSize );
    InitializeSingleSource(myArray2, graphSize, 4);
    
    double dijk_min = dijkstra(graph, 4, 3, myArray2);
    printf("Dijkstra min distance is: %f\n", dijk_min);
    
    
    
    freeGraph(graph);
    
    printf("Hello, World!\n");
    return 0;
}




