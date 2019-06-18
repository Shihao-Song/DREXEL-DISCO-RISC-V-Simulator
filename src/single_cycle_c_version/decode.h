#include <stdio.h>
#include "data.h"
struct r_type_info{
	int valid;
	unsigned int opcode;
	unsigned int r_dest_reg;
	unsigned int r_funct3;
	unsigned int r_source_reg_1;
	unsigned int r_source_reg_2;
	unsigned int r_funct7;

	unsigned int r_dest_reg_value;
	unsigned int r_source_reg_1_value;
	unsigned int r_source_reg_2_value;

};

struct i_type_info{
	int valid;
	unsigned int opcode;
	unsigned int i_dest_reg;
	unsigned int i_funct3;
	unsigned int i_source_reg;
	unsigned int i_imm;
	
	unsigned int i_dest_reg_value;
	unsigned int i_source_reg_value;
};

struct s_type_info{
	int valid;
	unsigned int opcode;
	unsigned int s_imm_1;
	unsigned int s_funct3;
	unsigned int s_source_reg_1;
	unsigned int s_source_reg_2;
	unsigned int s_imm_2;

	unsigned int s_source_reg_1_value;
	unsigned int s_source_reg_2_value;
    unsigned int s_imm_full;
};

struct sb_type_info{
	int valid;
	unsigned int opcode;
        unsigned int sb_imm_1;
	unsigned int sb_funct3;
	unsigned int sb_source_reg_1;
	unsigned int sb_source_reg_2;
	unsigned int sb_imm_2;

	unsigned int sb_source_reg_1_value;
	unsigned int sb_source_reg_2_value;
};

struct uj_type_info{
	int valid;
	unsigned int opcode;
	unsigned int uj_dest_reg;
	unsigned int uj_imm;

	unsigned int uj_dest_reg_value;
};

struct decode_info{
	struct r_type_info r_type;
	struct i_type_info i_type;	
	struct s_type_info s_type;
	struct sb_type_info sb_type;
	struct uj_type_info uj_type;
};

void decode_instruction(int* instruction, struct decode_info *decode, struct register_data* registers);
