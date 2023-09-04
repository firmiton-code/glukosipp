#include <Arduino.h>
#include "device_config.h"
#include "network/network.h"

void setup() {
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  pinMode(27, INPUT_PULLUP);
  net.begin();
}
 
void loop() {
  digitalWrite(23, HIGH);
  delay(200);
  digitalWrite(23, LOW);
  delay(200);
  Serial.println(digitalRead(27));
}
