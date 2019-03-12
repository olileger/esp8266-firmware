@ECHO OFF

SET BIN=arduino_debug
SET ACTION=--%1
SET BOARD=--board esp8266:esp8266:d1_mini:CpuFrequency=80,FlashSize=4M3M,UploadSpeed=921600
SET PORT=--port COM5
SET MAIN_INO=..\ESP8266_Firmware.ino

%BIN% %ACTION% %BOARD% %PORT% %MAIN_INO%