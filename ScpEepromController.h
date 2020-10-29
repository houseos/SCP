/*
secure-control-protocol
This is the header file for the ScpEepromController class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpEepromController_h
#define ScpEepromController_h

#include <EEPROM.h>

#include "Arduino.h"
#include "ScpDebug.h"

class ScpEepromController
{

public:
  /**
   * @brief Construct a new Scp Password object
   * 
   */
  ScpEepromController();

  // ====== Flags ======

  /**
   * @brief 
   * 
   * @return is device ID set 
   */
  bool isDeviceIdSet();

  /**
   * @brief 
   * 
   */
  void setIsDeviceIdSet();

  /**
   * @brief 
   * 
   * @return is password set 
   */
  bool isDefaultPasswordSet();

  /**
   * @brief 
   * 
   */
  void setIsDefaultPasswordSet();

  /**
   * @brief 
   * 
   * @return is password set 
   */
  bool areWifiCredentialsSet();

  /**
   * @brief 
   * 
   */
  void setAreWifiCredentialsSet();
  // ====== Values ======

  /**
   * @brief 
   * 
   * @return password 
   */
  String getPassword();

  /**
   * @brief 
   * 
   * @return password 
   */
  void setPassword(String password);

  /**
   * @brief 
   * 
   * @return uint32_t 
   */
  uint32_t getCurrentPwNumber();

  /**
   * @brief 
   * 
   * @param uint32_t 
   */
  void setCurrentPwNumber(uint32_t currentPwNumber);

  /**
   * @brief 
   * 
   * @return deviceID 
   */
  String getDeviceId();

  /**
   * @brief 
   * 
   * @param deviceId 
   */
  void setDeviceId(String deviceId);

  /**
   * @brief 
   * 
   * @return SSID 
   */
  String getWifiSSID();

  /**
   * @brief 
   * 
   * @param ssid 
   */
  void setWifiSSID(String ssid);

  /**
   * @brief 
   * 
   * @return Wifi Password 
   */
  String getWifiPassword();

  /**
   * @brief 
   * 
   * @param password 
   */
  void setWifiPassword(String password);

  /**
   * @brief 
   * 
   * @return device Name 
   */
  String getDeviceName();

  /**
   * @brief 
   * 
   * @param deviceName 
   */
  void setDeviceName(String deviceName);

  /**
   * @brief Resets the EEPROM to the default state
   * 
   */
  void resetToDefault();

private:
  const int FLAGS_ADDRESS = 0; // res. | res. | rest | res. | res. | Wifi Credentials set | Device ID set | Default PW Initialized
  const int FLAGS_LENGTH = 1;  // Byte 0
  const int PW_ADDRESS = 1;
  const int PW_LENGTH = 32; // Bytes 1 - 32
  const int CURRENT_PW_NUMBER_ADDRESS = 33;
  const int CURRENT_PW_NUMBER_LENGTH = 32; // Bytes 33 - 64
  const int DEVICE_ID_ADDRESS = 65;
  const int DEVICE_ID_LENGTH = 16; // Bytes 65 - 80
  const int WIFI_SSID_ADDRESS = 81;
  const int WIFI_SSID_LENGTH = 32; // Bytes 81 - 112
  const int WIFI_PASSWORD_ADDRESS = 113;
  const int WIFI_PASSWORD_LENGTH = 32; // Bytes 113 - 144
  const int DEVICE_NAME_ADDRESS = 145;
  const int DEVICE_NAME_LENGTH = 32; // Bytes 145 - 177

  ScpDebug scpDebug;
};

#endif
