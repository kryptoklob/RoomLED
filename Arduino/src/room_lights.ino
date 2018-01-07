#include "includes.h"

void setup() {
	// Serial, led, and mqtt setup
	init_serial();
	init_leds();
	init_mqtt();

  // Start default mode
  call_mode(mode, 1);
}

void loop() {
  if (!client.connected()) {
    Serial.println(F("Reconnecting MQTT..."));
    reconnect_mqtt();
  }

  client.loop();

  // Dynamic delay adjustment
  EVERY_N_MILLIS_I(global_timer, global_delay) {
    global_timer.setPeriod(global_delay);
    call_mode(mode, 0);
  }

  FastLED.show();
}
