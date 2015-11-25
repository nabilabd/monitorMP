//
//  BellmanFord.c
//  monitorSearch
//
//  Created by Nabil Abdurehman on 11/24/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "FIFOQueue.h"

// read the graph


typedef struct MetaNode {
    
    size_t predecessor;
    double DistToSource;
    
} MetaNode;


// initialize graph for B-F algorithm
void InitializeSingleSource(MetaNode** arr, size_t size, size_t sourceID);



void Relax(MetaNode** arr, size_t u, size_t v, double w);


/* 
 * 
 * @param g the Graph containing the node network
 * @param nodeID the index of the node for which to find the shortest distance to the source
 */
double *bellmanFord(Graph *g, size_t source) {
    
    
    // MetaNode** stores information concerning shortest path, so for each node,
    // it's predecessor, distance from source node to it, etc
    
    size_t numNodes = getNumNodes(g);
    MetaNode **holder = (MetaNode **) malloc(sizeof(MetaNode*) * numNodes);
    
    InitializeSingleSource(holder, numNodes, source);
    
    
    // loop over vertices and edges, updating distances until no longer possible
    
    for (unsigned vertex1ID=0; vertex1ID < numNodes; vertex1ID++) {

        for (size_t vertex2ID = vertex1ID+1 ; vertex2ID < numNodes; vertex2ID++) {
            
            unsigned currentID;
            for (currentID = neigh_first(g, vertex1ID); !neigh_done(g); neigh_next(g)) {
                
                // this condition ensures only single edge checked
                // TODO: change graph structure to avoid wasted space
                if (currentID >= vertex2ID) {
                    Relax(holder, vertex1ID, currentID, getWeight(g));
                    Relax(holder, currentID, vertex1ID, getWeight(g));
                }
                
            }
        }
    }
    
    
    
    //
    
    
    
    return 0;
}


/*
 *
 *
 * @param arr the array containing metadata for shortest-path route
 * @param size size of the graph (i.e., number of nodes in it)
 */
void InitializeSingleSource(MetaNode** arr, size_t size, size_t sourceID) {
    
    MetaNode* sourceNode = arr[sourceID];
    sourceNode->predecessor = (size_t) NULL;
    sourceNode->DistToSource = 0;
    
    for (size_t k = 0; k < size && k != sourceID; k++) {
        MetaNode* currentNode = arr[k];
        currentNode->DistToSource = INT64_MAX;
        currentNode->predecessor = (size_t) NULL;
    }
    
}



/*
 * Relaxes the edge if a shorter path can be found
 *
 * @param u,v vertices in the graph
 * @param w weight of edge u-v
 */
void Relax(MetaNode** arr, size_t u, size_t v, double w) {
    
    MetaNode* vertU = arr[u];
    MetaNode* vertV = arr[v];
    
    if (vertU->DistToSource + w < vertV->DistToSource) {
        vertV->predecessor = u;
        vertV->DistToSource = vertU->DistToSource + w;
    }
    
}






