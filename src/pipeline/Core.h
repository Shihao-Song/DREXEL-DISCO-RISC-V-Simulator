#ifndef __CORE_H__
#define __CORE_H__

#include <fstream>
#include <iostream>
#include <string>
#include <list>

#include "Instruction.h"
#include "Stages.h"

using namespace std;

class IF_Stage;
class ID_Stage;
class EX_Stage;
class MEM_Stage;
class WB_Stage;

class Core
{
public:
	Core(const string &fname, ofstream *out);

	bool tick(); // FALSE means all the instructions are exhausted

	int id; // Each core has its own ID

	friend class IF_Stage;

private:
	
	ofstream *out; // Output file

	unsigned long long int clk;

	/*
		Group One: Add Stages here.
	*/
	IF_Stage *if_stage;	
	ID_Stage *id_stage;
	EX_Stage *ex_stage;
	MEM_Stage *mem_stage;
	WB_Stage *wb_stage;

	/*
		Group Two: Simulator Related
	*/
	// For demonstration only, you should use your linked list data structure.
	list<Instruction> pending_queue;

	void serve_pending_instrs();

	void printStats(list<Instruction>::iterator &ite);
};

#endif
