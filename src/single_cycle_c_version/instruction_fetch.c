#include <stdlib.h>
#include <stdio.h>
#include "instructions.h"

// A function to return the instruction based on the program counter
void instruction_fetch(struct instruction_memory *instruct, int pc, int* instruction){
	int i;
	for (i = 0; i < 32; i++) {
		instruction[i] = instruct->instructions_array[pc][i];
	}
}
