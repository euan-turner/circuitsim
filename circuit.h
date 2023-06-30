typedef struct circuit *circuit;

circuit create_circuit(int num_inputs, int num_outputs);

void free_circuit(circuit circ);