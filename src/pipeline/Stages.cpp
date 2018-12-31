#include "Stages.h"

IF_Stage::IF_Stage(const string &fname, Core *core) : instr_mem(new Instruction_Memory(fname)),
                                                        PC(0),
                                                        core(core)
{
        if_id_reg.valid = 0;
}

bool IF_Stage::tick()
{
        if (PC <= instr_mem->last_addr())
        {
                // Get Instruction
                Instruction &instruction = instr_mem->get_instruction(PC);

                // Increment PC
                // TODO, PC should be incremented or decremented based on instruction
                PC += 4;

                /*
                 * TODO, fix me. Simulate IF Stage here.
                 * Example on how to extract fields have been given.
                 * */
                if_id_reg.valid = 1;

                if_id_reg.WB = 1; // For demonstration, I assume all instructions are R-type.

                if_id_reg.rd_index = (instruction.instruction >> 7) & 31;
                if_id_reg.rs_1_index = (instruction.instruction >> (7 + 5 + 3)) & 31;
                if_id_reg.rs_2_index = (instruction.instruction >> (7 + 5 + 3 + 5)) & 31;

		/*
                        Simulator related
                */
                instruction.begin_exe = core->clk;

                // Initialize end execution time to 5 clock cycles, adjust it
                // in the run time
                instruction.end_exe = core->clk + 5;

                // Push instruction into queue;
                (core->pending_queue).push_back(instruction);
                instr = (core->pending_queue).end();
                instr--;

                return true;
        }

        if_id_reg.valid = 0;

	// TODO, end should be set
        return false;
}

bool ID_Stage::tick()
{
        return false;
}

void WB_Stage::tick()
{
        /*
         * Read from MEM_WB Register
         **/

        if (bubble == 1)
        {
                // A bubble is inserted, do nothing.
                return;
        }

        if (end == 1)
        {
                // Instructions are run out, do nothing.
                return;
        }

        if (mem_stage->mem_wb_reg.valid == 0)
        {
                // MEM_WB register is invalid, do nothing.
                return;
        }
}

