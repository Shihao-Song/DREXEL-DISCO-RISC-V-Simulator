#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "decode.h"
#include "assembler.h"
// A function that returns the specified array of bits in a number

void decode_instruction(int* instruction, struct decode_info *decode, struct register_data* registers){
	// All opcode in same location!
	int opcode_arr[7]; 
	unsigned int opcode;
	get_bits(instruction, 0, 6, opcode_arr);
    	opcode = convert_arr_to_decimal(opcode_arr, 7);
	struct r_type_info r_type_data;
	struct i_type_info i_type_data;
	struct s_type_info s_type_data;
	struct sb_type_info sb_type_data;
	struct uj_type_info uj_type_data;
	switch(opcode){
		// R-type (add sub sll srl xor or and)
		case 0b0110011:
			;
            		int r_dest_reg_arr[5];
			get_bits(instruction, 7, 11, r_dest_reg_arr);
			unsigned int r_dest_reg = convert_arr_to_decimal(r_dest_reg_arr, 5);
		       
			int r_funct3_arr[3];
			get_bits(instruction, 12, 14, r_funct3_arr);
			unsigned int r_funct3 = convert_arr_to_decimal(r_funct3_arr, 3);
				
			int r_source_reg_1_arr[5];
			get_bits(instruction, 15, 19, r_source_reg_1_arr);
			unsigned int r_source_reg_1 = convert_arr_to_decimal(r_source_reg_1_arr, 5);
								
			int r_source_reg_2_arr[5];
			get_bits(instruction, 20, 24, r_source_reg_2_arr);
			unsigned int r_source_reg_2 = convert_arr_to_decimal(r_source_reg_2_arr, 5);
		
			int r_funct7_arr[7];
			get_bits(instruction, 25, 31, r_funct7_arr);
			unsigned int r_funct7 = convert_arr_to_decimal(r_funct7_arr, 7);
		    
			r_type_data.valid = 1;
			r_type_data.opcode = opcode;
			r_type_data.r_dest_reg = r_dest_reg;
			r_type_data.r_funct3 = r_funct3;
			r_type_data.r_source_reg_1 = r_source_reg_1;
			r_type_data.r_source_reg_2 = r_source_reg_2;
			r_type_data.r_funct7 = r_funct7;
			
			/*Read the value of the register array for the source reg vales*/
			r_type_data.r_source_reg_1_value = registers->registers_data[r_source_reg_1];
            		r_type_data.r_source_reg_2_value = registers->registers_data[r_source_reg_2];

            		decode->r_type = r_type_data;

            		i_type_data.valid = 0;
			s_type_data.valid = 0;
			sb_type_data.valid = 0;
			uj_type_data.valid = 0;

			decode->i_type = i_type_data;
			decode->s_type = s_type_data;
			decode->sb_type = sb_type_data;
			decode->uj_type = uj_type_data;

			break;
		// I-type (addi slli xori srli ori andi)
        	case 0b0010011:
		// Special I-type (ld) 
		case 0b0000011:
		// Special I-type (jalr)
		case 0b1100111:
			;
			int i_dest_reg_arr[5];
			get_bits(instruction, 7, 11, i_dest_reg_arr);
			unsigned int i_dest_reg = convert_arr_to_decimal(i_dest_reg_arr, 5);
			int i_funct3_arr[3];
			get_bits(instruction, 12, 14, i_funct3_arr);
			unsigned int i_funct3 = convert_arr_to_decimal(i_funct3_arr, 3);
				
			int i_source_reg_arr[5];
			get_bits(instruction, 15, 19, i_source_reg_arr);
			unsigned int i_source_reg = convert_arr_to_decimal(i_source_reg_arr, 5);
								
			int i_imm_arr[12];
			get_bits(instruction, 20, 31, i_imm_arr);
			unsigned int i_imm = convert_arr_to_decimal(i_imm_arr, 12);
			
			i_type_data.valid = 1;
			i_type_data.opcode = opcode;
			i_type_data.i_dest_reg = i_dest_reg;
			i_type_data.i_funct3 = i_funct3;
			i_type_data.i_source_reg = i_source_reg;
			i_type_data.i_imm = i_imm;

			/*Read the value of the source reg here*/
			i_type_data.i_source_reg_value = registers->registers_data[i_source_reg];
			decode->i_type = i_type_data;
                

			r_type_data.valid = 0;
			s_type_data.valid = 0;
			sb_type_data.valid = 0;
			uj_type_data.valid = 0;

			decode->r_type = r_type_data;
			decode->s_type = s_type_data;
			decode->sb_type = sb_type_data;
			decode->uj_type = uj_type_data;
			
			break;
		// S-type (sd)
		case 0b0100011:
			;
			int s_imm_1_arr[5];
			get_bits(instruction, 7, 11, s_imm_1_arr);
			unsigned int s_imm_1 = convert_arr_to_decimal(s_imm_1_arr, 5);
		    
			int s_funct3_arr[3];
			get_bits(instruction, 12, 14, s_funct3_arr);
			unsigned int s_funct3 = convert_arr_to_decimal(s_funct3_arr, 3);
				
			int s_source_reg_1_arr[5];
			get_bits(instruction, 15, 19, s_source_reg_1_arr);
			unsigned int s_source_reg_1 = convert_arr_to_decimal(s_source_reg_1_arr, 5);
								
			int s_source_reg_2_arr[5];
			get_bits(instruction, 20, 24, s_source_reg_2_arr);
			unsigned int s_source_reg_2 = convert_arr_to_decimal(s_source_reg_2_arr, 5);
		
			int s_imm_2_arr[7];
			get_bits(instruction, 25, 31, s_imm_2_arr);
			unsigned int s_imm_2 = convert_arr_to_decimal(s_imm_2_arr, 7);
			
            		s_type_data.valid = 1;
			s_type_data.opcode = opcode;
			s_type_data.s_imm_1 = s_imm_1;
			s_type_data.s_funct3 = s_funct3;
    			s_type_data.s_source_reg_1 = s_source_reg_1;
			s_type_data.s_source_reg_2 = s_source_reg_2;
			s_type_data.s_imm_2 = s_imm_2;

			/*Read the value of the source reg here*/
			//s_type_data.s_source_reg_1_value = registers->registers_data[s_source_reg_1];

			s_type_data.s_source_reg_2_value = registers->registers_data[s_source_reg_2];

			decode->s_type = s_type_data;

			r_type_data.valid = 0;
			i_type_data.valid = 0;
			sb_type_data.valid = 0;
			uj_type_data.valid = 0;

			decode->r_type = r_type_data;
			decode->i_type = i_type_data;
			decode->sb_type = sb_type_data;
			decode->uj_type = uj_type_data;
			
			break;
		// SB-type (beq bne blt bge)
        	case 0b1100011:
			;
			int sb_imm_1_arr[5];
			get_bits(instruction, 7, 11, sb_imm_1_arr);
			unsigned int sb_imm_1 = convert_arr_to_decimal(sb_imm_1_arr, 5);
		       
			int sb_funct3_arr[3];
			get_bits(instruction, 12, 14, sb_funct3_arr);
			unsigned int sb_funct3 = convert_arr_to_decimal(sb_funct3_arr, 3);
				
			int sb_source_reg_1_arr[5];
			get_bits(instruction, 15, 19, sb_source_reg_1_arr);
			unsigned int sb_source_reg_1 = convert_arr_to_decimal(sb_source_reg_1_arr, 5);
								
			int sb_source_reg_2_arr[5];
			get_bits(instruction, 20, 24, sb_source_reg_2_arr);
			unsigned int sb_source_reg_2 = convert_arr_to_decimal(sb_source_reg_2_arr, 5);
		
			int sb_imm_2_arr[7];
			get_bits(instruction, 25, 31, sb_imm_2_arr);
			unsigned int sb_imm_2 = convert_arr_to_decimal(sb_imm_2_arr, 7);
			

			sb_type_data.valid = 1;
			sb_type_data.opcode = opcode;
			sb_type_data.sb_imm_1 = sb_imm_1;
			sb_type_data.sb_funct3 = sb_funct3;
			sb_type_data.sb_source_reg_1 = sb_source_reg_1;
			sb_type_data.sb_source_reg_2 = sb_source_reg_2;
			sb_type_data.sb_imm_2 = sb_imm_2;

			/*Read the value of the source reg here*/
			sb_type_data.sb_source_reg_1_value = registers->registers_data[sb_source_reg_1];
			sb_type_data.sb_source_reg_2_value = registers->registers_data[sb_source_reg_2];
			decode->sb_type = sb_type_data;

            		r_type_data.valid = 0;
			i_type_data.valid = 0;
			s_type_data.valid = 0;
			uj_type_data.valid = 0;

			decode->r_type = r_type_data;
			decode->i_type = i_type_data;
			decode->s_type = s_type_data;
			decode->uj_type = uj_type_data;
			
			break;
		// UJ-type (jal)
		case 0b0101111:
			;
        		int uj_dest_reg_arr[5];
			get_bits(instruction, 7, 11, uj_dest_reg_arr);
			unsigned int uj_dest_reg = convert_arr_to_decimal(uj_dest_reg_arr, 5);
		    
			int uj_imm_arr[20];
			get_bits(instruction, 12, 31, uj_imm_arr);
			unsigned int uj_imm = convert_arr_to_decimal(uj_imm_arr, 20);
			
			uj_type_data.valid = 1;
			uj_type_data.opcode = opcode;
			uj_type_data.uj_dest_reg = uj_dest_reg;
			uj_type_data.uj_imm = uj_imm;
			decode->uj_type = uj_type_data;

			r_type_data.valid = 0;
			i_type_data.valid = 0;
			s_type_data.valid = 0;
			sb_type_data.valid = 0;

			decode->r_type = r_type_data;
			decode->i_type = i_type_data;
			decode->s_type = s_type_data;
			decode->sb_type = sb_type_data;
			
			break;
		// No-type	
		default:
			printf("This instruction is not supported!\n");
	}
};
