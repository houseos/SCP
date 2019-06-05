/*
secure-control-protocol
This is the header file for the ScpCrypto class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpCrypto_h
#define ScpCrypto_h

// store DevceID persistently
#include <EEPROM.h>

#include <Crypto.h>
#include <rBase64.h>

#include "Arduino.h"
#include "ScpDebug.h"

#define BLOCK_SIZE 16
#define KEY_LENGTH 16

const int SEED_PIN = A0;

class ScpCrypto
{

public:
  /**
   * @brief Construct a new Scp Crypto object
   * 
   */
  ScpCrypto();

  /**
   * @brief 
   * 
   * @param enciphered 
   * @param lengthOfText 
   * @param key 
   * @param iv 
   * 
   * @returns String
   */
  String decrypt(char *enciphered, uint32_t lengthOfText,
                  uint8_t *key, uint8_t *iv);

  /**
  * @brief 
  * 
  * @param message 
  * @param length 
  * @param key 
  * @param authCode 
  */
  void generateHMAC(byte *message, uint32_t length, uint8_t *key,
                    byte *authCode);

  /**
 * @brief 
 * 
 */
  void setIV();

  /**
 * @brief 
 * 
 * @return String 
 */
  String getIVString();

  /**
 * @brief 
 * 
 * @return uint8_t* 
 */
  uint8_t *getIVPlain();

private:
  uint8_t iv[BLOCK_SIZE];
};

#endif