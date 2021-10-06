#!/bin/bash

#max=$1
#if  [[ "$max" -lt "$2" ]]; then max=$2; fi
#if  [[ "$max" -lt "$3" ]]; then max=$3; fi
#echo $max

max=$1
if [[ $(echo $max\<$2 | bc) -eq 1 ]]; then max=$2; fi
if [[ $(echo $max\<$3 | bc) -eq 1 ]]; then max=$3; fi
echo $max
