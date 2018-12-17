#include "Instruction_Memory.h"

Instruction_Memory::Instruction_Memory(const string trace_fname)
{
	Trace *trace = new Trace(this, trace_fname);

	trace->write_into_instr_mem();

	free(trace);
}
