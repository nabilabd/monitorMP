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



double bellmanFord(Graph *g, size_t source, size_t dest);


double dijkstra(Graph *g, size_t source, size_t dest);


#endif /* BellmanFord_h */





