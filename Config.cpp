#include "Config.h"

Config::Config(const string &fname)
{
	parse(fname);
}

void Config::parse(const string &fname)
{
	ifstream file(fname);
	assert(file.good());

	string line;
	while(getline(file, line))
	{
        char delim[] = " \t=";
        vector<string> tokens;

        while (true) 
        {
            size_t start = line.find_first_not_of(delim);
            if (start == string::npos) 
                break;

            size_t end = line.find_first_of(delim, start);
            if (end == string::npos) {
                tokens.push_back(line.substr(start));
                break;
            }

            tokens.push_back(line.substr(start, end - start));
            line = line.substr(end);
        }

        // empty line
        if (!tokens.size())
            continue;

        // comment line
        if (tokens[0][0] == '#')
            continue;

        // parameter line
        assert(tokens.size() == 2 && "Only allow two tokens in one line");

        // Extract Timing Parameters
        if(tokens[0] == "num_of_cores")
        {
        	num_cores = atoi(tokens[1].c_str());
	}
	else if(tokens[0] == "frequency")
        {
        	frequency = atof(tokens[1].c_str());
	}
	else if(tokens[0] == "mc_mode")
        {
        	mc_mode = atof(tokens[1].c_str());
	}
    }

    file.close();
}

