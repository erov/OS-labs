#!/bin/bash

echo $$ > .pid

result=1

usr1() {
	result=$(bc <<< $result"+2")
}

usr2() {
	result=$(bc <<< $result"*2")
}

trap 'usr1' USR1
trap 'usr2' USR2

while true; do
	echo $result
	sleep 1
done
