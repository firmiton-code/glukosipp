#ifndef Motor_h_
#define Motor_h_

#include <Arduino.h>
#include <A4988.h>

#define MOTOR_STEPS     250

#define DRIVER1_DIR     4
#define DRIVER1_STEP    16
#define DRIVER1_MS1     19
#define DRIVER1_MS2     18
#define DRIVER1_MS3     5
#define DRIVER1_SLEEP   17

#define DRIVER2_DIR     25
#define DRIVER2_STEP    26
#define DRIVER2_MS1     15
#define DRIVER2_MS2     13
#define DRIVER2_MS3     12
#define DRIVER2_SLEEP   14

typedef enum{
  MOTOR_1,
  MOTOR_2
} Motor_select_t;

class MotorClass {
  private:
    int _position_1 = 0;
    int _position_2 = 0;
    uint8_t _speed = 15;
  public:
    MotorClass();
    void begin();
    void reset();
    void run(Motor_select_t motor, int position);
    int position(Motor_select_t motor);
};

extern MotorClass motor;

#endif // Motor_h_