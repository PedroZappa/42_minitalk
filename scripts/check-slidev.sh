#!/bin/bash

if [ $(! npm list -g | grep slidev/cli | wc -l) -eq 1 ]; then
	echo "* Slidev is installed Globally"
else
	echo "* Building Slidev Locally" &&
	npm init slidev@latest;
fi

