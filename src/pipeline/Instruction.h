#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <vector>
#include <string>

using namespace std;

class Instruction
{
public:
	long addr; // Address of the instruction

	string raw_instr; // Raw instruction from input file

	unsigned int instruction = 0; // Instruction read from instruction memory

	unsigned long long int begin_exe; // Clock which it starts to execute

	unsigned long long int end_exe; // Clock which it ends execution

	/*
		Constructor
	*/
	Instruction(){}
};

#endif
