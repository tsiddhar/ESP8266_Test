#include <ESP8266WiFi.h>
#include<WiFiUDP.h>

const char WiFiAPPSK[] = "zerouiziro";
const char ssid[] = "Ziro";

int Analog_Pin = A0;

byte packetbuffer[512];

WiFiUDP udp;
WiFiClient client;
IPAddress ip_multi(239, 0, 0,57);
unsigned int port_multi = 12345;

void setup() {
  Serial.begin(9600);
  setupWiFi();
  printWifiStatus();
  //udp.beginMulticast(WiFi.localIP(), ip_multi,port_multi);
}

void loop() {

 // WiFiClient client = server.available();
  client.connect("z1roC3E",port_multi);

   int noBytes = udp.parsePacket();
   udp.read(packetbuffer,noBytes);
   
   for (int i=1;i<=noBytes;i++){
      Serial.print(packetbuffer[i-1],HEX);
      if (i % 32 == 0){
        Serial.println();
      }
      else Serial.print(' ');
    }
 
}

void setupWiFi()
{
  WiFi.mode(WIFI_STA);

//  // Do a little work to get a unique-ish name. Append the
//  // last two bytes of the MAC (HEX'd) to "Thing-":
//  uint8_t mac[WL_MAC_ADDR_LENGTH];
//  WiFi.softAPmacAddress(mac);
//  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
//                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
//  macID.toUpperCase();
//  String AP_NameString = ssid + macID;
//
//  char AP_NameChar[AP_NameString.length() + 1];
//  memset(AP_NameChar, 0, AP_NameString.length() + 1);
//
//  for (int i=0; i<AP_NameString.length(); i++)
//    AP_NameChar[i] = AP_NameString.charAt(i);
//
//  WiFi.begin("ZiroC3E", WiFiAPPSK);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
