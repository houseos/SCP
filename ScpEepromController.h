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
   * @return password 
   */
  String getDeviceId();

      /**
   * @brief 
   * 
   * @param password 
   */
  void setDeviceId(String deviceId);

private:
    const int FLAGS_ADDRESS = 0; // Device ID | PW_SET
    const int FLAGS_LENGTH = 1; // 0
    const int PW_ADDRESS = 1;
    const int PW_LENGTH = 16; // 1 - 17
    const int CURRENT_PW_NUMBER_ADDRESS = 18;
    const int CURRENT_PW_NUMBER_LENGTH = 32; // 18 - 49
    const int DEVICE_ID_ADDRESS = 50;
    const int DEVICE_ID_LENGTH = 16; // 50 - 65

    ScpDebug scpDebug;

};

#endif
