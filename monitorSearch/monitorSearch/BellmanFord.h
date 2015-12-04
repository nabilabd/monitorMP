//
//  BellmanFord.h
//  monitorSearch
//
//  Created by Nabil Abdurehman on 12/2/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//

#ifndef BellmanFord_h
#define BellmanFord_h

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <omp.h>



/*
 * Compute Shortest Distance via BF Algorithm Between Two Given Nodes
 *
 * @param g a pointer to a graph over which the algorithm is executed
 * @param source ID of the "source" node
 * @param dest ID of the "destination" node
 * @return the distance between "source" and "dest" nodes in the graph
 */
double bellmanFord(Graph *g, size_t source, size_t dest);


/*
 * OpenMP Version of BF Algorithm
 *
 *
 * @param g a pointer to a graph over which the algorithm is executed
 * @param source ID of the "source" node
 * @param dest ID of the "destination" node
 * @param nthreads Number of threads over which to parallize operations
 * @return the distance between "source" and "dest" nodes in the graph
 */
double ompBellFord(Graph *g, size_t source, size_t dest, int nthreads);


/*
 * Compute Shortest Distance via Dijkstra's Algorithm Between Two Given Nodes
 *
 *
 * @param g a pointer to a graph over which the algorithm is executed
 * @param source ID of the "source" node
 * @param dest ID of the "destination" node
 * @return the distance between "source" and "dest" nodes in the graph
 */
double dijkstra(Graph *g, size_t source, size_t dest);


/*
 * OpenMP Version of Dijkstra's Algorithm
 *
 * @param g a pointer to a graph over which the algorithm is executed
 * @param source ID of the "source" node
 * @param dest ID of the "destination" node
 * @param nthreads Number of threads over which to parallize operations
 * @return the distance between "source" and "dest" nodes in the graph
 */
double ompDijkstra(Graph *g, size_t source, size_t dest, int nthreads);



#endif /* BellmanFord_h */





