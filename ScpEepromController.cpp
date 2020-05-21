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
   scpDebug.println(scpDebug.eeprom, getPassword());
}

// ====== Flags ======

/**
   * @brief 
   * 
   * @return is password set 
   */
bool ScpEepromController::isDefaultPasswordSet()
{
   if ((EEPROM.read(FLAGS_ADDRESS) & 0x01) == 0x01)
   {
      scpDebug.println(scpDebug.eeprom, "      ScpEepromController.isDefaultPasswordSet: Default password initialized.");
      return true;
   }
   else
   {
      scpDebug.println(scpDebug.eeprom, "      ScpEepromController.isDefaultPasswordSet: Default Password not initialized.");
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
   EEPROM.commit();
}

/**
   * @brief 
   * 
   * @return is device ID set 
   */
bool ScpEepromController::isDeviceIdSet()
{
   if ((EEPROM.read(FLAGS_ADDRESS) & 0x02) == 0x02)
   {
      scpDebug.println(scpDebug.eeprom, "      ScpEepromController.isDeviceIdSet: DeviceID set");
      return true;
   }
   else
   {
      scpDebug.println(scpDebug.eeprom, "      ScpEepromController.isDeviceIdSet: DeviceID not set");
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
   EEPROM.commit();

}

/**
   * @brief 
   * 
   */
void ScpEepromController::setAreWifiCredentialsSet()
{
   uint8_t byteOne = EEPROM.read(FLAGS_ADDRESS);
   EEPROM.write(FLAGS_ADDRESS, (byteOne | 0x04));
   EEPROM.commit();
}

/**
   * @brief 
   * 
   * @return is password set 
   */
bool ScpEepromController::areWifiCredentialsSet()
{
   if ((EEPROM.read(FLAGS_ADDRESS) & 0x04) == 0x04)
   {
      scpDebug.println(scpDebug.eeprom, "      ScpEepromController.areWifiCredentialsSet: Wifi Credentials set");
      return true;
   }
   else
   {
      scpDebug.println(scpDebug.eeprom, "      ScpEepromController.areWifiCredentialsSet: Wifi Credentials not set");
      return false;
   }
}

// ====== Values ======

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
      scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getPassword: EEPROM Addr: " + String(i));
      password = password + char(EEPROM.read(i));
      scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getPassword: char " + String(char(EEPROM.read(i))));
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
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getCurrentPwNumber: Current Password Number Byte:" + String(EEPROM.read(CURRENT_PW_NUMBER_ADDRESS) << 24));
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getCurrentPwNumber: Current Password Number Result:" + String(currentPasswordNumber));
   currentPasswordNumber += (EEPROM.read(CURRENT_PW_NUMBER_ADDRESS + 1) << 16);
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getCurrentPwNumber: Current Password Number Byte:" + String(EEPROM.read(CURRENT_PW_NUMBER_ADDRESS) << 16));
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getCurrentPwNumber: Current Password Number Result:" + String(currentPasswordNumber));
   currentPasswordNumber += (EEPROM.read(CURRENT_PW_NUMBER_ADDRESS + 2) << 8);
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getCurrentPwNumber: Current Password Number Byte:" + String(EEPROM.read(CURRENT_PW_NUMBER_ADDRESS) << 8));
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getCurrentPwNumber: Current Password Number Result:" + String(currentPasswordNumber));
   currentPasswordNumber += EEPROM.read(CURRENT_PW_NUMBER_ADDRESS + 3);
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getCurrentPwNumber: Current Password Number Byte:" + String(EEPROM.read(CURRENT_PW_NUMBER_ADDRESS)));
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.getCurrentPwNumber: Current Password Number Result:" + String(currentPasswordNumber));

   return currentPasswordNumber;
}

/**
   * @brief 
   * 
   * @param uint32_t 
   */
void ScpEepromController::setCurrentPwNumber(uint32_t currentPwNumber)
{
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.setCurrentPwNumber: Current Password Number to be set:" + String(currentPwNumber));

   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.setCurrentPwNumber: Current Password Number to be set byte 0:" + String((currentPwNumber >> 24) & 0x000000FF));
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.setCurrentPwNumber: Current Password Number to be set byte 1:" + String((currentPwNumber >> 16) & 0x000000FF));
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.setCurrentPwNumber: Current Password Number to be set byte 2:" + String((currentPwNumber >> 8) & 0x000000FF));
   scpDebug.println(scpDebug.eeprom, "      ScpEepromController.setCurrentPwNumber: Current Password Number to be set byte 3:" + String(currentPwNumber & 0x000000FF));

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

/**
   * @brief 
   * 
   * @return Wifi SSID 
   */
String ScpEepromController::getWifiSSID()
{
   String ssid;
   for (int i = 0; i < WIFI_SSID_LENGTH; i++)
   {
      ssid = ssid + char(EEPROM.read(WIFI_SSID_ADDRESS + i));
   }
   return ssid;
}

/**
   * @brief 
   * 
   * @param ssid 
   */
void ScpEepromController::setWifiSSID(String ssid)
{
   for (int i = 0; i < WIFI_SSID_LENGTH; i++)
   {
      EEPROM.write(WIFI_SSID_ADDRESS + i, ssid[i]);
   }
   EEPROM.commit();
}

/**
   * @brief 
   * 
   * @return Wifi Password 
   */
String ScpEepromController::getWifiPassword()
{
   String password;
   for (int i = 0; i < WIFI_PASSWORD_LENGTH; i++)
   {
      password = password + char(EEPROM.read(WIFI_PASSWORD_ADDRESS + i));
   }
   return password;
}

/**
   * @brief 
   * 
   * @param password 
   */
void ScpEepromController::setWifiPassowrd(String password)
{
   for (int i = 0; i < WIFI_PASSWORD_LENGTH; i++)
   {
      EEPROM.write(WIFI_PASSWORD_ADDRESS + i, password[i]);
   }
   EEPROM.commit();
}
