

# Introduction

There are many monitoring locations across the US. They take measurements of various chemicals and 
air pollutants at ground level of the atmosphere. Now, there are different networks of monitoring 
locations, which vary in the characteristics of the vicinity where they're placed as well as 
other features, such as frequency measurements are taken. 


# Problem Statement

It is entirely reasonable that due to different circumstances concerning the monitors, that they 
would malfunction at different times. 

Suppose for each monitor in a given network, there was a probability with which the monitor 
malfunctioned at each time step. And that to fix a monitor, it requires manual attention by 
a service-person who would visit the site. Assume the vehicles deployed to service a monitor 
can carry supplies enough to service five monitors. Then, to avoid redundancy and conserve 
resources, ideally a service-person would only be sent when there are enough monitors to fix 
so that all supplies in the vehicle would be used. Also, there are two monitoring station networks, 
where each network has monitors which malfunction with a different probability.

Then, we have a discrete event simulation, where each monitor randomly malfunctions at each time 
step. Workers are dispatched whenever five monitors are malfunctioning. Dijkstra's algorithm is 
used to identify the shortest path which the service-person would use (this is a rough heuristic 
ignoring complications such as roads). Time-permitting, perhaps 

Possible additions: 

* Assuming the monitor networks aren't completely connected graphs
* Implementing a parallel implementation of Dijkstra's algorithm, can be implemented as well, like if we increase probabilities of malfunction.


# Goal

Analyze average waiting times from when a monitor site first malfunctions to when it is fixed. 
Provide recommendations/prescriptions on how to facilitate faster repair times for different sites.




