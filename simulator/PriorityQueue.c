//
//  PriorityQueue.c
//  Assignment 2
//
//  Created by Karl Gemayel on 9/15/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#include "PriorityQueue.h"

#include <stdlib.h>

#include "Common.h"

// define the priority queue element
typedef struct PQElement {
    double priority;
    void* data;
    struct PQElement *next;     // next element
    struct PQElement *prev;     // previous element
} PQElement;


// define priority queue structure that
// holds the head node and the size
struct PriorityQueue {
    unsigned int size;
    PQElement *head;
    PQElement *tail;
};


// create an empty priority queue
PriorityQueue* pq_create() {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq == NULL) FatalError("pq_create", "Could not allocate memory.");
    
    pq->head = NULL;
    pq->tail = NULL;
    
    // pq starts empty
    pq->size = 0;
    
    return pq;
}

// Push an element with a given priority into the queue
void pq_push(PriorityQueue *pq, double priority, void *data) {
    
    if (pq == NULL)
        return;
    
    // create a new element with the given data and priority
    PQElement *r = (PQElement *) malloc(sizeof(PQElement));
    if (r == NULL) FatalError("pq_push", "Could not allocate memory.");
    
    // init members of r
    r->priority = priority;
    r->data = data;
    
    r->next = NULL;
    r->prev = NULL;
    
    
    // if priority queue is empty, point head and tail to new element
    if (pq->size == 0) {
        pq->head = r;
        pq->tail = r;
        
        pq->size += 1;
        return;
    }
    
    // otherwise, find correct place for element based on priority

    PQElement *p = pq->head;
    
    // find the correct location in which to put the new element (r)
    for ( ; p != NULL; p=p->next) {
        // check if this is correct location
        if (priority < p->priority)
            break;
    }
    
    // if p is NULL, then r is last element
    if (p == NULL) {
        
        //       BEFORE            =>                  AFTER
        //
        //      tail                                             tail
        //       ___                                    ___       ___
        //  <-> | q |                              <-> | q | <-> | r |
        
        PQElement *q = pq->tail;
        q->next = r;
        r->prev = q;
        pq->tail = r;

    }
    
    // else; if p is not NULL but p->prev is NULL, then r is first element
    else if (p->prev == NULL) {
        
        //       BEFORE            =>                  AFTER
        //
        //      head                                   head
        //       ___                                    ___       ___
        //      | p | <->                              | r | <-> | p | <->
        
        r->next = p;
        p->prev = r;
        pq->head = r;
    }
    
    // else; r is somewhere in the queue (not head or tail)
    else {
        
        //       BEFORE               =>                  AFTER
        //
        //       ___       ___                          ___       ___       ___
        //      | q | <-> | p |                        | q | <-> | r | <-> | p |

        PQElement *q = p->prev;
        q->next = r;
        r->prev = q;
        
        p->prev = r;
        r->next = p;
        
    }

    pq->size++;
}

// Pop an element from the priority queue
void* pq_pop(PriorityQueue *pq) {
    
    if (pq == NULL)
        return NULL;
    
    // check if queue is empty
    if (pq->size == 0)
        return NULL;
    
    // otherwise, remove and return the first element in the list
    PQElement *first = pq->head;
    
    // if only one element exists, then tail and head both should point to NULL
    if (pq->size == 1) {
        pq->head = NULL;
        pq->tail = NULL;
    }
    // otherwise, head points to next element; tail doesn't change
    else  {
        pq->head = pq->head->next;
        pq->head->prev = NULL;          // remove link to "previous" element
    }
    
    void* data = first->data;	// get the data of the first element
    
    free(first);				// free the "container" of the first element
    pq->size--;                 // decrement size of pq by 1
    
    // return the data of the first element
    return data;
}


// get the size of the priority queue
unsigned int pq_size(PriorityQueue *pq) {
    if (pq == NULL)
        return 0;
    
    return pq->size;
}


// free the priority queue (with its elements)
void pq_free (PriorityQueue *pq) {
    if (pq == NULL)
        return;
    
    PQElement *e = pq->head;
    
    while (e != NULL) {
        PQElement *temp = e;
        e = e->next;
        free(temp);
    }
    
    free(pq);
}