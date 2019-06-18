#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int dump_data_memory_to_data_memory(struct data_memory* data, FILE *dfp){
	int i;
	for (i = 0; i < data->num_data; i++){
		fprintf(dfp, "i\n", data->data[i]);
	}
}
