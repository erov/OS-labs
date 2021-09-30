#!/bin/bash

cat /var/log/*.log | wc -l

#wc -l /var/log/*.log | awk '{print $1}' | tail -1
