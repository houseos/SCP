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
#include "ScpPassword.h"
#include "ScpCrypto.h"

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
   * @brief Create a Message Control Up string
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createMessageControlUp(String deviceID, String status);

  /**
   * @brief Create a Message Control Down string
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createMessageControlDown(String deviceID, String status);

  /**
   * @brief Create a Message Control Stop string
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createMessageControlStop(String deviceID, String status);

  /**
   * @brief Create a Message Control Status string
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createMessageControlStatus(String deviceID, String status);

// Security Messages

  /**
   * @brief Create a Message Security Fetch NVCN string
   * 
   * @param deviceID 
   * @param ivString 
   * @return String 
   */
  String createMessageSecurityFetchNVCN(String deviceID,String nvcnString);

  /**
   * @brief Create a Message Security Pw Change string
   * 
   * @param status 
   * @return String 
   */
  String createMessageSecurityPwChange(String deviceID, String numberOfPasswordChanges, String status);

  /**
   * @brief Create a Message Security Wifi Config string
   * 
   * @return String 
   */
  String createMessageSecurityWifiConfig();

  /**
   * @brief Create a Message Security Reset To Default string
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
   * @param deviceType 
   * @param defaultPWresult 
   * @param hmac 
   * @return String 
   */
  String createMessageDiscoverHello(String deviceID, String deviceType);

private:
  ScpDebug scpDebug;
  ScpPassword password;
  ScpCrypto crypto;

  String hmacForString(String string);
};

#endif
