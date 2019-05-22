/*
secure-control-protocol
This is the header file for the ScpPassword class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpPassword_h
#define ScpPassword_h

// store Password persistently
#include <EEPROM.h>

#include "Arduino.h"
#include "ScpDebug.h"

#define PW_LENGTH 16
#define DEFAULTPASSWORD_IS_SET_ADDRESS 0  // 0
#define PASSWORD_ADDRESS 1 // 1 - 17
#define NUMBER_OF_PW_CHANGES_ADDRESS //

class ScpPassword
{

public:
  /**
   * @brief Construct a new Scp Password object
   * 
   */
  ScpPassword();

  /**
   * @brief Set the Default Password object
   * 
   */
  void setDefaultPassword();

  /**
   * @brief 
   * 
   * @return true 
   * @return false 
   */
  bool isDefaultPasswordSetOnce();

  /**
   * @brief 
   * 
   * @param password 
   */
  void writePasswordToEEPROM(String password);

  /**
   * @brief 
   * 
   * @return String 
   */
  String readPasswordFromEEPROM();

  /**
   * @brief 
   * 
   * @param number 
   */
  void storeNumberOfPasswordChanges(uint32_t number);

  /**
   * @brief 
   * 
   * @return number
   */
  uint32_t readNumberOfPasswordChanges();

  void storePasswordInIntArray(uint8_t buffer[], uint8_t buffer_length);

private:
 const String DEFAULT_PW = "1234567890123456";

};

#endif
