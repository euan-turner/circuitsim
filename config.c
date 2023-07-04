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
    int value = atoi(val);
    inputs[i] = create_input(value);
    add(inputs[i], label);
  }
  return inputs;
}

void parse_gates(char **lines, int num_gates) {
  for (int i = 0; i < num_gates; i++) {
    char *line = lines[i];
    char *label = strtok(line, " ");
    char *input1 = strtok(NULL, " ");
    char *input2 = strtok(NULL, " ");
    if (input2 == NULL) {
      // Case of NOT gate with only 1 input
      input2 = input1;
    }
    logic_gate i1 = lookup(input1);
    assert(i1 != NULL); // No forward referencing
    logic_gate i2 = lookup(input2);
    assert(i2 != NULL);
    char *op = strdup(label);
    for (char *s = op + strlen(op) - 1; isdigit(*s); s--) {
      *s = '\0';
    }
    logic_gate gate = create_gate(i1, i2, match_op(op));
    add(gate, label);
  }
}

logic_output *parse_outputs(char **lines, int num_outputs) {
  logic_output *outputs = malloc(sizeof(logic_output) * num_outputs);
  for (int i = 0; i < num_outputs; i++) {
    char *line = lines[i];
    char *label = strtok(line, " ");
    char *gate_label = strtok(NULL, " ");
    logic_gate gate = lookup(gate_label);
    outputs[i] = create_output(gate);
    add(outputs[i], label);
  }
  return outputs;
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
  parse_gates(lines + num_inputs, line_num - num_inputs - num_outputs);
  // Iterate over and build outputs
  logic_output *outputs = parse_outputs(lines + line_num - num_outputs, num_outputs);
  circuit circ = create_circuit(num_inputs, inputs, num_outputs, outputs);
  return circ;
}

