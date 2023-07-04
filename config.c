#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circuit.h"
#include "config.h"
#include "logicgate.h"
#include "typedefs.h"

/**
 * @brief Removes leading and trailing whitespace from a string in place
 * 
 * @param line 
 */
void clean_line(char *line) {
  assert(line != NULL);
  // Remove leading whitespace
  int num_leading = 0;
  while (isspace(*line)) {
    num_leading++;
  }
  strcpy(line, line + num_leading);
  // Remove trailing whitespace
  char *end = line + strlen(line) - 1;
  while (isspace(*end)) {
    *end = '\0';
    end--;
  }
}

char **make_line_buffer() {
  char **lines = malloc(sizeof(char* ) * MAX_NUM_LINES);
  lines[0] = malloc(sizeof(char) * MAX_LINE_LENGTH * MAX_NUM_LINES);
  for (int i = 1; i < MAX_NUM_LINES; i++) {
    lines[i] = lines[i - 1] + 1;
  }
  return lines;
}

void free_line_buffer(char **lines) {
  free(lines[0]);
  free(lines);
}

circuit read_config(char *filename, input_type itype) {
  FILE *file = fopen(filename, "r");
  assert(file != NULL);
  char **lines = make_line_buffer();
  int line_num = 0;
  int num_inputs = 0;
  int num_outputs = 0;
  // Read in file and count number of inputs/outputs
  while (fgets(lines[line_num], MAX_LINE_LENGTH, file) != NULL) {
    // EOF not reached
    clean_line(lines[line_num]);
    // Improve to use REGEX
    if (lines[line_num][0] == 'I') {
      num_inputs++;
    } else if ((lines[line_num][0] == 'O') && (lines[line_num][1] != 'R')) {
      num_outputs++;
    }
    line_num++;
  }
  fclose(file);
  return NULL;
}

