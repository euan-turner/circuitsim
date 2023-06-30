#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "circuit.h"
#include "config.h"
#include "logicgate.h"

/**
 * @brief Removes whitespace from the line. If the line just contains a newline,
 * replaces it with a null-terminator
 * 
 * @param line 
 * @return char* Pointer to cleand line
 */
char *clean_line(char *line) {
  assert(line != NULL);
  // Remove leading whitespace
  while (isspace(*line)) {
    line++;
  }
  // Remove trailing whitespace
  char *end = line + strlen(line) - 1;
  while (isspace(*end)) {
    *end = '\0';
    end--;
  }
  return line;
}

void read_input(char *line, circuit circ) {
  
}

circuit read_config(char *filename, input_type itype) {
  FILE *file = fopen(filename);
  assert(file != NULL);
  char *line = malloc(sizeof(char) * MAX_LINE_LENGTH);
  // TODO: Count number of inputs and outputs first
  // Then call create_circuit
  circuit circ = NULL; // here
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    // EOF not reached
    line = clean_line(line);
    // Improve to use REGEX
    if (line[0] == 'I') {

    }
  }
}

