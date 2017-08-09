# RoomLEDControl

RoomLEDControl - control LED strips with cool effects, dynamic color pallets, dynamic effects, with event-driven or programmatic control.

## Set-Up

You will need:
1. [LED strips](#led-strips)
2. [Arduino Microcontroller](#arduino-microcontroller)
3. [Node Server](#node-server)
4. [Alexa](#alexa-and-homeassistant.io)
5. [Home-Assistant.io Server](#alexa-and-homeassistant.io)

### LED Strips

You can use any supported LED strip that works with the [FastLED.io](http://fastled.io) framework.
I use WS2812B for my projects.

Make sure you read up on how to properly power and ground the strips, or you will have issues.

### Arduino Uno Microcontroller

Connect the signal / data wires from the LED strips to PWM outputs on the Arduino.
If you want to control the effects from a computer, power the Arduino itself via USB cable to the computer.

### Node Server

The old command-and-control server is defunct. New version coming soon!

### Alexa and HomeAssistant.io

The old voice-control system is defunct. New version coming soon!

## Attribution

* [Bootstrap](http://getbootstrap.com/2.3.2/) - The web framework used for the front-end control panel
* [FastLed.io](https://github.com/FastLED/FastLED) - LED framework used for LED-control
* [atuline/FastLED-Demos](https://github.com/atuline/FastLED-Demos) - Control framework and template patterns for LEDs
* [Home-Assistant.io](https://home-assistant.io) - Smart-home software used for voice control with Alexa
