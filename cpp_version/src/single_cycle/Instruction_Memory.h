#ifndef __INSTRUCTION_MEMORY_H_
#define __INSTRUCTION_MEMORY_H_

#include <bitset>
#include <map>
#include <vector>

#include "Instruction.h"

class Assembler;

class Instruction_Memory
{
    typedef uint64_t Addr;
    typedef uint64_t Tick;

  public:
    Instruction_Memory(const std::string fname);

    Instruction& get_instruction(Addr addr);

    // Return the address of the last instruction
    Addr last_addr() 
    { 
        std::map<Addr, Instruction>::iterator ite = instructions.end();
        ite--;

        return ite->second.addr;
    }

    std::map<Addr, Instruction> instructions;

    // For debug only
    void printInstr()
    {
        for (std::map<Addr, Instruction>::iterator ite = instructions.begin();
                                                   ite != instructions.end(); ite++)	
        {
            std::cout << "   " << ite->first << " : " << ite->second.raw_instr;
            std::bitset<32> ins(ite->second.instruction);
            std::cout << " => " << ins << "\n";
        }
    }
};

#endif
