#include "battery.h"

BatteryClass *batt_instances;

BatteryClass::BatteryClass(){
  batt_instances = this;
}

void BatteryClass::begin(){
  pinMode(_pin, INPUT);
}

uint8_t BatteryClass::get_percentage(){
  return map(analogReadMilliVolts(_pin), 2.8, 3.2, 0, 100);
}

float BatteryClass::get_voltage(){
  return analogReadMilliVolts(_pin)/1000;
}

BatteryClass battery;