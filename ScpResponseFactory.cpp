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
String ScpResponseFactory::createResponseControlUp(String deviceID, String status)
{
    String response = "{ \"type\" : \"control-up\",";
    response +="\"deviceId\" : " + deviceID + ",";
    response += "\"status\" : " + status + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseControlDown(String deviceID, String status)
{
    String response = "{ \"type\" : \"control-down\",";
    response +="\"deviceId\" : " + deviceID + ",";
    response += "\"status\" : " + status + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseControlStop(String deviceID, String status)
{
    String response = "{ \"type\" : \"control-stop\",";
    response +="\"deviceId\" : " + deviceID + ",";
    response += "\"status\" : " + status + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseControlStatus(String deviceID, String status)
{
    String response = "{ \"type\" : \"control-status\",";
    response +="\"deviceId\" : " + deviceID + ",";
    response += "\"status\" : " + status + "\"";
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

String ScpResponseFactory::createResponseSecurityWifiConfig(String deviceID, String result)
{
    String response = "{ \"type\" : \"security-wifi-config\",";
    response += "\"deviceId\" :\"" + deviceID + "\" ,";
    response += "\"result\" :\"" + result + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseSecurityResetToDefault(String deviceID,String result)
{
    String response = "{ \"type\" : \"security-reset-to-default\",";
    response += "\"deviceId\" :\"" + deviceID + "\" ,";
    response += "\"result\" :\"" + result + "\"";
    response += "}";
    return response;
}

String ScpResponseFactory::createResponseSecurityRestart(String deviceID,String result)
{
    String response = "{ \"type\" : \"security-restart\",";
    response += "\"deviceId\" :\"" + deviceID + "\" ,";
    response += "\"result\" :\"" + result + "\"";
    response += "}";
    return response;
}

// ====== Discover Repsonse ======
String ScpResponseFactory::createResponseDiscoverHello(String deviceID, String deviceType, String currentPasswordNumber)
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
    response += "\"currentPasswordNumber\":\"" + currentPasswordNumber + "\",";
    response += "\"hmac\":\"" + hmac + "\"";
    response +=  "}";
    return response;
}

// ====== Encrypted Repsonse ======
String ScpResponseFactory::createEncryptedResponse(String plainTextResponse) {
    // Get password
    String pw = scpPassword.readPassword();

    String nonce;
    String mac;
    int payloadLength = 0;
    String encryptedPayload;
    encryptedPayload = scpCrypto.encryptAndEncode(plainTextResponse, &payloadLength, pw, &nonce, &mac);

    String response = "{\"payload\":\"" + encryptedPayload + "\",";
    response += "\"payloadLength\":\"" + String(payloadLength) + "\",";
    response += "\"nonce\":\"" + nonce + "\",";
    response += "\"mac\":\"" + mac + "\"";
    response +=  "}";
    Serial.println("Encrypted Response: " + response);
    return response;
}