#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <cmath>
#include <vector>

#include "Config.h"
#include "Core.h"

class Socket
{
    typedef uint64_t Addr;
    typedef uint64_t Tick;

  public:
    // Constructor
    Socket(const Config &configs, std::vector<Core *> &cores);

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
    std::vector<Core*> cores;

    Tick ref_clk; // Reference clock cycle, 1 GHz

    Tick clk;

    int num_cores;
    double frequency;
};

#endif
