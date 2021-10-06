#!/bin/bash

#max=$1
#if  [[ "$max" -lt "$2" ]]; then max=$2; fi
#if  [[ "$max" -lt "$3" ]]; then max=$3; fi
#echo $max

max=$1
if (( $(bc <<< "$max<$2") )); then max=$2; fi
if (( $(bc <<< "$max<$3") )); then max=$3; fi
echo $max

