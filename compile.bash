#!/bin/bash

if [ "$1" == "single-cycle" ]; then
	make -C src/single_cycle
	mv src/single_cycle/RVSim .
else
	echo "Unsupported architecture"
fi
