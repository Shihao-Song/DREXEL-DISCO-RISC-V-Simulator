#include "Core.h"

Core::Core(const string &fname, ofstream *out) : out(out), 
						clk(0) 
{
	/*
	 * Initialize Stages
	 * */
	if_stage = (new IF_Stage(fname, this));	
	id_stage = (new ID_Stage());
	ex_stage = (new EX_Stage());
	mem_stage = (new MEM_Stage());
	wb_stage = (new WB_Stage());

	wb_stage->mem_stage = mem_stage;
	mem_stage->ex_stage = ex_stage;
	ex_stage->id_stage = id_stage;
	
	id_stage->if_stage = if_stage;
	id_stage->ex_stage = ex_stage;
	id_stage->mem_stage = mem_stage;
	id_stage->wb_stage = wb_stage;	
}	

/*
	TODO - Add more functions and modify tick() to simulate single-cycle RISC-V architecture
*/
bool Core::tick()
{
	/*
		Step One: Serving pending instructions
	*/
	if (pending_queue.size() > 0)
	{
		serve_pending_instrs();
	}
	
	/*
		Step Two: Where simulation happens
	*/
	if_stage->tick();

	clk++;

	/*
		Step Four: Should we shut down simulator
	*/
	if (pending_queue.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Core::serve_pending_instrs()
{
	list<Instruction>::iterator instr = pending_queue.begin();

	if (instr->end_exe <= clk)
	{
		printStats(instr);
		
		pending_queue.erase(instr);	
	}
}

void Core::printStats(list<Instruction>::iterator &ite)
{
	*out << ite->raw_instr << " => ";
	*out << "Core ID: " << id << "; ";
	*out << "Begin Exe: " << ite->begin_exe << "; ";
	*out << "End Exe: " << ite->end_exe << endl;
}

