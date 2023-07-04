CC	= gcc
CFLAGS	= -Wall -g
BUILD = circuit

all: $(BUILD)

clean:
	/bin/rm -f *.o $(BUILD)

circuit: circuit.o

circuit.o: logicgate.h typedefs.h

logicgate.o:	typedefs.h