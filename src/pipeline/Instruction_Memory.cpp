#include "Instruction_Memory.h"

Instruction_Memory::Instruction_Memory(const string fname)
{
	Assembler *assm = new Assembler(this, fname);

	assm->write_into_instr_mem();

	free(assm);
}

Instruction& Instruction_Memory::get_instruction(long addr)
{
	return instructions.find(addr)->second;
}
