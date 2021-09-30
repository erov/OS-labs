#!/bin/bash

man bash | grep -o "[[:alpha:]]\{4,\}" | sort | uniq -c -i | sort -n -r | head -3 | awk '{print $2}'
