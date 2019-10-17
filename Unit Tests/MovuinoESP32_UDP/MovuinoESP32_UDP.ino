#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include "FS.h"
#include "SPIFFS.h"

WiFiMulti WiFiMulti;

int opMode=0;

// WiFi network name and password:
const char * ssid = "Ke20 iPhone";
const char * password = "z123456789";

//IP address to send UDP data to:
// either use the ip address of the server or 
// a network broadcast address
const char * udpAddress = "172.20.10.10";
const int udpPort = 2390;

//Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;


void connect_wifi() {
  // WiFi.disconnect();
  if (WiFi.status() != WL_CONNECTED) { // FIX FOR USING 2.3.0 CORE (only .begin if not connected)
    //WiFi.forceSleepWake();
    WiFi.persistent(false);
    WiFi.setAutoConnect ( false );                                             // Autoconnect to last known Wifi on startup
    WiFi.setAutoReconnect ( false ) ;
    //WiFi.config(ip, gateway, subnet);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password); // connect to the network
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void disconnect_wifi() {
  Serial.println("Closing Wifi");
  WiFi.mode(WIFI_OFF);
  WiFi.disconnect();
  //WiFi.forceSleepBegin();
  delay(1);
}

void setup(){
  // Initilize hardware serial:
  Serial.begin(115200);
  // We start by condelay(500);
  WiFi.mode(WIFI_OFF);
  WiFi.persistent(false);
  WiFi.setAutoConnect ( false );
  WiFi.setAutoReconnect ( false );
  delay(500);
  connect_wifi();
  delay(100);
  
}

void loop(){
  Serial.println("hola");
  //only send data when connected
    //Send a packet
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("Seconds since boot: %lu", millis()/1000);
    udp.endPacket();
  //Wait for 1 second
  delay(1000);
}
