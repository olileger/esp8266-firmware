# ESP8266 Firmware

## Features
- Wifi client connexion
- DHT Sensor reading
- Diode read/write
- HTTP/S request to backend

## Dependencies
- Board :
  * ESP8266 board 2.3.0 or higher <https://github.com/esp8266/Arduino>
- Libraries :
  * Adafruit GFX library by Adafruit version 1.1.9 or higher : <https://github.com/adafruit/Adafruit-GFX-Library>
  * Adafruit Unified Sensor by Adafruit version 1.0.2 or higher : <https://github.com/adafruit/Adafruit_Sensor>
  * Adafruit SSD1306 by Mike Cause (forked from Adafruit) : <https://github.com/mcauser/Adafruit_SSD1306/tree/esp8266-64x48>
  * DHT sensor library by Adafruit version 1.3.0 or higher : <https://github.com/adafruit/DHT-sensor-library>
- Tools :
  * ESP8266 Sketch data upload tool : <https://github.com/esp8266/arduino-esp8266fs-plugin>
  * esptool-0.4.9-win32 (installed by ESP8266 board 2.3.0)
  * mkspiffs-0.1.2-windows (installed by ESP8266 board 2.3.0)

## BackLog
- Required :
  * OK : Class HelperJsonFile
  * OK : Class ConfigApp
  * OK : Class ConfigWifi
  * OK : Class ConfigHttp
  * OK : Class ControllerHttpClient
  * OK : Load config files from Controllers
  * OK : ManagerArduino -> ControllerApp
  * OK : Setup the ESP8266 hostname according to the config file
  * OK : Consider app frequency for loop exec instead of hardcoded value
  * OK : Fully rely on the CLI compilation instead of Arduino IDE board & other stuff
  * OK : Upload device data files through CLI instead of Arduino IDE
    - mkspiffs to create SPIFFS images
    - esptool to upload data to the board
  * OK : Diode device manager
  * OK : ControllerAzureIoTHub : D2C, C2D, startup message with Commands, azureiothubclient.json
  * OK : config section for the Device Sensor + class instance instead of static : type, pin
  * OK : config section for the Device Diode + class instance instead of static : pin
  * OK : OLED display controller + showing DHT values
  * OK : Cloud to Device splash screen / write to OLED
  * TODO : Gen IoT Hub Sas token from the device itself
- Nice to have :
  * TODO : Read config files from mini SD controller
  * TODO : deepsleep
- Issues :
  * OK : DHT returns no values
  * OK : Exception 29 running the firmware @ 500ms (adding log : not reproduced)
  * OK : Compilation fails with error `section ``.text' will not fit in region ``iram1_0_seg`
    - OK : Move JSON to INI file (Helper)
    - OK : HelperIniFile as an instance
    - OK : Update the Config* objects to retrieve values