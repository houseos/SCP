/*
secure-control-protocol
This is the source file for the ScpResponseFactory class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpResponseFactory.h"

ScpResponseFactory::ScpResponseFactory()
{
}

// ====== Control Repsonses ======
String ScpResponseFactory::createResponseControl(String deviceID, String action, String result)
{
    String response = "{ \"type\" : \"control\",";
    response += "\"action\" :  \"" + action + "\",";
    response += "\"deviceId\" : \"" + deviceID + "\",";
    response += "\"result\" : \"" + result + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseControlStatus(String deviceID, String status)
{
    String response = "{ \"type\" : \"control-status\",";
    response += "\"deviceId\" : \"" + deviceID + "\",";
    response += "\"status\" : \"" + status + "\"";
    response += "}";
    return response;
}

// ====== Security Repsonses ======
String ScpResponseFactory::createResponseSecurityFetchNVCN(String deviceID, String nvcnString)
{
    String response = "{ \"type\" : \"security-fetch-nvcn\",";
    response += "\"deviceId\" :\"" + deviceID + "\" ,";
    response += "\"nvcn\" :\"" + nvcnString + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseSecurityPwChange(String deviceID, String numberOfPasswordChanges, String status)
{
    String response = "{\"type\":\"security-pw-change\",";
    response += "\"deviceId\":\"" + deviceID + "\",";
    response += "\"currentPasswordNumber\":\"" + numberOfPasswordChanges + "\",";
    response += "\"result\":\"" + status + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseSecurityNameChange(String deviceID, String deviceName, String status)
{
    String response = "{\"type\":\"security-name-change\",";
    response += "\"deviceId\":\"" + deviceID + "\",";
    response += "\"deviceName\":\"" + deviceName + "\",";
    response += "\"result\":\"" + status + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseSecurityWifiConfig(String deviceID, String result)
{
    String response = "{ \"type\" : \"security-wifi-config\",";
    response += "\"deviceId\" :\"" + deviceID + "\" ,";
    response += "\"result\" :\"" + result + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseSecurityResetToDefault(String deviceID, String result)
{
    String response = "{ \"type\" : \"security-reset-to-default\",";
    response += "\"deviceId\" :\"" + deviceID + "\" ,";
    response += "\"result\" :\"" + result + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseSecurityRestart(String deviceID, String result)
{
    String response = "{ \"type\" : \"security-restart\",";
    response += "\"deviceId\" :\"" + deviceID + "\" ,";
    response += "\"result\" :\"" + result + "\"";
    response += "}";
    return response;
}

// ====== Discover Response ======
String ScpResponseFactory::createResponseDiscoverHello(String deviceID, String deviceType, String deviceName, uint8_t numberOfActions, char *actions[], String currentPasswordNumber)
{
    String stringForHMAC = "discover-response" + deviceID + deviceType + currentPasswordNumber + "\0";

    uint8_t key[KEY_LENGTH];
    memset(key, 0, KEY_LENGTH * sizeof(uint8_t));
    String pw = scpPassword.readPassword();
    //Get bytes of password string + 1, otherwise the last character is omitted
    pw.getBytes(key, KEY_LENGTH + 1);
    String hmac = scpCrypto.generateHMAC(stringForHMAC, key, KEY_LENGTH);

    String response = "{";
    response += "\"type\":\"discover-response\",";
    response += "\"deviceId\":\"" + deviceID + "\",";
    response += "\"deviceType\":\"" + deviceType + "\",";
    response += "\"deviceName\":\"" + deviceName + "\",";
    response += "\"actions\": [";
    for (uint8_t i = 0; i < numberOfActions)
    {
        response += "\"" + actions[i] + "\",";
    }
    response += "],";
    response += "\"currentPasswordNumber\":\"" + currentPasswordNumber + "\",";
    response += "\"hmac\":\"" + hmac + "\"";
    response += "}";
    return response;
}

// ====== HMAC SHA512 Response ======
String ScpResponseFactory::createHmacResponse(String plainTextResponse)
{

    bigBase64.encode(plainTextResponse);
    char *encodedPayload = bigBase64.result();
    String payloadToSend = String(encodedPayload);

    uint8_t key[KEY_LENGTH];
    memset(key, 0, KEY_LENGTH * sizeof(uint8_t));
    String pw = scpPassword.readPassword();
    //Get bytes of password string + 1, otherwise the last character is omitted
    pw.getBytes(key, KEY_LENGTH + 1);
    String hmac = scpCrypto.generateHMAC(payloadToSend, key, KEY_LENGTH);

    String response = "{";
    response += "\"response\":\"" + payloadToSend + "\",";
    response += "\"hmac\":\"" + hmac + "\"";
    response += "}";
    return response;
}