#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "typedefs.h"

void add(logic_gate gate, char *label);
logic_gate lookup(char *label);
void free_symbol_table();


#endif /* SYMBOLTABLE_H */