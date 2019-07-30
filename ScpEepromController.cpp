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
   scpDebug.println(getPassword());

}

/**
   * @brief 
   * 
   * @return is device ID set 
   */
bool ScpEepromController::isDeviceIdSet()
{
  if ((EEPROM.read(FLAGS_ADDRESS) & 0x02) == 0x02 )
  {
    #ifdef DEBUG
    Serial.println("      ScpEepromController.isDeviceIdSet: DeviceID set");
    #endif
    return true;
  }
  else
  {
    #ifdef DEBUG
    Serial.println("      ScpEepromController.isDeviceIdSet: DeviceID not set");
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
    uint8_t byteOne = EEPROM.read(FLAGS_ADDRESS);
    EEPROM.write(FLAGS_ADDRESS, (byteOne | 0x02));
}

/**
   * @brief 
   * 
   * @return is password set 
   */
bool ScpEepromController::isDefaultPasswordSet()
{
  if ((EEPROM.read(FLAGS_ADDRESS) & 0x01) == 0x01 )
  {
    #ifdef DEBUG
    Serial.println("      ScpEepromController.isDefaultPasswordSet: Default Password set");
    #endif
    return true;
  }
  else
  {
    #ifdef DEBUG
    Serial.println("      ScpEepromController.isDefaultPasswordSet: Default Password not set");
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
    uint8_t byteOne = EEPROM.read(FLAGS_ADDRESS);
    EEPROM.write(FLAGS_ADDRESS, (byteOne | 0x01));
}

/**
   * @brief 
   * 
   * @return password 
   */
String ScpEepromController::getPassword()
{
    String password = "";
    for (int i = PW_ADDRESS; i <= PW_LENGTH; i++)
    {
        scpDebug.println("      ScpEepromController.getPassword: EEPROM Addr: " + String(i));
        password = password + char(EEPROM.read(i));
        scpDebug.println("      ScpEepromController.getPassword: char " + String(char(EEPROM.read(i))));
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
    for (int i = 0; i < PW_LENGTH; i++)
    {
        EEPROM.write(PW_ADDRESS + i, (uint8_t)password.charAt(i));
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
   uint32_t currentPasswordNumber = 0;

   currentPasswordNumber = (EEPROM.read(CURRENT_PW_NUMBER_ADDRESS) << 24);
   scpDebug.println("      ScpEepromController.getCurrentPwNumber: Current Password Number Byte:" + String(EEPROM.read(CURRENT_PW_NUMBER_ADDRESS) << 24));
   scpDebug.println("      ScpEepromController.getCurrentPwNumber: Current Password Number Result:" + String(currentPasswordNumber));
   currentPasswordNumber += (EEPROM.read(CURRENT_PW_NUMBER_ADDRESS + 1) << 16);
   scpDebug.println("      ScpEepromController.getCurrentPwNumber: Current Password Number Byte:" + String(EEPROM.read(CURRENT_PW_NUMBER_ADDRESS) << 16));
   scpDebug.println("      ScpEepromController.getCurrentPwNumber: Current Password Number Result:" + String(currentPasswordNumber));
   currentPasswordNumber += (EEPROM.read(CURRENT_PW_NUMBER_ADDRESS + 2) << 8);
   scpDebug.println("      ScpEepromController.getCurrentPwNumber: Current Password Number Byte:" + String(EEPROM.read(CURRENT_PW_NUMBER_ADDRESS) << 8));
   scpDebug.println("      ScpEepromController.getCurrentPwNumber: Current Password Number Result:" + String(currentPasswordNumber));
   currentPasswordNumber += EEPROM.read(CURRENT_PW_NUMBER_ADDRESS + 3);
   scpDebug.println("      ScpEepromController.getCurrentPwNumber: Current Password Number Byte:" + String(EEPROM.read(CURRENT_PW_NUMBER_ADDRESS)));
   scpDebug.println("      ScpEepromController.getCurrentPwNumber: Current Password Number Result:" + String(currentPasswordNumber));

   return currentPasswordNumber;
}

/**
   * @brief 
   * 
   * @param uint32_t 
   */
void ScpEepromController::setCurrentPwNumber(uint32_t currentPwNumber)
{
   scpDebug.println("      ScpEepromController.setCurrentPwNumber: Current Password Number to be set:" + String(currentPwNumber));
   
   scpDebug.println("      ScpEepromController.setCurrentPwNumber: Current Password Number to be set byte 0:" + String((currentPwNumber >> 24) & 0x000000FF));
   scpDebug.println("      ScpEepromController.setCurrentPwNumber: Current Password Number to be set byte 1:" + String((currentPwNumber >> 16) & 0x000000FF));
   scpDebug.println("      ScpEepromController.setCurrentPwNumber: Current Password Number to be set byte 2:" + String((currentPwNumber >> 8) & 0x000000FF));
   scpDebug.println("      ScpEepromController.setCurrentPwNumber: Current Password Number to be set byte 3:" + String(currentPwNumber & 0x000000FF));

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
  for (int i = 0; i < DEVICE_ID_LENGTH; i++)
  {
    deviceID = deviceID + char(EEPROM.read(DEVICE_ID_ADDRESS + i));
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
  for (int i = 0; i < DEVICE_ID_LENGTH; i++)
  {
    EEPROM.write(DEVICE_ID_ADDRESS + i, deviceId[i]);
  }
  EEPROM.commit();
}
