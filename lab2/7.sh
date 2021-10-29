#!/bin/bash

id=()
readBytes=()

for pid in $(ls /proc/ | grep "[0-9]\+")
do

bytes=$(grep -s "read_bytes" "/proc/"$pid"/io" | awk '{print $2}')
if [[ -n "$bytes" ]]
then
id+=($pid)
readBytes+=($bytes)
fi

done


sleep 60


for i in ${!id[@]}
do

pid=${id[i]}
cmdline=$(cat /proc/$pid/cmdline 2>/dev/null | tr -d "\0")
bytes=$(grep -s "read_bytes" "/proc/"$pid"/io" | awk '{print $2}')

if [[ -n "$bytes" ]]
then
result=$result"\n"$pid":"$cmdline":"$(bc <<< "$bytes-${readBytes[i]}")
fi

done

echo -e "$result" | tail -n +2 | sort -t ":" -n -k3 | head -n +3
