#include <ESP8266WiFi.h>
#include<WiFiUDP.h>

const char WiFiAPPSK[] = "zerouiziro";
const char ssid[] = "z1ro";

int Analog_Pin = A0;

byte packetbuffer[512];

WiFiServer server(80);

WiFiUDP udp;

IPAddress ip_multi(239, 0, 0,57);
unsigned int port_multi = 12345;

void setup() {
  Serial.begin(9600);
  setupWiFi();
  server.begin();
  udp.beginMulticast(WiFi.localIP(), ip_multi,port_multi);
}

void loop() {
  
  int flexposition = analogRead(Analog_Pin);
  Serial.println(flexposition);

  udp.beginPacket(ip_multi, port_multi);
  udp.write (flexposition);
  udp.endPacket();

}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = ssid + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}
