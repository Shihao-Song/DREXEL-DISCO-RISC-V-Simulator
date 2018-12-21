#include "Instruction_Memory.h"

Instruction_Memory::Instruction_Memory(const string trace_fname)
{
	Assembler *assm = new Assembler(this, trace_fname);

	assm->write_into_instr_mem();

	free(assm);

	printInstr();
}
