#!/bin/bash

max=-1
id=-1

for pid in $(ls /proc/ | grep "[0-9]\+")
do

# same as field status %ld
memUsage=$(cat /proc/$pid/statm 2>/dev/null | awk '{print $2}')

if [[ $max -lt $memUsage ]]
then
max=$memUsage
id=$pid
fi

done

echo "PID: "$id"  MEM USAGE: "$max
