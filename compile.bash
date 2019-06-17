#!/bin/bash

if [ "$1" == "single-cycle" ]; then
	make -C src/single_cycle
	mv src/single_cycle/RVSim .

elif [ "$1" == "pipeline" ]; then
	make -C src/pipeline
	mv src/pipeline/RVSim .

else
	echo "Unsupported architecture"
fi
