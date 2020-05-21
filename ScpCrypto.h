/*
secure-control-protocol
This is the header file for the ScpCrypto class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 - 2020 Benjamin Schilling
*/

#ifndef ScpCrypto_h
#define ScpCrypto_h

// Arduino Libraries
#include "Arduino.h"

// ESP8266 Libraries
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <Crypto.h>

// SCP Libraries
#include "ScpDebug.h"
#include "ScpDecode.h"

// Defines for ChaCha20 Poly1305
#define MAC_LENGTH 16
#define KEY_LENGTH 32
#define NONCE_LENGTH 12

// Defines for the HMAC
#define HMAC_LENGTH 64

#define SUCCESS 0
#define ERROR 1

const int SEED_PIN = A0;

using namespace experimental::crypto;

class ScpCrypto
{

public:
  /**
   * @brief Construct a new Scp Crypto object
   * 
   */
  ScpCrypto();

  /**
   * @brief Uses ChaCha20_Poly1305 to decrypt the message and verify
   *        the message authentication code afterwards
   * 
   * @param base64Payload The base64 encoded encrypted payload
   * @param payloadLength The length of the encrypted payload
   * @param key The key
   * @param base64Nonce The base64 encoded nonce
   * @param base64Mac The base64 encoded message authentication code
   * 
   * @returns String The decrypted message on success, empty string on error
   */
  String decrypt(String base64Payload, int payloadLength,
                 String key, String base64Nonce, String base64Mac);

  /**
  * @brief Generates a SHA512 HMAC for the given payload
  * 
  * @param payload The payload to hash
  * @param key The key for the HMAC as byte array
  * @param keyLength The length of the key
  * 
  * @returns The resulting HMAC as HEX String
  */
  String generateHMAC(String payload, uint8_t *key, size_t keyLength);

  String getNVCN();

  bool checkNVCN(String nvcn);

private:
  long unsigned int currentNvcn;

};

#endif