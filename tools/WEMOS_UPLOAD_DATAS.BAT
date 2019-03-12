@ECHO OFF

SET MKSPIFFS=mkspiffs-0.1.2-windows\mkspiffs.exe
SET ESPTOOL=esptool-0.4.9-win32\esptool.exe
SET IMG=tmp.bin
SET PORT=COM5

REM Invoke MKSPIFFS according to WeMos board config in \boards\wemos.txt
%MKSPIFFS% --create ..\data --debug 5 --block 8192 --page 256 %IMG%

REM Invoke ESPTOOL according to WeMos board config in \boards\wemos.txt
%ESPTOOL% -cp %PORT% -cd nodemcu -cb 921600 -ca 0x00100000 -cf %IMG%