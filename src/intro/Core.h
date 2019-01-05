#ifndef __CORE_H__
#define __CORE_H__

#include <iostream>
#include <bitset>
#include <cstdint>
#include <cstdlib>

#define NUM_OF_REGS 32
#define SIZE_OF_MEM 256

using namespace std;

class Core
{
public:
	Core();
	~Core()
	{
		free(data_mem);
		free(regs);
	}

	bool tick();

	void printResult();

private:

	unsigned int instruction = 0x00053483; // Pre-coded instruction

	uint8_t *data_mem; // Byte-addressable

	int64_t *regs;
};

#endif
