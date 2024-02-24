#!/bin/bash

# Get PID of valgrind process
ps aux | grep valgrind.bin | grep -v grep | awk '{print $2}'
