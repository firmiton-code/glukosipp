#include "grove.h"

GroveClass *grove_instances;

GroveClass::GroveClass(){
  grove_instances = this;
}

void GroveClass::begin(){
  Wire.begin(_sda_pin, _scl_pin);
}

void GroveClass::update(){
  Wire.requestFrom(0xA0 >> 1, 1);    // request 1 bytes from slave device
  int data;
  if(Wire.available()) {          // slave may send less than requested
    unsigned char c = Wire.read();   // receive heart rate value (a byte)
    data = c;

    _bpm = data;
    _glucose = _bpm > 0 ? ((_bpm * 0.8518) + 40.708) * glu_calibration : 0;
  }
}

int GroveClass::bpm(){
  return _bpm;
}

int GroveClass::glucose(){
  return _glucose;
}

GroveClass grove;