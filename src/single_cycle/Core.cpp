#include "Core.h"

Core::Core(const string &fname, ofstream *out) : out(out), 
						clk(0), 
						PC(0),
						instr_mem(new Instruction_Memory(fname))
{

}

bool Core::tick()
{
	/*
		Step One: Serving pending instructions
	*/
	

	/*
		Step Two: Serve new instruction
	*/
	// Get Instruction
	Instruction &instruction = instr_mem->get_instruction(PC);

	// Increment PC
	PC += 4;

	// We are reaching the last instruction
	if (PC > instr_mem->last_addr())
	{
		return false;
	}
	else
	{
		return true;
	}
}