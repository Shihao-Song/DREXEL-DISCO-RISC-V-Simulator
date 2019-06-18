#include "instructions.h"
struct core{
    int core_id;
    float freq;
    int status;
    struct instruction_memory instruction_set;
};

void init_config();
