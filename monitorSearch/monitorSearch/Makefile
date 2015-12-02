# Build program executable

# EXECUTABLE defines the name of the executable that will be generated
# SOURCES should include all the .c files in your project (do not include .h)

EXECUTABLE=analyzer
SOURCES=main.c BellmanFord.c Common.c FIFOQueue.c Graph.c

CC=gcc-5
CFLAGS=-c -Wall -lm -g
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -lm $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)

