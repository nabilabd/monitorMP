

# Introduction

Team Members: Nabil Abdurehman, Henry Huray

Suppose you have a network of machines located at various places across the US. Occasionally, these 
machines might malfunction, in which case a service-person would have to be dispatched 
to repair the device. Each device functions properly with a lifetime given by an exponential distribution.
Suppose further that this technician can only travel along the routes directly connecting two such machines. 

Then, there are a number of questions of interest, such as: 
* What is the optimal number of technicians to have on reserve to minimize the number of malfunctions at any given moment? 


# Problem Statement

## Description

There are two parts to this assignment. 

1. Graph Generation and Resource Analysis using Dijkstra's algorithm

2. Implementing parallel Dijkstra's algorithm with openMP, and comparing Dijkstra's against an alternative shortest-path algorithm


## Graph Generation and Discrete event simulation

We are assuming that the machine network consists of sites which form a connected graph. The edges have 
lengths equal to Euclidean distance between the latitude-longitude coordinates. One partner generates 
this connected graph with the edge lengths, and outputs that as a text file, which can be read into other 
programs for further analysis.

Additionally, this partner can implement event handlers, that schedule for events to happen based on 
when a machine malfunctions. In particular, a technician is deployed to fix the error-ridden machine. 
To do so, he uses a certain amount of resources (e.g., fuel, money for expenses) along the way, and his 
traveling to the machine is directly proportional to the distance from the base where he was sent from. To 
find the shortest path, the Dijkstra's algorithm code from the previous assignment can be used.

This partner can conduct an analysis, by calculating through simulations, where he examines how the numbers of 
malfunctioning equipment grows as the number of technicians and the parameter of the survival function, vary. 

That is, with a given number of technicians, does the number of malfunctioning machines grow over time, or remains 
approximately level, or decreases and remains small over time? Then we can see whether more resources (e.g., human or 
financial) need to be allocated to ensure the network's percentage of functioning machines is maintained above 
a certain threshold.


## Algorithm Comparison/Analysis

The second partner would focus on writing algorithms, to compare their performance and influence on 
the questions proposed earlier (that the other partner would also be working to answer). 

Specifically, this second partner can program a parallel implementation of Dijkstra's algorithm with OpenMP. 
To compare against these two versions of Dijkstra's algorithm, he can also implement an alternative shortest-path 
algorithm, and (perhaps) code that up in parallel as well. Then he would be providing three different algorithms 
which can each be used to examine how their use affects the aforementioned questions.
 

## Possible additions: 

* Assuming the monitor networks aren't completely connected graphs, but perhaps (e.g.) two connected components
* Assuming the network of machines actually consists of two kinds of machines, where each has a separate survival 
function (and so, different exponential distributions modelling expected lifetime before the next malfunction)


## Execution

The executable takes three different arguments. One is a text file containing site names, long/lat coordinates, 
and network name. The next is the parameter of the exponential distribution for the survival function of the monitors:

```
repairmonits sitenames.txt 0.05 0.02
```

## Report

Analyze average durations for how much time passes between machine failure and its repair. 
Provide recommendations/prescriptions on how to facilitate faster repair times for different sites.




