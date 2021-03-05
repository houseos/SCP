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
  scpDebug.println(scpDebug.deviceId, "ScpDeviceID:setDeviceID: Mac Addresss: for device ID: " + WiFi.macAddress());
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
  scpDebug.println(scpDebug.deviceId, "ScpDeviceID:setDeviceID: Random device id: " + deviceID);

  scpEeprom.setDeviceId(deviceID);
  scpEeprom.setIsDeviceIdSet();
#ifdef DEBUG
  if (!isDeviceIDSet())
  {
    scpDebug.println(scpDebug.deviceId, "ScpDeviceID:setDeviceID: error - device id setting failed.");
  }
  deviceID = readDeviceID();
  scpDebug.println(scpDebug.deviceId, "ScpDeviceID:setDeviceID:  DeviceID: " + deviceID);
#endif

}

bool ScpDeviceID::isDeviceIDSet()
{
 return scpEeprom.isDeviceIdSet();
}
