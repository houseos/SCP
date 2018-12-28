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
    ScpDebug();

    void println(String debugString);

};


#endif