#include <stdio.h>

#include "circuit.h"
#include "config.h"
#include "logicgate.h"
#include "typedefs.h"

int main(void) {
  printf("Main\n");
  circuit circ = read_config("./examples/mx.txt", GIVEN);
  printf("Read Complete\n");
  for (int i = 0; i < circ->num_inputs; i++) {
    printf("Input: %s\n", circ->inputs[i]->label);
  }
  for (int i = 0; i < circ->num_outputs; i++) {
    printf("Output: %s\n", circ->outputs[i]->label);
  }
  return 0;
}