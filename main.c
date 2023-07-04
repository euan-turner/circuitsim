#include <stdio.h>

#include "circuit.h"
#include "config.h"
#include "logicgate.h"
#include "typedefs.h"

int main(void) {
  printf("Main\n");
  read_config("./examples/mx.txt", GIVEN);
  printf("Read Complete\n");
  return 0;
}