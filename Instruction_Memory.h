#ifndef __INSTRUCTION_MEMORY_H_
#define __INSTRUCTION_MEMORY_H_

#include <vector>
#include <map>

#include "Assembler.h"
#include "Instruction.h"

using namespace std;

class Assembler;

class Instruction_Memory
{
public:
	Instruction_Memory(const string trace_fname);

private:
	map<int, Instruction> instructions;
};

#endif
