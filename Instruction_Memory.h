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

	Instruction& get_instruction(int addr);

	friend class Assembler;
private:
	map<int, Instruction> instructions;

	// For debug only
	void printInstr()
	{
		for (map<int, Instruction>::iterator ite = instructions.begin();
				ite != instructions.end(); ite++)	
		{
			cout << ite->first << " => " << ite->second.addr;
			bitset<32> ins(ite->second.instruction);
			cout << " => " << ins << endl;
		}
	}
};

#endif
