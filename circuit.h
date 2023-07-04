#include "logicgate.h"
typedef struct circuit *circuit;

circuit create_circuit(int num_inputs, logic_input *inputs, int num_outputs, logic_output *outputs);

void free_circuit(circuit circ);