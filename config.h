#include "circuit.h"

#define MAX_LINE_LENGTH 30

typedef enum { GIVEN, ALL } input_type;

circuit read_config(char *filename, input_type itype);