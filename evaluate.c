#include <stdbool.h>
#include <stdio.h>

#include "evaluate.h"
#include "logicgate.h"
#include "typedefs.h"

/**
 * @brief Recursively evaluates a gate
 * 
 * @param gate 
 */
static void eval_gate(logic_gate gate) {
  if (!gate->defined) {
    eval_gate(gate->input1);
    eval_gate(gate->input2);
    gate->value = (*gate->op)(gate->input1->value, gate->input2->value);
    gate->defined = true;
  }
}

static void undef_gate(logic_gate gate) {
  if (!(gate->input1 == NULL)) {
    gate->defined = false;
    undef_gate(gate->input1);
    undef_gate(gate->input2);
  }
}

/**
 * @brief Prints the inputs and outputs of a circuit
 * 
 * @param circ 
 */
static void log_circuit(circuit circ) {
  printf("Inputs:\n");
  for (int i = 0; i < circ->num_inputs; i++) {
    printf("%s - %s\n", circ->inputs[i]->label, circ->inputs[i]->value ? "TRUE" : "FALSE");
  }
  printf("Outputs:\n");
  for (int i = 0; i < circ->num_outputs; i++) {
    printf("%s - %s\n", circ->outputs[i]->label, circ->outputs[i]->gate->value ? "TRUE" : "FALSE");
  }
}

/**
 * @brief Evaluates a circuit in the GIVEN mode
 * 
 * @param circ 
 * @pre All gate inputs have a defined value
 */
static void eval_given_circuit(circuit circ) {
  for (int i = 0; i < circ->num_inputs; i++) {
    assert(circ->inputs[i]->defined);
  }
  for (int i = 0; i < circ->num_outputs; i++) {
    eval_gate(circ->outputs[i]->gate);
  }
  log_circuit(circ);
}

static void eval_all_circuit(circuit circ) {
  for (int i = 0; i < (1 << circ->num_inputs); i++) {
    for (int i = 0; i < circ->num_outputs; i++) {
      undef_gate(circ->outputs[i]->gate);
    }
    // The first circ->num_inputs of i represent the logical values to assign
    for (int j = 0; j < circ->num_inputs; j++) {
      bool val = (i >> j) & 1;
      logic_input input = circ->inputs[j];
      def_input(input, val);
    }
    printf("%d:\n", i);
    eval_given_circuit(circ);
    printf("\n");
  }
}

void eval_circuit(circuit circ, input_type itype) {
  switch (itype) {
    case GIVEN:
      eval_given_circuit(circ);
      break;
    case ALL:
      eval_all_circuit(circ);
  }
}