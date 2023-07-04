#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <stdbool.h>

#include "typedefs.h"


typedef bool (*logic_op)(bool val1, bool val2);

logic_op match_op(char *op);

logic_gate create_gate(logic_gate input1, logic_gate input2, logic_op op);

logic_input create_input(bool value);

logic_output create_output(logic_gate gate);

void free_gate(logic_gate gate);

void free_input(logic_input input);

void free_output(logic_output output);

#endif /* LOGICGATE_H */