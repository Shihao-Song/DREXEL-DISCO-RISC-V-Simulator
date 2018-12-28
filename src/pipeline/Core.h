#ifndef __CORE_H__
#define __CORE_H__

#include <fstream>
#include <iostream>
#include <string>
#include <list>

#include "Instruction_Memory.h"
#include "Instruction.h"
#include "Config.h"

using namespace std;

class Core
{
public:
	Core(Config &config, const string &fname, ofstream *out);

	bool tick(); // FALSE means all the instructions are exhausted

	int id; // Each core has its own ID

	void printInstrs()
	{
		cout << "Core " << id << " : " << endl;

		instr_mem->printInstr();
	}

private:
	
	struct Pipeline
	{
		int num_stages_mul;
		int num_stages_div;
		int num_stages_fadd;
		int num_stages_fmul;
		int num_stages_fdiv;
	};

	Pipeline pipeline_info; // This is used to calculate estimated end execution time

	ofstream *out; // Output file

	unsigned long long int clk;

	/*
		Group One: Design Components Here, an instruction memory has already been
		designed for you.
	*/
	long PC;

	Instruction_Memory *instr_mem;

	/*
		Group Two: Simulator Related
	*/
	// For demonstration only, you should use your linked list data structure.
	list<Instruction> pending_queue;

	void serve_pending_instrs();

	void printStats(list<Instruction>::iterator &ite);

	/*
		Group Three: State Machine 
	*/
};

#endif
