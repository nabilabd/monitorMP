//
//  BellmanFord.c
//  monitorSearch
//
//  Created by Nabil Abdurehman on 11/24/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//



#include "BellmanFord.h"



// IDEA: don't export "Relax", "Initialize", and move definition of
// MetaNode back to this .c file. Then all user has to do is call
// BellmanFord. They shouldn't know about the internals anyway.



MetaNode** make_array(size_t numNodes) {
    
    MetaNode** my_array = malloc(sizeof(MetaNode*) * numNodes);
    for (size_t m = 0; m < numNodes; m++) {
        my_array[m] = NULL;
    }
    
    return my_array;
}

/*
 * Generates a non-source node
 *
 */
MetaNode* genNonSource() {
    MetaNode* currentNode = (MetaNode*) malloc(sizeof(MetaNode));
    currentNode->DistToSource = (double) INT64_MAX;
    currentNode->predecessor = (size_t) NULL;
    
    return currentNode;
}



/*
 *
 *
 * @param arr the array containing metadata for shortest-path route
 * @param size size of the graph (i.e., number of nodes in it)
 */
void InitializeSingleSource(MetaNode** arr, size_t size, size_t sourceID) {
    
    MetaNode* sourceNode = (MetaNode*) malloc(sizeof(MetaNode));
    sourceNode->predecessor = (size_t) NULL;
    sourceNode->DistToSource = 0;
    arr[sourceID] = sourceNode;
    
    // REMEMBER THIS ERROR; WAS PREVIOUSLY : k < size && k != sourceID
    for (size_t k = 0; k < size; k++) {
        
        if (k != sourceID) { arr[k] = genNonSource(); }
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

/* 
 * Print array of metadata
 */
void print_holder(MetaNode** holder, size_t length) {
    
    for (size_t k = 0; k < length; k++) {
        MetaNode* element = holder[k];
        printf("Vertex ID: %zu\t", k);
        printf("Distance from source: %f\t", element->DistToSource);
        printf("Previous node: %zu\n", element->predecessor);
    }
    
}






/* 
 * 
 * @param g the Graph containing the node network
 * @param nodeID the index of the node for which to find the shortest distance to the source
 */
double bellmanFord(Graph *g, size_t source, size_t dest, size_t numNodes, MetaNode** holder) {
    
    
    // MetaNode** stores information concerning shortest path, so for each node,
    // it's predecessor, distance from source node to it, etc
    
//    size_t numNodes = getNumNodes(g);
//    MetaNode **holder = (MetaNode **) malloc(sizeof(MetaNode*) * numNodes);
//    
//    InitializeSingleSource(holder, numNodes, source);
    
    
    // loop over vertices and edges, updating distances until no longer possible
    
//    print_holder(holder, numNodes);
    for (unsigned vertex1ID=0; vertex1ID < numNodes; vertex1ID++) {

//        for (size_t vertex2ID = vertex1ID+1 ; vertex2ID < numNodes; vertex2ID++) {
        
        // NB: by specification, always have that vertex2ID < vertex1ID
            unsigned vertex2ID;
            for (vertex2ID = neigh_first(g, vertex1ID); !neigh_done(g); vertex2ID = neigh_next(g)) {
                
                Relax(holder, vertex1ID, vertex2ID, getWeight(g));
                Relax(holder, vertex2ID, vertex1ID, getWeight(g));
                
            }
//        }
    }
    
    
    double destToSource = holder[dest]->DistToSource;
    return destToSource;
}


/*
 * Helper function for Dijkstra's algorithm
 *
 * @return the vertex ID closest to the source node
 */
size_t getClosest(MetaNode** holder, size_t sourceID, size_t numNodes) {
    
    size_t tempMin;  // current minimum value
    size_t tempInd;  // index of the current minimum value
    size_t currentVal;
    
    // initialize values
    if (sourceID != 0) tempInd = 0;
    else tempInd = 1;
    tempMin = holder[tempInd]->DistToSource;
    
    for (size_t j = 0; j < numNodes; j++) {
        if (j != sourceID) {
            
            currentVal = holder[j]->DistToSource;
            if (tempMin > currentVal) {
                tempInd = j;
                tempMin = currentVal;
            }
            
        }
    }
    
    
    return tempInd;
}


/*
 *
 * NB: Parameters are same as for Bellman-Ford
 */
double dijkstra(Graph *g, size_t source, size_t dest, size_t numNodes, MetaNode** holder) {
    
    PriorityQueue *S = pq_make();
    
    size_t verticesRemaining = numNodes;
    
    while (verticesRemaining > 0) {
        
        
        
    }
    
    
    
    return 0.0;
}


