/*
secure-control-protocol
This is the source file for the ScpCrypto class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 - 2020 Benjamin Schilling
*/

#include "ScpCrypto.h"

ScpCrypto::ScpCrypto()
{
  currentNvcn = 1;
}

String ScpCrypto::decrypt(String payload, int payloadLength,
                          String key, String nonce, String mac)
{
  ScpDecode decoder();
  // decode payload
  rbase64.decode(payload);
  char* decodedPayload = rbase64.result();
  char correctPayload[payloadLength + 1];
  memset(correctPayload, 0, payloadLength + 1);
  memcpy(correctPayload, decodedPayload, payloadLength);
  for(int i = 0; i < payloadLength; i++){
    Serial.print("Element Payload ");
    Serial.print(i, DEC);
    Serial.print(": ");
    Serial.println(correctPayload[i], HEX);
  }

  // decode mac
  rbase64.decode(mac);
  char* decodedMac = rbase64.result();
  char correctMac[MAC_LENGTH + 1];
  memset(correctMac, 0, MAC_LENGTH + 1);
  memcpy(correctMac, decodedMac, MAC_LENGTH);
  for(int i = 0; i < MAC_LENGTH; i++){
    Serial.print("Element Mac ");
    Serial.print(i, DEC);
    Serial.print(": ");
    Serial.println(correctMac[i], HEX);
  }
  
  // key
  unsigned char correctKey[KEY_LENGTH +1];
  memset(correctKey, 0, KEY_LENGTH + 1);
  key.getBytes(correctKey, KEY_LENGTH + 1);
 

  // decode nonce
  rbase64.decode(nonce);
  char* decodedNonce = rbase64.result();
  char correctNonce[NONCE_LENGTH +1];
  memset(correctNonce, 0, NONCE_LENGTH + 1);
  memcpy(correctNonce, decodedNonce, NONCE_LENGTH);

  bool decryptionSucceeded = ChaCha20Poly1305::decrypt(correctPayload, payloadLength, correctKey, nullptr, sizeof 0, correctNonce, correctMac);

  if (decryptionSucceeded)
  {
    return String(correctPayload);
  }
  else
  {
    return "";
  }
}

String ScpCrypto::generateHMAC(String payload, uint8_t *key, size_t keyLength)
{
  return SHA512::hmacCT(payload.begin(), key, keyLength, HMAC_LENGTH);
}

  String ScpCrypto::getNVCN(){
    currentNvcn++;
    return String(currentNvcn);
  }

  bool ScpCrypto::checkNVCN(String nvcn){
    if(currentNvcn == nvcn.toInt()){
      return true;
    }
    return false;
  }