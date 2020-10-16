/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/
#include <math.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include "BLEBeacon.h"
#include <BLEAdvertisedDevice.h>
#include <Adafruit_NeoPixel.h>
#define PIN           15//gpio12

int notFoundCounter = 3;

#define NUMPIXELS     55

//calibration rsi @1meter
int calRSSI=-65;
int n=4;


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

BLEAdvertising *pAdvertising;
// device 0 : 
//#define BEACON_UUID           "8ec76ea3-6668-48da-9866-75be8bc86f4d"
//device 1 
#define BEACON_UUID           "8ec76ea3-6668-48da-9866-75be8bc86f3d" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
static uint32_t bootcount=0; 

int scanTime = 1; //In seconds
BLEScan* pBLEScan;
//device 1 
//String beaconID = "4c0002153d";
//device 0 
String beaconID = "4c0002154d";
int currentStatus = 0;
int lastStatus = 0;

void setBeacon() {

  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
  oBeacon.setProximityUUID(BLEUUID(BEACON_UUID));
  oBeacon.setMajor((bootcount & 0xFFFF0000) >> 16);
  oBeacon.setMinor(bootcount&0xFFFF);
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04
  
  std::string strServiceData = "";
  
  strServiceData += (char)26;     // Len
  strServiceData += (char)0xFF;   // Type
  strServiceData += oBeacon.getData(); 
  oAdvertisementData.addData(strServiceData);
  
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);

}


void allOff(){
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
     // pixels.show();
      }
      pixels.show();
}
void allOn(int rValue , int gValue , int bValue){
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(rValue,gValue,bValue)); // Moderately bright green color.
      pixels.show();
      }
}
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
     // Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    String tmpStr =advertisedDevice.toString().c_str();
    //Serial.printf("%s ", advertisedDevice.toString().c_str());
     if(tmpStr.substring(55, 65).equals(beaconID)) {
      notFoundCounter=0;
      Serial.print("found rssi :  ");
      int tempRSSI=advertisedDevice.getRSSI();
      Serial.println(tempRSSI);
      //rssi to distance
      //int texp=calRSSI-tempRSSI;
      //-65--93/20 = 28/20 =1.4
      //-65--65/20 = 0 => 1m

    //  found rssi :  -51
//-14 0.00 -51 5.01 m


      
      int temp0 = (calRSSI-(tempRSSI));
      float temp= float(temp0)/(10*n);
      float temp1= temp0/40;
      Serial.print(String(temp0)+" "+String(temp)+" "+String(temp1)+" ");
      float distanceRSSI=pow(10, temp);
      //float distanceRSSI=pow(10,2);
      Serial.print(advertisedDevice.getRSSI());
      Serial.print(" ");
      Serial.print(distanceRSSI);
       Serial.println(" m");
      if(advertisedDevice.getRSSI()>=-65) { 
         Serial.println("close range");
        currentStatus=-1;
        }
      else {
          currentStatus=1;
      }
        
   //  Serial.println(tmpStr.substring(55, 65));
   Serial.println(advertisedDevice.getRSSI());
    }
    else {
      //currentStatus=lastStatus;
       notFoundCounter++;
       if(notFoundCounter==15){
          Serial.println("notfound");
          currentStatus=0;
          notFoundCounter=0;
       }
    }
    }
};


void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  pixels.begin(); // This initializes the NeoPixel library.
  allOff();
  BLEDevice::init("");
  pAdvertising = BLEDevice::getAdvertising();
  setBeacon();
   // Start advertising
  pAdvertising->start();
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
  allOn(0,25,25);
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  if(currentStatus != lastStatus){
    if(currentStatus ==0) {
      Serial.println("turn off");
      allOn(0,25,25);
     // allOff();
    }
    else if(currentStatus ==-1) {
      Serial.println("turn red");
      allOn(25,0,0);
    }
    else {
      allOn(0,25,25);
      Serial.println("turn blue");
    }
    lastStatus=currentStatus;
  }
Serial.print("currentStatus ");
Serial.println(currentStatus);
}
