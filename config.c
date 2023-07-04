#include <assert.h>
#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "circuit.h"
#include "config.h"
#include "logicgate.h"
#include "symboltable.h"
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

/**
 * @brief Allocates a 2D array, along with 1D array of row pointers
 * 
 * @return char** 
 */
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

/**
 * @brief Wrapper for regex matching
 * 
 * @param str string to match
 * @param regex_exp POSIX regex string
 * @return true if matched
 * @return false otherwise
 */
bool matches_regex(char *str, char *regex_exp) {
  regex_t regex;
  int ret = regcomp(&regex, regex_exp, REG_EXTENDED);
  if (ret) {
    fprintf(stderr, "Could not compile regex.\n");
    return false;
  }
  ret = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);
  return !ret;
}

logic_input *parse_inputs(char **lines, int num_inputs) {
  logic_input *inputs = malloc(sizeof(logic_input) * num_inputs);
  for (int i = 0; i < num_inputs; i++) {
    char *line = lines[i];
    char *label = strtok(line, " ");
    char *val = strtok(NULL, " ");
    assert(val != NULL);
    int value = atoi(val);
    inputs[i] = create_input(value);
    add(inputs[i], label);
  }
  return inputs;
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
    char *line = lines[line_num];
    clean_line(line);
    // Improve to use REGEX
    if (matches_regex(line, "(^I[0-9]+ [1|0]$)")) {
      num_inputs++;
    } else if (matches_regex(line, "(^O[0-9]+ (AND|OR|NOT|XOR|NOR|NAND)[0-9]+)")) {
      num_outputs++;
    }
    line_num++;
  }
  fclose(file);
  printf("Number of Inputs: %d\n", num_inputs);
  printf("Number of Outputs: %d\n", num_outputs);
  printf("Number of Lines: %d\n", line_num);

  // Iterate over and build inputs
  logic_input *inputs = parse_inputs(lines, num_inputs);
  // Iterate over and build main gates
  // Iterate over and build outputs
  return NULL;
}

