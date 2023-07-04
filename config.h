#ifndef CONFIG_H
#define CONFIG_H

#include "typedefs.h"

#define MAX_LINE_LENGTH 30
#define MAX_NUM_LINES 100


circuit read_config(char *filename, input_type itype);

#endif /* CONFIG_H */