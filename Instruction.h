#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <vector>

using namespace std;

class Instruction
{
public:
	long addr; // Address of the instruction

	unsigned int instruction = 0; // The instruction read from instruction memory

	int begin_exe; // Clock which it starts to execute

	int end_exe; // Clock which it ends execution

	/*
		Constructor
	*/
	Instruction(){}
};

#endif
