# secure-control-protocol - Arduino Library
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FbenjaminSchilling33%2Fsecure-control-protocol.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FbenjaminSchilling33%2Fsecure-control-protocol?ref=badge_shield)

The protocol specification can be found in `doc/`.

## Dependencies

The SCP Arduino library uses the rBase64 library and esp8266 core libraries.

They can be found in the repositories described in the library.json file.

## Installation

To install the library copy it into your Arduino Libraries directory.

## Integrating SCP

We made integrating SCP as easy as possible.

Several examples of successful integrations can be found in the [scp-devices](https://github.com/HouseOS/scp-devices) repository.

The following Arduino Sketch outlines how the library can be included.

```cpp
// First include the SCP library and create a SCP object
#include <SCP.h>
SCP scp;
//To register function pointers include the std::placeholders namespace
using namespace std::placeholders;

void setup(void)
{
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  Serial.begin(115200);
  Serial.println("");

// Initialize the SCP object
  scp.init("shutter-control");
// Register your control function.
  scp.registerControlFunction(std::bind(control, _1));
}

// In the control function define all supported actions, 
// each action is identified by a unique string
void control(String action){
  Serial.println("control: " + action);
  if(action == "up"){
    digitalWrite(D5, 1);
    digitalWrite(D6, 0);
  }
  if(action == "down"){
    digitalWrite(D6, 1);
    digitalWrite(D5, 0); 
  }
  if(action == "stop"){
    digitalWrite(D5, 0);
    digitalWrite(D6, 0); 
  }
}

void loop(void)
{
// In the loop call the handleClient 
// function to listen for HTTP requests
  scp.handleClient();
}
```

## License

SPDX-License-Identifier: GPL-3.0-or-later

The full version of the license can be found in LICENSE. 

[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FbenjaminSchilling33%2Fsecure-control-protocol.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2FbenjaminSchilling33%2Fsecure-control-protocol?ref=badge_large)

If you need a license for commercial use, please contact [Benjamin Schilling](mailto:schilling.benjamin@delusionsoftware.de). 

## Copyright
Copyright (C) 2018 - 2021 Benjamin Schilling
