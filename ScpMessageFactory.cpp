/*
secure-control-protocol
This is the source file for the ScpMessageFactory class.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "ScpMessageFactory.h"

ScpMessageFactory::ScpMessageFactory()
{
}

//Control Message
String ScpMessageFactory::createMessageControlUp(String deviceID, String status)
{
    String message = "{ \"type\" : \"control-up\", \"deviceId\" : " + deviceID +
                     ", \"status\" : " + status + " }";
    return message;
}
String ScpMessageFactory::createMessageControlDown(String deviceID, String status)
{
    String message = "{ \"type\" : \"control-down\", \"deviceId\" : " + deviceID +
                     ", \"status\" : " + status + " }";
    return message;
}
String ScpMessageFactory::createMessageControlStop(String deviceID, String status)
{
    String message = "{ \"type\" : \"control-stop\", \"deviceId\" : " + deviceID +
                     ", \"status\" : " + status + " }";
    return message;
}
String ScpMessageFactory::createMessageControlStatus(String deviceID, String status)
{
    String message = "{ \"type\" : \"control-status\", \"deviceId\" : " + deviceID +
                     ", \"status\" : " + status + " }";
    return message;
}

// Security Messages
String ScpMessageFactory::createMessageSecurityFetchIV(String deviceID, String ivString)
{
    String message = "{ \"type\" : \"security-fetch-iv\",  \"deviceId\" :\"" + deviceID + "\" ,  \"iv\" :\"" + ivString + "\"  }";
    return message;
}
String ScpMessageFactory::createMessageSecurityPwChange(String status)
{
    String message = "{ \"type\" : \"security-pw-change\", \"result\" : " + status +
                     " }";
    return message;
}
String ScpMessageFactory::createMessageSecurityWifiConfig()
{
    return "";
}
String ScpMessageFactory::createMessageSecurityResetToDefault(String status)
{
    String message = "{ \"type\" : \"security-reset-to-default\", \"result\" : " +
                     status + " }";
    return message;
}

//Discovery Messages
String ScpMessageFactory::createMessageDiscoverHello()
{
    return "";
}
