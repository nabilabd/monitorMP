//
//  Generator.c
//  Assignment 3
//
//  Created by Karl Gemayel on 10/26/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void usage(const char* progName) {
    printf("Usage: %s N P O\n", progName);
    printf("\tN: number of nodes\n");
    printf("\tP: probability of an edge between two nodes\n");
    printf("\tO: name of output file\n");
}

int main(int argc, const char * argv[]) {
    
    // if number of input args not met, quit
    if (argc != 4) {
        usage(argv[0]);
        return 0;
    }

    srand( (unsigned int) time(NULL));
    
    // parse input
    size_t numNodes = (size_t) strtoul (argv[1], NULL, 10);     // num nodes
    double prob = strtod(argv[2], NULL);
    const char* fname = argv[3];
    
    // open file for writing
    FILE* fp = fopen(fname, "w");
    
    // write number of nodes
    fprintf(fp, "%zu\n", numNodes);
    
    for (size_t n = 1; n < numNodes; n++) {
        
        for (size_t to = 0; to < n; to++) {
            
            // compute probability of edge
            double r = rand() / (double) RAND_MAX;
            
            if (r < prob) {         // edge exists
                fprintf(fp, "%zu %zu\n", n, to);
            }
        }
    }
    
    fclose(fp);
    
}