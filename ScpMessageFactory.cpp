/*
secure-control-protocol
This is the source file for the ScpMessageFactory class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpMessageFactory.h"

ScpMessageFactory::ScpMessageFactory()
{
}

//Control Messages
String ScpMessageFactory::createMessageControlUp(String deviceID, String status)
{
    String message = "{ \"type\" : \"control-up\", \"deviceId\" : " + deviceID +
                     ", \"status\" : " + status + " }";
    return message;
}
String ScpMessageFactory::createMessageControlDown(String deviceID, String status)
{
    String message = "{ \"type\" : \"control-down\", \"deviceId\" : " + deviceID +
                     ", \"status\" : " + status + " }";
    return message;
}
String ScpMessageFactory::createMessageControlStop(String deviceID, String status)
{
    String message = "{ \"type\" : \"control-stop\", \"deviceId\" : " + deviceID +
                     ", \"status\" : " + status + " }";
    return message;
}
String ScpMessageFactory::createMessageControlStatus(String deviceID, String status)
{
    String message = "{ \"type\" : \"control-status\", \"deviceId\" : " + deviceID +
                     ", \"status\" : " + status + " }";
    return message;
}

// Security Messages
String ScpMessageFactory::createMessageSecurityFetchNVCN(String deviceID, String nvcnString)
{
    String message = "{ \"type\" : \"security-fetch-nvcn\",  \"deviceId\" :\"" + deviceID + "\" ,  \"nvcn\" :\"" + nvcnString + "\"  }";
    return message;
}
String ScpMessageFactory::createMessageSecurityPwChange(String deviceID, String numberOfPasswordChanges, String status)
{
    String message = "{ \"type\" : \"security-pw-change\",  \"deviceId\" :\"" + deviceID + "\" ,  \"currentPasswordNumber\" :\"" + numberOfPasswordChanges + "\" , \"result\" : \"" + status +
                     "\" }";
    return message;
}
String ScpMessageFactory::createMessageSecurityWifiConfig()
{
    return "";
}
String ScpMessageFactory::createMessageSecurityResetToDefault(String status)
{
    String message = "{ \"type\" : \"security-reset-to-default\", \"result\" : " +
                     status + " }";
    return message;
}

//Discovery Messages
String ScpMessageFactory::createMessageDiscoverHello(String deviceID, String deviceType)
{
    scpDebug.println("  SCP.handleDiscoverHello -> createMessageDiscoverHello:  Number of password changes: " + String(password.readCurrentPasswordNumber()));
    String currentPasswordNumber = String(password.readCurrentPasswordNumber());

    String stringForHMAC = "discover-response" + deviceID + deviceType + currentPasswordNumber + "\0";

    String hmac = hmacForString(stringForHMAC);

    String message = "{ \"type\" : \"discover-response\",";
    message += "\"deviceId\" : \"" + deviceID + "\",";
    message += "\"deviceType\" : \"" + deviceType + "\",";
    message += "\"currentPasswordNumber\" :\"" + currentPasswordNumber + "\",";
    message += "\"hmac\" :\"";
    message += hmac;
    message += "\" }";
    return message;
}


String ScpMessageFactory::hmacForString(String string){

    scpDebug.println("  SCP.handleDiscoverHello -> createMessageDiscoverHello:  ToHmac: " + string);

    uint8_t key[BLOCK_SIZE];
    memset(key, 0, BLOCK_SIZE * sizeof(uint8_t));
    String pw = password.readPassword();
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
      char c = pw.charAt(i);
      key[i] = c;
    }
    byte hmacBytes[SHA256HMAC_SIZE];

    byte buffer[string.length()];
    for (int i = 0; i < string.length(); i++)
    {
      buffer[i] = string.charAt(i);
      scpDebug.println("  SCP.handleDiscoverHello -> createMessageDiscoverHello:  Buffer: " +  String(buffer[i]));
    }
    crypto.generateHMAC(buffer, string.length(), key, hmacBytes);

    for(int i = 0; i< SHA256HMAC_SIZE; i++){
        scpDebug.println("  SCP.handleDiscoverHello -> createMessageDiscoverHello:  HMAC Byte: " + String(i) + ": " + String(hmacBytes[i]));
    }

    rbase64.encode(hmacBytes, SHA256HMAC_SIZE);

    return rbase64.result();
}