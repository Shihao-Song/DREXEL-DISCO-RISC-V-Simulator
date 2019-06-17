#include <fstream>
#include <iostream>
#include <vector>

#include "Config.h"
#include "Core.h"
#include "Socket.h"

void run_simulation(Socket *socket);

int main(int argc, const char *argv[])
{	
    if (argc <= 3)
    {
        std::cout << "Usage: " << argv[0];
        std::cout << " <cfg file> <output-file> <instr-file-1> <instr-file-2> ...\n";

        return 0;
    }

    /*
        Preparation	
    */
    // Parse configuration file
    Config config(argv[1]);

    // Output file
    std::ofstream out(argv[2]);

    // Initialize Cores
    std::vector<Core *> cores;

    for (int i = 0; i < config.get_num_cores(); i++)
    {
        Core *core = new Core(argv[(3 + i)], &out);
        core->id = i;

        cores.push_back(core);
    }

    // Initialize Socket
    Socket *socket = new Socket(config, cores);

    /*
        Run Simulation
    */
    if (config.get_mc_mode() != 1)
    {
        run_simulation(socket);
    }
    else
    {
        socket->printInstrs();
    }

    std::cout << "Execution Time (ns): " << socket->get_execution_time() << "\n";

    /*
        Free Resource
    */
    out.close();

    for (int i = 0; i < config.get_num_cores(); i++)
    {
        delete cores[i];
    }

    delete socket;
}

void run_simulation(Socket *socket)
{
    while (true)
    {
        if (socket->tick() == false)
        {
            break;
        }
    }	
}
