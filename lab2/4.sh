#!/bin/bash

for pid in $(ls /proc/ | grep "[0-9]\+")
do
ppid=$(grep -s -i "ppid:" "/proc/"$pid"/status" | awk '{print $2}')

sched="/proc/"$pid"/sched"
num=$(grep -s -i "sum_exec_runtime" "$sched" | awk '{print $3}')
denom=$(grep -s -i "nr_switches" "$sched" | awk '{print $3}')

if [ -z "$num" ]; then num=0; fi

if [ ! -z "$denom" ]
then
echo "ProcessID="$pid" : Parent_ProcessID="$ppid" : Average_Running_Time="$(bc -l <<< $num"/"$denom) >> 4.log
fi

done
