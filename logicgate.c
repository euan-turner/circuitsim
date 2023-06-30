#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "logicgate.h"

typedef bool (*logic_op)(bool val1, bool val2);

typedef struct gate_input *gate_input;

typedef union {
  logic_gate gate;
  logic_input input;
} gate_input_u;

typedef enum { INPUT, GATE } gate_input_t;

struct gate_input {
  gate_input_u input_u;
  gate_input_t input_t;
}

/**
 * @brief Represents a logic gate, with a logic operator function pointer
 * @note Single-input NOT gates will have the second input as NULL
 */
struct logic_gate {
  gate_input input1;
  gate_input input2;
  logic_op op;
};

/**
 * @brief Represents a logic input to a circuit
 * 
 */
struct logic_input {
  bool input;
};

logic_input create_input(bool value) {
  logic_input input = malloc(sizeof(struct logic_input));
  assert(input != NULL);
  input->input = value;
  return input;
}

/**
 * @brief Represents a logic output from a circuit
 * 
 */
struct logic_output {
  logic_gate gate;
};

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
  assert(val2 == NULL);
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

int main(void) {
  printf("Main\n");
  return 0;
}