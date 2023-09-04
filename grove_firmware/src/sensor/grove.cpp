#include "grove.h"

GroveClass *grove_instances;

GroveClass::GroveClass(){
  grove_instances = this;
}

void GroveClass::begin(){
  // Wire.begin(_sda_pin, _scl_pin);
  Wire.begin();
  Wire.setTimeOut(100);
  Serial.println(Wire.getTimeOut());
}

int GroveClass::bpm(){
  Wire.requestFrom(0xA0 >> 1, 1);    // request 1 bytes from slave device
  unsigned char data;
  while(Wire.available()) {          // slave may send less than requested
    data = Wire.read();   // receive heart rate value (a byte)
    Serial.println(data, DEC);         // print heart rate value        
  }
  return data;
}

GroveClass grove;