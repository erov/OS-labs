#!/bin/bash

grep -E -o -r -h -I "([a-zA-Z0-9_\-\.\+]+)@([a-zA-Z0-9_\-\.]+)\.([a-zA-Z]+)" /etc/ | tr "\n" "," | sed 's/,$/\n/' > emails.lst
# -o --only-mathching
# -r --recoursive
# -h --no-filename
# -I no match binary files
