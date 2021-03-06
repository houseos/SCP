/*
secure-control-protocol
This is the header file for the ScpDeviceID class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpDeviceID_h
#define ScpDeviceID_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "ScpDebug.h"
#include "ScpEepromController.h"

class ScpDeviceID
{

public:
  /**
   * @brief Construct a new ScpDeviceID object
   * 
   */
  ScpDeviceID();

  /**
   * @brief Set the Device I D object
   * 
   */
  void setDeviceID();

  /**
   * @brief 
   * 
   * @return true 
   * @return false 
   */
  bool isDeviceIDSet();

  /**
   * @brief 
   * 
   * @return String 
   */
  String readDeviceID();

private:
  /**
   * @brief 
   * 
   * @return void 
   */
  void writeDeviceID(String deviceID);

  ScpEepromController scpEeprom;
  ScpDebug scpDebug;
};

#endif
