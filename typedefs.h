#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdbool.h>

typedef bool (*logic_op)(bool val1, bool val2);

typedef struct logic_gate *logic_gate;
typedef struct logic_gate *logic_input;
struct logic_gate {
  logic_gate input1;
  logic_gate input2;
  logic_op op;
  bool value;
  bool defined;
  char *label;
};

typedef struct logic_output *logic_output;
struct logic_output {
  logic_gate gate;
  char *label;
};

typedef struct circuit *circuit;
struct circuit {
  logic_input *inputs;
  int num_inputs;
  logic_output *outputs;
  int num_outputs;
};

typedef enum { GIVEN, ALL } input_type;

#endif /* TYPEDEFS_H */