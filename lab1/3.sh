#!/bin/bash

while [[ true ]]
do
echo "Menu:
1. open nano
2. open vi
3. open links
4. close menu"

read id
case $id in
1 )
nano
;;
2 )
vi
;;
3 )
links
;;
4 )
exit 0
;;
* )
echo "Usage: [1-4]"
;;
esac

done
