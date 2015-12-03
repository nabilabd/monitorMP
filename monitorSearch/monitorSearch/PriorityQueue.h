//
//  PriorityQueue.h
//  Assignment 2
//
//  Created by Karl Gemayel on 9/15/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <stdio.h>

// This file implements a MIN Priority Queue (i.e. elements with the
// smallest "priority" are removed first from the queue.


// Declare type of priority queue
typedef struct PriorityQueue PriorityQueue;

/*
 * Create an empty priority queue.
 *
 * @return a pointer to the priority queue.
 */
PriorityQueue* pq_make();

/*
 * Push an element with a given priority into the queue.
 *
 * @param pq the priority queue
 * @param priority the element's priority
 * @param data the data representing our element
 */
void pq_push(PriorityQueue *pq, double priority, void *data);


/*
 * Pop the top element from the priority queue.
 *
 * @param pq the priority queue
 *
 * @return the data representing the top element
 */
void* pq_pop(PriorityQueue *pq);


/*
 * Get the size of the priority queue
 *
 * @param pq the priority queue
 *
 * @return the size of the queue
 */
unsigned int pq_size(PriorityQueue *pq);


/*
 * Free the memory allocated to the priority queue.
 *
 * @param pq the priority queue
 */
void pq_free(PriorityQueue *pq);



#endif /* PriorityQueue_h */
