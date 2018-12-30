#ifndef __IF_STAGE_H__
#define __IF_STAGE_H__

#include <fstream>
#include <iostream>
#include <string>
#include <list>

#include "Core.h"

#include "Instruction_Memory.h"
#include "Instruction.h"

using namespace std;

class Core;

/*
 * This class is for demonstration only. You should modify it based on the requirements.
 * */
class IF_Stage
{
public:
	IF_Stage(const string &fname, Core* core);

	bool tick();

	/*
	 * Important signals.
	 * */
	list<Instruction>::iterator instr; // Points to the instruction currently in the stage

	int stall; // Is the stage stalled?
	int bubble; // A bubble is inserted?
	int end; // All instructions are exhausted?

	/*
	 * Related Class
	 * */
	Core *core;

	/*
	 * Design components here
	 * */	
	long PC;

	Instruction_Memory *instr_mem;

	/*
	 * For demonstration (of hazard detection) only, delete the followings please
	 * */
};

#endif
