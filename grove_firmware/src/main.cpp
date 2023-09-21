#include <Arduino.h>
#include "device_config.h"
#include "driver/rtc_io.h"

#define MAIN_TAG "MAIN"

float glucose_calibration = 1.0;
float bpm_calibration = 1.0;

int bpm = 0;
int glu = 0;
int bat = 0;

bool sleep_state = false;

void sendTask(void *param) {
  int last_bpm = 0;
  int last_glu = 0;
  int last_bat = 0;
  while(1){
    if(bpm != last_bpm && bpm > 0 && !sleep_state){
      last_bpm = bpm;
      debugVal(MAIN_TAG, "Update bpm : ", bpm);
      debugVal(MAIN_TAG, "Status : ",fb.set(bpm, "user-1/device/heart-rate"));
    }

    if(glu != last_glu && glu > 40 && !sleep_state){
      last_glu = glu;
      debugVal(MAIN_TAG, "Update glucose : ", glu);
      debugVal(MAIN_TAG, "Status : ",fb.set(glu, "user-1/device/glucose"));
    }

    if(bat != last_bat && !sleep_state){
      last_bat = bat;
      debugVal(MAIN_TAG, "Update battery : ", bat);
      debugVal(MAIN_TAG, "Status : ",fb.set(bat, "user-1/device/battery"));
    }
    
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void scanTask(void *param) {
  while(1){
    if(!sleep_state){
      grove.update();
      int req = grove.request();
      debugVal(MAIN_TAG, "Request : ", req);
      if(req){
        bpm = grove.bpm() * bpm_calibration;
        glu = grove.glucose() * glucose_calibration;
        bat = battery.get_percentage();
      } else{
        debug(MAIN_TAG, "Device disconnected");
        digitalWrite(17, HIGH);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        digitalWrite(17, LOW);
      }
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
  }
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void sleepTask (void *param){
  pinMode(27, INPUT_PULLUP);
  
  while(1){
    if(!digitalRead(27)){
      debug(MAIN_TAG, "Sleeping started");
      sleep_state = true;
      rtc_gpio_pullup_en(GPIO_NUM_27);
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_27, LOW);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
      esp_deep_sleep_start();
    } 

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(23, OUTPUT);
  pinMode(17, OUTPUT);
  delay(500);
  digitalWrite(17, LOW);
  delay(500);
  digitalWrite(17, HIGH);
  delay(500);
  digitalWrite(17, LOW);
  print_wakeup_reason();

  xTaskCreate(sleepTask, "Sleep Mode Task", 5000, NULL, 3, NULL);

  net.begin();
  fb.begin(DATABASE_URL, DATABASE_SECRET);
  battery.begin();
  grove.begin();

  digitalWrite(23, HIGH);

  xTaskCreate(scanTask, "Update sensor data", 5000, NULL, 4, NULL);
  xTaskCreate(sendTask, "Update database", 10000, NULL, 3, NULL);

  // vTaskDelete(NULL);
}

void loop() {
  delay(1);
}
