#include "Core.h"

Core::Core(const string &fname, ofstream *out) : out(out), 
						clk(0), 
						PC(0),
						instr_mem(new Instruction_Memory(fname))
{

}

/*
	TODO - Add more functions and modify tick() to simulate single-cycle RISC-V architecture
*/
bool Core::tick()
{
	/*
		Step One: Serving pending instructions
	*/
	if (pending_queue.size() > 0)
	{
		serve_pending_instrs();
	}

	/*
		Step Two: Where simulation happens
	*/
	// Get Instruction
	Instruction &instruction = instr_mem->get_instruction(PC);

	// Increment PC
	PC += 4;

	/*
		Step Three: Simulator related
	*/
	instruction.begin_exe = clk;
	instruction.end_exe = clk + 1; // Single-cycle always takes one clock cycle to complete
	pending_queue.push_back(instruction);

	clk++;

	/*
		Step Four: Should we shut down simulation
	*/
	// Are we reaching the last instruction
	if (PC > instr_mem->last_addr())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Core::serve_pending_instrs()
{
	list<Instruction>::iterator instr = pending_queue.begin();

	if (instr->end_exe <= clk)
	{
		printStats(instr);
		
		pending_queue.erase(instr);	
	}
}

void Core::printStats(list<Instruction>::iterator &ite)
{
	*out << "<" << ite->raw_instr << ">,";
	*out << id << ",";
	*out << ite->begin_exe << ",";
	*out << ite->end_exe << endl;
}

