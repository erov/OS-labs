#!/bin/bash

./loop.sh &
id1=$!

./loop.sh &
id2=$!

./loop.sh &
id3=$!

echo -e $id1"\n"$id2"\n"$id3 > 4.log

