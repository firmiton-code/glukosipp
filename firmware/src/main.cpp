#include <Arduino.h>
#include "device_config.h"
#include "network/network.h"
#include "A4988.h"

// using a 200-step motor (most common)
#define MOTOR_STEPS 200
// configure the pins connected
#define DIR   4
#define STEP  16
#define MS1   19
#define MS2   18
#define MS3   5
#define SLP   17

#define INTERFACE 1
// AccelStepper myStepper(INTERFACE, STEP, DIR);
A4988 stepper(MOTOR_STEPS, DIR, STEP, SLP, MS1, MS2, MS3);

void setup() {
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  pinMode(27, INPUT_PULLUP);
  net.begin();
  digitalWrite(23, HIGH);
  stepper.begin(30, 1);
  stepper.enable();
}
 
void loop() {
  digitalWrite(23, HIGH);
  delay(200);
  digitalWrite(23, LOW);
  delay(200);
  Serial.println(digitalRead(27));

  stepper.move(250);
  delay(1000);
  stepper.move(-250);
  delay(1000);
}
