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
    
    if (argc != 3) {
        Warning("main", "Should only have graph's filename and number of edges");
    }
    
    char const *graph_file = argv[1];
    size_t numberOfEdges = strtol(argv[2], NULL, 10);

    Graph* graph = readGraph(graph_file, numberOfEdges);    
    
    double mindist = bellmanFord(graph, 4, 3);
    printf("Bellman-Ford min distance is: %.3f\n", mindist);
    
    double dijk_min = dijkstra(graph, 4, 3);
    printf("Dijkstra min distance is: %.3f\n", dijk_min);
    
    printf("\n");
    
    double bf_dist = bellmanFord(graph, 10, 3);
    printf("Second Bellman-Ford min distance is: %.2f\n", bf_dist);
    
    
    double dijk = dijkstra(graph, 10, 3);
    printf("Second Dijkstra min distance is: %.2f\n", dijk);
    
    
    freeGraph(graph);
    
    printf("Hello, World!\n");
    return 0;
}




