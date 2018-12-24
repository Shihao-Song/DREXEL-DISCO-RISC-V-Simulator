#include "Core.h"

Core::Core(const string &fname, ofstream *out) : out(out), 
						clk(0), 
						PC(0),
						instr_mem(new Instruction_Memory(fname))
{

}

bool Core::tick()
{
	// Get Instruction
	Instruction &instruction = instr_mem->get_instruction(PC);

	bitset<32> test(instruction.instruction);

	cout << test << endl;

	// Increment PC
	PC += 4;

	if (PC > instr_mem->last_addr())
	{
		return false;
	}
	else
	{
		return true;
	}
}
