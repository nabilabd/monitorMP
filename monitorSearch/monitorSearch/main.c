//
//  main.c
//  Assignment3P1
//
//  Created by Nabil Abdurehman on 11/24/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//

#include "BellmanFord.h"
#include "Common.h"
#include <time.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (argc < 5) {
        Warning("main", "Not enough arguments");
    }
    
    char const *graph_file = argv[1];
    size_t sourceID = (size_t) strtol(argv[2], NULL, 10);
    size_t destID = (size_t) strtol(argv[3], NULL, 10);
    int nthreads = (int) strtol(argv[4], NULL, 10);
    
    Graph* graph = readGraph(graph_file);    
    
    clock_t begin, end;
    
    
//    double mindist = bellmanFord(graph, sourceID, destID);
//    printf("BF min distance is: %.3f\n", mindist);
//    
//    double dijk_min = dijkstra(graph, sourceID, destID);
//    printf("Dijkstra min distance is: %.3f\n", dijk_min);
//    
//    printf("\n");
    
    double avg_times[4] = {0, 0, 0, 0};
    double num_reps = 10;
    double bf_dist, dijk, ompbf_dist, omp_dijk_dist;
    
    
    for (int m=0; m < num_reps; m++) {
        begin = clock();
        bf_dist = bellmanFord(graph, 10, 3);
        end = clock();
        avg_times[0] += (double) (end - begin) / (num_reps * CLOCKS_PER_SEC);
        
        
        begin = clock();
        dijk = dijkstra(graph, 10, 3);
        end = clock();
        avg_times[1] += (double) (end - begin) / (num_reps * CLOCKS_PER_SEC);
        
        
        begin = clock();
        ompbf_dist = ompBellFord(graph, 10, 3, nthreads);
        end = clock();
        avg_times[2] += (double) (end - begin) / (num_reps * CLOCKS_PER_SEC);
        
        
        begin = clock();
        omp_dijk_dist = ompBellFord(graph, 10, 3, nthreads);
        end = clock();
        avg_times[3] += (double) (end - begin) / (num_reps * CLOCKS_PER_SEC);
    }
    
    // Print Results
    
    
    printf("Type\tBF\tDK\tOMPBF\tOMPDK\n");
    printf("Dist\t%.3f\t%.3f\t%.3f\t%.3f\n", bf_dist, dijk, ompbf_dist, omp_dijk_dist);
    printf("Time\t%.5f\t%.5f\t%.5f\t%.5f\n", avg_times[0], avg_times[1], avg_times[2], avg_times[3]);
    
    
    
    freeGraph(graph);
    return 0;
}




