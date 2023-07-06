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

/**
 * @brief Hashes a key for the symbol table
 * 
 * @param s 
 * @return uint64_t 
 */
static uint64_t hash(char *s) {
  uint64_t hash;
  for (hash = 0; *s != '\0'; s++) {
    hash = *s + 31 * hash;
  }
  return hash % HASHSIZE;
}

/**
 * @brief Looks up an entry in the symbol table
 * 
 * @param label 
 * @return logic_gate 
 */
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

/**
 * @brief Adds an entry to the symbol table
 * 
 * @param gate 
 * @param label 
 */
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

/**
 * @brief Frees a single symbol table entry
 * 
 * @param se 
 */
static void free_symbol_entry(symbol_entry se) {
  if (se != NULL) {
    free_symbol_entry(se->next);
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

