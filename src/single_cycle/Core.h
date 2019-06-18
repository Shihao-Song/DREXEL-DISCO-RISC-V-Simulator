#ifndef __CORE_H__
#define __CORE_H__

#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "Instruction.h"
#include "Instruction_Memory.h"

class Instruction_Memory;
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

        instr_mem->printInstr();
    }

  private:
    std::ofstream *out; // Output file

    Tick clk;

    /*
        Group One: Design Components Here, an instruction memory has already been
        designed for you.
    */
    Addr PC;

    std::unique_ptr<Instruction_Memory> instr_mem;

    /*
	Group Two: Simulator Related
    */
    std::list<Instruction> pending_queue;

    void serve_pending_instrs();

    void printStats(std::list<Instruction>::iterator &ite);
};

#endif
