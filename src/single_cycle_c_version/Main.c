#include <cstdio>
#include <fstream>

#include "../single_cycle/Config.h"

// void run_simulation(Socket* socket);

int main(int argc, const char *argv[])
{	
    if (argc <= 3)
    {
        printf("Usage: %s %s %s %s\n", argv[0],
                                       "<cfg file>",
                                       "<output-file>",
                                       "<trace-file>");
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
    // Socket* socket = new Socket(config, &out, argv);

    /*
        Run Simulation
    */
    /*
    if (config.get_mc_mode() != 1)
    {
        run_simulation(socket.get());
    }
    else
    {
        socket->printInstrs();
    }

    std::cout << "Execution Time (ns): " << socket->get_execution_time() << "\n";
    */
    /*
        Free Resource
    */
    out.close();
}

/*
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
*/
