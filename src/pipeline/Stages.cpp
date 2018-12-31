#include "Stages.h"

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
                instruction.end_exe = core->clk + 4;

                // Push instruction into queue;
                (core->pending_queue).push_back(instruction);
                instr = (core->pending_queue).end();
                instr--;

                return true;
        }
	else
	{
		if_id_reg.valid = 0;
		end = 1;

        	return false;
	}
}

void ID_Stage::tick()
{
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

        if (if_stage->if_id_reg.valid == 0)
        {
                // EX_MEM register is invalid, do nothing.
                return;
        }
	
	/*
         * Read from EX_MEM Register
         **/
	end = if_stage->end; // end signal is propagated from IF stage
	
	instr = if_stage->instr; // instruction pointer is also propagated from IF stage

	id_ex_reg.valid = if_stage->if_id_reg.valid;

	id_ex_reg.WB = if_stage->if_id_reg.WB;

	id_ex_reg.rd_index = if_stage->if_id_reg.rd_index;
	id_ex_reg.rs_1_index = if_stage->if_id_reg.rs_1_index;
	id_ex_reg.rs_2_index = if_stage->if_id_reg.rs_2_index;
}

void EX_Stage::tick()
{
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

        if (id_stage->id_ex_reg.valid == 0)
        {
                // EX_MEM register is invalid, do nothing.
                return;
        }
	
	/*
         * Read from EX_MEM Register
         **/
	end = id_stage->end; // end signal is propagated from IF stage
	
	instr = id_stage->instr; // instruction pointer is also propagated from IF stage

	ex_mem_reg.valid = id_stage->id_ex_reg.valid;

	ex_mem_reg.WB = id_stage->id_ex_reg.WB;

	ex_mem_reg.rd_index = id_stage->id_ex_reg.rd_index;
	ex_mem_reg.rs_1_index = id_stage->id_ex_reg.rs_1_index;
	ex_mem_reg.rs_2_index = id_stage->id_ex_reg.rs_2_index;
}

void MEM_Stage::tick()
{
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

        if (ex_stage->ex_mem_reg.valid == 0)
        {
                // EX_MEM register is invalid, do nothing.
                return;
        }
	
	/*
         * Read from EX_MEM Register
         **/
	end = ex_stage->end; // end signal is propagated from IF stage
	
	instr = ex_stage->instr; // instruction pointer is also propagated from IF stage

	mem_wb_reg.valid = ex_stage->ex_mem_reg.valid;

	mem_wb_reg.WB = ex_stage->ex_mem_reg.WB;

	mem_wb_reg.rd_index = ex_stage->ex_mem_reg.rd_index;
	mem_wb_reg.rs_1_index = ex_stage->ex_mem_reg.rs_1_index;
	mem_wb_reg.rs_2_index = ex_stage->ex_mem_reg.rs_2_index;
}

void WB_Stage::tick()
{
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

	
	/*
         * Read from MEM_WB Register
         **/
	end = mem_stage->end; // end signal is propagated from IF stage
	
	instr = mem_stage->instr; // instruction pointer is also propagated from IF stage

	// TODO, read the rest of the register
}

