#!/bin/bash
if [[ "$PWD" =~ $HOME.* ]]
then
echo $HOME
exit 0
else
echo "error: working directory is not home directory"
exit 1
fi

