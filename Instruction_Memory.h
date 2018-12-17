#ifndef __INSTRUCTION_MEMORY_H_
#define __INSTRUCTION_MEMORY_H_

#include <vector>
#include <map>

#include "Trace.h"
#include "Instruction.h"

using namespace std;

class Trace;

class Instruction_Memory
{
public:
	Instruction_Memory(const string trace_fname);

private:
	map<int, Instruction> instructions;
};

#endif
