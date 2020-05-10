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
SCP::SCP() : scpDebug(false)
{
  server = new ESP8266WebServer(80);

  EEPROM.begin(512);  
}

void SCP::handleSecureControl()
{
  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: handleClient");

  String payload = server->arg("payload");
  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: Encoded Payload:" + payload);
  rbase64.decode(payload);
  // The payload base64-decoded is the encrypted message
  char* ivAndEncryptedText = rbase64.result();

  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: Decoded iv & enc text: " +  String(rbase64.result()));

  //Get the IV from the first 16 bytes
  uint8_t iv[16];
  memset(iv, 0, 16 * sizeof(uint8_t));
  for (uint32_t i = 0; i < 16; i++)
  {
    iv[i] = ivAndEncryptedText[i];
    scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: iv[" + String(i)+ "]: " + String(iv[i]));
  }

  //Get the encrypted text from the 16. location until end of string
  int lengthOfEncryptedText = rbase64_dec_len((char*)payload.c_str(), payload.length()) - 16;
  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: encrypted text length: " + String(lengthOfEncryptedText));
  char encText[lengthOfEncryptedText];
  memset(encText, 0, lengthOfEncryptedText * sizeof(char));
  for (uint32_t i = 0; i < lengthOfEncryptedText; i++)
  {
    encText[i] = ivAndEncryptedText[i+16];
    scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: encText[" + String(i) + "]: " + String(encText[i], HEX));
  }

  // Read the key from the EEPROM
  uint8_t key[BLOCK_SIZE];
  password.storePasswordInIntArray(key, BLOCK_SIZE);

  for(uint32_t i = 0; i < BLOCK_SIZE; i ++){
  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: Password as byte[" + String(i) + "]: " + String(key[i], HEX));
  }

  // decrypt the message
  String decrypted =  crypto.decrypt(encText, lengthOfEncryptedText, key, iv);
  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: Decrypted Text: " + decrypted);

  uint32_t NVCNSplitter = decrypted.indexOf(":");
  uint32_t deviceIDSplitter = decrypted.indexOf(":", NVCNSplitter+1);

  String receivedNVCN = decrypted.substring(0, NVCNSplitter);
  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: receivedNVCN: " + receivedNVCN);

  String receivedDeviceID = decrypted.substring(NVCNSplitter + 1, deviceIDSplitter);
  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: receivedDeviceID: " + receivedDeviceID);

  String messageType = decrypted.substring(deviceIDSplitter + 1, decrypted.length());
  scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: messageType: " + messageType);
  
  if (receivedDeviceID.equals(deviceID))
  {
    if (messageType.startsWith("control-up"))
    {

      // control up
      if (!(DEFAULT_PW.equals(password.readPassword())))
      {
        String answer = messageFactory.createMessageControlUp(deviceID, "up");
        scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
        server->send(200, "application/json", answer);
      }
      else
      {
        String answer = messageFactory.createMessageControlUp(deviceID, "error - default password set");
        scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
        server->send(200, "application/json", answer);
      }
    }
    else if (messageType.startsWith("control-down"))
    {
      // control down
      if (!(DEFAULT_PW.equals(password.readPassword())))
      {
        // control down
        String answer = messageFactory.createMessageControlDown(deviceID, "down");
        scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
        server->send(200, "application/json", answer);
      }
      else
      {
        String answer = messageFactory.createMessageControlDown(deviceID, "error - default password set");
        scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
        server->send(200, "application/json", answer);
      }
    }
    else if (messageType.startsWith("control-stop"))
    {
      // control stop
      if (!(DEFAULT_PW.equals(password.readPassword())))
      {
        // control stop
        controlStopFunction();
        String answer = messageFactory.createMessageControlStop(deviceID, "stop");
        scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
        server->send(200, "application/json", answer);
      }
      else
      {
        String answer = messageFactory.createMessageControlStop(deviceID, "error - default password set");
        scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
        server->send(200, "application/json", answer);
      }
    }
    else if (messageType.startsWith("control-status"))
    {
      // control status
      if (!(DEFAULT_PW.equals(password.readPassword())))
      {
        // control status
        String answer = messageFactory.createMessageControlStatus(deviceID, "status");
        scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
        server->send(200, "application/json", answer);
      }
      else
      {
        String answer = messageFactory.createMessageControlStatus(deviceID, "error - default password set");
        scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
        server->send(200, "application/json", answer);
      }
    }
    else if (messageType.startsWith("security-pw-change"))
    {
      // Set new password from message
      char newPassword[PW_LENGTH+1];
      memset(newPassword, 0, (PW_LENGTH+1) * sizeof(char));
      for (int i = 0; i < 16; i++)
      {
        newPassword[i] = messageType.charAt(19 + i);
      }
      // store new password
      scpDebug.println(scpDebug.base, "  SCP.handleSecureControl -> security-pw-change : new password: " + String(newPassword));
      password.writePassword(String(newPassword));
      scpDebug.println(scpDebug.base, "  SCP.handleSecureControl -> security-pw-change : new password set");
      //Increment number of password changes
      scpDebug.println(scpDebug.base, "  SCP.handleSecureControl -> security-pw-change : new number of password changes: " + String(password.readCurrentPasswordNumber() + 1));
      password.storeCurrentPasswordNumber(password.readCurrentPasswordNumber() + 1);

      //Create answer
      String answer = messageFactory.createMessageSecurityPwChange(deviceID, String(password.readCurrentPasswordNumber()) , "done");
      scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: security-pw-change send " + answer);
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
      scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: " + answer);
      server->send(200, "application/json", answer);
    }
    else if (messageType.startsWith("security-restart"))
    {
      // ESP.restart
    }
  }
}

void SCP::handleSecurityFetchNVCN()
{
  scpDebug.println(scpDebug.base, "  SCP.handleSecurityFetchNVCN: Message: SecurityFetchIV");

  String payload = server->arg("payload");

  scpDebug.println(scpDebug.base, "  SCP.handleSecurityFetchNVCN: Payload:" + payload);
  scpDebug.println(scpDebug.base, "  SCP.handleSecurityFetchNVCN: Device ID:" + deviceID);

  if (payload.startsWith(deviceID))
  {
    String receivedDeviceID = payload.substring(0, deviceID.length());
    String messageType =
        payload.substring(deviceID.length() + 1, payload.length());

    String ivString = crypto.getIVString();

    String answer = messageFactory.createMessageSecurityFetchNVCN(deviceID, ivString);
    scpDebug.println(scpDebug.base, "  SCP.handleSecurityFetchNVCN: " + answer);
    server->send(200, "application/json", answer);
  }
  else
  {
    sendMalformedPayload();
  }
  scpDebug.println(scpDebug.base, "  SCP.handleSecurityFetchNVCN: Message End: SecurityFetchIV");
}

void SCP::handleDiscoverHello()
{
  scpDebug.println(scpDebug.base, "  SCP.handleDiscoverHello: Message: DiscoverHello");

  String payload = server->arg("payload");

  scpDebug.println(scpDebug.base, "  SCP.handleDiscoverHello:  Payload:" + payload);

  // handle discover-hello message
  if (payload.equals("discover-hello"))
  {

    String answer = messageFactory.createMessageDiscoverHello(deviceID, deviceType);
    server->send(200, "application/json", answer);

    scpDebug.println(scpDebug.base, "  SCP.handleDiscoverHello:  discover-response send: " + answer);
  }
  else
  {
    sendMalformedPayload();
  }

  scpDebug.println(scpDebug.base, "  SCP.handleDiscoverHello:  Message End: DiscoverHello");
}

void SCP::sendMalformedPayload()
{
  scpDebug.println(scpDebug.base, "    Error: MalformedPayload");

  String message = "Malformed payload\n\n";
  for (uint8_t i = 0; i < server->args(); i++)
  {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }

  server->send(404, "text/plain", message);

  scpDebug.println(scpDebug.base, "    Error End: MalformedPayload");
}

void SCP::handleNotFound()
{
  scpDebug.println(scpDebug.base, "    Error: HandleNotFound");

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

  scpDebug.println(scpDebug.base, "    Error End: HandleNotFound");
}

void SCP::handleClient() { server->handleClient(); }



void SCP::init(String deviceType, bool enableLog)
{
  
  scpDebug = new ScpDebug(enableLog);

  crypto.setIV();

  this->deviceType = deviceType;

  if (password.isDefaultPasswordSetOnce() == false)
  {
    scpDebug.println(scpDebug.base, "  SCP.init: password not set, setting default password");
    password.setDefaultPassword();
  }

  if (!dID.isDeviceIDSet())
  {
    scpDebug.println(scpDebug.base, "  SCP.init: device ID not set, setting device ID");
    dID.setDeviceID();
  }
  deviceID = dID.readDeviceID();

  scpDebug.println(scpDebug.base, "  SCP.init: DeviceID: " + deviceID);

  server->on("/secure-control", std::bind(&SCP::handleSecureControl, this));
  server->on("/secure-control/security-fetch-nvcn",
             std::bind(&SCP::handleSecurityFetchNVCN, this));
  server->on("/secure-control/discover-hello",
             std::bind(&SCP::handleDiscoverHello, this));
  server->onNotFound(std::bind(&SCP::handleNotFound, this));
  server->begin();

  scpDebug.println(scpDebug.base, "  SCP.init: HTTP server started");

  scpDebug.println(scpDebug.base, "  SCP.init: SCP initialized");
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