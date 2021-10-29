#!/bin/bash

info=$(ps -e -U root -o pid,command | tail -n +2 | awk '{print $1 ": " $2}')
echo "$info" | wc -l > 1.log
echo "$info" >> 1.log
