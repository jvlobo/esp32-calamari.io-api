#include "config.h"
#include "Calamari.h"
#include "helpers.h"

Calamari calamari(CalamariAPIBase, CalamariUser, CalamariPassword, employeeEmail);
#define BUTTON_PIN_BITMASK 0xC000000 // GPIOs 26 and 27
int vibrationMotor = 17;

void setup() {
  Serial.begin(9600);
  Helper::connectToWiFi();

  pinMode(vibrationMotor, OUTPUT);

  print_GPIO_wake_up();
  esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);
  esp_deep_sleep_start();
}

void print_GPIO_wake_up() {
  int GPIO_reason = esp_sleep_get_ext1_wakeup_status();
  int buttonPushed = (log(GPIO_reason))/log(2);

  if(buttonPushed == 26) {
    if(calamari.shiftIsOn()) {
      Serial.println("Stop shift");
      calamari.stopShift();
    } else {
      Serial.println("Start shift");
      calamari.startShift();
      vibrationPatternStart(vibrationMotor);
    }

    delay(1000);
  }

  if(buttonPushed == 27) {
    if(calamari.breakIsOn()) {
      Serial.println("Stop lunch break");
      calamari.stopLunchBreak();
    } else {
      Serial.println("Start lunch break");
      calamari.startLunchBreak();
      vibrationPatternStart(vibrationMotor);
    }

    delay(1000);
  }
}

void loop(){}

void vibrationPatternStop(int motorPin) {
  digitalWrite(motorPin, HIGH);
  delay(800);
  digitalWrite(motorPin, LOW);

  delay(200);
  
  digitalWrite(motorPin, HIGH);
  delay(400);
  digitalWrite(motorPin, LOW);

  delay(200);

  digitalWrite(motorPin, HIGH);
  delay(200);
  digitalWrite(motorPin, LOW);
}

void vibrationPatternStart(int motorPin) {
  digitalWrite(motorPin, HIGH);
  delay(300);
  digitalWrite(motorPin, LOW);

  delay(300);
  
  digitalWrite(motorPin, HIGH);
  delay(300);
  digitalWrite(motorPin, LOW);

  delay(400);

  digitalWrite(motorPin, HIGH);
  delay(800);
  digitalWrite(motorPin, LOW);
}