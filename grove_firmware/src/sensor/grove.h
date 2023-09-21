#ifndef Grove_h_
#define Grove_h_

#include <Arduino.h>
#include <Wire.h>

class GroveClass{
  private:
    uint8_t _sda_pin = 21;
    uint8_t _scl_pin = 22;

    int _bpm = 0;
    int _glucose = 0;

    float glu_calibration = 1.0;

    size_t _req;
  public:
    GroveClass();
    void begin();
    void update();
    int bpm();
    int glucose();

    size_t request();
};

extern GroveClass grove;

#endif // Grove_h_