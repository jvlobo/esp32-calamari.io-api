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

Calamari::Calamari(String baseUrl, String user, String password) {
  _baseUrl.concat(baseUrl);
  _user.concat(user);
  _password.concat(password);
}

String Calamari::getBaseURL() {
  return _baseUrl;
}

void Calamari::startShift(String email) {
  Calamari::_toggleShift(email, "in");
}

void Calamari::stopShift(String email) {
  Calamari::_toggleShift(email, "out");
}

void Calamari::_toggleShift(String email, String type) {
  String endpoint = "clockin/terminal/v1/clock-" + type;
  String payload = "{\"person\": \"" + email + "\", \"time\": \"" + Helper::getCurrentTime() + "\"}";

  Calamari::_apiCall(endpoint, payload);
}

bool Calamari::shiftIsOn(String email) {
  String endpoint = "clockin/shift/status/v1/get-current";
  String payload = "{\"person\": \"" + email + "\"}";

  String response = Calamari::_apiCall(endpoint, payload);
  JSONVar myObject = JSON.parse(response);
  String shiftStatus = (const char*) myObject["status"];

  return shiftStatus == "STARTED";
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