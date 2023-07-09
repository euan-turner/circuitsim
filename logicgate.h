#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <stdbool.h>

#include "typedefs.h"

logic_op match_op(char *op);

logic_gate create_gate(logic_gate input1, logic_gate input2, logic_op op, char *label);

logic_input create_def_input(bool value, char *label);

logic_input create_undef_input(char *label);

logic_output create_output(logic_gate gate, char *label);

void def_input(logic_input input, bool value);

void free_gate(logic_gate gate);

void free_output(logic_output output);

#endif /* LOGICGATE_H */