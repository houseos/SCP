/*
secure-control-protocol
This is the source file for the ScpPassword class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpPassword.h"

ScpPassword::ScpPassword(){

}

void ScpPassword::setDefaultPassword()
{
  writePasswordToEEPROM(DEFAULT_PW);
  EEPROM.write(0, 1);
  EEPROM.commit();
}

bool ScpPassword::isDefaultPasswordSetOnce()
{
  if (EEPROM.read(0) == 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void ScpPassword::writePasswordToEEPROM(String password)
{
  for (int i = 1; i < 17; i++)
  {
    EEPROM.write(i, (byte)password.charAt(i - 1));
  }
  EEPROM.commit();
}

String ScpPassword::readPasswordFromEEPROM()
{
  String password;
  for (int i = 1; i < 17; i++)
  {
    password = password + char(EEPROM.read(i));
  }
  return password;
}

void ScpPassword::storePasswordInIntArray(uint8_t buffer[], uint8_t buffer_length) {
  memset(buffer, 0, buffer_length);
  String pw = readPasswordFromEEPROM();
  for (int i = 0; i < buffer_length; i++)
  {
    char c = pw.charAt(i);
    buffer[i] = c;
  }
}