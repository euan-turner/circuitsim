#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "logicgate.h"

typedef bool (*logic_op)(bool val1, bool val2);

/**
 * @brief Represents a logic gate, with a logic operator function pointer
 * @note Single-input NOT gates will have the input duplicated for consistency
 */
struct logic_gate {
  logic_gate input1;
  logic_gate input2;
  logic_op op;
};

/**
 * @brief Represents a logic input to a circuit
 * 
 */
struct logic_input {
  bool input;
};

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
 * @pre val1 == val2
 */
bool not(bool val1, bool val2) {
  assert(val1 == val2);
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