# RoomLEDControl

RoomLEDControl - control LED strips with cool effects, dynamic color pallets, dynamic effects, with event-driven or programmatic control.

## Set-Up

You will need:
1. [LED strips](#led-strips)
2. [Arduino Microcontroller](#arduino-microcontroller)
5. [Home-Assistant.io Server](#alexa-and-homeassistant.io)

### LED Strips

You can use any supported LED strip that works with the [FastLED.io](http://fastled.io) framework.
I use WS2812B for my projects.

Make sure you read up on how to properly power and ground the strips, or you will have issues.

### Arduino Uno Microcontroller

Connect the signal / data wires from the LED strips to PWM outputs on the Arduino.
