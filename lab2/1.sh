#!/bin/bash

info=$(ps -e -o uname,pid,command | awk '$1 == "root" {print $2 ": " $3}')
echo "$info" | wc -l > 1.log
echo "$info" >> 1.log
