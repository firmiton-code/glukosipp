#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

#include <Arduino.h>
#include <String.h>
#include "network/network.h"
#include "sensor/battery.h"
#include "sensor/grove.h"

#define DEFAULT_UP_PIN      16
#define DEFAULT_MID_PIN     9
#define DEFAULT_DOWN_PIN    10

#define FIREBASE_USE_PSRAM

#define DEFAULT_SSID        "3DPractical"
#define DEFAULT_PASS        "embeddedelectronics"
#define DEFAULT_AP_SSID     "Glukosipp-Sensor"

#define DEFAULT_DEVICE_CODE (uint32_t)ESP.getEfuseMac()

#define debug(x, y)         Serial.print("[");Serial.print(millis());Serial.print("]"); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.println(y);
#define debugVal(x, y, z)   Serial.print("[");Serial.print(millis());Serial.print("]"); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.print(y); Serial.println(z);

#endif // DEVICE_CONFIG_H_