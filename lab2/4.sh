#!/bin/bash

for pid in $(ls /proc/ | grep "[0-9]\+")
do

sched="/proc/"$pid"/sched"
ppid=$(grep -s "PPid:" "/proc/"$pid"/status" | awk '{print $2}')
num=$(grep -s "sum_exec_runtime" "$sched" | awk '{print $3}')
denom=$(grep -s "nr_switches" "$sched" | awk '{print $3}')

if [[ -n "$denom" ]]
then
#wrap ppid in ';' to sort by splitting them
result=$result"\nProcessID="$pid" : Parent_ProcessID=;"$ppid"; : Average_Running_Time="$(bc -l <<< "$num/$denom")
fi

done

# tail -n +2 due to result starts by \n
echo -e "$result" | sort -t ";" -n -k2 | tr -d ";"| tail -n +2 > 4.log

