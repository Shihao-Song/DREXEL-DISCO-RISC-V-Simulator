#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "instructions.h"

/* Creates an array of binary values backwards*/
void convert_to_binary_arr(int num_bits, int num, int* array){
    int c, k;
    for(c = num_bits; c >= 0; c--){
        k = num >> c;

        if(k & 1){
            array[c] = 1;
        }
        else{
            array[c] = 0;
        } 
    }

}

int modify_bit(int n, int p, int b){
    int mask = 1 << p;
    return (n & ~mask) | ((b << p) & mask);
}
void modify_bits(int *instruction, int start, int finish, int *num){
    int i;
    int counter = 0;
    for(i = finish; i >= start; i--){
        instruction[i] = num[counter];
        counter++;
    }

}

void get_bits(int *instruction, int start, int finish, int *num){
    int i;
    int pos = 0;
    for(i = start; i <= finish; i++){
        num[pos] = instruction[i];
        pos++;
    }
}

int convert_arr_to_decimal(int *arr, int num_bits){
    int decimal = 0;
    int i;
    int power = 1;
    for(i = 0; i < num_bits; i++){
        int index = (num_bits - 1) - i;
        decimal += arr[index] * power;
        power *= 2;
    }

    return decimal;
}

void init_instruct(int *instruction){
    int i;
    for(i = 0;i < 32; i++)
        instruction[i] = 0;

}

int check_type(char** functs, char* command, int num_functs){
    
    int i = 0;
    for(i = 0; i < num_functs; i++){
        char* pos = functs[i];
        if(strstr(command, pos) != NULL)
            return 1;
    }

    return 0;
}

void assembly_to_machine(FILE *fp, struct instruction_memory *instruct){
    //First, get the instruction
    //Read the type
    char test[100];
    int num_instructs = 0;
    while(fgets(test, 100, fp)){
            char * instruction = strtok(test, "\n");
            int instruction_template[32];
            init_instruct(instruction_template);
            int not_decoded = 1;
    int opcode[7];
    int funct3[3];
    int funct7[7];
    int rd[5];
    int rs1[5];
    int rs2[5];
    int imm_i[12];
    int imm_uj[20];
    int imm_s[12];
    int imm_sb[12];
    int i;
    int split_count;

    if(not_decoded){
        char i_types[8][5];
    strcpy(i_types[0], "ld");
    strcpy(i_types[1], "addi");
    strcpy(i_types[2], "slli");
    strcpy(i_types[3], "ori");
    strcpy(i_types[4], "srli");
    strcpy(i_types[5], "xori");
    strcpy(i_types[6], "andi");
    strcpy(i_types[7], "jalr");
    /* Determine what type of instruction it is*/
    for(i = 0; i< 8; i++){
        if(strstr(instruction, i_types[i]) != NULL){
            /* Deal with I-types from here*/
            /* Assembly: addi x7, x8, imm*/
            char i_type_split[3][256];
            char backup [100];
            strcpy(backup, instruction);
            char* token;
            char* rest = instruction;
            
            split_count = 0;
            while((token = strtok_r(rest, " ", &rest))){
                if(split_count > 0){
                    char* temp = token;
                    if(split_count < 3){
                        temp++;
                        temp[strlen(temp) -1 ] = 0;
                    }
                    strcpy(i_type_split[split_count-1], temp);
                }
                split_count++;
            }
            convert_to_binary_arr(5, atoi(i_type_split[0]),rd);
            modify_bits(instruction_template,7, 11, rd);
            
            convert_to_binary_arr(5, atoi(i_type_split[1]), rs1);
            modify_bits(instruction_template, 15, 19, rs1);

            convert_to_binary_arr(12, atoi(i_type_split[2]), imm_i);
            modify_bits(instruction_template, 20, 31, imm_i);

            if(!(strcmp(i_types[i], "ld")))
            {
                convert_to_binary_arr(7, 3, opcode);
                //instruction_template = modify_bits(instruction_template, 0, 7, opcode);
                modify_bits(instruction_template, 0, 6, opcode);
                convert_to_binary_arr(3,3, funct3);
                modify_bits(instruction_template, 12, 14, funct3);
                char* new_token;
                char* new_rest = backup;
                split_count = 0;

                char end[3];
                strncpy(end, &backup[strlen(backup)-3], 2);
                end[2] = '\0';
                strcpy(i_type_split[2], end);
                while((new_token = strtok_r(new_rest, " ", &new_rest))){
                    if(split_count == 1){
                    char *temp = new_token;
                    temp++;
                    temp[strlen(temp) -1 ] = 0;
                    strcpy(i_type_split[0], temp);
                }
                if(split_count == 2){
                    char *temp2 = strtok_r(new_token, "(", &token);
                    temp2++;
                    strcpy(i_type_split[1], temp2);
                }   

                 split_count++;
             }
                convert_to_binary_arr(5, atoi(i_type_split[0]),rd);
                modify_bits(instruction_template,7, 11, rd);
        
                convert_to_binary_arr(5, atoi(i_type_split[1]), rs1);
                modify_bits(instruction_template, 15, 19, rs1);
                
                convert_to_binary_arr(12, atoi(i_type_split[2]), imm_i);
                modify_bits(instruction_template, 20, 31, imm_i);

            }
            else if(!(strcmp(i_types[i], "addi"))){
                
                convert_to_binary_arr(7, 19, opcode);
                //instruction_template = modify_bits(instruction_template, 0, 7, opcode);
                modify_bits(instruction_template, 0, 6, opcode);
    
                convert_to_binary_arr(3,0, funct3);
                 modify_bits(instruction_template, 12, 14, funct3);
            }
            else if(!(strcmp(i_types[i], "slli"))){
                
                convert_to_binary_arr(7, 19, opcode);
                modify_bits(instruction_template, 0, 6, opcode);

                convert_to_binary_arr(3,1, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

            }
            else if(!(strcmp(i_types[i], "srli"))){
                 convert_to_binary_arr(7, 19, opcode);
                //instruction_template = modify_bits(instruction_template, 0, 7, opcode);
                modify_bits(instruction_template, 0, 6, opcode);

                convert_to_binary_arr(3,5, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

            }
            else if(!(strcmp(i_types[i], "ori"))){
                 convert_to_binary_arr(7, 19, opcode);
                //instruction_template = modify_bits(instruction_template, 0, 7, opcode);
                modify_bits(instruction_template, 0, 6, opcode);

                convert_to_binary_arr(3,6, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

            }
            else if(!(strcmp(i_types[i], "xori"))){
                 convert_to_binary_arr(7, 19, opcode);
                //instruction_template = modify_bits(instruction_template, 0, 7, opcode);
                modify_bits(instruction_template, 0, 6, opcode);

                
                convert_to_binary_arr(3,4, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

            }

            else if(!(strcmp(i_types[i], "andi"))){
                 convert_to_binary_arr(7, 19, opcode);
                //instruction_template = modify_bits(instruction_template, 0, 7, opcode);
                modify_bits(instruction_template, 0, 6, opcode);

                convert_to_binary_arr(3,7, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

            }
            else if(!(strcmp(i_types[i], "jalr"))){
                char* new_token;
                char* new_rest = backup;
                split_count = 0;

                char end[3];
                strncpy(end, &backup[strlen(backup)-3], 2);
                end[2] = '\0';
                strcpy(i_type_split[2], end);
                while((new_token = strtok_r(new_rest, " ", &new_rest))){
                    if(split_count == 1){
                    char *temp = new_token;
                    temp++;
                    temp[strlen(temp) -1 ] = 0;
                    strcpy(i_type_split[0], temp);
                }
                if(split_count == 2){
                    char *temp2 = strtok_r(new_token, "(", &token);
                    temp2++;
                    strcpy(i_type_split[1], temp2);
                }   

                 split_count++;
             }
                convert_to_binary_arr(5, atoi(i_type_split[0]),rd);
                modify_bits(instruction_template,7, 11, rd);
        
                convert_to_binary_arr(5, atoi(i_type_split[1]), rs1);
                modify_bits(instruction_template, 15, 19, rs1);
                
                convert_to_binary_arr(12, atoi(i_type_split[2]), imm_i);
                modify_bits(instruction_template, 20, 31, imm_i);

                
                convert_to_binary_arr(7, 103, opcode);
                modify_bits(instruction_template, 0, 6, opcode);
                
                convert_to_binary_arr(3,0, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

            }
            not_decoded = 0;
        }
    }
    }
    if(not_decoded){
        char s_types[1][3];
    strcpy(s_types[0], "sd");
    if(strstr(test, s_types[0]) != NULL){
        /* Assembly: sw rs2, imm(rs1)*/
        convert_to_binary_arr(7, 35, opcode);
        modify_bits(instruction_template, 0, 6, opcode);
        
        char s_type_split[3][256];
        char* token;
        char* rest = instruction;
        split_count = 0;
        while((token = strtok_r(rest, " ", &rest))){
            if(split_count == 1){
                char *temp = token;
                temp++;
                temp[strlen(temp) -1 ] = 0;
                strcpy(s_type_split[0], temp);
            }
            if(split_count == 2){
                char *temp2 = strtok_r(token, "(", &token);
                token++;
                token[strlen(token) -1 ] = 0;

                strcpy(s_type_split[1], token);
                strcpy(s_type_split[2], temp2);
            }

            split_count++;
        }
        convert_to_binary_arr(5, atoi(s_type_split[0]),rd);
        modify_bits(instruction_template,15, 19, rd);
        
        convert_to_binary_arr(5, atoi(s_type_split[1]), rs1);
        modify_bits(instruction_template, 20, 24, rs1);

        convert_to_binary_arr(3, 3, funct3);
        modify_bits(instruction_template, 12, 14, funct3);

        convert_to_binary_arr(12, atoi(s_type_split[2]), imm_s);
        int temp1[5];
        temp1[4] = imm_s[11];
        temp1[3] = imm_s[10];
        temp1[2] = imm_s[9];
        temp1[1] = imm_s[8];
        temp1[0] = imm_s[7];
        int temp2[7];
        temp2[6] = imm_s[6];
        temp2[5] = imm_s[5];
        temp2[4] = imm_s[4];
        temp2[3] = imm_s[3];
        temp2[2] = imm_s[2];
        temp2[1] = imm_s[1];
        temp2[0] = imm_s[0];
        modify_bits(instruction_template, 7, 11, temp1);
        modify_bits(instruction_template, 25,31, temp2);
        not_decoded = 0;
    }
    }
    if(not_decoded){
        char r_types[7][4];
    strcpy(r_types[0], "add");
    strcpy(r_types[1], "sub");
    strcpy(r_types[2], "sll");
    strcpy(r_types[3], "srl");
    strcpy(r_types[4], "XOR");
    strcpy(r_types[5], "or");
    strcpy(r_types[6], "and");
    
    for(i = 0; i< 7; i++){
        if(strstr(instruction, r_types[i]) != NULL){
            /* Deal with R-types from here*/
            /* Assembly: add x7, x8, x9*/
            convert_to_binary_arr(7, 51, opcode);
            modify_bits(instruction_template, 0, 6, opcode);
            char r_type_split[3][256];
            char* token;
            char* rest = instruction;
            split_count = 0;
            while((token = strtok_r(rest, " ", &rest))){
                if(split_count > 0){
                    char* temp = token;
                    if(split_count < 3){
                        temp++;
                        temp[strlen(temp) -1 ] = 0;
                    }
                    if(split_count == 3){
                        temp++;
                    }
                    strcpy(r_type_split[split_count-1], temp);
                }
                split_count++;
            }
            convert_to_binary_arr(5, atoi(r_type_split[0]),rd);
            modify_bits(instruction_template,7, 11, rd);

            convert_to_binary_arr(5, atoi(r_type_split[1]), rs1);
            modify_bits(instruction_template, 15, 19, rs1);
            convert_to_binary_arr(5, atoi(r_type_split[2]), rs2);
            modify_bits(instruction_template, 20, 24, rs2);

            if(!(strcmp(r_types[i], "add"))){
                convert_to_binary_arr(3,0, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

                convert_to_binary_arr(7, 0, funct7);
                modify_bits(instruction_template, 25, 31, funct7);
            }
            else if(!(strcmp(r_types[i], "sub"))){
                convert_to_binary_arr(3,0, funct3);
                modify_bits(instruction_template, 12, 14, funct3);
                
                convert_to_binary_arr(7, 32, funct7);
                modify_bits(instruction_template, 25, 31, funct7);

            }
            else if(!(strcmp(r_types[i], "sll"))){
                convert_to_binary_arr(3,1, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

                convert_to_binary_arr(7, 0, funct7);
                modify_bits(instruction_template, 25, 31, funct7);

            }
            else if(!(strcmp(r_types[i], "srl"))){
                convert_to_binary_arr(3,5, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

                convert_to_binary_arr(7, 0, funct7);
                modify_bits(instruction_template, 25, 31, funct7);

            }
            else if(!(strcmp(r_types[i], "or"))){
                printf("Or\n");
                convert_to_binary_arr(3,6, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

                convert_to_binary_arr(7, 0, funct7);
                modify_bits(instruction_template, 25, 31, funct7);
            }

            else if(!(strcmp(r_types[i], "XOR"))){
                printf("xor\n");
                convert_to_binary_arr(3,4, funct3);
                modify_bits(instruction_template, 12, 14, funct3);
                
                convert_to_binary_arr(7, 0, funct7);
                modify_bits(instruction_template, 25, 31, funct7);

            }
            else if(!(strcmp(r_types[i], "and"))){
                convert_to_binary_arr(3,7, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

                convert_to_binary_arr(7, 0, funct7);
                modify_bits(instruction_template, 25, 31, funct7);

            }
            not_decoded = 0;
        }
    }
    }

    if(not_decoded){
    char sb_types[4][4];
    strcpy(sb_types[0], "beq");
    strcpy(sb_types[1], "bne");
    strcpy(sb_types[2], "blt");
    strcpy(sb_types[3], "bge");
    for(i = 0; i< 4; i++){
        if(strstr(instruction, sb_types[i]) != NULL){
            /* Deal with SB-types from here*/
            /* Assembly: rs1, rs2, imm*/
            convert_to_binary_arr(7, 99, opcode);
            modify_bits(instruction_template, 0, 6, opcode);

            char sb_type_split[3][256];
            char* token;
            char* rest = instruction;
            split_count = 0;
            while((token = strtok_r(rest, " ", &rest))){
                if(split_count > 0){
                    char* temp = token;
                    if(split_count < 3){
                        temp++;
                        temp[strlen(temp) -1 ] = 0;
                    }
                    strcpy(sb_type_split[split_count-1], temp);
                }
                split_count++;
            }
            convert_to_binary_arr(5, atoi(sb_type_split[0]),rs1);
            modify_bits(instruction_template,15, 19, rs1);
            
            convert_to_binary_arr(5, atoi(sb_type_split[1]), rs2);
            modify_bits(instruction_template, 20, 24, rs2);
            convert_to_binary_arr(12, atoi(sb_type_split[2]), imm_sb);
            int temp1[5];
            temp1[4] = imm_sb[11];
            temp1[3] = imm_sb[10];
            temp1[2] = imm_sb[9];
            temp1[1] = imm_sb[8];
            temp1[0] = imm_sb[7];
            int temp2[7];
            temp2[6] = imm_sb[6];
            temp2[5] = imm_sb[5];
            temp2[4] = imm_sb[4];
            temp2[3] = imm_sb[3];
            temp2[2] = imm_sb[2];
            temp2[1] = imm_sb[1];
            temp2[0] = imm_sb[0];
            modify_bits(instruction_template, 7, 11, temp1);
            modify_bits(instruction_template, 25,31, temp2);

            if(!(strcmp(sb_types[i], "beq"))){
                convert_to_binary_arr(3,0, funct3);
                modify_bits(instruction_template, 12, 14, funct3);
            }
            else if(!(strcmp(sb_types[i], "bne"))){
                convert_to_binary_arr(3,1, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

            }
            else if(!(strcmp(sb_types[i], "blt"))){
                convert_to_binary_arr(3,4, funct3);
                modify_bits(instruction_template, 12, 14, funct3);
            }
            else if(!(strcmp(sb_types[i], "bge"))){
                convert_to_binary_arr(3,5, funct3);
                modify_bits(instruction_template, 12, 14, funct3);

            }
            not_decoded = 0;
        }
    }
    }

    if(not_decoded){
    char uj_types[1][4];
    strcpy(uj_types[0], "jal");
    if(strstr(instruction, uj_types[0]) != NULL){
        /*deal with uj types*/
        /* Assembly: jal rd, imm*/
        convert_to_binary_arr(7,111 , opcode);
        int a;
        for(a =0; a < 7; a++){
            printf("%d",opcode[a]);
        }
        printf("\n");
        modify_bits(instruction_template, 0, 6, opcode);
        char uj_type_split[2][256];
        char* token;
        char* rest = instruction;
        split_count = 0;
        while((token = strtok_r(rest, " ", &rest))){
            if(split_count > 0){
                char* temp = token;
                if(split_count < 2){
                    temp++;
                    temp[strlen(temp) -1 ] = 0;
                }
                strcpy(uj_type_split[split_count-1], temp);
            }
            split_count++;
        }
        printf("The imm is %s\n", uj_type_split[1]);
        convert_to_binary_arr(5, atoi(uj_type_split[0]),rd);
        modify_bits(instruction_template,7, 11, rd);
            
        convert_to_binary_arr(20, atoi(uj_type_split[1]), imm_uj);
        modify_bits(instruction_template, 12, 31, imm_uj);
        not_decoded = 0;
    }
    }
    /* Based on what type it is, parse the remaining information*/
    /* Assign the remaining information to the value*/
    /* Store the instruction into the structure*/
    
    int z;
    for(z =0; z < 32; z++){
        instruct->instructions_array[num_instructs][z] = instruction_template[z];
    }
    num_instructs++;
    }
    
    instruct->num_instructions = num_instructs;

}
