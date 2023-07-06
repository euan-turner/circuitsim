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

#define INPUT_REGEX "(^I[0-9]+ [1|0]$)"
#define OUTPUT_REGEX "(^O[0-9]+ (AND|OR|NOT|XOR|NOR|NAND)[0-9]+)"

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
  memmove(line, line + num_leading, sizeof(char) * (strlen(line) - num_leading));
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
  assert(lines != NULL);
  lines[0] = malloc(sizeof(char) * MAX_LINE_LENGTH * MAX_NUM_LINES);
  assert(lines[0] != NULL);
  for (int i = 1; i < MAX_NUM_LINES; i++) {
    lines[i] = lines[i - 1] + MAX_LINE_LENGTH;
  }
  return lines;
}

/**
 * @brief Frees memory associated with 2-D line buffer
 * 
 * @param lines 
 */
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

/**
 * @brief Parses input gates
 * 
 * @param lines 
 * @param num_inputs 
 * @return logic_input* Array of logic_input gates
 */
static logic_input *parse_inputs(char **lines, int num_inputs) {
  logic_input *inputs = malloc(sizeof(logic_input) * num_inputs);
  for (int i = 0; i < num_inputs; i++) {
    char *line = lines[i];
    char *label = strtok(line, " ");
    char *val = strtok(NULL, " ");
    inputs[i] = create_input(atoi(val), label);
    add(inputs[i], label);
  }
  return inputs;
}

/**
 * @brief Parses regular logic gates
 * 
 * @param lines 
 * @param num_gates 
 * @pre All required input gates already defined
 */
static void parse_gates(char **lines, int num_gates) {
  for (int i = 0; i < num_gates; i++) {
    char *line = lines[i];
    char *label = strtok(line, " ");
    char *input1 = strtok(NULL, " ");
    char *input2 = strtok(NULL, " ");

    logic_gate i1 = lookup(input1);
    assert(i1 != NULL); // No forward referencing
    i1->fan_out++;

    logic_gate i2;
    if (input2 == NULL) {
      // Case of NOT gate - duplicate input
      i2 = i1;
    } else {
      i2 = lookup(input2);
      assert(i2 != NULL);
      i2->fan_out++;
    }
    
    char *op = strdup(label);
    for (char *s = op + strlen(op) - 1; isdigit(*s); s--) {
      *s = '\0';
    }
    logic_gate gate = create_gate(i1, i2, match_op(op), label);
    free(op);
    add(gate, label);
  }
}

/**
 * @brief Parses output gates
 * 
 * @param lines 
 * @param num_outputs 
 * @return logic_output* 
 */
static logic_output *parse_outputs(char **lines, int num_outputs) {
  logic_output *outputs = malloc(sizeof(logic_output) * num_outputs);
  for (int i = 0; i < num_outputs; i++) {
    char *line = lines[i];
    char *label = strtok(line, " ");
    char *gate_label = strtok(NULL, " ");
    logic_gate gate = lookup(gate_label);
    gate->fan_out++;
    outputs[i] = create_output(gate, label);
  }
  return outputs;
}

/**
 * @brief Builds a circuit from a config file
 * 
 * @param filename Path to config file
 * @param itype GIVEN if inputs defined, ALL if inputs undefined
 * @return circuit 
 */
circuit read_config(char *filename, input_type itype) {
  FILE *file = fopen(filename, "r");
  assert(file != NULL);
  char **lines = make_line_buffer();
  // Indexing is into characters, not lines
  int line_num = 0;
  int num_inputs = 0;
  int num_outputs = 0;
  // Read in file and count number of inputs/outputs
  while (fgets(lines[line_num], MAX_LINE_LENGTH, file) != NULL) {
    // EOF not reached
    char *line = lines[line_num];
    clean_line(line);
    // Improve to use REGEX
    if (matches_regex(line, INPUT_REGEX)) {
      num_inputs++;
    } else if (matches_regex(line, OUTPUT_REGEX)) {
      num_outputs++;
    }
    line_num++;
  }
  fclose(file);

  logic_input *inputs = parse_inputs(lines, num_inputs);
  parse_gates(lines + num_inputs, line_num - num_inputs - num_outputs);
  logic_output *outputs = parse_outputs(lines + line_num - num_outputs, num_outputs);

  circuit circ = create_circuit(num_inputs, inputs, num_outputs, outputs);
  
  free_line_buffer(lines);
  free_symbol_table();
  return circ;
}

