#include "IF_Stage.h"

IF_Stage::IF_Stage(const string &fname, Core *core) : instr_mem(new Instruction_Memory(fname)), 
							PC(0),
							core(core)
{

}

bool IF_Stage::tick()
{
	if (PC <= instr_mem->last_addr())
        {
                // Get Instruction
                Instruction &instruction = instr_mem->get_instruction(PC);

                // Increment PC
                // TODO, PC should be incremented or decremented based on instruction
                PC += 4;

                /*
                	Simulator related
                */
                instruction.begin_exe = core->clk;

                // Initialize end execution time to 5 clock cycles, adjust it
		// in the run time
		instruction.end_exe = core->clk + 5;

		// Push instruction into queue;
		(core->pending_queue).push_back(instruction);
		instr = (core->pending_queue).end();
		instr--;

		return true;
        }

	return false;
}
