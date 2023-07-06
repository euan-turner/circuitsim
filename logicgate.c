#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logicgate.h"
#include "typedefs.h"

/**
 * @brief Allocates and checks pointer for a logic_gate
 * 
 * @return logic_gate 
 */
static logic_gate alloc_gate() {
  logic_gate gate = malloc(sizeof(struct logic_gate));
  assert(gate != NULL);
  return gate;
}

/**
 * @brief Create a gate object
 * 
 * @param input1 
 * @param input2 
 * @param op 
 * @param label 
 * @return logic_gate 
 */
logic_gate create_gate(logic_gate input1, logic_gate input2, logic_op op, char *label) {
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(op != NULL);
  logic_gate gate = alloc_gate();
  gate->input1 = input1;
  gate->input2 = input2;
  gate->op = op;
  gate->defined = false;
  gate->label = strdup(label);
  assert(gate->label != NULL);
  return gate;
}

/**
 * @brief Create an input object
 * 
 * @param value 
 * @param label 
 * @return logic_input 
 */
logic_input create_input(bool value, char *label) {
  logic_gate gate = alloc_gate();
  gate->input1 = NULL;
  gate->input2 = NULL;
  gate->op = NULL;
  gate->value = value;
  gate->defined = true;
  gate->label = strdup(label);
  assert(gate->label != NULL);
  return gate;
}

/**
 * @brief Create an output object
 * 
 * @param gate 
 * @param label 
 * @return logic_output 
 */
logic_output create_output(logic_gate gate, char *label) {
  logic_output output = malloc(sizeof(struct logic_output));
  assert(output != NULL);
  output->gate = gate;
  output->label = strdup(label);
  assert(output->label != NULL);
  return output;
}

/**
 * @brief Frees a logic_gate
 * 
 * @param gate 
 */
void free_gate(logic_gate gate) {
  if (gate->input1 != NULL) {
    free_gate(gate->input1);
    if (gate->input1 == gate->input2) {
      gate->input2 = NULL; // deal with case of NOT
    } // need to deal with issue of gate already being freed by some other parent gate
    gate->input1 = NULL;
  }
  if (gate->input2 != NULL) {
    free_gate(gate->input2);
    gate->input2 = NULL;
  }
  gate->op = NULL;
  free(gate->label);
  free(gate);
}

/**
 * @brief Frees an input
 * 
 * @param input 
 * @note May be redundant, free_gate likely sufficient
 */
void free_input(logic_input input) {
  free(input->label);
  free(input);
}

/**
 * @brief Frees an output
 * 
 * @param output 
 */
void free_output(logic_output output) {
  if (output->gate != NULL) {
    free_gate(output->gate);
    output->gate = NULL;
  }
  free(output->label);
  free(output);
}

// Logic Operators
#define NUM_OPS 6
/**
 * @brief Performs logic-and
 * 
 * @param val1 
 * @param val2 
 * @return true val1 && val2
 * @return false !(val1 && val2)
 */
bool and(bool val1, bool val2) {
  return val1 && val2;
}

/**
 * @brief Performs logic-or
 * 
 * @param val1 
 * @param val2 
 * @return true val1 || val2
 * @return false !(val1 || val2)
 */
bool or(bool val1, bool val2) {
  return val1 || val2;
}

/**
 * @brief Performs logic-not
 * 
 * @param val1 
 * @param val2 
 * @return true !val1
 * @return false !val2
 * @pre val2 == val1
 */
bool not(bool val1, bool val2) {
  assert(val2 == val1);
  return !val1;
}

/**
 * @brief Performs logic-xor
 * 
 * @param val1 
 * @param val2 
 * @return true val1 xor val2
 * @return false !(val1 xor val2)
 */
bool xor(bool val1, bool val2) {
  return val1 != val2;
}

/**
 * @brief Performs logic-nor
 * 
 * @param val1 
 * @param val2 
 * @return true !(val1 || val2)
 * @return false val1 || val2
 */
bool nor(bool val1, bool val2) {
  return !or(val1, val2);
}

/**
 * @brief Performs logic-nand
 * 
 * @param val1 
 * @param val2 
 * @return true !(val1 && val2)
 * @return false val1 && val2
 */
bool nand(bool val1, bool val2) {
  return !and(val1, val2);
}

/**
 * @brief Matches a string binary op to its function pointer
 * 
 * @param op 
 * @return logic_op 
 */
logic_op match_op(char *op) {
  char *ops[NUM_OPS] = { "AND", "OR", "NOT", "XOR", "NOR", "NAND" };
  logic_op lops[NUM_OPS] = { &and, &or, &not, &xor, &nor, &nand };
  for (int i = 0; i < NUM_OPS; i++) {
    if (strcmp(op, ops[i]) == 0) {
      return lops[i];
    }
  }
  return NULL;
}