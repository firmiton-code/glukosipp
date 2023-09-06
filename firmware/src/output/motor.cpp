#include "motor.h"

A4988 motor_1(MOTOR_STEPS, DRIVER1_DIR, DRIVER1_STEP, DRIVER1_SLEEP, DRIVER1_MS1, DRIVER1_MS2, DRIVER1_MS3);
A4988 motor_2(MOTOR_STEPS, DRIVER2_DIR, DRIVER2_STEP, DRIVER2_SLEEP, DRIVER2_MS1, DRIVER2_MS2, DRIVER2_MS3);

MotorClass *motor_instances;

MotorClass::MotorClass(){
  motor_instances = this;
}

void MotorClass::begin(){
  motor_1.begin(_speed, 1);
  motor_2.begin(_speed, 1);
  
  motor_1.enable();
  motor_2.enable();

  motor_1.move(-100);
  motor_2.move(-100);
}

void MotorClass::run(Motor_select_t motor, int position){
  if(motor == MOTOR_1){
    _position_1 = position;
    motor_1.move(position);
  } else{
    _position_2 = position;
    motor_2.move(position);
  }
}

int MotorClass::position(Motor_select_t motor){
  if(motor == MOTOR_1){
    return _position_1;
  } else{
    return _position_2;
  }
}

MotorClass motor;