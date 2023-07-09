#include <stdio.h>
#include <string.h>

#include "circuit.h"
#include "config.h"
#include "evaluate.h"
#include "logicgate.h"
#include "typedefs.h"

int main(int argc, char *argv[]) {
  input_type itype = GIVEN;
  if (argc >= 2) {
    // Additional arguments
    for (int i = 1; i < argc - 1; i++) {
      if (strcmp(argv[i],"-a") == 0) {
        itype = ALL;
      }
    }
  }
  char *filepath = argv[argc - 1];
  circuit circ = read_config(filepath, itype);
  printf("Read Complete\n");

  eval_circuit(circ, itype);

  free_circuit(circ);
  return 0;
}