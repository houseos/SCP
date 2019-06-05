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

//Control Messages

  /**
   * @brief Create a Message Control Up object
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createMessageControlUp(String deviceID, String status);

  /**
   * @brief Create a Message Control Down object
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createMessageControlDown(String deviceID, String status);

  /**
   * @brief Create a Message Control Stop object
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createMessageControlStop(String deviceID, String status);

  /**
   * @brief Create a Message Control Status object
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createMessageControlStatus(String deviceID, String status);

// Security Messages

  /**
   * @brief Create a Message Security Fetch I V object
   * 
   * @param deviceID 
   * @param ivString 
   * @return String 
   */
  String createMessageSecurityFetchIV(String deviceID,String ivString);

  /**
   * @brief Create a Message Security Pw Change object
   * 
   * @param status 
   * @return String 
   */
  String createMessageSecurityPwChange(String status);

  /**
   * @brief Create a Message Security Wifi Config object
   * 
   * @return String 
   */
  String createMessageSecurityWifiConfig();

  /**
   * @brief Create a Message Security Reset To Default object
   * 
   * @param status 
   * @return String 
   */
  String createMessageSecurityResetToDefault(String status);

//Discovery Messages
  
  /**
   * @brief Create a Message Discover Hello object
   * 
   * @param deviceID 
   * @param ipAddress 
   * @param defaultPWresult 
   * @param hmac 
   * @return String 
   */
  String createMessageDiscoverHello(String deviceID, String ipAddress, String defaultPWresult, String hmac);

private:
  ScpDebug scpDebug;
};

#endif
