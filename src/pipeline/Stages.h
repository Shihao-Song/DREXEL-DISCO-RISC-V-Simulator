#ifndef __STAGES_H__
#define __STAGES_H__

#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "Instruction_Memory.h"
#include "Instruction.h"

#define DEBUG 1

class Core;

class IF_Stage;
class ID_Stage;
class EX_Stage;
class MEM_Stage;
class WB_Stage;

typedef uint64_t Addr;
typedef uint64_t Tick;

/*
 * The following classes are for demonstration only.
 * You should modify them based on the requirements.
 * */
class IF_Stage
{
  public:
    IF_Stage(const std::string &fname, Core *_core)
        : instr_mem(new Instruction_Memory(fname)),
          core(_core),
          PC(0),
          stall(0),
          end(0)
    {
        // Initially, IF/ID Register is invalid.
        if_id_reg.valid = 0;
    }

    void tick();

    /*
     * Important signals.
     * */
    // Points to the instruction currently in the stage
    std::list<Instruction>::iterator instr; 

    int stall; // Is the stage stalled?
    int end; // All instructions are run-out?

    /*
     * TODO, Design components of IF stage here
     * */
    Core *core;
    Addr PC;

    std::unique_ptr<Instruction_Memory> instr_mem;
    
    /*
     * TODO, define your IF/ID register here.
     * */
    /*
     * Here shows one possible prototype of an in-complete IF/ID register. You should
     * extend it further to get a complete IF/ID register.
     * */
    struct Register
    {
        int valid; // Is content inside register valid?

        int WB; // Is WB required?

        int rd_index;
        int rs_1_index;
        int rs_2_index;
    };
    Register if_id_reg;
};

class ID_Stage
{
  public:
    ID_Stage()
      : stall(0),
        end(0)
    {
        id_ex_reg.valid = 0;
    }

    void tick();

    /*
     * Hazard detection unit: stall ID and IF stages, meanwhile, insert bubbles to
     * EX stage.
     * */
    void hazardDetection();

    /*
     * Important signals.
     * */
    // Points to the instruction currently in the stage
    std::list<Instruction>::iterator instr;

    int stall; // Is the stage stalled?
    int end; // All instructions are run-out?

    /*
     * Related Class
     *
     * Hazard detection unit needs access to IF and EX stage.
     * */
    IF_Stage *if_stage;
    EX_Stage *ex_stage;
    MEM_Stage *mem_stage;

    /*
     * TODO, design components of ID stage here.
     * */

    /*
     * TODO, define your ID/EX register here.
     * */

    /*
     * Here shows one possible prototype of an in-complete ID/EX register. 
     * You should extend it further to get a complete ID/EX register.
     * */
    struct Register
    {
        int valid; // Is content inside register valid?

        int WB; // Is WB required?

        int rd_index;
        int rs_1_index;
        int rs_2_index;
    };
    Register id_ex_reg;
};

class EX_Stage
{
  public:
    EX_Stage()
    : bubble(0),
      end(0)
    {
        ex_mem_reg.valid = 0;
    }

    void tick();

    /*
     * Important signals.
     */
    // Points to the instruction currently in the stage
    std::list<Instruction>::iterator instr; 

    int bubble; // A bubble is inserted?
    int end; // All instructions are exhausted?

    /*
     * Related Class
     * */
    ID_Stage *id_stage;

    /*
     * TODO, design components of EX stage here.
     * */

    /*
     * TODO, define your EX/MEM register here.
     * */

    /*
     * Here shows the prototype of an in-complete EX/MEM register. Extend it further to a 
     * complete EX/MEM register.
     * */
    struct Register
    {
        int valid; // Is content inside register valid?

        int WB; // Is WB required?

        int rd_index;
        int rs_1_index;
        int rs_2_index;
    };
    Register ex_mem_reg;
};

class MEM_Stage
{
  public:
    MEM_Stage() : end(0)
    {
        mem_wb_reg.valid = 0;
    }

    void tick();

    /*
     * Important signals.
     * */
    // Points to the instruction currently in the stage
    std::list<Instruction>::iterator instr;

    int end; // All instructions are exhausted?

    /*
     * Related Class
     * */
    EX_Stage *ex_stage;

    /*
     * TODO, design component of MEM stage here.
     * */

    /*
     * TODO, define your MEM/WB register here.
     * */

    /*
     * Here shows the prototype of an in-complete MEM/WB register. Extend it further to get
     * a complete MEM/WB register.
     * */
    struct Register
    {
        int valid; // Is content inside register valid?

        int WB; // Is WB required?

        int rd_index;
        int rs_1_index;
        int rs_2_index;
    };
    Register mem_wb_reg;
};

class WB_Stage
{
  public:
    WB_Stage() : end(0) {}

    void tick();

    /*
     * Important signals.
     * */
    // Points to the instruction currently in the stage
    std::list<Instruction>::iterator instr;

    int end; // All instructions are exhausted?

    /*
     * Related Class
     * */
    MEM_Stage *mem_stage;
    ID_Stage *id_stage;

    /*
     * TODO, you should write to the register file defined in ID stage.
     * */
};

#endif
