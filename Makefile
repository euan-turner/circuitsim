CC	= gcc
CFLAGS	= -Wall -g
BUILD = logicgate

all: $(BUILD)

clean:
	/bin/rm -f *.o $(BUILD)
	
logicgate: logicgate.o
