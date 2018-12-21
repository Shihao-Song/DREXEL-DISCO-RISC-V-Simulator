#include <iostream>
#include <fstream>
#include <bitset>

#include "Instruction_Memory.h"
#include "Instruction.h"

using namespace std;

int main(int argc, const char *argv[])
{	
	if (argc <= 3)
	{
		cout << "Usage: " << argv[0];
		cout << " <cfg file> <output-file> <instr-file-1> <instr-file-2> ..." << endl;
		
		return 0;
	}	

	Instruction_Memory instr_mem(argv[1]);
	
	/*
		Output File
	*/
	ofstream out(argv[2]);

	/*
		Free Resource
	*/
	out.close();
}

