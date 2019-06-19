#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <cmath>
#include <memory>
#include <vector>

#include "Config.h"
#include "Core.h"

class Socket
{
    typedef uint64_t Addr;
    typedef uint64_t Tick;

  public:
    // Constructor
    Socket(const Config &configs, std::ofstream *out, const char *argv[]);

    bool tick(); // FALSE means all the instructions are exhausted

    void printInstrs()
    {
        for (int i = 0; i < cores.size(); i++)
        {
            cores[i]->printInstrs();
	}
    }

    int get_execution_time()
    {
        return ref_clk;
    }

  private:
    std::vector<std::unique_ptr<Core>> cores;

    Tick ref_clk; // Reference clock cycle, 1 GHz

    Tick clk;

    int num_cores;
    double frequency;
};

#endif
