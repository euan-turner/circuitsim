# Propositional Circuit Configuration Format

## Inputs

Inputs may either be given a defined value, or just marked as existing. (The GIVEN and ALL modes respectively).
Given inputs are specified in the form ```I-label [1|0]``` (POSIX regex is ```(^IN-[[:alnum:]]+ [1|0]$)```)
For example, ```IN-a 1``` is an input, of value 1, and ```IN-b 0``` is an input, of value 0.
Otherwise, inputs are specified in the form ```I-label``` (POSIX regex is ```(^IN-[[:alnum:]]+$)```)

If the ALL mode is to be used, the ```-a``` flag should be used from the command line. The filepath to the config file should always be last.

## Gates

The available gates to use are:

- AND
- OR
- NOT
- XOR
- NOR
- NAND

Gates are specified in the form ```type# input1 input2``` (POSIX regex to match the gate type is ```(^(AND|OR|NOT|XOR|NOR|NAND)[0-9]+)```)

For example, ```AND1 I1 I2``` is the first AND gate, taking inputs from the first and second inputs to the circuit.
```OR1 AND1 I3``` is the first OR gate, taking inputs from the first AND gate and third input.
NOT gates only have one input, so can be written as ```NOT# input1```.

## Outputs

Logic gates defined earlier in the configuration file can be marked as circuit outputs.

Outputs are specified in the form ```O-label gate``` (POSIX regex for the initial output part is ```(^OUT-[[:alnum:]]+)```. Note that an input label may be used as the gate for an output if desired).

For example, ```OUT-res OR1``` marks the first OR gate as the ```res``` output of the circuit.

## Layout

All circuit inputs should be defined first.
Then all logic gates should be defined, in such a way that a logic gate is only defined where both of its inputs are previously defined.
Finally, all circuit outputs should be defined.
Configurations should be written in a ```.txt``` file, where the relative path to the file will be passed as a command-line argument to the program.

## Examples

The examples sub-directory is aptly named. So far it contains:

- A 2-input multiplexer with defined inputs
- A 2-input multiplexer with undefined inputs
- A 1-input decoder with defined inputs
- A 1-input decoder with undefined inputs
- A half-adder with undefined inputs
