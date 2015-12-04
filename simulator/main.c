//
//  main.c
//  Final Project
//
//  Created by Henry Huray on 11/22/15.
//  Copyright © 2015 Henry Huray. All rights reserved.
//

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SimulationEngine.h"
#include "FIFOQueue.h"
#include "Common.h"

#define VERBOSE                 // comment this command to disable verbose mode

int baseIndex;
int numTechnicians;
int numMachines;
double maintenanceTime;
double distributionMean;

void usage(const char* progName) {
    printf("Usage: %s gf bi NumTech NumMach mt dist\n", progName);
    printf("\tbi  : basecamp index (int)\n");
    printf("\tNumTech: number of technicians (int)\n");
    printf("\tNumMach: number of machines (int)\n");
    printf("\tmt  : maintenance time (double)\n");
    printf("\tdist: mean of exponential distribution (double)\n");
}

/***************** Random Number Generation *****************\
 *                                                          *
 * These functions define how to generate a random number   *
 * from an exponential distribution. Also defined are the   *
 * variables used as the means of the distribution.         *
 \************************************************************/

/*
 * Generate a uniform random number in the range [0,1)
 */
double urand(void) {
    double x;
    while ((x = (rand() / (double) RAND_MAX)) >= 1.0);		// loop until x < 1 to exclude 1.0
    return x;
}

/*
 * Generate a random number from an exponential distribution
 * with a given mean.
 *
 * @param mean the mean of the distribution
 * @return a number draw from exponential distribution
 */
double randexp(double mean) {
    return (-1 * mean) * (log(1.0 - urand()));
}




/***************** Events, Handlers, States *****************\
 *                                                          *
 * Defined below are the event handlers, the event types,   *
 * as well as the state variables for the simulation.       *
 \************************************************************/

// EventKind: The kinds of events
typedef enum {MALFUNCTION, MAINTENANCE, FIXED, RETURNED} EventKind;

// Statistics variables
double  STAT_totalWaitingTime   = 0;                // total waiting time of machines before being fixed
int     STAT_numMalfunctions     = 0;               // number of malfunctions that have been simulated


// State Variables
int nWaiting = 0;					// number of machines waiting to be fixed
int nTechnician = 0;                // number of technicians on standby in the base
int nTotalFixed = 0;                // total number of machines that have been fixed

// fifo queue to hold waiting machines
FIFOQueue *machinesQ = NULL;

// Define a machine
typedef struct Machine {
    int machineID;              // machine ID
    double startWaiting;        // time when machine starts to wait for maintenance
    double endWaiting;          // time when machine stops waiting
} Machine;


// define the event data structure
typedef struct EventData {
    EventKind eventKind;
    Machine *machine;
} EventData;


// Event handlers
void malfunction        (EventData *e);
void maintenance        (EventData *e);
void fixed              (EventData *e);
void returned           (EventData *e);




/********** Function Implementations **********/

// This function is called by the simulation engine, and should process the event
// described by the event data

void callback(void* data) {
    
    EventData* eventData = (EventData*) data;
    
    if (eventData->eventKind == MALFUNCTION) {
        malfunction(eventData);
    }
    else if (eventData->eventKind == MAINTENANCE) {
        maintenance(eventData);
    }
    else if (eventData->eventKind == FIXED) {
        fixed(eventData);
    }
    else if (eventData->eventKind == RETURNED) {
        returned(eventData);
    }
    
}

// function to calculate travelling time
double travel_time(int base, int machine_dest) {
    double x = 1;
    return x;
}

/*
 * Event handler for machine malfunction
 *
 * @param malfunctionData the event data
 */
void malfunction (EventData *malfunctionData) {
    
    
#ifdef VERBOSE
    printf("TS = %f: Machine %d: malfunctioned.", current_time(), malfunctionData->machine->machineID);
    fflush(stdout);
#endif
    
    nWaiting += 1;          // number of waiting machines to be fixed
    STAT_numMalfunctions += 1;
    malfunctionData->machine->startWaiting = current_time(); // start waiting time since malfunction event happens
    
    // create a machine
    Machine* temp_machine = (Machine *) malloc(sizeof(Machine));
    if (temp_machine == NULL) FatalError("malfunction", "Could not allocate memory for machine.");
    
    temp_machine->machineID = malfunctionData->machine->machineID;                   // set machine ID
    temp_machine->startWaiting = current_time();                                    // set time machine starts waiting (now)
    
    
    // if there is a technician in the basecamp, schedule maintenance event
    if (nTechnician > 0) {
        
        nTechnician -= 1;                                   // reduce number of technician at basecamp by 1
        
        printf(" Technician dispatched, remaining technicians at basecamp is %d.\n", nTechnician);
        fflush(stdout);
        
        EventData* newMaintenance = (EventData *) malloc(sizeof(EventData));
        if (newMaintenance == NULL) FatalError("malfunction", "Could not allocate memory for new maintenance event.");
        
        newMaintenance->eventKind = MAINTENANCE;
        newMaintenance->machine = temp_machine;
        
        schedule(current_time() + travel_time(baseIndex, temp_machine->machineID), newMaintenance);
    }
    
    // otherwise, there is no technician in the basecamp, push machine to queue
    else {
        printf(" No technician left at basecamp.\n");
        fflush(stdout);
        fifo_push(machinesQ, temp_machine);
    }
    
    
    // done with malfunction event; free it
    free(malfunctionData);
}



/*
 * Event handler for a maintenance event
 *
 * @param maintenanceData the event data
 */
void maintenance (EventData *maintenanceData) {
    
    nWaiting -= 1;          // number of machines that are waiting to be fixed decreases
    maintenanceData->machine->endWaiting = current_time();          // end its waiting time
    double waiting_time = maintenanceData->machine->endWaiting - maintenanceData->machine->startWaiting; //calculate waiting time
    
#ifdef VERBOSE
    printf("TS = %f: Machine %d started maintenance, waited for %f.\n", current_time(), maintenanceData->machine->machineID, waiting_time);
    fflush(stdout);
#endif
    
    STAT_totalWaitingTime = STAT_totalWaitingTime + waiting_time;   // update statistics
    
    // schedule maintenance to finish by the given time
    double ts = current_time() + maintenanceTime;
    
    EventData *newFixed = (EventData *) malloc(sizeof(EventData));
    if (newFixed == NULL) FatalError("maintenance", "Could not allocate memory for fixed event.");
    
    newFixed->eventKind = FIXED;
    newFixed->machine = maintenanceData->machine;
    
    // schedule the finish of the maintenance, called the Fixed event
    schedule(ts, newFixed);
    
    free(maintenanceData);
}



/*
 * Event handler for fixed machine
 *
 * @param fixedData the event data
 */
void fixed(EventData *fixedData) {
    nTotalFixed += 1;         // total machines fixed increases
    
#ifdef VERBOSE
    printf("TS = %f: Machine %d finished maintenance.\n", current_time(), fixedData->machine->machineID);
    fflush(stdout);
#endif
    
    EventData *newMalfunction= (EventData *) malloc(sizeof(EventData));
    if (newMalfunction == NULL) FatalError("fixed", "Could not allocate memory for malfunction event.");
    
    newMalfunction->eventKind = MALFUNCTION;
    newMalfunction->machine = fixedData->machine;
    
    EventData *newReturned= (EventData *) malloc(sizeof(EventData));
    if (newReturned == NULL) FatalError("fixed", "Could not allocate memory for returned event.");
    
    newReturned->eventKind = RETURNED;
    newReturned->machine = fixedData->machine;
    
    // schedule the next malfunction and the technician returned to basecamp
    schedule (current_time() + randexp(distributionMean), newMalfunction);
    schedule (current_time() + travel_time(baseIndex, fixedData->machine->machineID), newReturned);
    
    // free event data
    free(fixedData);
}


/*
 * Event handler for returned event
 *
 * @param returnedData the event data
 */
void returned(EventData *returnedData) {
    
#ifdef VERBOSE
    printf("TS = %f: Technician returned from fixing Machine %d.", current_time(), returnedData->machine->machineID);
    fflush(stdout);
#endif
    
    // if there is a machine waiting to be fixed
    if (nWaiting > 0) {
        
        // pop from queue
        Machine* temp_machine = fifo_pop(machinesQ);
        EventData *newMaintenance = (EventData *) malloc(sizeof(EventData));
        if (newMaintenance == NULL) FatalError("returned","Could not allocate memory for maintenance event.");
        
        newMaintenance->eventKind = MAINTENANCE;
        newMaintenance->machine = temp_machine;
        
        // schedule a maintenance event immediately
        schedule(current_time() + travel_time(baseIndex, temp_machine->machineID), newMaintenance);
        
        printf(" Technician dispatched to fix Machine %d.\n", temp_machine->machineID);
        fflush(stdout);
        
        
    }
    else
        nTechnician += 1; //number of technician in the basecamp increases

    
    // free the event data
    free(returnedData);
}



int main(int argc, const char * argv[]) {
    
     //if number of input args not met, quit
    if (argc != 6) {
        usage(argv[0]);
        return 0;
    }
    
    srand((unsigned int)time(NULL));        // seed the random number generator
    
    baseIndex = atoi(argv[1]);//(int) stroul (argv[2], NULL, 10);
    numTechnicians = atoi(argv[2]);//(int) stroul (argv[3], NULL, 10);
    numMachines = atoi(argv[3]);
    maintenanceTime = strtod(argv[4], NULL);
    distributionMean = strtod(argv[5], NULL);
    
    // create empty machines queue
    machinesQ = fifo_create();
    
    for (int i = 0; i < numMachines; i++) {
        if (i != baseIndex){
            EventData *malfunction = (EventData *) malloc(sizeof(EventData));
            if (malfunction == NULL) FatalError("main", "Could not allocate memory for first malfunctions.");
            Machine* temp_machine = (Machine *) malloc(sizeof(Machine));
            if (temp_machine == NULL) FatalError("main", "Could not allocate memory for machines.");
            
            malfunction->eventKind = MALFUNCTION;
            temp_machine->machineID = i;
            malfunction->machine = temp_machine;
            
            double ts = randexp(distributionMean);
            schedule(ts, malfunction);

        }
    }
    
    nTechnician = numTechnicians;
    
    // start the simulation
    run_sim();
    
    
    printf("Number of malfunctions: %d\n", STAT_numMalfunctions);
    printf("Average waiting time: %.2f\n", STAT_totalWaitingTime / STAT_numMalfunctions);
}

// assume 1 day travel time
// 1 day maintenance time
//