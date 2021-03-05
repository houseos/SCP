/*
secure-control-protocol
This is the source file for the ScpDecode class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2020 Benjamin Schilling
*/

#include "ScpDecode.h"

ScpDecode::ScpDecode()
{
}

uint8_t *ScpDecode::base64DecodeToInt(String base64String)
{
    rbase64.decode(base64String);
    return reinterpret_cast<uint8_t *>(rbase64.result());
}

char *ScpDecode::base64DecodeToChar(String base64String)
{
    rbase64.decode(base64String);
    return rbase64.result();
}

String ScpDecode::base64Encode(uint8_t *payload)
{
    rbase64.encode(reinterpret_cast<const char *>(payload));
    return String(rbase64.result());
}