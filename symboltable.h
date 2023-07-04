#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "typedefs.h"

void add(logic_gate gate, char *label);
logic_gate lookup(char *label);
void add_output(logic_output output, char *label);
logic_output lookup_output(char *label);
void free_symbol_table();


#endif /* SYMBOLTABLE_H */