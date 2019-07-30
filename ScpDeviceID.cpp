/*
secure-control-protocol
This is the source file for the ScpDeviceID class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpDeviceID.h"

ScpDeviceID::ScpDeviceID() {
}

String ScpDeviceID::readDeviceID()
{
return scpEeprom.getDeviceId();
}

void ScpDeviceID::setDeviceID()
{
  char buffer[17];
#ifdef DEBUG
  Serial.println("    ScpDeviceID:setDeviceID: Mac Addresss: for device ID: " + WiFi.macAddress());
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
  Serial.println("    ScpDeviceID:setDeviceID: Random device id: " + deviceID);
#endif

  scpEeprom.setDeviceId(deviceID);
  scpEeprom.setIsDeviceIdSet();
#ifdef DEBUG
  if (!isDeviceIDSet())
  {
    scpDebug.println("    ScpDeviceID:setDeviceID: error - device id setting failed.");
  }
  deviceID = readDeviceID();
  scpDebug.println("    ScpDeviceID:setDeviceID:  DeviceID: " + deviceID);
#endif

}

bool ScpDeviceID::isDeviceIDSet()
{
 return scpEeprom.isDeviceIdSet();
}
