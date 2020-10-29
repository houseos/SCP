/*
secure-control-protocol
This is the source file for the ScpDeviceName class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpDeviceName.h"

ScpDeviceName::ScpDeviceName()
{
}

void ScpDeviceName::writeDeviceName(String deviceName)
{
    scpDebug.println(scpDebug.password, "    ScpDeviceName.writeDeviceName: Setting " + deviceName + " as new device name");
    scpEeprom.setDeviceName(deviceName);
}

String ScpDeviceName::readDeviceName()
{

    return scpEeprom.getDeviceName();
}