#!/bin/bash
while  [[ "$str" != "q" ]]
do
result=$result$str
read str
done
echo $result
