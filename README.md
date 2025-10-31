# Lab 7 Vector Calculator
This is a vector calculator, it can save and load 3 dimension vectors and do addition, Subtraction, and scalar multiplication.

## Build instructions
 - if you have make installed, build by running make in your terminal
 - otherwise, run gcc -o vectorcalc main.c vec_util.c vecmath.c

## Running
 - Run the command with a -h or -help flag to get this help message


#### Commands
- list — List all stored vectors
- clear — Clear all stored vectors
- quit — Exit the program
#### Vector Operations
- A = 1.0 2.0 3.0 — Create or overwrite vector A
- A — Display vector A
- A = B + C — Add vectors
- A = B - C — Subtract vectors
- A = 2 * B or A = B * 2 — Scalar multiply

## Dynamic Memory
This caclulator stores the vectors by having an initial allocation for 10 vectors, then increasing the allocation by 1 with realloc every time a new vector above 10 is added. The memory is then freed at any program exit.