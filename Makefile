CC	= gcc
CFLAGS	= -Wall -g
BUILD = main

all: $(BUILD)

clean:
	/bin/rm -f *.o $(BUILD)

main: main.o circuit.o config.o logicgate.o

main.o: circuit.h config.h logicgate.h typedefs.h
circuit.o: logicgate.h typedefs.h
config.o: circuit.h logicgate.h typedefs.h
logicgate.o:	typedefs.h