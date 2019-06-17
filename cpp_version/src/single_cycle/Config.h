#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Config
{
  private:
    int mc_mode = 0;
    int num_cores = 1; // Default: 1 core per socket
    double frequency = 1.0; // Default: 1 GHz

  public:
    Config(const std::string &fname);

    void parse(const std::string &fname);

    int get_mc_mode() const { return mc_mode; }
    int get_num_cores() const { return num_cores; }
    double get_freq() const { return frequency; }
};

#endif
