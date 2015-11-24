//
//  FIFOQueue.c
//  Assignment 2
//
//  Created by Karl Gemayel on 9/15/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#include "FIFOQueue.h"
#include <stdlib.h>
#include "Common.h"


// define the fifo queue element
typedef struct FIFOElement {
    void* data;
    struct FIFOElement *next;
} FIFOElement;

// define the fifo queue
struct FIFOQueue {
    unsigned int size;
    FIFOElement *front;     // points to the front of the queue
    FIFOElement *end;       // points to the end of the queue
};


// create an empty FIFO queue
FIFOQueue* fifo_create() {
    FIFOQueue *ffq = (FIFOQueue *) malloc(sizeof(FIFOQueue));
    if (ffq == NULL) FatalError("fifo_create", "Could not allocate memory.");
    
    ffq->front = NULL;
    ffq->end = NULL;
    ffq->size = 0;
    
    return ffq;
}


// Push an element into the queue
void fifo_push(FIFOQueue *ffq, void *data) {
    
    if (ffq == NULL)
        return;
    
    FIFOElement *e = (FIFOElement *) malloc(sizeof(FIFOElement));
    if (e == NULL) FatalError("fifo_push", "Could not allocate memory.");
    
    e->data = data;
    e->next = NULL;
    
    if (ffq->size == 0) {
        ffq->end = e;
        ffq->front = e;
    }
    else {
        ffq->end->next = e;
        ffq->end = ffq->end->next;
    }
    
    ffq->size++;
}

// Pop an element from the queue
void* fifo_pop(FIFOQueue *ffq) {
    if (ffq->size == 0)
        return NULL;
    
    FIFOElement *temp = ffq->front;
    ffq->front = ffq->front->next;
    
    void *data = temp->data;
    free(temp);
    
    ffq->size--;
    
    return data;
}


// returns 1 if queue is empty; 0 otherwise
unsigned int fifo_size(FIFOQueue *ffq) {
    return ffq->size;
}



// free the fifo queue
void fifo_free(FIFOQueue *ffq) {
    if (ffq == NULL)
        return;
    
    FIFOElement *current = ffq->front;
    FIFOElement *next = NULL;
    
    while (current != NULL) {
        next = current->next;       // keep track of next
        
        free(current);              // free current
        current = next;             // current is next
    }
    
    free(ffq);
}