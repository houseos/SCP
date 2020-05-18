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

// 3rd Party Libraries
#include <rBase64.h>

// SCP Libraries
#include "ScpDebug.h"

// Defines for ChaCha20 Poly1305
#define MAC_LENGTH 16
#define KEY_LENGTH 32
#define NONCE_LENGTH 12

// Defines for the HMAC
#define HMAC_LENGTH 16

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
   * @param payload The encrypted payload
   * @param payloadLength The length of the encrypted payload
   * @param key The key as a byte array
   * @param nonce The nonce as a byte array
   * @param mac The message authentication code as a byte array
   * 
   * @returns String The decrypted message on success, empty string on error
   */
  String decrypt(char *payload, size_t payloadLength,
                 uint8_t *key, uint8_t *nonce, uint8_t *mac);

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
};

#endif