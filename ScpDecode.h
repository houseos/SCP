/*
secure-control-protocol
This is the header file of the ScpDecode class

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2020 Benjamin Schilling
*/

#ifndef ScpDecode_h
#define ScpDecode_h

// Arduino Libraries
#include "Arduino.h"

// 3rd Party Libraries
#include <rBase64.h>

class ScpDecode
{

public:
    ScpDecode();

    uint8_t *base64Decode(String base64String);
    String base64Encode(uint8_t *payload);
};

#endif