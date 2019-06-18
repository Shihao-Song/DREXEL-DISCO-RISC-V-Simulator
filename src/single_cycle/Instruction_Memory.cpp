#include "Assembler.h"
#include "Instruction_Memory.h"

Instruction_Memory::Instruction_Memory(const std::string fname)
{
    std::unique_ptr<Assembler> assm = std::make_unique<Assembler>(this, fname);

    assm->write_into_instr_mem();
}

Instruction& Instruction_Memory::get_instruction(Addr addr)
{
    return instructions.find(addr)->second;
}
