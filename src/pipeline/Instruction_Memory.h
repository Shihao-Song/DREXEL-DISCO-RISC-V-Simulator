#ifndef __INSTRUCTION_MEMORY_H_
#define __INSTRUCTION_MEMORY_H_

#include <vector>
#include <map>
#include <bitset>

#include "Assembler.h"
#include "Instruction.h"

using namespace std;

class Assembler;

class Instruction_Memory
{
public:
	Instruction_Memory(const string fname);

	Instruction& get_instruction(long addr);

	// Return the address of the last instruction
	long last_addr() 
	{ 
		map<long, Instruction>::iterator ite = instructions.end();
		ite--;

		return ite->second.addr;
	}

	friend class Assembler;
	friend class Core;
private:
	map<long, Instruction> instructions;

	// For debug only
	void printInstr()
	{
		for (map<long, Instruction>::iterator ite = instructions.begin();
				ite != instructions.end(); ite++)	
		{
			cout << "   " << ite->first << " : " << ite->second.raw_instr;
			bitset<32> ins(ite->second.instruction);
			cout << " => " << ins << endl;
		}
	}
};

#endif
