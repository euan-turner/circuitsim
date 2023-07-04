#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "symboltable.h"
#include "typedefs.h"

#define HASHSIZE 51

typedef struct symbol_entry *symbol_entry;
typedef enum { GATE, OUTPUT } type;
typedef union { logic_gate gate; logic_output output; } entry;
struct symbol_entry {
  symbol_entry next;
  char *label;
  entry e;
  type t;
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
      assert(se->t == GATE);
      return se->e.gate;
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
  se->t = GATE;
  se->e.gate = gate;
  SYMTAB[h] = se;
}

logic_output lookup_output(char *label) {
  symbol_entry se;
  for (se = SYMTAB[hash(label)]; se != NULL; se = se->next) {
    if (strcmp(label, se->label) == 0) {
      assert(se->t == OUTPUT);
      return se->e.output;
    }
  }
  return NULL;
}
void add_output(logic_output output, char *label){
  assert(lookup_output(label) == NULL);
  symbol_entry se = malloc(sizeof(struct symbol_entry));
  assert(se != NULL);
  se->label = strdup(label);
  assert(se->label != NULL);
  uint64_t h = hash(label);
  se->next = SYMTAB[h];
  se->t = OUTPUT;
  se->e.output = output;
  SYMTAB[h] = se;
}


void free_symbol_entry(symbol_entry se) {
  if (se != NULL) {
    free(se->next);
    free(se->label);
    if (se->t == GATE) {
      se->e.gate = NULL;
    } else {
      se->e.output = NULL;
    }
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

