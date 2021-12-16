#!/bin/bash

N=$1
K=$2

for ((i = 0; i < "$K"; ++i))
do
	sleep 1
	{ ./newmem.bash "$N" & }
done
