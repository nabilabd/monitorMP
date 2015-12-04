//
//  BellmanFord.h
//  monitorSearch
//
//  Created by Nabil Abdurehman on 12/2/15.
//  Copyright © 2015 Nabil Abdurehman. All rights reserved.
//

#ifndef BellmanFord_h
#define BellmanFord_h

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct MetaNode {
    
    size_t predecessor;
    double DistToSource;
    
} MetaNode;



MetaNode** make_array(size_t numNodes);


void InitializeSingleSource(MetaNode** arr, size_t size, size_t sourceID);


void Relax(MetaNode** arr, size_t u, size_t v, double w);


double bellmanFord(Graph *g, size_t source, size_t dest);


double dijkstra(Graph *g, size_t source, size_t dest);


#endif /* BellmanFord_h */





