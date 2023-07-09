#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdbool.h>

typedef bool (*logic_op)(bool val1, bool val2);

typedef struct logic_gate *logic_gate;
typedef struct logic_gate *logic_input;
struct logic_gate {
  bool value;
  bool defined;
  char *label;
  logic_gate input1;
  logic_gate input2;
  logic_op op;
  int fan_out;
};

typedef struct logic_output *logic_output;
struct logic_output {
  char *label;
  logic_gate gate;
};

typedef struct circuit *circuit;
struct circuit {
  int num_inputs;
  int num_outputs;
  logic_input *inputs;
  logic_output *outputs;
};

typedef enum { GIVEN, ALL } input_type;

#endif /* TYPEDEFS_H */