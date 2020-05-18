/*
secure-control-protocol
This is the header file for the ScpDebug class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#ifndef ScpDebug_h
#define ScpDebug_h

#include "Arduino.h"

#define DEBUG 1

class ScpDebug
{

public:
    enum logClass_t
    {
        base = 1,
        crypto = 2,
        deviceId = 3,
        eeprom = 4,
        messageFactory = 5,
        password = 6
    };

    ScpDebug();

    void println(logClass_t logClass, String debugString);
};

#endif