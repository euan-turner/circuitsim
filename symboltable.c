#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "symboltable.h"
#include "typedefs.h"

#define HASHSIZE 51

typedef struct symbol_entry *symbol_entry;
struct symbol_entry {
  symbol_entry next;
  char *label;
  logic_gate gate;
};

symbol_entry SYMTAB[HASHSIZE];

static uint64_t hash(char *s) {
  uint64_t hash;
  for (hash = 0; *s != '\0'; s++) {
    hash = *s + 31 * hash;
  }
  return hash % HASHSIZE;
}

logic_gate lookup(char *label) {
  symbol_entry se;
  for (se = SYMTAB[hash(label)]; se != NULL; se = se->next) {
    if (strcmp(label, se->label) == 0) {
      return se->gate;
    }
  }
  return NULL;
}

void add(logic_gate gate, char *label) {
  assert(lookup(label) == NULL);
  symbol_entry se = malloc(sizeof(struct symbol_entry));
  assert(se != NULL);
  se->label = strdup(label);
  assert(se->label != NULL);
  uint64_t h = hash(label);
  se->next = SYMTAB[h];
  se->gate = gate;
  SYMTAB[h] = se;
}


void free_symbol_entry(symbol_entry se) {
  if (se != NULL) {
    free(se->next);
    free(se->label);
    se->gate = NULL;
    free(se);
  }
}
/**
 * @brief Frees memory allocated for symbol table
 * @note Does not free logic gates as these will be reused
 * 
 */
void free_symbol_table() {
  for (int i = 0; i < HASHSIZE; i++) {
    free_symbol_entry(SYMTAB[i]);
  }
}

