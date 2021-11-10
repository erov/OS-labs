#!/bin/bash

starting_time=$(date | tr " " "_")

mkdir test && {
	echo "catalog test was created successfully" > test/report
	touch test/"$starting_time"
}

ping www.net_nikogo.ru || echo $(date) ": host is unavailable" >> test/report
