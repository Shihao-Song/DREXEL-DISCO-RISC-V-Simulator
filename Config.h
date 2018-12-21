#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Config
{
private:
	int num_cores = 1; // Default: 1 core per socket
	int frequency = 1; // Default: 1 GHz

public:
	Config(const string &fname);

	void parse(const string &fname);

	int get_num_cores() const { return num_cores; }
	int get_freq() const { return frequency; }
};

#endif
