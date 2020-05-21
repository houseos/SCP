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

String ScpMessageFactory::createMessageDiscoverHello(String deviceID, String deviceType)
{
    scpDebug.println(scpDebug.messageFactory, "  SCP.handleDiscoverHello -> createMessageDiscoverHello:  Number of password changes: " + String(password.readCurrentPasswordNumber()));
    String currentPasswordNumber = String(password.readCurrentPasswordNumber());

    String stringForHMAC = "discover-response" + deviceID + deviceType + currentPasswordNumber + "\0";

    uint8_t key[KEY_LENGTH];
    memset(key, 0, KEY_LENGTH * sizeof(uint8_t));
    String pw = password.readPassword();
    //Get bytes of password string + 1, otherwise the last character is omitted
    pw.getBytes(key, KEY_LENGTH + 1);
    String hmac = crypto.generateHMAC(stringForHMAC, key, KEY_LENGTH);

    String message = "{ \"type\" : \"discover-response\",";
    message += "\"deviceId\" : \"" + deviceID + "\",";
    message += "\"deviceType\" : \"" + deviceType + "\",";
    message += "\"currentPasswordNumber\" :\"" + currentPasswordNumber + "\",";
    message += "\"hmac\" :\"";
    message += hmac;
    message += "\" }";
    return message;
}