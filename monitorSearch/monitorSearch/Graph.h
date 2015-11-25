//
//  Graph.h
//  Assignment 3
//
//  Created by Karl Gemayel on 10/26/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>


// A graph structure
typedef struct Graph Graph;


/*
 * Create a graph with a given number of nodes
 *
 * @param numNodes the number of nodes
 * @return a pointer to a graph.
 */
Graph* makeGraph(size_t numNodes);

/*
 * Free the memory allocated for the graph
 *
 * @param g the graph
 */
void freeGraph(Graph *g);

/*
 * Add a directed edge to the graph. Nodes are specified
 * using an integer index scheme, such that for N nodes,
 * the indeces run from 0 to N-1 (inclusive).
 *
 * @param g the graph
 * @param from the index of the first node
 * @param to the index of the second node
 */
void addEdge(Graph* g, unsigned from, unsigned to);


/*
 * Get the number of nodes in the graph.
 *
 * @param g the graph
 * @return the number of nodes.
 */
size_t getNumNodes(Graph *g);


/********** Iterators **********\
 *                             *
 * Iterators provide access to *
 * the neighbors of any given  *
 * node.                       *
 *                             *
\*******************************/

/*
 * Get the first neighbor of a node.
 *
 * If no neighbor exists, then this will return an arbitrary
 * value. To check the validity of this value, neigh_done should be 
 * called immediately after.
 *
 * @param g the graph
 * @param from the index of the node whose neighbor we want to access
 * @return the index of from's first neighbor
 */
unsigned neigh_first (Graph *g, unsigned from);

/*
 * Get the next neighbor of a node. The current neighbor is
 * defined either by a call to neigh_first, or by subsequent
 * calls to neigh_next. 
 *
 * If no next neighbor exists, then this will return an arbitrary
 * value. To check the validity of this value, neigh_done should be
 * called immediately after.
 *
 * @param g the graph
 */
unsigned neigh_next (Graph *g);

/*
 * Checks whether the last value returned by neigh_first or
 * neigh_next is valid.
 *
 * @param g the graph
 */
int neigh_done (Graph *g);


/*
 * Returns the weight of the edge currently accessed
 */
double getWeight(Graph *g);



#endif /* Graph_h */
