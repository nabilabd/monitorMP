# Build program executable

# EXECUTABLE defines the name of the executable that will be generated
# SOURCES should include all the .c files in your project (do not include .h)

EXECUTABLE_ANALYSIS=analyzer
SOURCES_ANALYSIS=AnalyzeComponents.c Common.c FIFOQueue.c Graph.c

EXECUTABLE_GEN=graphgen1
SOURCES_GEN=Generator.c

CC=gcc
CFLAGS=-c -Wall -g
OBJECTS_ANALYSIS=$(SOURCES_ANALYSIS:.c=.o)
OBJECTS_GEN=$(SOURCES_GEN:.c=.o)

all: $(SOURCES_ANALYSIS) $(EXECUTABLE_ANALYSIS) $(SOURCES_GEN) $(EXECUTABLE_GEN)

$(EXECUTABLE_ANALYSIS): $(OBJECTS_ANALYSIS)
	$(CC) -lm $(OBJECTS_ANALYSIS) -o $@

$(EXECUTABLE_GEN): $(OBJECTS_GEN)
	$(CC) -lm $(OBJECTS_GEN) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE_ANALYSIS) $(OBJECTS_ANALYSIS) $(EXECUTABLE_GEN) $(OBJECTS_GEN)
