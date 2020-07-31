/*
secure-control-protocol
This is the source file for the ScpDebug class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpDebug.h"

ScpDebug::ScpDebug()
{
}

void ScpDebug::println(logClass_t logClass, String debugString)
{
#ifdef DEBUG
    Serial.println(debugString);
#endif
}

void ScpDebug::print(logClass_t logClass, String debugString)
{
#ifdef DEBUG
    Serial.print(debugString);
#endif
}