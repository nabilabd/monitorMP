//
//  SimulationEngine.c
//  Assignment 2
//
//  Created by Karl Gemayel on 9/15/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#include "SimulationEngine.h"
#include "PriorityQueue.h"
#include "Common.h"
#include <stdlib.h>

// declare simulation time
double simtime = 0;

PriorityQueue *FEL = NULL;      // Future Event List

// define container for simulations events
typedef struct SimEvent {
    double timestamp;					// event time stamp
    void *data;                         // application data
} SimEvent;

// schedule the event at time-stamp, and provide a callback to its handler
void schedule(double timestamp, void* eventData) {
    
    SimEvent *se = (SimEvent *) malloc(sizeof(SimEvent));
    if (se == NULL) FatalError("schedule", "Could not allocate memory.");
    
    se->data =eventData;
    se->timestamp = timestamp;
    
    // if we have not yet initialize a priority queue, create one
    if (FEL == NULL)
        FEL = pq_create();
    
    // pass the simulation event into the queue with priority equal to timestamp
    pq_push(FEL, timestamp, se);
    
}

// run the simulation
void run_sim() {
    
    if (FEL == NULL)
        return;
    
    // as long as the priority queue is not empty
    // remove its top element, and execute its callback
    // on the event data
    while (simtime <= 365) {
        SimEvent *se = (SimEvent *) pq_pop(FEL);
        simtime = se->timestamp;
        callback(se->data);
        free(se);
    }
    
    // free the pq
    pq_free(FEL);
    FEL = NULL;
    
}

// returns the current simulation time
double current_time() {
    return simtime;
}

