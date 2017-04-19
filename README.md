# RoomLEDControl

RoomLEDControl is a personal project I started on several months ago. I've always been intrigued by addressable LED strips, and the fact that you can "program" the lights in real-time. So I bought a bunch of LED strips off of Alibaba, and got to work.

## The Set-Up

The project consists of ~~3~~ 5 major components:
1. [LED strips](#ws2801b-led-strips)
2. [Arduino Microcontroller](#arduino-uno-microcontroller)
3. [Node Server](#node-server)
4. [Alexa](#alexa-and-homeassistant.io)
5. [Home-Assistant.io Server](#alexa-and-homeassistant.io)

### WS2801b LED Strips

40 feet of WS2801B led strips are attached to the border of my ceiling, wrapping all the way around the room. Power and ground are hooked up at every wall intersection, with power, ground, and signal wires snaking behind furniture. Power is hooked up to an old PC power supply on the 5V rail, since 500+ LED's pull a good 20A or so of power - far too much for a simple wall-plug, and certainly too much for the Arduino itself.

### Arduino Uno Microcontroller

Signal wires (and ground, for a common ground) from the LED strips are hooked into 4 separate digital pins of an Arduino Uno sitting near the power supply. The Uno runs code found in this repo, under `/Room/`. This code has files for 15+ different lighting effects, and listens for commands on the serial port. The main code loop can be found in `/Room/src/aalight.ino`

### Node Server

I'm running Node with Express on my server machine for the Control Panel. It communicates with the Arduino via Serial over USB,
and receives commands from clients using the control panel via sockets.io.

### Alexa and HomeAssistant.io

The open-source home-assistant.io smart-home software is set up on the save server machine as the Node server. It emulates a Philips Hue bridge, which allows me to command the lights via natural-sounding commands, such as "~~Alexa~~ Computer, turn on the lights." or "~~Alexa~~ Computer, turn on party mode."

## Attribution

* [Bootstrap](http://getbootstrap.com/2.3.2/) - The web framework used for the front-end control panel
* [FastLed.io](https://github.com/FastLED/FastLED) - LED framework used for LED-control
* [atuline/FastLED-Demos](https://github.com/atuline/FastLED-Demos) - Control framework and template patterns for LEDs
* [Home-Assistant.io](https://home-assistant.io) - Smart-home software used for voice control with Alexa
