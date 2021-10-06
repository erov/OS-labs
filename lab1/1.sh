#!/bin/bash

#max=$1
#if  [[ "$max" -lt "$2" ]]; then max=$2; fi
#if  [[ "$max" -lt "$3" ]]; then max=$3; fi
#echo $max

max=$1
if [[ ${#max} -lt ${#2} || ( ${#max} -eq ${#2} && $max < $2 ) ]]; then max=$2; fi
if [[ ${#max} -lt ${#3} || ( ${#max} -eq ${#3} && $max < $3 ) ]]; then max=$3; fi
echo $max
