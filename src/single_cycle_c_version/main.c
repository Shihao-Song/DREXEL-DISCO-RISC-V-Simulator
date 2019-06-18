#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "instructions.h"
#include "data.h"
#include "instructionfetch.h"
#include "decode.h"
#include "memory.h"
#include "writeback.h"
#include "execute.h"
#include "assembler.h"
#include "config.h"

void print_instruction(int* instruct){
    int i;
    for(i = 0; i < 32; i++)
    printf("%d", instruct[i]);
    printf("\n");

}

int main(int argc, char** argv){	
    // Declare some file pointers
    FILE *ifp, *dfp, *cfp;

    if(argc < 3){
        printf("USAGE: ./simulator <config.txt> <instruction_memory_1.txt> ...\n");
        return 1;
    }

    cfp = fopen(argv[1], "r");
    char buffer[100];
    char *token;
    int num_cores;
    float freq;

    fgets(buffer, 100, cfp);
    token = strtok(buffer, ":");
    token = strtok(NULL, ":");
    token++;
    num_cores = atoi(token);
    fgets(buffer, 100, cfp);
    token = strtok(buffer, ":");
    token = strtok(NULL, ":");
    token++;
    freq = atof(token);
    if(argc != num_cores + 2){
        printf("ERROR: You did not supply enough instruction memory files\nHint: Provide 1 file for each core\nYour configuration file specifies %d cores, so please run again with %d instruction memory files\n", num_cores, num_cores);
        return 1;
    }
    
    struct core cores[num_cores];
    int core_index;
    for(core_index = 0; core_index < num_cores; core_index++){
        cores[core_index].core_id = core_index;
        cores[core_index].freq = freq;
        cores[core_index].status = 1;

        ifp = fopen(argv[2 + core_index], "r");
        struct instruction_memory instructions;
        assembly_to_machine(ifp, &instructions);
        fclose(ifp);
        cores[core_index].instruction_set = instructions;
    }
    
    // Open the data memory file and load it into a struct
    dfp = fopen("data_memory.txt", "r+");

    struct data_memory mem;
    init_data_memory(dfp, &mem);

    struct instruction_memory core_instructs;

    struct register_data registers;
    init_register_data(&registers);
    double time_taken = 0;
    int i = 0;
    for(i = 0; i < num_cores; i++){
        clock_t t;
        t = clock();
        core_instructs.num_instructions = cores[i].instruction_set.num_instructions;
	printf("NUM_INSTRUCTS : %d\n", core_instructs.num_instructions);
        int j;
        for(j =0; j < 256; j++){
            int k;
            for(k =0; k < 32; k++){
                core_instructs.instructions_array[j][k] = cores[i].instruction_set.instructions_array[j][k];
            }
        }
        
	// Initialize the program counter
	int pc;
	int branch = -1;
	
	// FIXME, Iterate over each instruction while incrementing the pc
	// Decode the instructions in the loop as well
	for(pc = 0; pc < core_instructs.num_instructions;pc++){
            
            int instruct[32];
            instruction_fetch(&core_instructs, pc, instruct);
        	
	    /*Decode the instruction*/
  	    struct decode_info decoded_instruction;
            decode_instruction(instruct, &decoded_instruction, &registers);
		
	    /*Execute the instruction*/
            // TODO, implement execute()
	    branch = execute(&decoded_instruction, pc);
		
	    /*If the instruction is i type, feed it to the mem stage*/
	    if(decoded_instruction.i_type.valid || decoded_instruction.s_type.valid || decoded_instruction.uj_type.valid)
            // TODO, implement memory()
	    memory(&decoded_instruction, &mem, &registers);
	    
	    /*Go to writeback stage*/
            // TODO, implement writeback()
	    writeback(&decoded_instruction, &registers);
	
	    if(branch > 0){
            	pc = branch - 1;
          	branch = -1;
            }  
	}

        t = clock() - t;
        time_taken = (time_taken + ((double) t)) * (1 / freq);
    }

    // This is all testing... will need to move into the for-loop	
    // Declare a decode struct and decode the instruction
    int a;
    size_t ret;
    fseek(dfp, 0, SEEK_SET);
    for(a =0; a <mem.num_data ; a++){
        fprintf(dfp, "%d\n", mem.data[a]);
    }
    
    // Print register values
    print_registers(&registers);
    printf("Time elapsed is: %.3fns\n", (time_taken / CLOCKS_PER_SEC) * 1000000000);
    
    fclose(dfp);  
    return 0;
}
