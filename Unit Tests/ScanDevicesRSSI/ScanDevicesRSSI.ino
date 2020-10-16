/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 1; //In seconds
BLEScan* pBLEScan;

String BLEName;
String BLENameRSSI;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
//  The below code displays all BLE devices with names and without names.
//  The device without names will be displayed as blanks
//  if(advertisedDevice.getName().c_str()){
//    Serial.println(advertisedDevice.getName().c_str()); 
//  }
 String tmpStr =advertisedDevice.toString().c_str();
//  Display devices only with names
    BLEName = advertisedDevice.getName().c_str();
    
    //if(BLEName != ""){
//    Serial.println(BLEName);
      BLENameRSSI += BLEName;
      BLENameRSSI += ":";
      BLENameRSSI += advertisedDevice.getRSSI();
      BLENameRSSI += ",";
      Serial.print(tmpStr);
      Serial.print(" ");
      Serial.println(advertisedDevice.getRSSI());
   // }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  //Serial.print("Devices found: ");
  //Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
 // Serial.println(BLENameRSSI);
  
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
 // delay(500);
}
