#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <vector>
#include <cmath>

#include "Core.h"
#include "Config.h"

using namespace std;

class Socket
{
public:
	// Constructor
	Socket(const Config &configs, vector<Core *> &cores);

	bool tick(); // FALSE means all the instructions are exhausted

	int get_execution_time()
	{
		return ref_clk;
	}

private:
	vector<Core*> cores;

	unsigned long long int ref_clk; // Reference clock cycle, 1 GHz

	unsigned long long int clk;

	int num_cores;
	double frequency;
};

#endif
