#!/bin/bash

if [ $(! npm list -g | grep slidev/cli | wc -l) -eq 1 ]; then
	echo "* Slidev is installed globally" && 
	slidev;
else
	echo "* Building Slidev locally" &&
	npm init slidev@latest;
fi

