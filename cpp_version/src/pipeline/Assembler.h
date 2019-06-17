#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include "Instruction_Memory.h"
#include "Instruction.h"

/*
	Number of registers in RISC-V architecture. 
	There are 32 integer registers and 32 floating-point registers.
*/
#define NUM_OF_REGS 64

using namespace std;

class Instruction_Memory;

/*
	This class helps to parse and translate assesmbly traces to
	machine codes then stores into instruction memory.
*/

class Assembler
{
public:
	Assembler(Instruction_Memory *instr_mem, const string trace_fname);

	~Assembler()
	{
		// Close trace file
		file.close(); 
	}

	void write_into_instr_mem();

private:

	ifstream file; // This contains input assembly trace.

	Instruction_Memory *instr_mem; // Targeting instruction memory

	/*
		Map (1), Register names to (numbering) index
	*/
	map<string, int>reg_name_to_index;	

	/*
		Map (2), Operation to opcode, funct3 and funct7
	*/
	map<string, int>opr_to_opcode;

	map<string, int>opr_to_funct3;
	
	map<string, int>opr_to_funct7;

	/*
		Register names
	*/
	const string regs[NUM_OF_REGS] = {
		"x0",
		"x1",
		"x2",
		"x3",
		"x4",
		"x5",
		"x6",
		"x7",
		"x8",
		"x9",
		"x10",
		"x11",
		"x12",
		"x13",
		"x14",
		"x15",
		"x16",
		"x17",
		"x18",
		"x19",
		"x20",
		"x21",
		"x22",
		"x23",
		"x24",
		"x25",
		"x26",
		"x27",
		"x28",
		"x29",
		"x30",
		"x31",
		"f0",
		"f1",
		"f2",
		"f3",
		"f4",
		"f5",
		"f6",
		"f7",
		"f8",
		"f9",
		"f10",
		"f11",
		"f12",
		"f13",
		"f14",
		"f15",
		"f16",
		"f17",
		"f18",
		"f19",
		"f20",
		"f21",
		"f22",
		"f23",
		"f24",
		"f25",
		"f26",
		"f27",
		"f28",
		"f29",
		"f30",
		"f31"
	};

	const string reg_name_sym[NUM_OF_REGS] = {
	      "zero",
	      "ra",
	      "sp",
	      "gp",
	      "tp",
	      "t0",
	      "t1",
	      "t2",
	      "s0",
	      "s1",
	      "a0",
	      "a1",
	      "a2",
	      "a3",
	      "a4",
	      "a5",
	      "a6",
	      "a7",
	      "s2",
	      "s3",
	      "s4",
	      "s5",
	      "s6",
	      "s7",
	      "s8",
	      "s9",
	      "s10",
	      "s11",
	      "t3",
	      "t4",
	      "t5",
	      "t6",
	      "ft0",
	      "ft1",
	      "ft2",
	      "ft3",
	      "ft4",
	      "ft5",
	      "ft6",
	      "ft7",
	      "fs0",
	      "fs1",
	      "fa0",
	      "fa1",
	      "fa2",
	      "fa3",
	      "fa4",
	      "fa5",
	      "fa6",
	      "fa7",
	      "fs2",
	      "fs3",
	      "fs4",
	      "fs5",
	      "fs6",
	      "fs7",
	      "fs8",
	      "fs9",
	      "fs10",
	      "fs11",
	      "ft8",
	      "ft9",
	      "ft10",
	      "ft11"
	};
};

#endif
