/*
secure-control-protocol
This is the central source file for the secure-control-protocol.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "SCP.h"

/**
 * Initialize the SCP library
 */
SCP::SCP()
{
  server = new ESP8266WebServer(80);

  EEPROM.begin(512);
}

void SCP::handleSecureControl()
{
#ifdef DEBUG
  Serial.println("handleClient");
#endif
  String payload = server->arg("payload");

  // The payload is an encrypted message
  String encryptedText;

  // substring from colon is encrypted text
  encryptedText = payload;
#ifdef DEBUG
  Serial.println("encoded enc text: " + encryptedText);
#endif
  // Set the encrypted text from the payload
  int lengthOfText = 0;
  crypto.getBufferSize((char *)encryptedText.c_str(), lengthOfText);
  char encText[lengthOfText];
  memset(encText, 0, lengthOfText * sizeof(char));
  for (int i = 0; i < lengthOfText; i++)
  {
    encText[i] = encryptedText.c_str()[i];
  }

  // Read the key from the EEPROM
  uint8_t key[BLOCK_SIZE];
  password.storePasswordInIntArray(key, BLOCK_SIZE);

  char output[lengthOfText];
  memset(output, 0, lengthOfText * sizeof(char)); // initialize with all 0

  // decrypt the message
  crypto.decrypt(encText, output, lengthOfText, key, crypto.getIVPlain());
  String out = String(output);
#ifdef DEBUG
  Serial.println(out);
#endif
  String receivedDeviceID = out.substring(0, deviceID.length());
  String messageType =
      out.substring(deviceID.length() + 1, deviceID.length() + 11);

  if (receivedDeviceID.equals(deviceID))
  {
    if (messageType.startsWith("control-up"))
    {

      // control up
      if (!(DEFAULT_PW.equals(password.readPasswordFromEEPROM())))
      {
        String answer = messageFactory.createMessageControlUp(deviceID, "up");

        server->send(200, "application/json", answer);
      }
      else
      {
        String answer = messageFactory.createMessageControlUp(deviceID, "error");
        server->send(200, "application/json", answer);
      }
    }
    else if (messageType.startsWith("control-down"))
    {
      // control down
      if (!(DEFAULT_PW.equals(password.readPasswordFromEEPROM())))
      {
        // control down
        String answer = messageFactory.createMessageControlDown(deviceID, "down");
        server->send(200, "application/json", answer);
      }
      else
      {
        String answer = messageFactory.createMessageControlDown(deviceID, "error");
        server->send(200, "application/json", answer);
      }
    }
    else if (messageType.startsWith("control-stop"))
    {
      // control stop
      if (!(DEFAULT_PW.equals(password.readPasswordFromEEPROM())))
      {
        // control stop
        String answer = messageFactory.createMessageControlStop(deviceID, "stop");
        server->send(200, "application/json", answer);
      }
      else
      {
        String answer = messageFactory.createMessageControlStop(deviceID, "error");
        server->send(200, "application/json", answer);
      }
    }
    else if (messageType.startsWith("control-status"))
    {
      // control stop
      if (!(DEFAULT_PW.equals(password.readPasswordFromEEPROM())))
      {
        // control status
        String answer = messageFactory.createMessageControlStatus(deviceID, "status");

        server->send(200, "application/json", answer);
      }
      else
      {
        String answer = messageFactory.createMessageControlStatus(deviceID, "error");
        server->send(200, "application/json", answer);
      }
    }
    else if (messageType.startsWith("security-pw-change"))
    {
      // Set new password from message
      char newPassword[PW_LENGTH];
      memset(newPassword, 0, PW_LENGTH * sizeof(char));
      for (int i = 0; i < 16; i++)
      {
        newPassword[i] = messageType.charAt(19 + i);
      }
      // store new password

#ifdef DEBUG
      Serial.println(newPassword);
#endif
      password.writePasswordToEEPROM(String(newPassword));
      String answer = messageFactory.createMessageSecurityPwChange("done");

      server->send(200, "application/json", answer);
    }
    else if (messageType.startsWith("security-wifi-config"))
    {
      // Set SSID
      // Set Password

      // Try to connect

      // Return result
    }
    else if (messageType.startsWith("security-reset-to-default"))
    {
      password.setDefaultPassword();
      String answer = messageFactory.createMessageSecurityResetToDefault("done");

      server->send(200, "application/json", answer);
    }
    else if (messageType.startsWith("security-restart"))
    {
      // ESP.restart
    }
  }
}

void SCP::handleSecurityFetchIV()
{
#ifdef DEBUG
  Serial.println("  Message: SecurityFetchIV");
#endif
  String payload = server->arg("payload");
#ifdef DEBUG
  Serial.println("  Payload:" + payload);
  Serial.println("  Device ID:" + deviceID);
#endif
  if (payload.startsWith(deviceID))
  {
    String receivedDeviceID = payload.substring(0, deviceID.length());
    String messageType =
        payload.substring(deviceID.length() + 1, payload.length());

    String ivString = crypto.getIVString();

    String answer = messageFactory.createMessageSecurityFetchIV(deviceID, ivString);

    server->send(200, "application/json", answer);
  }
  else
  {
    sendMalformedPayload();
  }
#ifdef DEBUG
  Serial.println("  Message End: SecurityFetchIV");
#endif
}

void SCP::handleDiscoverHello()
{
#ifdef DEBUG
  Serial.println("  Message: DiscoverHello");
#endif
  String payload = server->arg("payload");
#ifdef DEBUG
  Serial.println("  Payload:" + payload);
#endif
  // handle discover-hello message
  if (payload.equals("discover-hello"))
  {
    String defaultPWresult;
#ifdef DEBUG
    Serial.println("Configured Password: " + password.readPasswordFromEEPROM());
#endif
    if (DEFAULT_PW.equals(password.readPasswordFromEEPROM()))
    {
      defaultPWresult = "true";
    }
    else
    {
      defaultPWresult = "false";
    }

    String stringForHMAC = "discover-response" + deviceID + "secure-control" +
                           WiFi.localIP().toString() + defaultPWresult + "\0";
#ifdef DEBUG
    Serial.println("  ToHash: " + stringForHMAC);
#endif
    uint8_t key[BLOCK_SIZE];
    memset(key, 0, BLOCK_SIZE * sizeof(uint8_t));
    String pw = password.readPasswordFromEEPROM();
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
      char c = pw.charAt(i);
      key[i] = c;
    }
    byte hmac[SHA256HMAC_SIZE];

    byte buffer[stringForHMAC.length()];
    for (int i = 0; i < stringForHMAC.length(); i++)
    {
      buffer[i] = stringForHMAC.charAt(i);
    }
    crypto.generateHMAC(buffer, stringForHMAC.length(), key, hmac);
    rbase64.encode(hmac, SHA256HMAC_SIZE);

    String answer = "{ \"type\" : \"discover-response\",";
    answer += "\"deviceId\" : \"" + deviceID + "\",";
    answer += "\"deviceType\" : \"secure-control\",";
    answer += "\"ipAddress\" : \"" + WiFi.localIP().toString() + "\" ,";
    answer += "\"defaultPw\" :\"" + defaultPWresult + "\",";
    answer += "\"hmac\" :\"";
    answer += rbase64.result();
    answer += "\" }";
    server->send(200, "application/json", answer);
    Serial.println("  discover-response send: " + answer);
  }
  else
  {
    sendMalformedPayload();
  }
#ifdef DEBUG
  Serial.println("  Message End: DiscoverHello");
#endif
}

void SCP::sendMalformedPayload()
{
#ifdef DEBUG
  Serial.println("    Error: MalformedPayload");
#endif
  String message = "Malformed payload\n\n";
  for (uint8_t i = 0; i < server->args(); i++)
  {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }

  server->send(404, "text/plain", message);
#ifdef DEBUG
  Serial.println("    Error End: MalformedPayload");
#endif
}

void SCP::handleNotFound()
{
#ifdef DEBUG
  Serial.println("    Error: HandleNotFound");
#endif

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server->uri();
  message += "\nMethod: ";
  message += (server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";

  for (uint8_t i = 0; i < server->args(); i++)
  {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }

  server->send(404, "text/plain", message);

#ifdef DEBUG
  Serial.println("    Error End: HandleNotFound");
#endif
}

void SCP::handleClient() { server->handleClient(); }

void SCP::init()
{
  crypto.setIV();

  if (password.isDefaultPasswordSetOnce() == false)
  {
    password.setDefaultPassword();
  }

  if (!dID.isDeviceIDSet())
  {
    dID.setDeviceID();
  }
  deviceID = dID.readDeviceIDFromEEPROM();
#ifdef DEBUG
  Serial.println("DeviceID: " + deviceID);
#endif

  server->on("/secure-control", std::bind(&SCP::handleSecureControl, this));
  server->on("/secure-control/security-fetch-iv",
             std::bind(&SCP::handleSecurityFetchIV, this));
  server->on("/secure-control/discover-hello",
             std::bind(&SCP::handleDiscoverHello, this));
  server->onNotFound(std::bind(&SCP::handleNotFound, this));
  server->begin();

#ifdef DEBUG
  Serial.println("HTTP server started");
#endif
}



void SCP::registerControlUpFunction(std::function<void()> fun)
{
  controlUpFunction = fun;
}

void SCP::registerControlDownFunction(std::function<void()> fun)
{
  controlDownFunction = fun;
}

void SCP::registerControlStopFunction(std::function<void()> fun)
{
  controlStopFunction = fun;
}