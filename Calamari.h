/*
  Calamari.h - Library for using Calamari.io API.
  Created by J.V. Lobo, April 16, 2020.
  Released into the public domain.
*/
#ifndef Calamari_h
#define Calamari_h

#include "Arduino.h"

class Calamari {
  public:
    Calamari(String baseUrl, String use, String password, String employee);
    void startShift();
    void stopShift();
    bool shiftIsOn();
    void startLunchBreak();
    void stopLunchBreak();
    bool breakIsOn();
  private:
    String _baseUrl;
    String _user;
    String _password;
    String _employee;

    String _apiCall(String endpoint, String payload = "");
    void _toggleShift(String type);
    void _toggleBreak(String type, String breakId);
    String _getShiftStatus();
};

#endif