/*
secure-control-protocol
This is the header file for the ScpPassword class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpPassword_h
#define ScpPassword_h

#include "Arduino.h"
#include "ScpDebug.h"
#include "ScpEepromController.h"

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
  void writePassword(String password);

  /**
   * @brief 
   * 
   * @return String 
   */
  String readPassword();

  /**
   * @brief 
   * 
   * @param number 
   */
  void storeCurrentPasswordNumber(uint32_t number);

  /**
   * @brief 
   * 
   * @return number
   */
  uint32_t readCurrentPasswordNumber();

  void storePasswordInIntArray(uint8_t buffer[], uint8_t buffer_length);

private:
  const String DEFAULT_PW = "01234567890123456789012345678901";
  ScpEepromController scpEeprom;
  ScpDebug scpDebug;
};

#endif
