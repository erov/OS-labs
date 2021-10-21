#!/bin/bash

appendSummary(){ #result lastPpid totalAvt cnt
	result=$1"\nAverage_Running_Children_of_ParentID="$2" is "$(bc -l <<< "$3/$4")
	echo -e "$result"
}

filename="4.log"
lastPpid=0
cnt=0
totalAvt=0

while read -r line
do
ppid=$(echo "$line" | awk '{print $3}' | awk -F "=" '{print $2}')
avt=$(echo "$line" | awk '{print $5}' | awk -F "=" '{print $2}')

if [[ "$ppid" -eq "$lastPpid" ]]
then
(( cnt++ ))
totalAvt=$(bc -l <<< "$totalAvt+$avt")

else
result=$(appendSummary "$result" "$lastPpid" "$totalAvt" "$cnt")
cnt=1
totalAvt=$avt
lastPpid=$ppid
fi

result=$result"\n"$line
done < "$filename"

result=$(appendSummary "$result" "$lastPpid" "$totalAvt" "$cnt")

echo -e "$result" | tail -n +2 > 5.log
