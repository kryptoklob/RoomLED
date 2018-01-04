#include "includes.h"

void setup() {
	// Serial, led, and mqtt setup
	init_serial();
	init_leds();
	init_mqtt();

  // Start default mode
  call_mode(led_mode, 1);
}

void loop() {
  if (!client.connected()) {
    Serial.println("Reconnecting MQTT...");
    reconnect_mqtt();
  }

  // Dynamic delay adjustment
  EVERY_N_MILLIS_I(global_timer, global_delay) {
    global_timer.setPeriod(global_delay);
    call_mode(led_mode, 0);
  }

  FastLED.show();
}
