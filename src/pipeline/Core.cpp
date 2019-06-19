#include "Core.h"

Core::Core(const std::string &fname, std::ofstream *out) : out(out)
{
    if_stage = std::make_unique<IF_Stage>(fname, this); 
    id_stage = std::make_unique<ID_Stage>();
    ex_stage = std::make_unique<EX_Stage>();
    mem_stage = std::make_unique<MEM_Stage>();
    wb_stage = std::make_unique<WB_Stage>();

    wb_stage->mem_stage = mem_stage.get();
    wb_stage->id_stage = id_stage.get();

    mem_stage->ex_stage = ex_stage.get();

    ex_stage->id_stage = id_stage.get();

    id_stage->if_stage = if_stage.get();
    id_stage->ex_stage = ex_stage.get();
    id_stage->mem_stage = mem_stage.get();
}

/*
FIXME - Add more functions and modify tick() to simulate single-cycle RISC-V architecture
*/
bool Core::tick()
{
    if (pending_queue.size() > 0)
    {
        servePendingInstrs();
    }

    if (DEBUG)
    {
        std::cout << "clk: " << clk << " : ";
    }

    wb_stage->tick();
    mem_stage->tick();
    ex_stage->tick();
    id_stage->tick();
    if_stage->tick();

    if (DEBUG)
    {
        std::cout << "\n";
    }

    clk++;
    if (pending_queue.size() == 0)
    {
        return false;
    }
    return true;
}

void Core::servePendingInstrs()
{
    std::list<Instruction>::iterator instr = pending_queue.begin();

    if (instr->end_exe <= clk)
    {
        printStats(instr);

        pending_queue.erase(instr);
    }
}

void Core::printStats(std::list<Instruction>::iterator &ite)
{
    *out << ite->raw_instr << " => ";
    *out << "Core ID: " << id << "; ";
    *out << "Begin Exe: " << ite->begin_exe << "; ";
    *out << "End Exe: " << ite->end_exe << "\n";
}
