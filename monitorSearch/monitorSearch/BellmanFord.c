//
//  BellmanFord.c
//  monitorSearch
//
//  Created by Nabil Abdurehman on 11/24/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//



#include "BellmanFord.h"


/***  Internal Code Structure ***/
 
/*
 The implementations of Dijkstra's and the BF Algorithm, both serial and parallized, 
 are below. These implementations make use of relaxation operations that operate 
 on separate arrays tracking metadata for each node (so, separate from the graph 
 structure itself.
 
 So, whenever the relaxation operations are performed, the tentative fields 
 storing the node's predecessor and the distance to source, are updated in this 
 auxiliary array (which is descriptively titled "holder" in the code below).
 */



typedef struct MetaNode {
    
    size_t predecessor;
    double DistToSource;
    
} MetaNode;



MetaNode** make_array(size_t numNodes) {
    
    MetaNode** my_array = malloc(sizeof(MetaNode*) * numNodes);
    for (size_t m = 0; m < numNodes; m++) {
        my_array[m] = NULL;
    }
    
    return my_array;
}


void free_array(MetaNode** holder_array, size_t length) {
    
    for (size_t m = 0; m < length; m++) {
        MetaNode* temp = holder_array[m];
        free(temp);
    }
    
    free(holder_array);
}


/*
 * Generates a Non-source Node
 *
 * This function generates a metadata element for each node in the graph 
 * which is not the source node.
 *
 */
MetaNode* genNonSource() {
    MetaNode* currentNode = (MetaNode*) malloc(sizeof(MetaNode));
    currentNode->DistToSource = (double) INT64_MAX;
    currentNode->predecessor = (size_t) NULL;
    
    return currentNode;
}



/*
 * Initialization Procedure for Dijkstra's and BF Algorithms
 *
 * @param arr the array containing metadata for shortest-path route
 * @param size size of the graph (i.e., number of nodes in it)
 * @param sourceID ID of the source node in the graph.
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
 * 
 * This is mainly a utility functino to facilitate testing.
 */
void print_holder(MetaNode** holder, size_t length) {
    
    for (size_t k = 0; k < length; k++) {
        MetaNode* element = holder[k];
        printf("Vertex ID: %zu\t", k);
        printf("Distance from source: %f\t", element->DistToSource);
        printf("Previous node: %zu\n", element->predecessor);
    }
    
}




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
    free_array(myArray, numNodes); // free metadata array
    
    return destToSource;
}


double ompBellFord(Graph *g, size_t source, size_t dest, int nthreads) {
    
    size_t numNodes = getNumNodes(g);
    MetaNode** myArray = make_array( numNodes );
    InitializeSingleSource(myArray, numNodes, source);
    
    
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
    free_array(myArray, numNodes); // free metadata array
    
    return destToSource;
}



/*
 * Helper function for Dijkstra's algorithm
 *
 * @param NodesInS[] an array identifying if node in S or Q, for D's algorithm
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
    free_array(holder, num_nodes); // free metadata array

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
    free_array(holder, num_nodes); // free metadata array
    
    return min_dist;
    
    
}


