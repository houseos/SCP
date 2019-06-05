/*
secure-control-protocol
This is the source file for the ScpCrypto class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpCrypto.h"

ScpCrypto::ScpCrypto() {
}

String ScpCrypto::decrypt(char *enciphered, uint32_t lengthOfText,
                  uint8_t *key, uint8_t *iv)
{

  uint8_t deciphered[lengthOfText];
  memset(deciphered, 0, (lengthOfText + 1) * sizeof(uint8_t));
  // create aesDecryptor abject
  AES aesDecryptor(key, iv, AES::AES_MODE_128, AES::CIPHER_DECRYPT);

  // decrypt the message
  aesDecryptor.process((uint8_t *)enciphered, deciphered, lengthOfText);

  String output = "";
  
  uint8_t padlength = deciphered[lengthOfText-1];
  for (uint32_t i = 0; i < (lengthOfText - padlength); i++ ){
    output.concat((char)deciphered[i]);
  }
  return output;
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