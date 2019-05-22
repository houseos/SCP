/*
secure-control-protocol
This is the source file for the ScpPassword class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpPassword.h"

ScpPassword::ScpPassword()
{

}

void ScpPassword::setDefaultPassword()
{
  scpEeprom.setPassword(DEFAULT_PW);
  scpEeprom.setIsDefaultPasswordSet();
}

bool ScpPassword::isDefaultPasswordSetOnce()
{
  return scpEeprom.isDefaultPasswordSet();
}

void ScpPassword::writePassword(String password)
{
  scpEeprom.setPassword(password);
}

String ScpPassword::readPassword()
{
  
  return scpEeprom.getPassword();
}

void ScpPassword::storeCurrentPasswordNumber(uint32_t number) {
scpEeprom.setCurrentPwNumber(number);
}

uint32_t ScpPassword::readCurrentPasswordNumber() {
return scpEeprom.getCurrentPwNumber();
}

void ScpPassword::storePasswordInIntArray(uint8_t buffer[], uint8_t buffer_length)
{
  memset(buffer, 0, buffer_length);
  String pw = scpEeprom.getPassword();
  for (int i = 0; i < buffer_length; i++)
  {
    char c = pw.charAt(i);
    buffer[i] = c;
  }
}