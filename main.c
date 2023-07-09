#include <stdio.h>

#include "circuit.h"
#include "config.h"
#include "evaluate.h"
#include "logicgate.h"
#include "typedefs.h"

int main(int argc, char *argv[]) {
  char *filepath = argv[argc - 1];
  circuit circ = read_config(filepath, GIVEN);
  printf("Read Complete\n");
  printf("Inputs:\n");
  for (int i = 0; i < circ->num_inputs; i++) {
    printf("%s - %s\n", circ->inputs[i]->label, circ->inputs[i]->value ? "TRUE" : "FALSE");
  }

  eval_circuit(circ);

  printf("Outputs:\n");
  for (int i = 0; i < circ->num_outputs; i++) {
    printf("%s - %s\n", circ->outputs[i]->label, circ->outputs[i]->gate->value ? "TRUE" : "FALSE");
  }

  free_circuit(circ);
  return 0;
}