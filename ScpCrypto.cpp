/*
secure-control-protocol
This is the source file for the ScpCrypto class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpCrypto.h"

ScpCrypto::ScpCrypto() {}

void ScpCrypto::decrypt(char *enciphered, char *output, int lengthOfText,
                  uint8_t *key, uint8_t *iv)
{
  lengthOfText = lengthOfText + 1; // re-adjust
  char *decoded = (char *)malloc(sizeof(char) * lengthOfText);
  byte deciphered[lengthOfText];

  memset(decoded, 0, lengthOfText);    // initialize with all 0
  memset(deciphered, 0, lengthOfText); // initialize with all 0

  // decode the base64 message
  rbase64.decode((const char *)enciphered);
  decoded = rbase64.result();

  // adjust lengthOfText to multiple of 16 bytes
  getBufferSize(enciphered, lengthOfText);

  // create aesDecryptor abject
  AES aesDecryptor(key, iv, AES::AES_MODE_128, AES::CIPHER_DECRYPT);

  // decrypt the message
  aesDecryptor.process((uint8_t *)decoded, deciphered, lengthOfText);

  // return the message
  strcpy(output, (char *)deciphered);
}

void ScpCrypto::generateHMAC(byte *message, uint32_t length, uint8_t *key,
                       byte *authCode)
{
  /* Create the HMAC instance with our key */
  SHA256HMAC hmac(key, KEY_LENGTH);

  /* Update the HMAC with just a plain string (null terminated) */
  hmac.doUpdate(message, length);

  /* Finish the HMAC calculation and return the authentication code */
  hmac.doFinal(authCode);
}

void ScpCrypto::getBufferSize(char *text, int &length)
{
  int i = strlen(text);
  int buf = round(i / BLOCK_SIZE) * BLOCK_SIZE;
  length = (buf <= i) ? buf + BLOCK_SIZE : buf;
}

void ScpCrypto::setIV()
{
  int seed;
  for (int i = 0; i < 100; i++)
  {
    seed += analogRead(SEED_PIN);
  }
  randomSeed(seed);
  for (int i = 0; i < BLOCK_SIZE; i++)
  {
    iv[i] = random(0, 9);
  }
}

String ScpCrypto::getIVString(){
    String ivString = "";
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
      ivString = ivString + String(iv[i]);
    }
    return ivString;
}

uint8_t* ScpCrypto::getIVPlain(){
    return iv;
}