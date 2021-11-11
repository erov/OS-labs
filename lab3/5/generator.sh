#!/bin/bash

while true; do
	read line
	echo "$line" > pipe

	if [[ $line != "+" && $line != "*" && ! $line =~ [0-9]+ ]]; then break; fi

	#read line < callback
#	if [[ $(read line < callback) && $line == "exit" ]]; then exit; fi
done
