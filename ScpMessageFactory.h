/*
secure-control-protocol
This is the header file for the ScpMessageFactory class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpMessageFactory_h
#define ScpMessageFactory_h

#include "Arduino.h"

#include "ScpDebug.h"

#define  PW_LENGTH 16

class ScpMessageFactory
{

public:
  /**
   * @brief Construct a new Scp Password object
   * 
   */
  ScpMessageFactory();

//Control Message
  String createMessageControlUp(String deviceID, String status);
  String createMessageControlDown(String deviceID, String status);
  String createMessageControlStop(String deviceID, String status);
  String createMessageControlStatus(String deviceID, String status);

// Security Messages
  String createMessageSecurityFetchIV(String deviceID,String ivString);
  String createMessageSecurityPwChange(String status);
  String createMessageSecurityWifiConfig();
  String createMessageSecurityResetToDefault(String status);

//Discovery Messages
  String createMessageDiscoverHello();

};

#endif
