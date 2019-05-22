/*
secure-control-protocol
This is the header file for the ScpEepromController class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include <EEPROM.h>

#include "Arduino.h"
#include "ScpDebug.h"
#include "ScpEepromController.h"

ScpEepromController::ScpEepromController()
{
}

/**
   * @brief 
   * 
   * @return is device ID set 
   */
bool ScpEepromController::isDeviceIdSet()
{
    if ((EEPROM.read(1) & 0x02) == 0x02 )
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

/**
   * @brief 
   * 
   */
void ScpEepromController::setIsDeviceIdSet()
{
    uint8_t byteOne = EEPROM.read(1);
    EEPROM.write(1, (byteOne | 0x02));
}

/**
   * @brief 
   * 
   * @return is password set 
   */
bool ScpEepromController::isDefaultPasswordSet()
{
  if ((EEPROM.read(1) & 0x01) == 0x01 )
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

/**
   * @brief 
   * 
   */
void ScpEepromController::setIsDefaultPasswordSet()
{
    uint8_t byteOne = EEPROM.read(1);
    EEPROM.write(1, (byteOne | 0x01));
}

/**
   * @brief 
   * 
   * @return password 
   */
String ScpEepromController::getPassword()
{
    String password = "";
    for (int i = PW_ADDRESS; i < PW_LENGTH + 1; i++)
    {
        password = password + char(EEPROM.read(i));
    }
    return password;
}

/**
   * @brief 
   * 
   * @return password 
   */
void ScpEepromController::setPassword(String password)
{
    for (int i = PW_ADDRESS; i < PW_LENGTH + 1; i++)
    {
        EEPROM.write(i, (uint8_t)password.charAt(i - 1));
    }
    EEPROM.commit();
}

/**
   * @brief 
   * 
   * @return uint32_t 
   */
uint32_t ScpEepromController::getCurrentPwNumber()
{
}

/**
   * @brief 
   * 
   * @param uint32_t 
   */
void ScpEepromController::setCurrentPwNumber(uint32_t currentPwNumber)
{
    EEPROM.write(CURRENT_PW_NUMBER_ADDRESS, uint8_t((currentPwNumber >> 24) & 0x000000FF));
    EEPROM.write(CURRENT_PW_NUMBER_ADDRESS + 1, uint8_t((currentPwNumber >> 16) & 0x000000FF));
    EEPROM.write(CURRENT_PW_NUMBER_ADDRESS + 2, uint8_t((currentPwNumber >> 8) & 0x000000FF));
    EEPROM.write(CURRENT_PW_NUMBER_ADDRESS + 3, uint8_t(currentPwNumber & 0x000000FF));
    EEPROM.commit();
}

/**
   * @brief 
   * 
   * @return password 
   */
String ScpEepromController::getDeviceId()
{
      String deviceID;
  for (int i = 18; i < 34; i++)
  {
    deviceID = deviceID + char(EEPROM.read(i));
  }
  return deviceID;
}

/**
   * @brief 
   * 
   * @param password 
   */
void ScpEepromController::setDeviceId(String deviceId)
{
      for (int i = 18; i < 34; i++)
  {
    EEPROM.write(i, deviceId[i - 18]);
  }
  EEPROM.commit();
}
