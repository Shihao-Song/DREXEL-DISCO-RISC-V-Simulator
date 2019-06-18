#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "Config.h"
#include "Core.h"
#include "Socket.h"

void run_simulation(Socket* socket);

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
 
    // Initialize Socket
    std::unique_ptr<Socket> socket = std::make_unique<Socket>(config, &out, argv);

    /*
        Run Simulation
    */
    if (config.get_mc_mode() != 1)
    {
        run_simulation(socket.get());
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
