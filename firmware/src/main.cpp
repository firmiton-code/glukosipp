#include <Arduino.h>
#include "device_config.h"

class FluidState{
  private:
    bool motor;
    uint8_t turn;
    long last;
  public:
    FluidState(){
      this->motor = false;
      this->turn = 0;
      this->last = 0;
    }

    void on(){
      this->motor = true;
    }

    void off(){
      this->motor = false;
    }

    void next_turn(){
      this->turn++;
    }

    void change_last(unsigned long last_inject){
      this->last = last_inject;
    }

    bool get_motor_state(){
      return this->motor;
    }

    uint8_t get_turn(){
      return this->turn;
    }

    long get_last(){
      return this->last;
    }
};

FluidState insulin, other;

void motorTask(void *param){
  while(1){
    if(insulin.get_motor_state()){
      Serial.println("Motor active");
      motor.run(MOTOR_1, 250);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      motor.run(MOTOR_1, -250);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      fb.set(0, DATA_PATH);
      insulin.off();
      insulin.next_turn();
      Serial.println(insulin.get_turn());
      insulin.change_last(millis());
      digitalWrite(23, LOW);
      Serial.println("Motor off");
    }
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void stateTask(void *param){
  while(1){
    if(fb.get(DATA_PATH) && !insulin.get_motor_state()){
      insulin.on();
      digitalWrite(23, HIGH);
      Serial.println("Status changed");
    }

    if(!digitalRead(27)){
      fb.set(1, DATA_PATH);
      vTaskDelay(200/ portTICK_PERIOD_MS);
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  pinMode(27, INPUT_PULLUP);
  net.begin();
  fb.begin(DATABASE_URL, DATABASE_SECRET);
  digitalWrite(23, HIGH);
  motor.begin();

  xTaskCreate(motorTask, "Motor Task", 10000, NULL, 3, NULL);
  xTaskCreate(stateTask, "Get State Task", 10000, NULL, 4, NULL);
}
 
void loop() {}
