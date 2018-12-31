#ifndef __STAGES_H__
#define __STAGES_H__

#include <fstream>
#include <iostream>
#include <string>
#include <list>

#include "Core.h"

#include "Instruction_Memory.h"
#include "Instruction.h"

using namespace std;

class Core;

class IF_Stage;
class ID_Stage;
class EX_Stage;
class MEM_Stage;
class WB_Stage;

/*
 * The following classes are for demonstration only. You should modify it based on the requirements.
 * */
class IF_Stage
{
public:
        IF_Stage(const string &fname, Core* core) : instr_mem(new Instruction_Memory(fname)),
							core(core),
							PC(0),
							stall(0),
							bubble(0),
							end(0)
	{
		if_id_reg.valid = 0;
	}

        void tick();

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
         * TODO, define your IF/ID register here.
         * */
        /*
         * For demonstration (of hazard detection) only, delete the followings please.
         * I assume all R-type instructions for demonstration.
         * */
        struct Register
        {
                int valid; // Is content inside register valid?

                int WB; // Is WB required?

                int rd_index;
                int rs_1_index;
                int rs_2_index;
	};
        
	Register if_id_reg;
};

class ID_Stage
{
public:
        ID_Stage() : stall(0), bubble(0), end(0)
        {
                id_ex_reg.valid = 0;
        }

        void tick();

        /*
         * Hazard detection unit: stall ID and IF stages, meanwhile, insert bubbles to
         * EX, MEM and WB stages.
         * */
        void hazard_detection();

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
        IF_Stage *if_stage;
        EX_Stage *ex_stage;
        MEM_Stage *mem_stage;
        WB_Stage *wb_stage;

        /*
         * TODO, define your ID_EX register here.
         * */
        /*
         * For demonstration (of hazard detection) only, delete the followings please.
         * I assume all R-type instructions for demonstration.
         * */
        struct Register
        {
                int valid; // Is content inside register valid?

                int WB; // Is WB required?

                int rd_index;
                int rs_1_index;
		int rs_2_index;
	};
        Register id_ex_reg;
};

class EX_Stage
{
public:
        EX_Stage() : stall(0), bubble(0), end(0)
	{
                ex_mem_reg.valid = 0;
        }

        void tick();

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
        ID_Stage *id_stage;

        /*
         * TODO, define your EX_MEM register here.
         * */
        /*
         * For demonstration (of hazard detection) only, delete the followings please.
         * I assume all R-type instructions for demonstration.
         * */
        struct Register
        {
                int valid; // Is content inside register valid?

                int WB; // Is WB required?

                int rd_index;
                int rs_1_index;
                int rs_2_index;
        };
        Register ex_mem_reg;
};

class MEM_Stage
{
public:
        MEM_Stage() : stall(0), bubble(0), end(0)
        {
                mem_wb_reg.valid = 0;
        }

        void tick();

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
        EX_Stage *ex_stage;

        /*
         * TODO, define your MEM_WB register here.
         * */
        /*
         * For demonstration (of hazard detection) only, delete the followings please.
         * I assume all R-type instructions for demonstration.
         * */
        struct Register
        {
                int valid; // Is content inside register valid?

                int WB; // Is WB required?

                int rd_index;
                int rs_1_index;
                int rs_2_index;
        };
        Register mem_wb_reg;
};

class WB_Stage
{
public:
        WB_Stage() : stall(0), bubble(0), end(0)
        {

        }

        void tick();

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
        MEM_Stage *mem_stage;
};

#endif
