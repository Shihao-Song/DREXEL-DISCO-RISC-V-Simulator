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

	void printInstrs()
	{
		for (int i = 0; i < cores.size(); i++)
		{
			cores[i]->printInstrs();
		}
	}
private:
	vector<Core*> cores;

	unsigned long long int ref_clk; // Reference clock cycle

	unsigned long long int clk;

	int num_cores;
	double frequency;
};

#endif