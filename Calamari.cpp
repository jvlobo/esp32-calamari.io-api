/*
  Calamari.cpp - Library for using Calamari.io API.
  Created by J.V. Lobo, April 16, 2020.
  Released into the public domain.
*/

#include "HTTPClient.h"
#include "Arduino.h"
#include "Arduino_JSON.h"
#include "Calamari.h"
#include "helpers.h"

Calamari::Calamari(String baseUrl, String user, String password, String employee) {
  _baseUrl.concat(baseUrl);
  _user.concat(user);
  _password.concat(password);
  _employee.concat(employee);
}

void Calamari::startShift() {
  Calamari::_toggleShift("in");
}

void Calamari::stopShift() {
  Calamari::_toggleShift("out");
}

void Calamari::_toggleShift(String type) {
  String endpoint = "clockin/terminal/v1/clock-" + type;
  String payload = "{\"person\": \"" + Calamari::_employee  
    + "\", \"time\": \"" + Helper::getCurrentTime() + "\"}";

  Calamari::_apiCall(endpoint, payload);
}

bool Calamari::shiftIsOn() {
  return Calamari::_getShiftStatus() == "STARTED";
}

void Calamari::startLunchBreak() {
  Calamari::_toggleBreak("start", "2");
}

void Calamari::stopLunchBreak() {
  Calamari::_toggleBreak("stop", "2");
}

void Calamari::_toggleBreak(String type, String breakId) {
  String endpoint = "clockin/terminal/v1/break-" + type;
  String payload = "{\"person\": \"" + Calamari::_employee 
    + "\", \"time\": \"" + Helper::getCurrentTime() 
    + "\", \"breakType\": \"" + breakId + "\"}";

  Calamari::_apiCall(endpoint, payload);
}

bool Calamari::breakIsOn() {
  return Calamari::_getShiftStatus() == "BREAK";
}

String Calamari::_getShiftStatus() {
  String endpoint = "clockin/shift/status/v1/get-current";
  String payload = "{\"person\": \"" + Calamari::_employee  + "\"}";

  String response = Calamari::_apiCall(endpoint, payload);
  JSONVar myObject = JSON.parse(response);
  String shiftStatus = (const char*) myObject["status"];

  return shiftStatus;
}

String Calamari::_apiCall(String endpoint, String payload) {
  HTTPClient http;
 
  http.begin(Calamari::_baseUrl + endpoint);
  http.setAuthorization(CalamariUser, CalamariPassword);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(payload);

  if (httpCode > 0) {
      String response = http.getString();
      Serial.println(httpCode);
      Serial.println(response);

      return response;
  } else {
    Serial.println("Error on HTTP request: ");
    Serial.println(httpCode);
  }

  http.end();
}