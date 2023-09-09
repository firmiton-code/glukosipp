#include <Arduino.h>
#include "device_config.h"

#define MAIN_TAG "MAIN"

int bpm = 0;
int glu = 0;

void sendTask(void *param) {
  int last_bpm = 0;
  int last_glu = 0;
  while(1){
    if(bpm != last_bpm){
      last_bpm = bpm;
      debugVal(MAIN_TAG, "Update bpm : ", bpm);
      debugVal(MAIN_TAG, "Status : ",fb.set(bpm, "test/bpm"));
    }

    if(glu != last_glu){
      last_glu = glu;
      debugVal(MAIN_TAG, "Update glucose : ", glu);
      debugVal(MAIN_TAG, "Status : ",fb.set(glu, "test/glu"));
    }

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void scanTask(void *param) {
  while(1){
    grove.update();
    bpm = grove.bpm();
    glu = grove.glucose();

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  net.begin();
  fb.begin(DATABASE_URL, DATABASE_SECRET);
  battery.begin();
  grove.begin();
  digitalWrite(23, HIGH);

  xTaskCreate(scanTask, "Update sensor data", 5000, NULL, 4, NULL);
  xTaskCreate(sendTask, "Update database", 10000, NULL, 3, NULL);

  vTaskDelete(NULL);
}

void loop() {}
