/*
secure-control-protocol
This is the central header file for the secure-control-protocol.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef SCP_h
#define SCP_h

#include <ESP8266WebServer.h>

#include "ScpDeviceID.h"
#include "ScpPassword.h"
#include "ScpCrypto.h"

#include "ScpDebug.h"

class SCP
{
public:
  /**
   * @brief Construct a new SCP object
   * 
   */
  SCP();

  /**
   * @brief 
   * 
   */
  void init();

    /**
   * @brief 
   * 
   */
  void handleClient();

  void registerControlUpFunction(std::function<void()> fun);

  void registerControlDownFunction(std::function<void()> fun);
   
  void registerControlStopFunction(std::function<void()> fun);

private:
  ScpPassword password;
  ScpDeviceID dID;
  ScpCrypto crypto;
  String deviceID = "";
  ESP8266WebServer *server;
  String DEFAULT_PW = "123456789012456";

  std::function<void()> controlUpFunction;
  std::function<void()> controlDownFunction;
  std::function<void()> controlStopFunction;


  // HTTP Endpoints
  /**
   * @brief 
   * 
   */
  void handleSecureControl();

  /**
   * @brief 
   * 
   */
  void handleSecurityFetchIV();

  /**
   * @brief 
   * 
   */
  void handleDiscoverHello();

  /**
   * @brief 
   * 
   */
  void handleNotFound();
  // HTTP Error Methods
  
  /**
   * @brief 
   * 
   */
  void sendMalformedPayload();
};

#endif
