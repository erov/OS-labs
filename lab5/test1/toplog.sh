#!/bin/bash

> top.log
step=0

while [ true ]
do
	(( step++ ))
	echo "== top log no.$step" >> top.log
	echo "first table lines:" >> top.log
	info=$(top -n 1 -b | head -n 100)
	echo -e "$info" | head -n 12 >> top.log
	echo "'mem.bash' log:" >> top.log
	echo -e "$info" | grep "mem.bash" >> top.log
	echo >> top.log
	sleep 1
done
