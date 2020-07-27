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
   * @brief Create a Response Control string
   * 
   * @param deviceID 
   * @param result 
   * @return String 
   */
  String createResponseControl(String deviceID, String action, String result);

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
   * @param result 
   * @return String 
   */
  String createResponseSecurityPwChange(String deviceID, String numberOfPasswordChanges, String result);

  /**
   * @brief Create a Response Security Wifi Config string
   * 
   * @return String 
   */
  String createResponseSecurityWifiConfig(String deviceID, String result);

  /**
   * @brief Create a Response Security Reset To Default string
   * 
   * @param result 
   * @return String 
   */
  String createResponseSecurityResetToDefault(String deviceID, String result);

  /**
   * @brief Create a Response Security Restart string
   * 
   * @param result 
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

// ====== HMAC SHA512 Responses ======
  /**
   * @brief Create a response JSON string protected by an HMAC 
   * 
   * @param plainTextResponse
   * @return String 
   */
  String createHmacResponse(String plainTextResponse);

private:
  ScpDebug scpDebug;
  ScpPassword scpPassword;
  ScpCrypto scpCrypto;
  rBase64generic<250> bigBase64;
};

#endif
