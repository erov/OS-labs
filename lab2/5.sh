#!/bin/bash

#USAGE: result lastPpid totalAvt cnt
appendSummary(){
result=$1"\nAverage_Running_Children_of_ParentID="$2" is "$(bc -l <<< "$3/$4")
echo -e "$result"
}


filename="4.log"
lastPpid=0
cnt=0
totalAvt=0

while read line
do

ppid=$(echo "$line" | awk '{print $3}' | awk -F "=" '{print $2}')
avt=$(echo "$line" | awk '{print $5}' | awk -F "=" '{print $2}')

if [[ "$ppid" -ne "$lastPpid" ]]
then
result=$(appendSummary "$result" "$lastPpid" "$totalAvt" "$cnt")
cnt=0
totalAvt=0
lastPpid=$ppid
fi

(( cnt++ ))
totalAvt=$(bc <<< "$totalAvt+$avt")
result=$result"\n"$line

done < "$filename"

result=$(appendSummary "$result" "$lastPpid" "$totalAvt" "$cnt")

echo -e "$result" | tail -n +2 > 5.log
