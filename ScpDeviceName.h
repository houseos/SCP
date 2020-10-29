/*
secure-control-protocol
This is the header file for the ScpDeviceName class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpDeviceName_h
#define ScpDeviceName_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "ScpDebug.h"
#include "ScpEepromController.h"

class ScpDeviceName
{

public:
    /**
   * @brief Construct a new ScpDeviceID object
   * 
   */
    ScpDeviceName();

    /**
   * @brief 
   * 
   * @param deviceName 
   */
    void writeDeviceName(String deviceName);

    /**
   * @brief 
   * 
   * @return String 
   */
    String readDeviceName();

private:
    ScpEepromController scpEeprom;
    ScpDebug scpDebug;
};

#endif
