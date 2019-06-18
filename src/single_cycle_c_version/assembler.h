#include "instructions.h"
int modify_bit(int n, int p, int b);
void assembly_to_machine(FILE *fp, struct instruction_memory *instruct);
void get_bits(int* instruction, int start, int finish, int *num);
int convert_arr_to_decimal(int *arr, int num_bits);

