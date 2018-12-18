/*
secure-control-protocol
This is the source file for the ScpDeviceID class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpDeviceID.h"

ScpDeviceID::ScpDeviceID() {}

void writeDeviceIDToEEPROM(String deviceID)
{
  for (int i = 18; i < 34; i++)
  {
    EEPROM.write(i, deviceID[i - 18]);
  }
  EEPROM.commit();
}

String ScpDeviceID::readDeviceIDFromEEPROM()
{
  String deviceID;
  for (int i = 18; i < 34; i++)
  {
    deviceID = deviceID + char(EEPROM.read(i));
  }
  return deviceID;
}

void ScpDeviceID::setDeviceID()
{
  char buffer[17];
#ifdef DEBUG
  Serial.println("Mac Addresss: for device ID" + WiFi.macAddress());
#endif
  WiFi.macAddress().toCharArray(buffer, 17);

  int seed;
  for (int i = 0; i < 17; i++)
  {
    seed += buffer[i];
  }
  randomSeed(seed);
  String deviceID = "";
  for (int i = 0; i < 16; i++)
  {
    deviceID += random(0, 9);
  }
#ifdef DEBUG
  Serial.println("Random device id: " + deviceID);
#endif

  writeDeviceIDToEEPROM(deviceID);
  EEPROM.write(17, 1);
  EEPROM.commit();
}

bool ScpDeviceID::isDeviceIDSet()
{
  if (EEPROM.read(17) == 1)
  {
    #ifdef DEBUG
    Serial.println("DeviceID set");
    #endif
    return true;
  }
  else
  {
    #ifdef DEBUG
    Serial.println("DeviceID not set");
    #endif
    return false;
  }
}
