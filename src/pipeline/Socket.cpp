#include "Socket.h"

Socket::Socket(const Config &configs, vector<Core *> &cores) : 
	ref_clk(0),
	clk(0),
	cores(cores),
	num_cores(configs.get_num_cores()),
	frequency(configs.get_freq())
{

}

bool Socket::tick()
{
	int trigger_for_x_clks = int(ceil(1.0 / frequency));

	vector<bool> end; // Indicate if any core runs out of the instructions
	for (int i = 0; i < cores.size(); i++)
	{
		end.push_back(true);
	}

	// Trigger all the cores
	for (int i = 0; i < cores.size(); i++)	
	{
		if (ref_clk % trigger_for_x_clks == 0)
		{
			end[i] = cores[i]->tick();
		}		
	}

	// Increment clk
	if (ref_clk % trigger_for_x_clks == 0)
	{
		clk++;
	}

	ref_clk++; // Increment reference clock

	// When all the cores are done, return FALSE
	for (int i = 0; i < end.size(); i++)
	{
		if (end[i] == true)
		{
			return true;
		}
	}

	return false;
}
