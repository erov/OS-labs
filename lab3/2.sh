#!/bin/bash

echo "./1.sh &" | at now +1 minute

(tail -f ./test/report) |
while read line; do
	#read line;
	echo $line
done &

#ps -e -o pid,ppid,command | awk -v this=$$ '$2 == this && $3 == "tail" {print $1}'
