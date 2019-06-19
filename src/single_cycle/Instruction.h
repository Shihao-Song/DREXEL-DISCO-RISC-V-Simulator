#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <vector>
#include <string>

typedef uint64_t Addr;
typedef uint64_t Tick;

class Instruction
{
  public:
    Addr addr; // Address of the instruction

    std::string raw_instr; // Raw instruction from input file

    unsigned int instruction = 0; // Instruction read from instruction memory

    Tick begin_exe; // Clock which it starts to execute

    Tick end_exe; // Clock which it ends execution

    /*
        Constructor
    */
    Instruction(){}
};

#endif
