#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

#include <Arduino.h>
#include <String.h>
#include "output/motor.h"
#include "network/network.h"

#define DEFAULT_SSID        "3DPractical"
#define DEFAULT_PASS        "embeddedelectronics"
#define DEFAULT_AP_SSID     "Glukosipp-Device"

/* 3. Define the RTDB URL */
#define DATABASE_URL    "gluko-sipp-default-rtdb.firebaseio.com"
#define DATABASE_SECRET "MTK2PFAXzykyqi6Pkmx6NciXmQdetg95GQ9I8yQ1"

#define DEFAULT_DEVICE_CODE (uint32_t)ESP.getEfuseMac()

#define DATA_PATH           "/user-1/device/inject_status"

#define debug(x, y)         Serial.print("[");Serial.print(millis());Serial.print("]"); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.println(y);
#define debugVal(x, y, z)   Serial.print("[");Serial.print(millis());Serial.print("]"); Serial.print("[");Serial.print(x);Serial.print("] "); Serial.print(y); Serial.println(z);

#endif // DEVICE_CONFIG_H_