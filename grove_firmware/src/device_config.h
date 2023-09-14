#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

#include <Arduino.h>
#include <String.h>
#include "network/network.h"
#include "sensor/battery.h"
#include "sensor/grove.h"

#define DATABASE_URL    "gluko-sipp-default-rtdb.firebaseio.com"
#define DATABASE_SECRET "MTK2PFAXzykyqi6Pkmx6NciXmQdetg95GQ9I8yQ1"

#define FIREBASE_USE_PSRAM

#define DEFAULT_SSID        "3DPractical"             // not used since it will be changed
#define DEFAULT_PASS        "embeddedelectronics"     // not used since it will be changed
#define DEFAULT_AP_SSID     "Glukosipp-Sensor"        // web-server hotspot name

#define DEFAULT_DEVICE_CODE (uint32_t)ESP.getEfuseMac()

#define debug(x, y)         Serial.print("[");Serial.print(millis());Serial.print("]"); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.println(y);
#define debugVal(x, y, z)   Serial.print("[");Serial.print(millis());Serial.print("]"); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.print(y); Serial.println(z);

#endif // DEVICE_CONFIG_H_