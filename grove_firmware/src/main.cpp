#include <Arduino.h>
#include "device_config.h"

void setup() {
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  net.begin();
  battery.begin();
  grove.begin();
  digitalWrite(23, HIGH);
}

void loop() {
  Serial.println(grove.bpm());
  delay(500);
}
