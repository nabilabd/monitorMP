//
//  Generator.c
//  Final Project
//
//  Created by Henry Huray on 11/23/15.
//  Copyright © 2015 Henry Huray. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void usage(const char* progName) {
    printf("Usage: %s inputFile outputFile probability \n", progName);
}

struct site{
    double LON;
    double LAT;
}site;

double getDistance(double lat1,double lon1,double lat2,double lon2) {
    double R = 6371; // Radius of the earth in km
    double dLat = (lat2-lat1)*22/(7*180);  // deg2rad below
    double dLon = (lon2-lon1)*22/(7*180);
    double a = sin(dLat/2) * sin(dLat/2) + cos((lat1)*22/(7*180)) * cos((lat2)*22/(7*180)) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = R * c; // Distance in km
    return d;
}

int main(int argc, const char * argv[]) {
    
    // if number of input args not met, quit
    if (argc != 4) {
        usage(argv[0]);
        return 0;
    }
    
    srand(time(NULL));
    
    
    // parse input
    const char* input_file = argv[1];
    const char* output_file = argv[2];
    double prob = strtod(argv[3], NULL); // c-p'd from Karl's code

    FILE *fp1 = fopen(input_file, "r");
    if (fp1 == NULL)
        return 0;            // file doesn't exist
    
    unsigned numNodes = 0;
    
    fscanf(fp1, "%u", &numNodes);        // read number of nodes
    
    struct site sites[numNodes];
    
    int index = 0;
    double u,v;
    
    while (fscanf(fp1, "%lf %lf", &u, &v) != EOF) {
        
        sites[index].LON = u;
        sites[index].LAT = v;
        index ++;
    }
    
    
    fclose(fp1);
    
    // open file for writing
    FILE* fp2 = fopen(output_file, "w");
    
    // write number of nodes
    fprintf(fp2, "%u\n", numNodes);
    
    for (size_t n = 1; n < numNodes; n++) {
        
        for (size_t to = 0; to < n; to++) {
            
            // compute probability of edge
            double r = rand() / (double) RAND_MAX;
            
            if (r < prob) {         // edge exists
                double distance = getDistance(sites[n].LAT,sites[n].LON,sites[to].LAT,sites[to].LON);
                fprintf(fp2, "%zu %zu %lf\n", n, to, distance);
                fprintf(fp2, "%zu %zu %lf\n", to, n, distance);
            }

        }
    }
    
    fclose(fp2);
}