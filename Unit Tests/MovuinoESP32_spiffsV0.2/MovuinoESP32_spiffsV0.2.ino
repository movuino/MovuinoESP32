#include "FS.h"
#include "SPIFFS.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project

int opMode=0;

void test_write(){
   // always use this to "mount" the filesystem
  bool result = SPIFFS.begin(true);
  Serial.print("SPIFFS opened: " + result);
  Serial.println(result);
  File f = SPIFFS.open("/f3.txt", "r");
   if(f && !f.isDirectory())
   {
      Serial.println("file exists!");
       // we could open the file
      while(f.available()) {
         //Lets read line by line from the file
         String line = f.readStringUntil('n');
         Serial.println(line);
        }
   }
   else 
      {
      Serial.println("file doesnot exists!");
      File fw = SPIFFS.open("/f3.txt", "w+");
      if(fw && !fw.isDirectory())
        {
        Serial.println("Creation suceeded!");
        fw.println("ssid=abc");
        fw.println("password=123455secret"); 
        fw.close(); 
        }
      else Serial.println("Creation failed");
     }
f.close();
}

void setup() {
  Serial.begin(115200);
 // delay(2000);
  // always use this to "mount" the filesystem
 
Serial.println("Initializing I2C devices...");
}

void loop() {
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    Serial.println(inByte);
    if(inByte=='p') {
     // read_memory();
     test_write();
    }
    //recording mode
    else if(inByte=='r') {
   //    fw = SPIFFS.open("/f.txt", "w+");
       opMode=2;
      //read_memory();
    }
     //stop recording mode
    else if(inByte=='R') {
//       fw.close();
       opMode=0;
      //read_memory();
    }
    //live mode
    else if(inByte=='l'){
      opMode=1;
    }
    //quit live mode
    else if(inByte=='L'){
      opMode=0;
    }
    else delay(2);
  }
 delay(2);
  //read_memory();
  //delay(100);
}


