#!/bin/bash

file="/var/log/anaconda/X.log"
warning_mark="(WW)"
info_mark="(II)"
grep $warning_mark $file | sed  "s/$warning_mark/Warning:/" > full.log
grep $info_mark $file | sed "s/$info_mark/Information:/" >> full.log
cat full.log
