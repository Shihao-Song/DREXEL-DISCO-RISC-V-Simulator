#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int dump_registers_to_data_memory(struct register_data* registers, FILE *dfp){
	int i;
	for(i =0; i <registers->num_registers; i++){
		fprintf(dfp, "%i\n", registers->registers_data[i]);
	}
}

