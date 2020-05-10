/*
secure-control-protocol
This is the source file for the ScpDebug class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpDebug.h"

ScpDebug::ScpDebug(bool enableLog){
    this->enableLog = enableLog;
}

void ScpDebug::println(logClass_t logClass, String debugString){
    if(this->enableLog){
        Serial.println(debugString);
    }
}