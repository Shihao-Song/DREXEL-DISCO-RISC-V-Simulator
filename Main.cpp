#include <iostream>
#include <fstream>

#include "Instruction_Memory.h"

using namespace std;

int main(int argc, const char *argv[])
{	
	if (argc != 3)
	{
		//cout << "Usage: " << argv[0];
		//cout << " <trace-file> <output-file>" << endl;
		
		//return 0;
	}	

	Instruction_Memory inst_mem(argv[1]);

	/*
		Output File
	*/
	ofstream out(argv[2]);

	/*
		Free Resource
	*/
	out.close();
}

