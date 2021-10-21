#!/bin/bash

info=$(ps -e --format="uname pid command" | awk -v user="$1" '{if ($1 == user) print $2":"$3}')
echo "$info" | wc -l > 1.log
echo "$info" >> 1.log
