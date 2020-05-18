/*
secure-control-protocol
This is the source file for the ScpCrypto class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 - 2020 Benjamin Schilling
*/

#include "ScpCrypto.h"

ScpCrypto::ScpCrypto()
{
}

String ScpCrypto::decrypt(char *payload, size_t payloadLength,
                          uint8_t *key, uint8_t *nonce, uint8_t *mac)
{
  bool decryptionSucceeded = ChaCha20Poly1305::decrypt(payload, payloadLength, key, nullptr, sizeof 0, nonce, mac);

  if (decryptionSucceeded)
  {
    return String(payload);
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