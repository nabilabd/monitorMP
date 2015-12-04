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


typedef struct MetaNode {
    
    size_t predecessor;
    double DistToSource;
    
} MetaNode;



MetaNode** make_array(size_t numNodes);


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
double bellmanFord(Graph *g, size_t source, size_t dest) {
    
    
    // MetaNode** stores information concerning shortest path, so for each node,
    // it's predecessor, distance from source node to it, etc
    
    size_t numNodes = getNumNodes(g);
    MetaNode** myArray = make_array( numNodes );
    InitializeSingleSource(myArray, numNodes, source);
    
    
    // loop over vertices and edges, updating distances until no longer possible
    
    for (unsigned vertex1ID=0; vertex1ID < numNodes; vertex1ID++) {

            unsigned vertex2ID;
            for (vertex2ID = neigh_first(g, vertex1ID); !neigh_done(g); vertex2ID = neigh_next(g)) {
                
                Relax(myArray, vertex1ID, vertex2ID, getWeight(g));
                Relax(myArray, vertex2ID, vertex1ID, getWeight(g));
                
            }
    }
    
    
    double destToSource = myArray[dest]->DistToSource;
    return destToSource;
}

/*
 
 * This works by having each thread relax a subset of the edges connecting a 
 * given node with its neighbors.
 
 */
double ompBellFord(Graph *g, size_t source, size_t dest, int nthreads) {
    
    size_t numNodes = getNumNodes(g);
    MetaNode** myArray = make_array( numNodes );
    InitializeSingleSource(myArray, numNodes, source);
    
    
    // loop over vertices and edges, updating distances until no longer possible
    
    omp_set_num_threads(nthreads);
//    printf("Num of threads is %d\n\n", nthreads);
    
    
    #pragma omp parallel shared(myArray, numNodes)
    {
        int id, num_threads;
        
        id = omp_get_thread_num();
        num_threads = omp_get_num_threads();
//        printf("ID is: %d\n", id);
        
        for (unsigned vertex1ID=id; vertex1ID < numNodes; vertex1ID += num_threads) {
            
            unsigned vertex2ID;
                
                #pragma omp critical
                {
                    for (vertex2ID = neigh_first(g, vertex1ID); !neigh_done(g); vertex2ID = neigh_next(g)) {
                        double wt = getWeight(g);
                        Relax(myArray, vertex1ID, vertex2ID, wt);
                        Relax(myArray, vertex2ID, vertex1ID, wt);
                    }
                }

            
        }
    }
    
    double destToSource = myArray[dest]->DistToSource;
    return destToSource;

    
}



/*
 * Helper function for Dijkstra's algorithm
 *
 * @return the vertex ID closest to the source node
 */
size_t getClosest(MetaNode** holder, size_t NodesInS[], size_t numNodes) {
    
    size_t tempMin = INT64_MAX;  // current minimum value
    size_t tempInd = -1;  // index of the current minimum value
    size_t currentVal;
    
    for (size_t j = 0; j < numNodes; j++) {
        
        // if node is not in S, then consider its distance to source
        if (NodesInS[j] == 1) {
            
            currentVal = holder[j]->DistToSource;
            if (tempMin > currentVal) {
                tempInd = j;
                tempMin = currentVal;
            }
        }
    }
    
    // closest node found, so update the array showing inclusion in S
    NodesInS[tempInd] = 0; //
    
    return tempInd;
}


/*
 *
 * NB: Parameters are same as for Bellman-Ford
 */
double dijkstra(Graph *g, size_t source, size_t dest) {
    
    // up to here, "holder" assumed to already be initialized with source node "source"
    
    size_t num_nodes = getNumNodes(g);
    MetaNode** holder = make_array( num_nodes );
    InitializeSingleSource(holder, num_nodes, source);
    
    size_t verticesRemaining = num_nodes;
    
    
    
    // initialize all elements to not being in S
    size_t nodesInS[num_nodes];    // 0 if contained in S, otherwise 1.
    for (int m = 0; m < num_nodes; m++) {
        nodesInS[m] = 1;
    }
    
    
    while (verticesRemaining > 0) {
        
        unsigned u = (unsigned) getClosest(holder, nodesInS, num_nodes);
        
        // loop through neighbors of u, updating distances and predecessors
        unsigned vertexID;
        for (vertexID = neigh_first(g, u); !neigh_done(g); vertexID = neigh_next(g)) {
            double wt = getWeight(g);
            Relax(holder, u, vertexID, wt);
            Relax(holder, vertexID, u, wt);
        }

        verticesRemaining--;
    }
    
    
    
    double min_dist = holder[dest]->DistToSource;
    return min_dist;
}




double ompDijkstra(Graph *g, size_t source, size_t dest, int nthreads) {
    
    // up to here, "holder" assumed to already be initialized with source node "source"
    
    size_t num_nodes = getNumNodes(g);
    MetaNode** holder = make_array( num_nodes );
    InitializeSingleSource(holder, num_nodes, source);
    
    size_t verticesRemaining = num_nodes;
    
    
    
    // initialize all elements to not being in S
    size_t nodesInS[num_nodes];    // 0 if contained in S, otherwise 1.
    for (int m = 0; m < num_nodes; m++) {
        nodesInS[m] = 1;
    }
    
    
    while (verticesRemaining > 0) {
        
        unsigned u = (unsigned) getClosest(holder, nodesInS, num_nodes);
        
        // loop through neighbors of u, updating distances and predecessors
        unsigned vertexID;
        
        
        
        omp_set_num_threads(nthreads);
        #pragma omp parallel
        {
            
            // this section parallelizes the relaxation of connected edges
            int id, num_threads;
            id = omp_get_thread_num();
            num_threads = omp_get_num_threads();
            
            
            
            for (vertexID = neigh_first(g, u); !neigh_done(g); vertexID = neigh_next(g)) {
                
                if (vertexID % num_threads == id) {

                    #pragma omp critical
                    {
                        double wt = getWeight(g);
                        Relax(holder, u, vertexID, wt);
                        Relax(holder, vertexID, u, wt);
                    }
                }
            }
            // ends parallelized section
        }
        
        
        verticesRemaining--;
    }
    
    
    
    double min_dist = holder[dest]->DistToSource;
    return min_dist;
    
    
}


