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
    Calamari(String baseUrl, String use, String password);
    String getBaseURL();
    void startShift(String email);
    void stopShift(String email);
    bool shiftIsOn(String email);
  private:
    String _baseUrl;
    String _user;
    String _password;

    String _apiCall(String endpoint, String payload = "");
    void _toggleShift(String email, String type);
};

#endif