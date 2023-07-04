#include <stdbool.h>

#include "typedefs.h"


typedef bool (*logic_op)(bool val1, bool val2);

logic_gate create_gate(logic_gate input1, logic_gate input2, logic_op op);

logic_gate create_input(bool value);

void free_gate(logic_gate gate);

void free_input(logic_input input);