/*
secure-control-protocol
This is the central source file for the secure-control-protocol.

SPDX-License-Identifier: GPL-3.0-or-later

Copyright (C) 2018 Benjamin Schilling
*/

#include "SCP.h"

/**
 * Initialize the SCP library
 */
SCP::SCP()
{
    server = new ESP8266WebServer(80);
    EEPROM.begin(512);
}

void SCP::handleSecureControl()
{
    scpDebug.println(scpDebug.base, "  SCP.handleSecureControl: handleClient");

    String payload = server->arg("payload");
}

void SCP::handleDiscoverHello()
{
    scpDebug.println(scpDebug.base, "  SCP.handleDiscoverHello: Message: DiscoverHello");

    String payload = server->arg("payload");

    scpDebug.println(scpDebug.base, "  SCP.handleDiscoverHello:  Payload:" + payload);

    // handle discover-hello message
    if (payload.equals("discover-hello"))
    {

        String answer = messageFactory.createMessageDiscoverHello(deviceID, deviceType);
        server->send(200, "application/json", answer);

        scpDebug.println(scpDebug.base, "  SCP.handleDiscoverHello:  discover-response send: " + answer);
    }
    else
    {
    }

    scpDebug.println(scpDebug.base, "  SCP.handleDiscoverHello:  Message End: DiscoverHello");
}

void SCP::handleNotFound()
{
    scpDebug.println(scpDebug.base, "    Error: HandleNotFound");
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server->uri();
    message += "\nMethod: ";
    message += (server->method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server->args();
    message += "\n";
    for (uint8_t i = 0; i < server->args(); i++)
    {
        message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
    }
    server->send(404, "text/plain", message);
    scpDebug.println(scpDebug.base, "    Error End: HandleNotFound");
}

void SCP::handleClient() { server->handleClient(); }

void SCP::init(String deviceType, bool enableLog)
{

    this->deviceType = deviceType;

    if (password.isDefaultPasswordSetOnce() == false)
    {
        scpDebug.println(scpDebug.base, "  SCP.init: password not set, setting default password");
        password.setDefaultPassword();
    }

    if (!dID.isDeviceIDSet())
    {
        scpDebug.println(scpDebug.base, "  SCP.init: device ID not set, setting device ID");
        dID.setDeviceID();
    }
    deviceID = dID.readDeviceID();

    scpDebug.println(scpDebug.base, "  SCP.init: DeviceID: " + deviceID);

    server->on("/secure-control", std::bind(&SCP::handleSecureControl, this));
    server->on("/secure-control/discover-hello",
               std::bind(&SCP::handleDiscoverHello, this));
    server->onNotFound(std::bind(&SCP::handleNotFound, this));
    server->begin();

    scpDebug.println(scpDebug.base, "  SCP.init: HTTP server started");

    scpDebug.println(scpDebug.base, "  SCP.init: SCP initialized");
}

void SCP::registerControlUpFunction(std::function<void()> fun)
{
    controlUpFunction = fun;
}

void SCP::registerControlDownFunction(std::function<void()> fun)
{
    controlDownFunction = fun;
}

void SCP::registerControlStopFunction(std::function<void()> fun)
{
    controlStopFunction = fun;
}