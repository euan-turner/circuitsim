#include <stdlib.h> 
#include "logicgate.h"

struct circuit {
  logic_input inputs;
  int num_inputs;
  logic_output outputs;
  int num_outputs;
}

/**
 * @brief Create a circuit object
 * 
 * @param num_inputs 
 * @param num_outputs 
 * @return circuit 
 */
circuit create_circuit(int num_inputs, int num_outputs) {
  circuit circ = malloc(sizeof(struct circuit));
  assert(circ != NULL);
  circ->inputs = malloc(sizeof(struct logic_input) * num_inputs);
  assert(circ->inputs != NULL);
  circ->num_inputs = num_inputs;
  circ->outputs = malloc(sizeof(struct logic_output) * num_outputs);
  assert(circ->outputs != NULL);
  circ->num_outputs = num_outputs;
  return circ;
}

/**
 * @brief Frees all memory associated with a circuit
 * 
 * @param circ 
 */
void free_circuit(circuit circ) {
  free(circ->inputs);
  free(circ->outputs);
  free(circ);
}