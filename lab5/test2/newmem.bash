#!/bin/bash

array=()
step=0
N=$1
#> report.log

while [ true ]
do
	array+=(1 2 3 4 5 6 7 8 9 10)
	(( step++ ))
	if [[ "${#array[@]}" -gt "$N" ]]
	then
		break
	fi
done

#echo "${#array[@]}"
