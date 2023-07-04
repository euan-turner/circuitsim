#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "circuit.h"
#include "logicgate.h"
#include "typedefs.h"

struct circuit {
  logic_input *inputs;
  int num_inputs;
  logic_output *outputs;
  int num_outputs;
};

/**
 * @brief Create a circuit object
 * 
 * @param num_inputs 
 * @param inputs Base pointer to array of pointers to heap-allocated input gates
 * @param num_outputs 
 * @param outputs Base pointer to array of pointers to heap-allocated output gates
 * @return circuit 
 */
circuit create_circuit(int num_inputs, logic_input *inputs, int num_outputs, logic_output *outputs) {
  circuit circ = malloc(sizeof(struct circuit));
  assert(circ != NULL);
  circ->inputs = malloc(sizeof(logic_input) * num_inputs);
  assert(circ->inputs != NULL);
  memcpy(circ->inputs, inputs, sizeof(logic_input) * num_inputs);
  circ->num_inputs = num_inputs;
  circ->outputs = malloc(sizeof(logic_output) * num_outputs);
  assert(circ->outputs != NULL);
  memcpy(circ->outputs, outputs, sizeof(logic_output) * num_outputs);
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

int main(void) {
  printf("Main\n");
  return 0;
}