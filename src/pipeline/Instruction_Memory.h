#ifndef __INSTRUCTION_MEMORY_H_
#define __INSTRUCTION_MEMORY_H_

#include "Instruction.h"

#define IMEM_SIZE 256
typedef struct
{
    Instruction instructions[IMEM_SIZE];
}Instruction_Memory;

#endif
