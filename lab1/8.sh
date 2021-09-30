#!/bin/bash

awk -F: '{print $3, $1}' /etc/passwd | sort -n -k 1
# awk -F: separator=":"
# sort:
#  -n - as numeric values
#  -k - by key
