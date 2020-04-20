#ifndef Helpers_h
#define Helpers_h

#include "config.h"
#include "Arduino.h"
#include "WiFi.h"
#include "time.h"

namespace Helper {  
  #define ntpServer "pool.ntp.org"
  #define gmtOffset_sec 0
  #define daylightOffset_sec 3600

  inline String getCurrentTime() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    struct tm timeinfo;

    if(!getLocalTime(&timeinfo)) {
      return "Failed to obtain time";
    }
    
    char fullDate[20];
    strftime(fullDate, 20, "%Y-%m-%dT%H:%M:%S", &timeinfo);

    return String(fullDate);
  }

  inline void connectToWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WifiSSID, WiFiPassword);
    
    Serial.print("Connecting to ");
    Serial.println(WifiSSID);
  
    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(500);
  
      if ((++i % 16) == 0) {
        Serial.println(F(" still trying to connect"));
      }
    }
  
    Serial.print(F("Connected. My IP address is: "));
    Serial.println(WiFi.localIP());
  }
}

#endif