#!/bin/bash

#rely on fact tail & awk doesn't call subprocesses
ps -e --sort=start_time -o pid,ppid,start_time | tail -n +2 | awk -v this=$$ '$1 != this && $2 != this {print "PID: " $1 "  START_TIME: " $3}' | tail -n 1
