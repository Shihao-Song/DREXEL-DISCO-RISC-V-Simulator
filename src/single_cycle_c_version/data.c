#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE_SIZE 32


// A struct to store the data memory in an array of ints
struct data_memory{
	int num_data;
	int data[256];
};

struct register_data{
	int num_registers;
	int registers_data[32];	
};

// A function to print the data
void print_data(struct data_memory *mem){
	printf("Number of data items: %i\n", mem->num_data);
	int i;
	for(i = 0; i<mem->num_data;i++)
		printf("%i\n", mem->data[i]);
}
// A function that reads the file and adds the data into the struct
void init_data_memory(FILE *dfp, struct data_memory *mem){
	int i = 0;
	char buffer[MAX_LINE_SIZE];
	int int_data;
	while(fgets(buffer, MAX_LINE_SIZE, dfp)!= NULL){
		int int_data = atoi(buffer);
		mem->data[i] = int_data;
		i++;
	}
	mem->num_data = i;
}

void print_registers(struct register_data* registers){
    int i;
	registers->num_registers = 32;
	for(i = 0; i < registers->num_registers; i++){
		printf("reg%d = %d\n",i, registers->registers_data[i]);
	}


}

void init_register_data(struct register_data* registers){
	int i;
	registers->num_registers = 32;
	for(i = 0; i < registers->num_registers; i++){
		if(i == 0){
            registers->registers_data[i] = 0;
        }
        else{
            registers->registers_data[i] = -1;
          }
	}
}
