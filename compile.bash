#!/bin/bash

if [ "$1" == "single-cycle-cpp" ]; then
	make -C src/single_cycle
	mv src/single_cycle/RVSim .

elif [ "$1" == "single-cycle-c" ]; then
        make -C src/single_cycle_c_version
        mv src/single_cycle_c_version/RVSim .

elif [ "$1" == "pipeline" ]; then
	make -C src/pipeline
	mv src/pipeline/RVSim .

else
	echo "Unsupported architecture"
fi
