/*
secure-control-protocol
This is the header file for the ScpResponseFactory class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpResponseFactory_h
#define ScpResponseFactory_h

#include "Arduino.h"

#include "ScpDebug.h"
#include "ScpPassword.h"
#include "ScpCrypto.h"

#define  PW_LENGTH 16

class ScpResponseFactory
{

public:
  /**
   * @brief Construct a new Scp Password object
   * 
   */
  ScpResponseFactory();

// ====== Control Responses ======

  /**
   * @brief Create a Response Control Up string
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createResponseControlUp(String deviceID, String status);

  /**
   * @brief Create a Response Control Down string
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createResponseControlDown(String deviceID, String status);

  /**
   * @brief Create a Response Control Stop string
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createResponseControlStop(String deviceID, String status);

  /**
   * @brief Create a Response Control Status string
   * 
   * @param deviceID 
   * @param status 
   * @return String 
   */
  String createResponseControlStatus(String deviceID, String status);

// ====== Security Responses ======

  /**
   * @brief Create a Response Security Fetch NVCN string
   * 
   * @param deviceID 
   * @param ivString 
   * @return String 
   */
  String createResponseSecurityFetchNVCN(String deviceID,String nvcnString);

  /**
   * @brief Create a Response Security Pw Change string
   * 
   * @param status 
   * @return String 
   */
  String createResponseSecurityPwChange(String deviceID, String numberOfPasswordChanges, String status);

  /**
   * @brief Create a Response Security Wifi Config string
   * 
   * @return String 
   */
  String createResponseSecurityWifiConfig(String deviceID, String result);

  /**
   * @brief Create a Response Security Reset To Default string
   * 
   * @param status 
   * @return String 
   */
  String createResponseSecurityResetToDefault(String deviceID, String result);

  /**
   * @brief Create a Response Security Restart string
   * 
   * @param status 
   * @return String 
   */
  String createResponseSecurityRestart(String deviceID, String result);

// ====== Discovery Responses ======
  
  /**
   * @brief Create a Response Discover Hello object
   * 
   * @param deviceID 
   * @param deviceType 
   * @param defaultPWresult 
   * @param hmac 
   * @return String 
   */
  String createResponseDiscoverHello(String deviceID, String deviceType, String currentPasswordNumber);

// ====== Encrypted Responses ======
  /**
   * @brief Create a encrpyted response JSON string
   * 
   * @param deviceID 
   * @param deviceType 
   * @param defaultPWresult 
   * @param hmac 
   * @return String 
   */
  String createEncryptedResponse(String plainTextResponse);

private:
  ScpDebug scpDebug;
  ScpPassword scpPassword;
  ScpCrypto scpCrypto;
};

#endif
