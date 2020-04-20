#include "config.h"
#include "Calamari.h"
#include "helpers.h"

Calamari calamari(CalamariAPIBase, CalamariUser, CalamariPassword);

void setup() {
  Serial.begin(9600);
  Helper::connectToWiFi();
  
  pinMode(27, INPUT);
}

void loop() {
  int pushButton = digitalRead(27);
  
  if(pushButton) {
    if(calamari.shiftIsOn(employeeEmail)) {
      Serial.println("Stop shift");
      calamari.stopShift(employeeEmail);
    } else {
      Serial.println("Start shift");
      calamari.startShift(employeeEmail);
    }

    delay(1000);
  }
}
