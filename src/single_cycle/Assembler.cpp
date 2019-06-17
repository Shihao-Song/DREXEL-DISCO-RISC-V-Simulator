#include "Assembler.h"

#include "Instruction_Memory.h"
#include "Instruction.h"

Assembler::Assembler(Instruction_Memory *instr_mem, const std::string trace_fname)
    : instr_mem (instr_mem),
      file (trace_fname)
{
    if (!file.good())
    {
        std::cerr << "Bad trace file: " << trace_fname << "\n";
        exit(1);
    }

    /*
        Initialize reg_name_to_index
    */
    for (int i = 0; i < NUM_OF_REGS; i++)
    {
        reg_name_to_index.insert(std::pair<std::string, int>(regs[i], i));
    }
	
    /*
        Initialize opr_to_opcode, opr_to_funct3 and opr_to_funct7.

        You are welcome to add more here.
    */

    /*
        I-type Instructions
    */
    // ld
    opr_to_opcode.insert(std::pair<std::string, int>("ld", 3));
    opr_to_funct3.insert(std::pair<std::string, int>("ld", 3));

    // addi
    opr_to_opcode.insert(std::pair<std::string, int>("addi", 19));	
    opr_to_funct3.insert(std::pair<std::string, int>("addi", 0));

    // slli
    opr_to_opcode.insert(std::pair<std::string, int>("slli", 19));	
    opr_to_funct3.insert(std::pair<std::string, int>("slli", 1));

    // xori
    opr_to_opcode.insert(std::pair<std::string, int>("xori", 19));	
    opr_to_funct3.insert(std::pair<std::string, int>("xori", 4));

    // srli
    opr_to_opcode.insert(std::pair<std::string, int>("srli", 19));	
    opr_to_funct3.insert(std::pair<std::string, int>("srli", 5));

    // ori
    opr_to_opcode.insert(std::pair<std::string, int>("ori", 19));	
    opr_to_funct3.insert(std::pair<std::string, int>("ori", 6));

    // andi
    opr_to_opcode.insert(std::pair<std::string, int>("andi", 19));	
    opr_to_funct3.insert(std::pair<std::string, int>("andi", 7));

    // jalr
    opr_to_opcode.insert(std::pair<std::string, int>("jalr", 103));
    opr_to_funct3.insert(std::pair<std::string, int>("jalr", 0));

    /*
        S-type instructions
    */
    // sd
    opr_to_opcode.insert(std::pair<std::string, int>("sd", 35));	
    opr_to_funct3.insert(std::pair<std::string, int>("sd", 3));

    /*
        R-type instructions
    */
    // add
    opr_to_opcode.insert(std::pair<std::string, int>("add", 51));	
    opr_to_funct3.insert(std::pair<std::string, int>("add", 0));
    opr_to_funct7.insert(std::pair<std::string, int>("add", 0));

    // sub
    opr_to_opcode.insert(std::pair<std::string, int>("sub", 51));	
    opr_to_funct3.insert(std::pair<std::string, int>("sub", 0));
    opr_to_funct7.insert(std::pair<std::string, int>("sub", 32));

    // sll
    opr_to_opcode.insert(std::pair<std::string, int>("sll", 51));	
    opr_to_funct3.insert(std::pair<std::string, int>("sll", 1));
    opr_to_funct7.insert(std::pair<std::string, int>("sll", 0));

    // srl
    opr_to_opcode.insert(std::pair<std::string, int>("srl", 51));	
    opr_to_funct3.insert(std::pair<std::string, int>("srl", 5));
    opr_to_funct7.insert(std::pair<std::string, int>("srl", 0));

    // xor
    opr_to_opcode.insert(std::pair<std::string, int>("xor", 51));	
    opr_to_funct3.insert(std::pair<std::string, int>("xor", 4));
    opr_to_funct7.insert(std::pair<std::string, int>("xor", 0));

    // or
    opr_to_opcode.insert(std::pair<std::string, int>("or", 51));	
    opr_to_funct3.insert(std::pair<std::string, int>("or", 6));
    opr_to_funct7.insert(std::pair<std::string, int>("or", 0));

    // and
    opr_to_opcode.insert(std::pair<std::string, int>("and", 51));	
    opr_to_funct3.insert(std::pair<std::string, int>("and", 7));
    opr_to_funct7.insert(std::pair<std::string, int>("and", 0));

    /*
        SB-type instruction
    */
    // beq
    opr_to_opcode.insert(std::pair<std::string, int>("beq", 99));	
    opr_to_funct3.insert(std::pair<std::string, int>("beq", 0));	

    // bne
    opr_to_opcode.insert(std::pair<std::string, int>("bne", 99));	
    opr_to_funct3.insert(std::pair<std::string, int>("bne", 1));	

    // blt
    opr_to_opcode.insert(std::pair<std::string, int>("blt", 99));	
    opr_to_funct3.insert(std::pair<std::string, int>("blt", 4));	

    // bge
    opr_to_opcode.insert(std::pair<std::string, int>("bge", 99));	
    opr_to_funct3.insert(std::pair<std::string, int>("bge", 5));

    /*
        UJ-type instruction
    */
    opr_to_opcode.insert(std::pair<std::string, int>("jal", 111));	
}

void Assembler::write_into_instr_mem()
{
    Addr addr = 0;

    // Iterator all the lines
    while (!file.eof())
    {
        std::string line;
        getline(file, line);

        if (line.size() != 0)
        {
            Instruction instr;
            instr.raw_instr = line;

            // (1) Extract operation first
            size_t pos = line.find_first_not_of(' ', 0);
            size_t end = line.find_first_of(' ', 0);

            std::string opr = line.substr(pos, end - pos);

            // Note, I use debug_print as a debugging tool to verify the correctness of
            // parsing and bit operations.
            // std::bitset<32> debug_print;
            // cout << "\n[DEBUG] Original Instruction: " << line << "\n";

            // (2) Determine instruction type
            if (opr == "add" ||
                opr == "sub" ||	
                opr == "sll" || 
                opr == "srl" || 
                opr == "xor" || 
                opr == "or" || 
                opr == "and") 
            {
                // R-type instruction format
                int opcode = opr_to_opcode.find(opr)->second;
                instr.instruction |= opcode;
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] Only opcode: " << debug_print << "\n"; 

                // Extract rd
                pos = line.find_first_of(' ', 0) + 1;
                end = line.find_first_of(',', 0);

                std::string rd = line.substr(pos, end - pos);
		
                unsigned int rd_index = reg_name_to_index.find(rd)->second;
                instr.instruction |= (rd_index << 7);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rd: " << debug_print << "\n";
                
                // Funct3
                unsigned int funct3 = opr_to_funct3.find(opr)->second;
                instr.instruction |= (funct3 << (7 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with F3 : " << debug_print << "\n"; 

                // Extract rs1
                pos = line.find_first_of(' ', pos + 1) + 1;
                end = line.find_first_of(',', end + 1);

                std::string rs_1 = line.substr(pos, end - pos);

                unsigned int rs_1_index = reg_name_to_index.find(rs_1)->second;
		
                instr.instruction |= (rs_1_index << (7 + 5 + 3));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rs1: " << debug_print << "\n"; 

                // Extract rs2
                pos = line.find_first_of(' ', pos + 1) + 1;

                std::string rs_2 = line.substr(pos, line.size() - pos);
		
                unsigned int rs_2_index = reg_name_to_index.find(rs_2)->second;
		
                instr.instruction |= (rs_2_index << (7 + 5 + 3 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rs2: " << debug_print << "\n"; 

                // Funct7
                unsigned int funct7 = opr_to_funct7.find(opr)->second;
		
                instr.instruction |= (funct7 << (7 + 5 + 3 + 5 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with F7: " << debug_print << "\n"; 

            }
            else if ( opr == "ld" || opr == "jalr" )
            {
                // Special I-type instruction
                int opcode = opr_to_opcode.find(opr)->second;
                instr.instruction |= opcode;
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] Only opcode: " << debug_print << "\n";

                // Extract rd
                pos = line.find_first_of(' ', 0) + 1;
                end = line.find_first_of(',', 0);

                std::string rd = line.substr(pos, end - pos);
		
                unsigned int rd_index = reg_name_to_index.find(rd)->second;
                instr.instruction |= (rd_index << 7);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rd: " << debug_print << "\n";

                // Funct3
                unsigned int funct3 = opr_to_funct3.find(opr)->second;
                instr.instruction |= (funct3 << (7 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with F3: " << debug_print << "\n";

                // Extract immediate
                pos = line.find_first_of(' ', pos + 1) + 1;
                end = line.find_first_of('(', 0);

                std::string imme = line.substr(pos, end - pos);

                int immediate = stoi(imme, &pos, 0);

                // Extract rs1
                pos = line.find_first_of('(', 0) + 1;
                end = line.find_first_of(')', 0);

                std::string rs_1 = line.substr(pos, end - pos);
                unsigned int rs_1_index = reg_name_to_index.find(rs_1)->second;

                instr.instruction |= (rs_1_index << (7 + 5 + 3));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rs1: " << debug_print << "\n";

                instr.instruction |= (immediate << (7 + 5 + 3 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme: " << debug_print << "\n";
            }
            else if (opr == "addi" ||
                     opr == "slli" ||  
                     opr == "xori" || 
                     opr == "srli" || 
                     opr == "ori" || 
                     opr == "andi")
            {
                // I-type instruction excluding ld
                int opcode = opr_to_opcode.find(opr)->second;
                instr.instruction |= opcode;
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] Only opcode: " << debug_print << "\n";

                // Extract rd
                pos = line.find_first_of(' ', 0) + 1;
                end = line.find_first_of(',', 0);

                std::string rd = line.substr(pos, end - pos);
		
                unsigned int rd_index = reg_name_to_index.find(rd)->second;
                instr.instruction |= (rd_index << 7);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rd: " << debug_print << "\n";

                // Funct3
                unsigned int funct3 = opr_to_funct3.find(opr)->second;
                instr.instruction |= (funct3 << (7 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with F3: " << debug_print << "\n";

                // Extract rs1
                pos = line.find_first_of(' ', pos + 1) + 1;
                end = line.find_first_of(',', end + 1);

                std::string rs_1 = line.substr(pos, end - pos);

                unsigned int rs_1_index = reg_name_to_index.find(rs_1)->second;
		
                instr.instruction |= (rs_1_index << (7 + 5 + 3));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rs1: " << debug_print << "\n";

                // Extract immediate
                pos = line.find_first_of(' ', pos + 1) + 1;

                std::string imme = line.substr(pos, line.size() - pos);
		
                int immediate = stoi(imme, &pos, 0);
                instr.instruction |= (immediate << (7 + 5 + 3 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] imme: " << debug_print << "\n";
            }
            else if (opr == "sd")
            {
                // S-type instruction (currently only sd supported)
                int opcode = opr_to_opcode.find(opr)->second;

                // Extract rs_2
                pos = line.find_first_of(' ', 0) + 1;
                end = line.find_first_of(',', 0);

                std::string rs_2 = line.substr(pos, end - pos);

                unsigned int rs_2_index = reg_name_to_index.find(rs_2)->second;

                // Funct3
                unsigned int funct3 = opr_to_funct3.find(opr)->second;

                // Extract immediate
                pos = line.find_first_of(' ', pos + 1) + 1;
                end = line.find_first_of('(', 0);
		
                std::string imme = line.substr(pos, end - pos);

                int immediate = stoi(imme, &pos, 0);

                // Extract rs1
                pos = line.find_first_of('(', 0) + 1;
                end = line.find_first_of(')', 0);

                std::string rs_1 = line.substr(pos, end - pos);
                unsigned int rs_1_index = reg_name_to_index.find(rs_1)->second;

                // Format instruction
		instr.instruction |= opcode;
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] Only opcode: " << debug_print << "\n";

                int mask = 31;
                int first_five_bits = mask & immediate;
                instr.instruction |= (first_five_bits << 7);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme1: " << debug_print << "\n";

                instr.instruction |= (funct3 << (7 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with F3: " << debug_print << "\n";

                instr.instruction |= (rs_1_index << (7 + 5 + 3));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rs1: " << debug_print << "\n";
		
                instr.instruction |= (rs_2_index << (7 + 5 + 3 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rs2: " << debug_print << "\n";

                int last_seven_bits = (immediate >> 5);
                instr.instruction |= (last_seven_bits << (7 + 5 + 3 + 5 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme2: " << debug_print << "\n";
            }
            else if (opr == "beq" || 
                     opr == "bne" ||  
                     opr == "blt" || 
                     opr == "bge")
            {
                // SB-type instruction
                int opcode = opr_to_opcode.find(opr)->second;

                // Extract rs_1
                pos = line.find_first_of(' ', 0) + 1;
                end = line.find_first_of(',', 0);

                std::string rs_1 = line.substr(pos, end - pos);

                unsigned int rs_1_index = reg_name_to_index.find(rs_1)->second;

                // Funct3
                unsigned int funct3 = opr_to_funct3.find(opr)->second;

                // Extract rs_2
                pos = line.find_first_of(' ', pos + 1) + 1;
                end = line.find_first_of(',', end + 1);

                std::string rs_2 = line.substr(pos, end - pos);

                unsigned int rs_2_index = reg_name_to_index.find(rs_2)->second;

                // Extract immediate
                pos = line.find_first_of(' ', pos + 1) + 1;

                std::string imme = line.substr(pos, line.size() - pos);
		
                int immediate = stoi(imme, &pos, 0);

                // Format instruction		
                immediate = immediate >> 1;
                int bit_1_to_4 = immediate & 15;

                immediate = immediate >> 4;
                int bit_5_to_10 = immediate & 63;

                immediate = immediate >> 6;
                int bit_11 = immediate & 1;

                immediate = immediate >> 1;
                int bit_12 = immediate & 1;

                instr.instruction |= opcode;
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] Only opcode: " << debug_print << "\n";

                instr.instruction |= bit_11 << 7;
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme1: " << debug_print << "\n";

                instr.instruction |= bit_1_to_4 << (7 + 1);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme2: " << debug_print << "\n";

                instr.instruction |= funct3 << (7 + 1 + 4);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with F3: " << debug_print << "\n";

                instr.instruction |= rs_1_index << (7 + 1 + 4 + 3);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rs1: " << debug_print << "\n";

                instr.instruction |= rs_2_index << (7 + 1 + 4 + 3 + 5);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rs2: " << debug_print << "\n";

                instr.instruction |= bit_5_to_10 << (7 + 1 + 4 + 3 + 5 + 5);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme3: " << debug_print << "\n";

                instr.instruction |= bit_12 << (7 + 1 + 4 + 3 + 5 + 5 + 6);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme4: " << debug_print << "\n";
            }
            else if (opr == "jal")
            {
                // UI-type instruction
                int opcode = opr_to_opcode.find(opr)->second;

                // Extract rd
                pos = line.find_first_of(' ', 0) + 1;
                end = line.find_first_of(',', 0);

                std::string rd = line.substr(pos, end - pos);

                unsigned int rd_index = reg_name_to_index.find(rd)->second;

                // Extract immediate
                pos = line.find_first_of(' ', pos + 1) + 1;

                std::string imme = line.substr(pos, line.size() - pos);

                int immediate = stoi(imme, &pos, 0);

                // Format instruction
                immediate = immediate >> 1;
                int bit_1_to_10 = immediate & 1023;

                immediate = immediate >> 10;
                int bit_11 = immediate & 1;

                immediate = immediate >> 1;
                int bit_12_to_19 = immediate & 255;

                immediate = immediate >> 8;
                int bit_20 = immediate & 1;

                instr.instruction |= opcode;
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] Only opcode: " << debug_print << "\n";

                instr.instruction |= (rd_index << 7);
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with rd: " << debug_print << "\n";

                instr.instruction |= (bit_12_to_19 << (7 + 5));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme1: " << debug_print << "\n";

                instr.instruction |= (bit_11 << (7 + 5 + 8));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme2: " << debug_print << "\n";

                instr.instruction |= (bit_1_to_10 << (7 + 5 + 8 + 1));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme3: " << debug_print << "\n";

                instr.instruction |= (bit_20 << (7 + 5 + 8 + 1 + 10));
                // debug_print = instr.instruction;
                // std::cout << "[DEBUG] with imme4: " << debug_print << "\n";
            }

            instr.addr = addr;

            (instr_mem->instructions).insert(std::pair<long, Instruction>(addr, instr));	

            addr += 4;
        }
    }
}

