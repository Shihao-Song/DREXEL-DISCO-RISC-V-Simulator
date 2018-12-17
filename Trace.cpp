#include "Trace.h"

Trace::Trace(Instruction_Memory *instr_mem, const string trace_fname) : 
	instr_mem (instr_mem),
	file (trace_fname)
{
	if (!file.good())
	{
		cerr << "Bad trace file: " << trace_fname << endl;
		exit(1);
	}

	/*
		Initialize reg_name_to_index
	*/
	for (int i = 0; i < NUM_OF_REGS; i++)
	{
		reg_name_to_index.insert(pair<string, int>(reg_name_sym[i], i));
	}
		
	/*
		Initialize opr_to_opcode and opr_to_funct3.

		You are welcome to add more here.
	*/

	/*
		I-type Instructions
	*/
	// ld
	opr_to_opcode.insert(pair<string, int>("ld", 3));	
	opr_to_funct3.insert(pair<string, int>("ld", 3));

	// addi
	opr_to_opcode.insert(pair<string, int>("addi", 19));	
	opr_to_funct3.insert(pair<string, int>("addi", 0));

	// slli
	opr_to_opcode.insert(pair<string, int>("slli", 19));	
	opr_to_funct3.insert(pair<string, int>("slli", 1));

	// xori
	opr_to_opcode.insert(pair<string, int>("xori", 19));	
	opr_to_funct3.insert(pair<string, int>("xori", 4));
	
	// srli
	opr_to_opcode.insert(pair<string, int>("srli", 19));	
	opr_to_funct3.insert(pair<string, int>("srli", 5));
	
	// ori
	opr_to_opcode.insert(pair<string, int>("ori", 19));	
	opr_to_funct3.insert(pair<string, int>("ori", 6));
	
	// andi
	opr_to_opcode.insert(pair<string, int>("andi", 19));	
	opr_to_funct3.insert(pair<string, int>("andi", 7));
	
	/*
		S-type instructions
	*/
	// sd
	opr_to_opcode.insert(pair<string, int>("sd", 35));	
	opr_to_funct3.insert(pair<string, int>("sd", 3));

	/*
		R-type instructions
	*/
	// add
	opr_to_opcode.insert(pair<string, int>("add", 51));	
	opr_to_funct3.insert(pair<string, int>("add", 0));
	
	// sll
	opr_to_opcode.insert(pair<string, int>("add", 51));	
	opr_to_funct3.insert(pair<string, int>("add", 0));

	// srl
	//
	// xor
	// or
	// and
}

void Trace::write_into_instr_mem()
{
	// Iterator all the lines
	while (!file.eof())
	{
		string line;
		getline(file, line);
		
		if (line.size() != 0)
		{
			Instruction instr;

			// (1) Extrac operation first
			size_t pos = line.find_first_not_of(' ', 0);
			size_t end = line.find_first_of(' ', 0);

			string opr = line.substr(pos, end - pos);

			// (2) Determine instruction type
			if (opr == "add")
			{
				// R-type instruction format
		//		instr.instr = opr_to_opcode.find()	
			}
		}
	}
}

/*
Trace::Trace(const string trace_fname) : file(trace_fname), trace_name(trace_fname)
{
	if (!file.good()) 
	{
        	cerr << "Bad trace file: " << trace_fname << endl;
        	exit(1);
    	}
}

bool Trace::get_memtrace_request(long long &req_addr, Request::Request_Type &req_type)
{
	string line;
	getline(file, line);
	if (file.eof()) 
	{
        	return false;
    	}

    	// pos - Pointer to an object of type size_t, whose value is set by the function to
    	// position of the next character in "line" after the numerical value
    	size_t pos;

	try
	{
    		req_addr = stoull(line, &pos, 0);
	}
	catch (out_of_range e)
	{
		req_addr = 0;
		req_type = Request::Request_Type::READ;

		return true;	
	}

    	// Extract request type and data (for write request only)
    	pos = line.find_first_not_of(' ', pos+1);

    	if (pos == string::npos || line.substr(pos)[0] == 'R')
    	{
        	req_type = Request::Request_Type::READ;
    	}
    	else if (line.substr(pos)[0] == 'W')
    	{
        	req_type = Request::Request_Type::WRITE;
	}
    	else 
    	{
    		assert(false);
    	}

    	return true;
}
*/
