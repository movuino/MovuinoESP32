# MovuinoESP32
Here is the Repo for the ESP32 version of movuino 

# Installation

Note : This procedure is temporary before we commit the movuino esp32 board to the main esp32 arduino repo 

1/The support for ESP32 has to be installed following those instructions : 
https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

2/We added a variant board called "Movuino ESP32" with the correct pinout (normally) in this repo
https://github.com/kevinlhoste/arduino-esp32 which is a fork fork arduino-esp32

Copy and paste "boards.txt and the whole folder "Variants" into your Arduino esp32 hardware folder (on windows : Arduino15/hardware/espressif/esp32)

3/Restart arduino 

4/ You should see a Board called "Movuino ESP32" in the board list

#Things to know

- Some libraries are not working yet on ESP32 (MPU6050 , OSC)

- Some libraries work but need adjustment of code (SPIFFS for file system)




