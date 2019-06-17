#include <iostream>
#include <fstream>
#include <vector>

#include "Config.h"
#include "Core.h"
#include "Socket.h"

using namespace std;

void run_simulation(Socket *socket);

int main(int argc, const char *argv[])
{	
	if (argc <= 3)
	{
		cout << "Usage: " << argv[0];
		cout << " <cfg file> <output-file> <instr-file-1> <instr-file-2> ..." << endl;
		
		return 0;
	}	

	/*
		Preparation	
	*/
	// Parse configuration file
	Config config(argv[1]);
	
	// Output file
	ofstream out(argv[2]);
		
	// Initialize Cores
	vector<Core *> cores;

	for (int i = 0; i < config.get_num_cores(); i++)
	{
		Core *core = new Core(argv[(3 + i)], &out);
		core->id = i;

		cores.push_back(core);
	}

	// Initialize Socket
	Socket *socket = new Socket(config, cores);

	/*
		Run Simulation
	*/
	if (config.get_mc_mode() != 1)
	{
		run_simulation(socket);
	}
	else
	{
		socket->printInstrs();
	}

	cout << "Execution Time (ns): " << socket->get_execution_time() << endl;

	/*
		Free Resource
	*/
	out.close();

	for (int i = 0; i < config.get_num_cores(); i++)
	{
		free(cores[i]);
	}

	free(socket);
}

void run_simulation(Socket *socket)
{
	while (true)
	{
		if (socket->tick() == false)
		{
			break;
		}
	}	
}
