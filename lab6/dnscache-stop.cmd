net stop dnscache
timeout /t 10
sc query > services-new.txt
compare-services.cmd
net start dnscache