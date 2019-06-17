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
	int mc_mode = 0;
	int num_cores = 1; // Default: 1 core per socket
	double frequency = 1.0; // Default: 1 GHz
	
public:
	Config(const string &fname);

	void parse(const string &fname);

	int get_mc_mode() const { return mc_mode; }
	int get_num_cores() const { return num_cores; }
	double get_freq() const { return frequency; }
};

#endif
