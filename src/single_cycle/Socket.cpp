#include "Socket.h"

Socket::Socket(const Config &configs, std::ofstream *out, const char *argv[])
    : ref_clk(0),
      clk(0),
      num_cores(configs.get_num_cores()),
      frequency(configs.get_freq())
{
    for (int i = 0; i < configs.get_num_cores(); i++)
    {
        cores.push_back(std::make_unique<Core>(argv[(3 + i)], out));
    }
}

bool Socket::tick()
{
    int trigger_for_x_clks = int(ceil(1.0 / frequency));

    std::vector<bool> end; // Indicate if any core runs out of the instructions
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
