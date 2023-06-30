# Propositional Circuit Configuration Format

## Inputs

Inputs are specified in the form ```I# [1|0]```
For example, ```I1 1``` is the first input, of value 1, and ```I2 0``` is the second input of value 0.

To test a circuit on all possible combinations of inputs, inputs still need to be specified as ```I#```, but their value need not be defined.
The ```-a``` flag will indicate the all possible inputs should be tested. These will then be enumerated in the output.

## Gates

The available gates to use are:

- AND
- OR
- NOT
- XOR
- NOR
- NAND

Gates are specified in the form ```type# input1 input2```

For example, ```AND1 I1 I2``` is the first AND gate, taking inputs from the first and second inputs to the circuit.
```OR1 AND1 I3``` is the first OR gate, taking inputs from the first AND gate and third input.
NOT gates only have one input, so can be written as ```NOT# input1```.

## Outputs

Logic gates defined earlier in the configuration file can be marked as circuit outputs.

Outputs are specified in the form ```O# gate```

For example, ```01 OR1``` marks the first OR gate as the first output of the circuit.

## Layout

All circuit inputs should be defined first.
Then all logic gates should be defined, in such a way that a logic gate is only defined where both of its inputs are previously defined.
Finally, all circuit outputs should be defined.
Configurations should be written in a ```.txt``` file, where the relative path to the file will be passed as a command-line argument to the program.

## Examples

The examples sub-directory is aptly named. So far it contains:

- A 2-input multiplexer
