#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "logicgate.h"
#include "typedefs.h"

/**
 * @brief Represents a logic gate, with a logic operator function pointer
 * @note Single-input NOT gates will have the second input as NULL
 * @note Circuit inputs will have NULL gate inputs and logic op, but will be immediately defined.
 * All other gates will not be defined initially
 */
struct logic_gate {
  logic_gate input1;
  logic_gate input2;
  logic_op op;
  bool value;
  bool defined;
};

/**
 * @brief Represents a logic output from a circuit
 * 
 */
struct logic_output {
  logic_gate gate;
};

static logic_gate alloc_gate() {
  logic_gate gate = malloc(sizeof(struct logic_gate));
  assert(gate != NULL);
  return gate;
}

/**
 * @brief Create a gate object, with defined set to false
 * 
 * @param input1 
 * @param input2 
 * @param op 
 * @return logic_gate 
 */
logic_gate create_gate(logic_gate input1, logic_gate input2, logic_op op) {
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(op != NULL);
  logic_gate gate = alloc_gate();
  gate->input1 = input1;
  gate->input2 = input2;
  gate->op = op;
  gate->defined = false;
  return gate;
}

/**
 * @brief Create a gate object for a circuit input, with a defined value
 * 
 * @param value 
 * @return logic_input
 */
logic_input create_input(bool value) {
  logic_gate gate = alloc_gate();
  gate->value = value;
  gate->defined = true;
  return gate;
}

void free_gate(logic_gate gate) {
  gate->input1 = NULL;
  gate->input2 = NULL;
  gate->op = NULL;
  free(gate);
}

void free_input(logic_input input) {
  free(input);
}

// Logic Operators
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
 * @pre val2 == NULL
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