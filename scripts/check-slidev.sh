#!/bin/bash

if [ $(! npm list -g | grep -q slidev/cli | wc -l) -ne 1 ]; then
	echo "* Slidev is installed globally" && 
	slidev;
else
	echo "* Building Slidev locally" &&
	npm init slidev@latest;
fi

