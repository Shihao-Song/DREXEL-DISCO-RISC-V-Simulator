#include "Core.h"

Core::Core()
{
	// Print pre-coded instruction
	bitset<32> ins(instruction);
	cout << "Simulaing Instruction: " << ins << endl;

	// Initialize register file and data memory
	data_mem = (uint8_t *)calloc(SIZE_OF_MEM, sizeof(uint8_t));
	data_mem[0] = 254;
	data_mem[1] = 255;
	data_mem[2] = 255;
	data_mem[3] = 255;
	data_mem[4] = 255;
	data_mem[5] = 255;
	data_mem[6] = 255;
	data_mem[7] = 255;
	
	regs = (int64_t *)calloc(NUM_OF_REGS, sizeof(int64_t));

}

bool Core::tick()
{
	// Step One: What is the instruction?
	
	// Step Two: Extract registers, immediate from the instruction.
		
	// Step Three: How do you calculate memory location?
	
	// Step Four: Time to load from memory to register.

	return true;
}

void Core::printResult()
{
	cout << "x9: " << regs[9] << endl;
}
