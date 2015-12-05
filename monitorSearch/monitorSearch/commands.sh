#!/bin/bash
#
# This is a script that generates timing results for the four 
# algorithms: Bellman-Ford, Dijkstra's, and the OMP versions of them.
#
# This file should be located in the same directory as the executable 
# which runs the four algorithms and tracks runtimes.
# 
# To analyze the four algorithms' runtimes, this script does the following:
#	1) Outputs runtime of each of the four algorithms from source node 0 to 
# 		to each of one hundred destination nodes
#	2) does (1) for each of three different thread counts: 2, 3, 4
# 
# Note that the for-loops below can be extended to generate results for all 
# combinations of other parameters one may deem interesting or otherwise 
# worthy of study.
# 
make
touch results.txt
echo "Starting calculations\n"
echo "Type	BF	DK	OMPBF	OMPDK	FROM	TO	NTHRDS" > results.txt
for i in {1..100}
do
	for k in {2..4}
	do
		#statements
		./analyzer na_test 0 $i $k >> results.txt
	done
done
say "done"
