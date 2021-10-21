#!/bin/bash

for pid in $(ls /proc/ | grep "[0-9]\+")
do
if [ ! -z $(readlink /proc/"$pid"/exe | grep "/sbin/") ]; then echo "$pid" >> 2.log; fi
done
