#include "Stages.h"

void IF_Stage::tick()
{
	if (end == 1)
	{
		// No instruction to run, return.
		return;
	}

	if (PC == instr_mem->last_addr())
	{
		// No instruction to run for next clock cycle since we have reached the last 
		// instruction.
		end = 1;
	}

	/*
	 * Simulate IF stage here
	 * */
	if (stall == 0)
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

		// For demonstration, I assume all instructions are R-type.
		if_id_reg.WB = 1; 

		if_id_reg.rd_index = (instruction.instruction >> 7) & 31;
		if_id_reg.rs_1_index = (instruction.instruction >> (7 + 5 + 3)) & 31;
		if_id_reg.rs_2_index = (instruction.instruction >> (7 + 5 + 3 + 5)) & 31;

		/*
			Simulator related
		*/
		instruction.begin_exe = core->clk;

		// Initialize end execution time to 5 clock cycles but adjust it
		// if a stall detected.
		instruction.end_exe = core->clk + 4;

		// Push instruction object into queue
		(core->pending_queue).push_back(instruction);
		instr = (core->pending_queue).end();
		instr--;

		/*
	 	* De-bugging
	 	* */
		if (DEBUG)
		{
			cout << "IF : " << instr->raw_instr << " | ";	
		}
	}
}

void ID_Stage::hazard_detection()
{
	/*
	 * TODO, fix me, please modify this function in order to get a complete detection unit.
	 * For demonstration, I assume all instructions are R-type (WB is always set).
	 * */

	/*
	 * (1) EX/MEM.rd = ID/EX.rs1
	 * (2) EX/MEM.rd = ID/EX.rs2
	 * (3) MEM/WB.rd = ID/EX.rs1
	 * (4) MEM/WB.rd = ID/EX.rs2
	 * */
	if (ex_stage->ex_mem_reg.valid == 1)
	{
		if (ex_stage->ex_mem_reg.rd_index == id_ex_reg.rs_1_index || 
			ex_stage->ex_mem_reg.rd_index == id_ex_reg.rs_2_index)
		{
			if_stage->stall = 1; // Fetching should not proceed.
			stall = 1; // ID should also stall.
			ex_stage->bubble = 1; // EX stage should not accept any new instructions

			instr->end_exe += 1; // The end execution time should be incremented by 1.

			return;
		}
	}
	else if (mem_stage->mem_wb_reg.valid == 1)
	{
		if (mem_stage->mem_wb_reg.rd_index == id_ex_reg.rs_1_index || 
			mem_stage->mem_wb_reg.rd_index == id_ex_reg.rs_2_index)
		{
			if_stage->stall = 1; // Fetching should not proceed.
			stall = 1; // ID should also stall.
			ex_stage->bubble = 1; // EX stage should not accept any new instructions

			instr->end_exe += 1; // The end execution time should be incremented by 1.
			
			return;
		}
	}

	if_stage->stall = 0; // No hazard found, fetching proceed.
	stall = 0; // No hazard found, ID stage proceed.
	ex_stage->bubble = 0; // No hazard found, execution proceed.
}

void ID_Stage::tick()
{
        if (end == 1 && stall == 0)
        {
                // Instructions are run out, do nothing.

		return;
        }

        if (if_stage->if_id_reg.valid == 0)
        {
                // IF_ID register is invalid, do nothing.
		return;
        }
	
	/*
         * Read from IF_ID Register
         **/
	end = if_stage->end; // end signal is propagated from IF stage
	
	instr = if_stage->instr; // instruction pointer is also propagated from IF stage
	
	id_ex_reg.valid = if_stage->if_id_reg.valid;

	id_ex_reg.WB = if_stage->if_id_reg.WB;

	id_ex_reg.rd_index = if_stage->if_id_reg.rd_index;
	id_ex_reg.rs_1_index = if_stage->if_id_reg.rs_1_index;
	id_ex_reg.rs_2_index = if_stage->if_id_reg.rs_2_index;

	hazard_detection();
	/*
	 * De-bugging
	 * */
	if (DEBUG)
	{
		cout << "ID : " << instr->raw_instr;
		
		if (stall)
		{
			cout << " (stalled) ";
		}

		cout << " | ";	
	}
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
                // ID_EX register is invalid, do nothing.
                return;
        }
	
	/*
         * Read from ID_EX Register
         **/
	end = id_stage->end; // end signal is propagated from IF stage
	
	instr = id_stage->instr; // instruction pointer is also propagated from IF stage

	ex_mem_reg.valid = id_stage->id_ex_reg.valid;
	id_stage->id_ex_reg.valid = 0; // I only allow any unique instruction to be read only
					// once in order to increase program performance.

	ex_mem_reg.WB = id_stage->id_ex_reg.WB;

	ex_mem_reg.rd_index = id_stage->id_ex_reg.rd_index;
	ex_mem_reg.rs_1_index = id_stage->id_ex_reg.rs_1_index;
	ex_mem_reg.rs_2_index = id_stage->id_ex_reg.rs_2_index;

	/*
	 * De-bugging
	 * */
	if (DEBUG)
	{
		cout << "EX : " << instr->raw_instr << " | ";	
	}
}

void MEM_Stage::tick()
{
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
	ex_stage->ex_mem_reg.valid = 0;

	mem_wb_reg.WB = ex_stage->ex_mem_reg.WB;

	mem_wb_reg.rd_index = ex_stage->ex_mem_reg.rd_index;
	mem_wb_reg.rs_1_index = ex_stage->ex_mem_reg.rs_1_index;
	mem_wb_reg.rs_2_index = ex_stage->ex_mem_reg.rs_2_index;

	/*
	 * De-bugging
	 * */
	if (DEBUG)
	{
		cout << "MEM : " << instr->raw_instr << " | ";	
	}
}

void WB_Stage::tick()
{
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
	
	mem_stage->mem_wb_reg.valid = 0; 

	if (DEBUG)
	{
		cout << "WB : " << instr->raw_instr << " | ";
	}	
}

