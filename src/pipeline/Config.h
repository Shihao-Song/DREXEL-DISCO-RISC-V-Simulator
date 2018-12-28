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

	// Pipeline specific
	int num_stages_mul = 1;
	int num_stages_div = 1;
	int num_stages_fadd = 1;
	int num_stages_fmul = 1;
	int num_stages_fdiv = 1;

public:
	Config(const string &fname);

	void parse(const string &fname);

	int get_mc_mode() const { return mc_mode; }
	int get_num_cores() const { return num_cores; }
	double get_freq() const { return frequency; }

	int get_num_stages_mul() const { return num_stages_mul; }
	int get_num_stages_div() const { return num_stages_div; }
	int get_num_stages_fadd() const { return num_stages_fadd; }
	int get_num_stages_fmul() const { return num_stages_fmul; }
	int get_num_stages_fdiv() const { return num_stages_fdiv; }
};

#endif
