#!/bin/bash

mode="+"
result=1

(tail -f pipe) |
while true; do
	read line;
	case $line in
		"+")
			mode="+"
			;;
		"*")
			mode="*"
			;;
		"QUIT")
			echo "exit"
#			echo "exit" > callback
			killall tail
			exit
			;;
		*)
			if [[ $line =~ [0-9]+ ]]; then result=$(bc <<< $result$mode$line);
			else {
				echo "input error: "$line
#				echo "exit" > callback
				killall tail
				exit
			};
			fi
			;;
	esac
	echo $result
done
