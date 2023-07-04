#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef struct logic_gate *logic_gate;
typedef struct logic_gate *logic_input;
typedef struct logic_output *logic_output;

typedef struct circuit *circuit;

typedef enum { GIVEN, ALL } input_type;

#endif /* TYPEDEFS_H */