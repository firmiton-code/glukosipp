#ifndef Grove_h_
#define Grove_h_

#include <Arduino.h>
#include <Wire.h>

class GroveClass{
  private:
    uint8_t _sda_pin = 21;
    uint8_t _scl_pin = 22;
  public:
    GroveClass();
    void begin();
    int bpm();
};

extern GroveClass grove;

#endif // Grove_h_