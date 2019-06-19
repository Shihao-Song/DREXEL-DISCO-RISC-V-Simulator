#ifndef __CORE_H__
#define __CORE_H__

#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "Instruction.h"
#include "Instruction_Memory.h"

#include "Stages.h"

class Core
{
    typedef uint64_t Addr;
    typedef uint64_t Tick;

  public:
    Core(const std::string &fname, std::ofstream *out);

    bool tick(); // FALSE means all the instructions are exhausted

    int id; // Each core has its own ID

    // For debugging
    void printInstrs()
    {
        std::cout << "Core " << id << " : \n";
        // Unsupported for Pipeline
    }

    // Stages
    std::unique_ptr<IF_Stage> if_stage;
    std::unique_ptr<ID_Stage> id_stage;
    std::unique_ptr<EX_Stage> ex_stage;
    std::unique_ptr<MEM_Stage> mem_stage;
    std::unique_ptr<WB_Stage> wb_stage;

    /*
     * Simulator related
     * */
    Tick clk;

    std::list<Instruction> pending_queue;
    void servePendingInstrs();

    std::ofstream *out; // Output file
    void printStats(std::list<Instruction>::iterator &ite);
};

#endif
