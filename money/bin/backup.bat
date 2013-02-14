@echo off
SET ISC_USER=SYSDBA
SET ISC_PASSWORD=Odin1Odin

set gbak=D:\Programs\fb\bin\gbak.exe
set gfix=D:\Programs\fb\bin\gfix.exe
set db=money
set bak=E:\BackUp\money\MONEY.FDB.fbk
set log=D:\Sasha\home_compa_dev\money\bin\backup.log
set arch=D:\Programs\arc\Rar.exe

time /t >> %log% 2>&1
echo backup >> %log% 2>&1
%gbak% -b -g -v -nod -se localhost:service_mgr %db% %bak% >> %log% 2>&1
echo sweep >> %log% 2>&1
%gfix% localhost:money -sweep >> %log% 2>&1
echo rar >> %log% 2>&1
%arch% a -m5 -ag -ep -df %bak%.rar %bak% >> %log% 2>&1
time /t >> %log% 2>&1
echo --------------------------------------------------------------------- >> %log% 2>&1
echo. >> %log% 2>&1
