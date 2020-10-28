# MovuinoESP32
Here is the Repo for the ESP32 version of movuino 

# Installation

Note : This procedure is temporary before we commit the movuino esp32 board to the main esp32 arduino repo 

1/Install CP2104 Drivers  https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

2/The support for ESP32 has to be installed following those instructions (lateste core version works) : 
https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md


3/Restart arduino 

4/ The board to use in arduino is ESP32-dev

#Things to know

- Some libraries are not working yet on ESP32 (MPU6050 , OSC)

- Some libraries work but need adjustment of code (SPIFFS for file system)




