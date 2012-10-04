@echo off
SET ISC_USER=SYSDBA
SET ISC_PASSWORD=Odin1Odin

set gbak=D:\Programs\fb\bin\gbak.exe
set db=money
set bak=E:\BackUp\money\MONEY.FDB.fbk

echo Backup...
time /t
%gbak% -b -g -v -nod -se localhost:service_mgr %db% %bak% >D:\Sasha\money\bin\backup.log 2>&1
rar a -m5 -ag -ep -df %bak%.rar %bak%
time /t
