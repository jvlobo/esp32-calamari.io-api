#include "config.h"
#include "Calamari.h"
#include "helpers.h"

Calamari calamari(CalamariAPIBase, CalamariUser, CalamariPassword, employeeEmail);
int shiftButton = 26;
int breakButton = 27;

void setup() {
  Serial.begin(9600);
  Helper::connectToWiFi();
  
  pinMode(shiftButton, INPUT);
  pinMode(breakButton, INPUT);
}

void loop() {
  int pushShiftButton = digitalRead(shiftButton);
  int pushBreakButton = digitalRead(breakButton);
  
  if(pushShiftButton) {
    if(calamari.shiftIsOn()) {
      Serial.println("Stop shift");
      calamari.stopShift();
    } else {
      Serial.println("Start shift");
      calamari.startShift();
    }

    delay(1000);
  }

  if(pushBreakButton) {
    if(calamari.breakIsOn()) {
      Serial.println("Stop lunch break");
      calamari.stopLunchBreak();
    } else {
      Serial.println("Start lunch break");
      calamari.startLunchBreak();
    }

    delay(1000);
  }
}
