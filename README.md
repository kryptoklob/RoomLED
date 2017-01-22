# RoomLEDControl

RoomLEDControl is a personal project I started on several months ago. I've always been intrigued by addressable LED strips, and the fact that you can "program" the lights in real-time. So I bought a bunch of LED strips off of Alibaba, and got to work.

## Magic Smoke & More

I didn't really know anything about microcontrollers or IOT-based systems at this time, so I mistakenly bought a RasPi to control the LED strips with. Unfortunately this didn't work, as these strips (WS28012b's) require precise timing to run correctly, which a RasPi can't do. I also accidentally burned up a RasPi from a bad power supply! So I purchased an Adrduino Uno to play around with the strips. After a lot of testing, I realized I could make this a larger project, and controllable from my phone.

## The Set-Up

The project consists of 3 major components: the physical LED strips themelves, the Ardruino Uno, and the RasPi.

### LED Strips - WS2801B

40 feet of WS2801B led strips are attached to the border of my ceiling, wrapping all the way around the room. Power and ground are hooked up at every wall intersection, with power, ground, and signal wires snaking behind furniture. Power is hooked up to an old PC power supply on the 5V rail, since 500+ LED's pull a good 20A or so of power - far too much for a simple wall-plug, and certainly too much for the Arduino itslef.

### Microcontroller - Arduino Uno

Signal wires (and ground, for a common ground) from the LED strips are hooked into 4 separate digital pins of an Arduino uno sitting near the power supply. The Uno runs code found in this repo, under /Room/. This code has files for 15+ different lighting effects, and listens for commands on the serial port. The main code loop can be found in /Room/src/aalight.ino

### Web Server / Control Panel - Raspberry Pi

A RasPi running a default Ubuntu image is attached to my switch via ethernet, and runs a Node web server hosting ditchfieldcaleb.com. It communicates with web clients via sockets.io for mode synchronization, and sends commands to the Uno via serial (over a physical USB cable).

## Attribution

I learned quite a lot while building this project. I had not worked with Node before this, and it was extremly helpful as it made socket programming pretty much pain-free. It certainly would have taken much longer without the help of other DIY-built libraries to assist with LED patterns and control schemes.

* [Bootstrap](http://getbootstrap.com/2.3.2/) - The web framework used for the front-end control panel
* [FastLed.io](https://github.com/FastLED/FastLED) - LED framework used for LED-control
* [atuline/FastLED-Demos](https://github.com/atuline/FastLED-Demos) - Control framework and template patterns for LEDs
