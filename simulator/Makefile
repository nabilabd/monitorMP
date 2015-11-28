# Build program executable

# EXECUTABLE defines the name of the executable that will be generated
# SOURCES should include all the .c files in your project (do not include .h)

EXECUTABLE=sim_airport
SOURCES=main.c FIFOQueue.c PriorityQueue.c SimulationEngine.c Common.c

CC=gcc
CFLAGS=-c -Wall -lm
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -lm $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)
