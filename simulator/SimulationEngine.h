//
//  SimulationEngine.h
//  Assignment 2
//
//  Created by Karl Gemayel on 9/15/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#ifndef SimulationEngine_h
#define SimulationEngine_h

#include <stdio.h>

/*
 * The callback function which will be called when a new event needs
 * to be processed. This function should be implemented by the user
 * of this simulation engine.
 *
 * @param event a pointer to an event of type defined by the application.
 */
void callback(void *eventData);

/*
 * Schedule the event at timestamp, given a callback to its handler.
 *
 * @param eventData the data representing the event to be scheduled
 * @param timestamp the event's timestamp
 */
void schedule(double timestamp, void* eventData);

/*
 * Run the simulation.
 */
void run_sim();

/*
 * Get the current simulation time
 *
 * @return the simulation time.
 */
double current_time();


#endif /* SimulationEngine_h */
