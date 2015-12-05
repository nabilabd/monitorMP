# Build program executable

# EXECUTABLE defines the name of the executable that will be generated
# SOURCES should include all the .c files in your project (do not include .h)

# NB: Since the default gcc compiler on Mac OS X(i.e., the one symlinked to "gcc") does 
# 	not contain <omp.h>, the latest GNU Compiler version, gcc-5, was used as the 
# 	compiler here. 
# 	To use this Makefile on a non-Mac system, one can change "gcc-5" on line 13 to 
# 	a compiler that would work.
# 	To install gcc-5 on a Mac, if `homebrew` is already installed, one can run the 
# 	terminal command `brew install gcc-5`.

analyzer: main.c BellmanFord.c Common.c Graph.c 
	gcc-5 main.c BellmanFord.c Common.c Graph.c -o analyzer -fopenmp




