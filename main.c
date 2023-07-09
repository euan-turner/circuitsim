#include <stdio.h>

#include "circuit.h"
#include "config.h"
#include "evaluate.h"
#include "logicgate.h"
#include "typedefs.h"

int main(int argc, char *argv[]) {
  char *filepath = argv[argc - 1];
  circuit circ = read_config(filepath, ALL);
  printf("Read Complete\n");

  eval_circuit(circ, ALL);

  free_circuit(circ);
  return 0;
}