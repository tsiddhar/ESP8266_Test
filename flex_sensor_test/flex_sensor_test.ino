#include <ESP8266WiFi.h>

int pin = A0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  
  int flexposition = analogRead(pin);
  Serial.println(flexposition);

}
