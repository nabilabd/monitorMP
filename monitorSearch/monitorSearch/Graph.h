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
 * Read in a Graph Structure from Text Representation
 *
 *
 * @param filename name of file containing graph to be read
 * @return a graph object as represented by the file
 */
Graph *readGraph(char const *filename);


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
 * Add Weighted Edges to a Graph
 *
 * Same as addEdge, except allows for weighted edges
 *
 * @param g the graph to which the edge is to be added
 * @param wt weight of the edge connecting "from" and "to"
 * @param from,to id's of nodes in the graph
 */
void addWtdEdge(Graph* g, unsigned from, unsigned to, float wt);


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
 * Prints a Graph Representation to Stdout
 * 
 * This is a utility function to facilitate testing
 *
 * @param myGraph the graph to print
 */
void print_graph(Graph* myGraph);


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
 * 
 * This function makes use of the iterator in the graph, by accessing the 
 * weight of the "edge" represented by the iterator. 
 *
 * So if, e.g., the iterator is pointing to the node with ID 3, and which is a 
 * neighbor of node 0, then this function returns the weight of the edge 
 * connecting 0 and 3.
 *
 * @param g The graph for
 */
double getWeight(Graph *g);



#endif /* Graph_h */
