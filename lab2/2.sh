#!/bin/bash

#ps -e -o pid,command | awk '$2 ~ /\/sbin\// {print $1}' > 2.log

ps -e -o pid,command | awk '$2 ~ /^\/sbin\// {print $1}' > 2.log
