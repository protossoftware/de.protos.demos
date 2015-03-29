
set USER=root
echo %USER%
set HOST=192.168.7.2
set USER_HOST=%USER%@%HOST%
pwd
C:\entw\projects\github\e4y.demos\projects\BBBTrafficLight\tools\Plink\plink %USER_HOST% killall FischertechnikBBB
C:\entw\projects\github\e4y.demos\projects\BBBTrafficLight\tools\Plink\pscp ../LinaroPosixDebug/FischertechnikBBB %USER_HOST%:/root/Test
REM C:\entw\projects\github\e4y.demos\projects\BBBTrafficLight\tools\Plink\pscp start root@%1:/home/debian
REM C:\entw\projects\github\e4y.demos\projects\BBBTrafficLight\tools\Plink\plink %USER_HOST% /root/Test/startFischertechnik.sh &
