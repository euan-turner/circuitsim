#include "evaluate.h"
#include "typedefs.h"

static void eval_gate(logic_gate gate) {
  if (!gate->defined) {
    eval_gate(gate->input1);
    eval_gate(gate->input2);
    gate->value = (*gate->op)(gate->input1->value, gate->input2->value);
    gate->defined = true;
  }
}

/**
 * @brief Evaluates a circuit in the GIVEN mode
 * 
 * @param circ 
 * @pre All gate inputs have a defined value
 */
void eval_circuit(circuit circ) {
  for (int i = 0; i < circ->num_outputs; i++) {
    eval_gate(circ->outputs[i]->gate);
  }
}